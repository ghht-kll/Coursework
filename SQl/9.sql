CREATE ROLE [manager] 
CREATE ROLE [admin] 
GRANT SELECT, INSERT, UPDATE, DELETE, EXECUTE ON DATABASE :: [Contract_test] TO [manager]
GRANT SELECT ON dbo.logsSet TO [manager]

CREATE LOGIN [Romanov_v] WITH PASSWORD=N'ADMIN'
CREATE USER [Романов Владимир Артёмович] FOR LOGIN [Romanov_v]
EXEC sp_addrolemember N'db_datawriter', N'admin'

CREATE LOGIN [Volkova_e] WITH PASSWORD=N'MANAGER'
CREATE USER [Волкова Екатерина Львовна] FOR LOGIN [Volkova_e]
EXEC sp_addrolemember N'db_datawriter', N'manager'