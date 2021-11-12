-- скалярная функция

CREATE FUNCTION [dbo].[getDateDiff] 
(
		@date_contract date, 
		@time_contract date
)
RETURNS int
AS
BEGIN
	RETURN CONVERT(INT, DATEDIFF(day, @date_contract, @time_contract)/356.2425)
END

SELECT dbo.contrAgentsSet.fullname_contr, COUNT(dbo.contractsSet.id_contract) AS Contracts, dbo.getDateDiff(date_contract, time_contract) AS time_contract
FROM   dbo.contractsSet, dbo.contrAgentsSet
WHERE  dbo.contractsSet.contragents_Id_contr = dbo.contrAgentsSet.Id_contr AND dbo.contrAgentsSet.type_contr = 1
GROUP BY dbo.contrAgentsSet.fullname_contr,  dbo.getDateDiff(date_contract, time_contract)
HAVING (dbo.contrAgentsSet.fullname_contr IS NOT NULL) AND (dbo.getDateDiff(date_contract, time_contract) > 1)

-- табличная функция

CREATE FUNCTION [dbo].[get_agent](@id_agent int = 1)
RETURNS TABLE 
AS
RETURN 
(
    SELECT DISTINCT compname_contr
                       FROM      dbo.contrAgentsSet, dbo.contractsSet
                       WHERE   dbo.contractsSet.contragents_Id_contr = @id_agent AND dbo.contractsSet.contragents_Id_contr = Id_contr AND compname_contr IS NOT NULL
)

SELECT DISTINCT dbo.contractsSet.id_contract, dbo.contractsSet.time_contract, dbo.contractsSet.date_contract, dbo.contractsSet.currency_contract, dbo.contractsSet.objects_Id_obj, dbo.contractsSet.subjects_Id_subj,
                      (SELECT * FROM dbo.get_agent(2))
FROM     dbo.contractsSet,
                      (SELECT Id_contr, type_contr, compname_contr, fullname_contr, itn_contr, msrn_contr, document_contr, bic_contr, chaccount_contr, address_contr, phnumber_contr
                       FROM      dbo.contrAgentsSet AS contrAgentsSet_1, dbo.contractsSet
                       WHERE   (dbo.contractsSet.contragents_Id_contr = Id_contr) AND (type_contr = 0)) AS Nedeed_agents
WHERE  (dbo.contractsSet.date_contract =
                      (SELECT CAST(GETDATE() AS DATE) AS Today) AND dbo.contractsSet.contragents_Id_contr = Id_contr)