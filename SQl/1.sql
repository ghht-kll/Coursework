
-- --------------------------------------------------
-- Entity Designer DDL Script for SQL Server 2005, 2008, 2012 and Azure
-- --------------------------------------------------
-- 
-- 
-- --------------------------------------------------

SET QUOTED_IDENTIFIER OFF;
GO
USE [ContractDB];
GO
IF SCHEMA_ID(N'dbo') IS NULL EXECUTE(N'CREATE SCHEMA [dbo]');
GO

-- --------------------------------------------------
-- Dropping existing FOREIGN KEY constraints
-- --------------------------------------------------


-- --------------------------------------------------
-- Dropping existing tables
-- --------------------------------------------------


-- --------------------------------------------------
-- Creating all tables
-- --------------------------------------------------

-- Creating table 'contrAgentsSet' Контрагенты
CREATE TABLE [dbo].[contrAgentsSet] (
    [Id_contr] int IDENTITY(1,1) NOT NULL,
    [type_contr] bit  NOT NULL,
    [compname_contr] nvarchar(max)  NULL,
    [fullname_contr] nvarchar(max)  NULL,
    [itn_contr] nchar(12)  NOT NULL,
    [msrn_contr] nchar(13)  NOT NULL,
    [document_contr] nchar(10)  NULL,
    [bic_contr] nchar(9)  NOT NULL,
    [chaccount_contr] nchar(20)  NOT NULL,
    [address_contr] nvarchar(max)  NULL,
    [phnumber_contr] nchar(11)  NULL
);
GO

-- Creating table 'documentsSet' Документы сделки
CREATE TABLE [dbo].[documentsSet] (
    [Id_doc] int IDENTITY(1,1) NOT NULL,
    [name_doc] nvarchar(max)  NOT NULL,
    [address_doc] nvarchar(max)  NOT NULL,
    [contracts_id_contract] int  NOT NULL
);
GO

-- Creating table 'contractsSet' Договоры
CREATE TABLE [dbo].[contractsSet] (
    [id_contract] int IDENTITY(1,1) NOT NULL,
    [time_contract] time  NOT NULL,
    [date_contract] datetime  NOT NULL,
    [currency_contract] nvarchar(max)  NOT NULL,
    [contragents_Id_contr] int  NOT NULL,
    [objects_Id_obj] int  NOT NULL,
    [subjects_Id_subj] int  NOT NULL
);
GO

-- Creating table 'notesSet' Записи о сделке
CREATE TABLE [dbo].[notesSet] (
    [Id_note] int IDENTITY(1,1) NOT NULL,
    [note] nvarchar(max)  NOT NULL,
    [contracts_id_contract] int  NOT NULL
);
GO

-- Creating table 'objectsSet' Объекты договора
CREATE TABLE [dbo].[objectsSet] (
    [Id_obj] int IDENTITY(1,1) NOT NULL,
    [name_obj] nvarchar(max)  NOT NULL
);
GO

-- Creating table 'subjectsSet' Субъекты договора
CREATE TABLE [dbo].[subjectsSet] (
    [Id_subj] int IDENTITY(1,1) NOT NULL,
    [name_obj] nvarchar(max)  NOT NULL
);
GO

-- Creating table 'logsSet' Логи БД
CREATE TABLE [dbo].[logsSet] (
    [Id_log] int IDENTITY(1,1) NOT NULL,
    [description_log] nvarchar(max)  NOT NULL
);
GO


-- --------------------------------------------------
-- Creating all PRIMARY KEY constraints
-- --------------------------------------------------

-- Creating primary key on [Id_contr] in table 'contrAgentsSet'
ALTER TABLE [dbo].[contrAgentsSet]
ADD CONSTRAINT [PK_contrAgentsSet]
    PRIMARY KEY CLUSTERED ([Id_contr] ASC);
GO

-- Creating primary key on [Id_doc] in table 'documentsSet'
ALTER TABLE [dbo].[documentsSet]
ADD CONSTRAINT [PK_documentsSet]
    PRIMARY KEY CLUSTERED ([Id_doc] ASC);
GO

-- Creating primary key on [id_contract] in table 'contractsSet'
ALTER TABLE [dbo].[contractsSet]
ADD CONSTRAINT [PK_contractsSet]
    PRIMARY KEY CLUSTERED ([id_contract] ASC);
