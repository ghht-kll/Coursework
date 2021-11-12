CREATE INDEX IX_FK_objectscontracts
ON dbo.contractsSet
    (objects_Id_obj);
GO

CREATE INDEX IX_FK_subjectscontracts
ON dbo.contractsSet
    (subjects_Id_subj);
GO

CREATE INDEX IX_FK_contractsnotes
ON dbo.notesSet
    (contracts_id_contract);
GO

CREATE INDEX IX_FK_contractsdocuments
ON dbo.documentsSet
    (contracts_id_contract);
GO