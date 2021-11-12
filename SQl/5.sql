CREATE PROCEDURE add_contragent
	@business_type bit, -- 0 - юр лицо, 1 - физ лицо
	@type bit = 0, -- 0 - контрагент, 1 - агент
	@name nvarchar(max),
	@itn nchar(12),
	@msrn nchar(13) = NULL,
	@document nchar(10) = NULL,
	@bic nchar(9),
	@chaccount nchar(20), 
	@address nvarchar(max) = NULL, 
	@phnumber nchar(10) = NULL

AS
IF NOT EXISTS ( SELECT 1 FROM dbo.contrAgentsSet WHERE fullname_contr = @name OR compname_contr = @name OR itn_contr = @itn)
	BEGIN
		IF (@business_type = 1)
		BEGIN
			INSERT INTO dbo.contrAgentsSet (type_contr, fullname_contr, itn_contr, document_contr, bic_contr, chaccount_contr, address_contr, phnumber_contr) 
			VALUES (@type, @name, @itn, @document, @bic, @chaccount, @address, @phnumber)
			RETURN 0
		END;
		ELSE
		BEGIN
			INSERT INTO dbo.contrAgentsSet (type_contr, compname_contr, itn_contr, msrn_contr, bic_contr, chaccount_contr, address_contr, phnumber_contr) 
			VALUES (@type, @name, @itn, @msrn, @bic, @chaccount, @address, @phnumber)
			RETURN 0
		END;
	SELECT ('Запись добавлена!')
	END
ELSE 
	SELECT 'Найдено совпадение данных! Проверьте уникальность названия, ФИО или ИНН.'



CREATE PROCEDURE upd_contragent 
	@business_type bit,
	@id_contragent int,
	@type_contr bit,
	@name nvarchar(max),
	@itn nchar(12),
	@msrn_document nchar(10),
	@bic nchar(9),
	@chaccount nchar(20), 
	@address nvarchar(max) = NULL, 
	@phnumber nchar(10) = NULL
AS
IF EXISTS (SELECT 1 FROM dbo.contrAgentsSet WHERE id_contr = @id_contragent) 
	BEGIN
		IF (@business_type = 0)
			UPDATE dbo.contrAgentsSet
			SET 
			type_contr = @type_contr,
			compname_contr = @name,
			itn_contr = @itn,
			msrn_contr = @msrn_document,
			bic_contr = @bic,
			chaccount_contr = @chaccount, 
			address_contr = @address, 
			phnumber_contr = @phnumber
			WHERE id_contr = @id_contragent
		ELSE
			UPDATE dbo.contrAgentsSet
			SET 
			type_contr = @type_contr,
			fullname_contr = @name,
			itn_contr = @itn,
			document_contr = @msrn_document,
			bic_contr = @bic,
			chaccount_contr = @chaccount, 
			address_contr = @address, 
			phnumber_contr = @phnumber
			WHERE id_contr = @id_contragent
	END
SELECT ('Запись обновлена!')
ELSE
	SELECT ('Такой записи не существует!')



CREATE PROCEDURE del_contragent 	
	@id_contragent int
	
AS
IF EXISTS (SELECT 1 FROM dbo.contrAgentsSet WHERE id_contr = @id_contragent) 
	BEGIN
		DELETE FROM dbo.contrAgentsSet WHERE id_contr = @id_contragent
		SELECT ('Запись удалена!')
	END
ELSE
	SELECT ('Такой записи не существует!')



