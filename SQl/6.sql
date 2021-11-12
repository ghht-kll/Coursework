CREATE PROCEDURE add_document 
	@id_contract int,
	@name_doc nvarchar(max),
	@address nvarchar(max),
	@name_obj nvarchar(max)=NULL,
	@name_sbj nvarchar(max)=NULL	
AS
BEGIN TRY
	BEGIN TRANSACTION
		INSERT dbo.objectsSet VALUES (@name_obj)
		INSERT dbo.subjectsSet VALUES (@name_sbj)    
		INSERT dbo.documentsSet VALUES (@name_doc, @address, @id_contract)
		SELECT ('Документ сохранен!')
	COMMIT TRANSACTION
END TRY
BEGIN CATCH
	ROLLBACK TRANSACTION
	SELECT ('Укажите объект и субъект договора!')
END CATCH
GO