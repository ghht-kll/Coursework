CREATE TRIGGER dbo.contracts_added 
   ON  dbo.contractsSet AFTER INSERT 
   AS 
BEGIN
	DECLARE @new_contr NVARCHAR(max)
	SELECT @new_contr = (SELECT  id_contract FROM INSERTED);
	INSERT INTO dbo.logsSet VALUES ('Добавлен новый договор № ' + @new_contr + ' ' + CONVERT(NVARCHAR(max),getdate()));
END

CREATE TRIGGER dbo.contracts_updated 
   ON  dbo.contractsSet AFTER Delete 
   AS 
BEGIN
	DECLARE @upd_contr NVARCHAR(max)
	SELECT @upd_contr = (SELECT  id_contract FROM INSERTED);
	INSERT INTO dbo.logsSet VALUES ('Изменен договор № ' + @upd_contr + ' ' + CONVERT(NVARCHAR(max),getdate()));
END


CREATE TRIGGER dbo.contracts_deleted 
   ON  dbo.contractsSet AFTER DELETE 
   AS 
BEGIN
	DECLARE @del_contr NVARCHAR(max)
	SELECT @del_contr = (SELECT  id_contract FROM DELETED);
	INSERT INTO dbo.logsSet VALUES ('Удален договор № ' + @del_contr + ' ' + CONVERT(NVARCHAR(max),getdate()));
END