GO

-- Creating primary key on [Id_note] in table 'notesSet'
ALTER TABLE [dbo].[notesSet]
ADD CONSTRAINT [PK_notesSet]
    PRIMARY KEY CLUSTERED ([Id_note] ASC);
GO

-- Creating primary key on [Id_obj] in table 'objectsSet'
ALTER TABLE [dbo].[objectsSet]
ADD CONSTRAINT [PK_objectsSet]
    PRIMARY KEY CLUSTERED ([Id_obj] ASC);
GO

-- Creating primary key on [Id_subj] in table 'subjectsSet'
ALTER TABLE [dbo].[subjectsSet]
ADD CONSTRAINT [PK_subjectsSet]
    PRIMARY KEY CLUSTERED ([Id_subj] ASC);
GO

-- Creating primary key on [Id_log] in table 'logsSet'
ALTER TABLE [dbo].[logsSet]
ADD CONSTRAINT [PK_logsSet]
    PRIMARY KEY CLUSTERED ([Id_log] ASC);
GO

-- --------------------------------------------------
-- Creating all FOREIGN KEY constraints
-- --------------------------------------------------

-- Creating foreign key on [contragents_Id_contr] in table 'contractsSet'
ALTER TABLE [dbo].[contractsSet]
ADD CONSTRAINT [FK_contragentscontracts]
    FOREIGN KEY ([contragents_Id_contr])
    REFERENCES [dbo].[contrAgentsSet]
        ([Id_contr])
    ON DELETE NO ACTION ON UPDATE NO ACTION;
GO

-- Creating non-clustered index for FOREIGN KEY 'FK_contragentscontracts'
CREATE INDEX [IX_FK_contragentscontracts]
ON [dbo].[contractsSet]
    ([contragents_Id_contr]);
GO

-- Creating foreign key on [objects_Id_obj] in table 'contractsSet'
ALTER TABLE [dbo].[contractsSet]
ADD CONSTRAINT [FK_objectscontracts]
    FOREIGN KEY ([objects_Id_obj])
    REFERENCES [dbo].[objectsSet]
        ([Id_obj])
    ON DELETE NO ACTION ON UPDATE NO ACTION;
GO

-- Creating non-clustered index for FOREIGN KEY 'FK_objectscontracts'
CREATE INDEX [IX_FK_objectscontracts]
ON [dbo].[contractsSet]
    ([objects_Id_obj]);
GO

-- Creating foreign key on [subjects_Id_subj] in table 'contractsSet'
ALTER TABLE [dbo].[contractsSet]
ADD CONSTRAINT [FK_subjectscontracts]
    FOREIGN KEY ([subjects_Id_subj])
    REFERENCES [dbo].[subjectsSet]
        ([Id_subj])
    ON DELETE NO ACTION ON UPDATE NO ACTION;
GO

-- Creating non-clustered index for FOREIGN KEY 'FK_subjectscontracts'
CREATE INDEX [IX_FK_subjectscontracts]
ON [dbo].[contractsSet]
    ([subjects_Id_subj]);
GO

-- Creating foreign key on [contracts_id_contract] in table 'notesSet'
ALTER TABLE [dbo].[notesSet]
ADD CONSTRAINT [FK_contractsnotes]
    FOREIGN KEY ([contracts_id_contract])
    REFERENCES [dbo].[contractsSet]
        ([id_contract])
    ON DELETE NO ACTION ON UPDATE NO ACTION;
GO

-- Creating non-clustered index for FOREIGN KEY 'FK_contractsnotes'
CREATE INDEX [IX_FK_contractsnotes]
ON [dbo].[notesSet]
    ([contracts_id_contract]);
GO

-- Creating foreign key on [contracts_id_contract] in table 'documentsSet'
ALTER TABLE [dbo].[documentsSet]
ADD CONSTRAINT [FK_contractsdocuments]
    FOREIGN KEY ([contracts_id_contract])
    REFERENCES [dbo].[contractsSet]
        ([id_contract])
    ON DELETE NO ACTION ON UPDATE NO ACTION;
GO

-- Creating non-clustered index for FOREIGN KEY 'FK_contractsdocuments'


-- --------------------------------------------------
-- Script has ended
-- --------------------------------------------------