CREATE PROCEDURE upd_contract
	@id_contragent int,
	@currency nvarchar(max),
	@id int = 0
	
AS
BEGIN
	SET NOCOUNT ON;
	SET @id = (SELECT MIN(id_contract) FROM dbo.contractsSet WHERE  contragents_Id_contr = @id_contragent)
	DECLARE upd_cursor CURSOR
	FOR SELECT * FROM dbo.contractsSet WHERE contragents_Id_contr = @id_contragent
	OPEN upd_cursor;

	FETCH NEXT FROM upd_cursor

	WHILE @@FETCH_STATUS = 0
	  BEGIN
		  UPDATE dbo.contractsSet
		  SET    currency_contract = @currency
		  WHERE  CURRENT OF upd_cursor;

		  SELECT @id = @id + 1;

		  FETCH NEXT FROM upd_cursor
	  END;

	CLOSE upd_cursor;

	DEALLOCATE upd_cursor;
END