-- 2 задание

-- a. вывести инн агентов и контрагентов, с которыми срок договора заканчивается не раньше 2005-05-05

SELECT dbo.contrAgentsSet.itn_contr AS ITN, SUM(CASE WHEN dbo.contractsSet.time_contract < '2005-05-05' THEN 1 ELSE 0 END) AS Contracts
FROM     dbo.contractsSet INNER JOIN
                  dbo.contrAgentsSet ON dbo.contractsSet.contragents_Id_contr = dbo.contrAgentsSet.Id_contr
WHERE dbo.contractsSet.time_contract < '2005-05-05'
GROUP BY dbo.contrAgentsSet.itn_contr

-- b. таблица договоров с контрагентами(юр.лицами)

CREATE VIEW dbo.view_entity_contragents
AS
SELECT dbo.contractsSet.id_contract AS [Contract Number], dbo.contrAgentsSet.compname_contr AS Contragent, dbo.contrAgentsSet.itn_contr AS ITN, dbo.contrAgentsSet.msrn_contr AS MSRN, dbo.contrAgentsSet.bic_contr AS BIC, 
                  dbo.contrAgentsSet.chaccount_contr AS [Checking account], dbo.contrAgentsSet.address_contr AS Address, dbo.contrAgentsSet.phnumber_contr AS [Phone number]
FROM     dbo.contractsSet INNER JOIN
                  dbo.contrAgentsSet ON dbo.contractsSet.contragents_Id_contr = dbo.contrAgentsSet.Id_contr INNER JOIN
                  dbo.objectsSet ON dbo.contractsSet.objects_Id_obj = dbo.objectsSet.Id_obj INNER JOIN
                  dbo.subjectsSet ON dbo.contractsSet.subjects_Id_subj = dbo.subjectsSet.Id_subj
WHERE  (dbo.contrAgentsSet.compname_contr IS NOT NULL) AND (dbo.contrAgentsSet.type_contr = 0)

-- c. Заключенные сегодня договора с агентом (юр. лицом)

SELECT DISTINCT dbo.contractsSet.id_contract, dbo.contractsSet.time_contract, dbo.contractsSet.date_contract, dbo.contractsSet.currency_contract, dbo.contractsSet.objects_Id_obj, dbo.contractsSet.subjects_Id_subj,
                      (SELECT DISTINCT compname_contr
                       FROM      dbo.contrAgentsSet
                       WHERE   dbo.contractsSet.contragents_Id_contr = 1 AND dbo.contractsSet.contragents_Id_contr = Id_contr
                        )AS Agent
FROM     dbo.contractsSet,
                      (SELECT Id_contr, type_contr, compname_contr, fullname_contr, itn_contr, msrn_contr, document_contr, bic_contr, chaccount_contr, address_contr, phnumber_contr
                       FROM      dbo.contrAgentsSet AS contrAgentsSet_1, dbo.contractsSet
                       WHERE   (dbo.contractsSet.contragents_Id_contr = Id_contr) AND (type_contr = 0)) AS Nedeed_agents
WHERE  (dbo.contractsSet.date_contract =
                      (SELECT CAST(GETDATE() AS DATE) AS Today) AND dbo.contractsSet.contragents_Id_contr = Id_contr )

-- d. Вывести количество договоров каждого контрагента (физ. лица), заключенные на срок более года

SELECT dbo.contrAgentsSet.fullname_contr, COUNT(dbo.contractsSet.id_contract) AS contracts, DATEDIFF ( year , date_contract , time_contract ) AS time_contract
FROM   dbo.contractsSet, dbo.contrAgentsSet
WHERE  dbo.contractsSet.contragents_Id_contr = dbo.contrAgentsSet.Id_contr AND dbo.contrAgentsSet.type_contr = 0
GROUP BY dbo.contrAgentsSet.fullname_contr, DATEDIFF ( YEAR , date_contract , time_contract )
HAVING (dbo.contrAgentsSet.fullname_contr IS NOT NULL) AND DATEDIFF ( year , date_contract , time_contract ) > 1


-- e. Вывести информацию по договорам с агентами (физ. лицами)

SELECT id_contract, time_contract, date_contract, currency_contract, contragents_Id_contr
FROM     dbo.contractsSet
WHERE  (contragents_Id_contr = ANY
                      (SELECT Id_contr
                       FROM      dbo.contrAgentsSet
                       WHERE   (type_contr = 1) AND (fullname_contr IS NOT NULL)))