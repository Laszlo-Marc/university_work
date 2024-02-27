USE [Psychology Center]
GO
--add table
CREATE PROCEDURE AddTableLecturer
AS
	CREATE TABLE Lecturer(LID INT NOT NULL,LName VARCHAR(50),CSid INT)
GO
--remove table
CREATE PROCEDURE DropTableLecturer
AS 
	DROP TABLE Lecturer
GO
--modify column type
CREATE PROCEDURE ModifyCoursePriceColumn
AS 
	ALTER TABLE COURSE
	ALTER COLUMN Price VARCHAR(50)
GO
--revert column type
CREATE PROCEDURE RevertCoursePriceColumn
AS 
	ALTER TABLE COURSE
	ALTER COLUMN Price INT
GO
--add column
CREATE PROCEDURE AddColumnToPsychologist
AS
	ALTER TABLE PSYCHOLOGIST
	ADD Experience INT 
GO
--remove column
CREATE PROCEDURE RemoveColumnFromPsychologist
AS
	ALTER TABLE PSYCHOLOGIST
	DROP COLUMN Experience
GO
--add a default constraint
CREATE PROCEDURE AddDefaultConstraintTSPrice
AS
BEGIN
    ALTER TABLE THERAPYSESSION
    ADD CONSTRAINT DF_TS_PRICE DEFAULT 150 FOR Price; 
END;
GO
--remove default constraint
CREATE PROCEDURE RemoveDefaultConstraintTSPrice
AS
BEGIN
    ALTER TABLE THERAPYSESSION
    DROP CONSTRAINT DF_TS_PRICE; 
END;
GO
--add a primary key
CREATE PROCEDURE AddPrimaryKeyLID
AS
BEGIN
	
    ALTER TABLE Lecturer 
	ADD CONSTRAINT PK_LecturerID PRIMARY KEY (LID); 
END;
GO
--remove primary key
CREATE PROCEDURE RemovePrimaryKeyLID
AS
BEGIN
    ALTER TABLE Lecturer
    DROP CONSTRAINT PK_LecturerID;
END;
GO
--add candidate key
CREATE PROCEDURE AddCandidateKeyFullName
AS
BEGIN
    ALTER TABLE CLIENT
    ADD CONSTRAINT AK_Client_FullName UNIQUE (FName, LName); 
END;
GO
-- remove candidate key
CREATE PROCEDURE RemoveCandidateKeyFullName
AS
BEGIN
    ALTER TABLE CLIENT
    DROP CONSTRAINT AK_Client_FullName; 
END;
GO
--add foreign key
CREATE PROCEDURE AddForeignKeyCid
AS
BEGIN
    ALTER TABLE Lecturer
    ADD CONSTRAINT FK_Lecturer_CourseID FOREIGN KEY (CSid) REFERENCES COURSE(CSid); 
END;
GO
--remove foreign key
CREATE PROCEDURE RemoveForeignKeyCid
AS
BEGIN
    ALTER TABLE Lecturer
    DROP CONSTRAINT FK_Lecturer_CourseID; 
END;
GO
CREATE OR ALTER PROCEDURE FinalVersion
AS
BEGIN
	PRINT 'This procedure does nothing';
END;
GO
CREATE OR ALTER PROCEDURE BaseVersion
AS 
BEGIN
	PRINT 'This procedure does nothing';
END;
GO
CREATE TABLE ProceduresTable(uspUP VARCHAR(100),uspDown VARCHAR(100),targetVersion INT)
CREATE TABLE crtVersion(crtVersion INT PRIMARY kEY)
INSERT INTO crtVersion(crtVersion) VALUES(0)
INSERT INTO ProceduresTable(uspUP,uspDown,targetVersion) VALUES('BaseVersion','BaseVersion',0),
('ModifyCoursePriceColumn','RevertCoursePriceColumn',1),
('AddColumnToPsychologist','RemoveColumnFromPsychologist',2),
('AddTableLecturer','DropTableLecturer',3),
('AddForeignKeyCid','RemoveForeignKeyCid',4),
('AddDefaultConstraintTSPrice','RemoveDefaultConstraintTSPrice',5),
('AddPrimaryKeyLID', 'RemovePrimaryKeyLID',6),
('AddCandidateKeyFullName','RemoveCandidateKeyFullName',7),('FinalVersion','FinalVersion',8);
GO



CREATE OR ALTER PROCEDURE updateSchemaToVersion(@targetVersion INT)
AS 
BEGIN
	DECLARE @CurrentVersion INT;
	DECLARE @storedProcedure VARCHAR(100)
	SELECT @CurrentVersion=crtVersion FROM crtVersion;

	WHILE @CurrentVersion>@targetVersion
	BEGIN
		DECLARE @downProcedure VARCHAR(50);

		SELECT @downProcedure=uspDown
		FROM ProceduresTable
		WHERE targetVersion=@CurrentVersion

		IF @downProcedure IS NOT NULL
		BEGIN
			EXEC(@downProcedure);
			PRINT 'Executed ' + @downProcedure;
		END

		UPDATE crtVersion SET crtVersion=@CurrentVersion-1;
		SET @CurrentVersion=@CurrentVersion-1;

		
	END

	
	
	
	--IF @CurrentVersion<@targetVersion
	--BEGIN
		WHILE @CurrentVersion<@targetVersion
		BEGIN
				DECLARE @upProcedure VARCHAR(50);

				SELECT @upProcedure=uspUp
				FROM ProceduresTable
				WHERE targetVersion=@CurrentVersion;

				IF @upProcedure IS NOT NULL
				BEGIN
					EXEC(@upProcedure)
					PRINT 'Executed '+@upProcedure;
				END

				UPDATE crtVersion SET crtVersion=@CurrentVersion+1;
				SET @CurrentVersion=@CurrentVersion+1;
				
		END
		--END
	--ELSE
	--BEGIN
		IF @currentVersion=@targetVersion
		BEGIN
			
			SELECT @upProcedure=uspUP
			FROM ProceduresTable
			WHERE targetVersion=@currentVersion
		END
		IF @upProcedure IS NOT NULL
		BEGIN
			EXEC (@upProcedure);
			PRINT 'Executed ' + @upProcedure;
		
		END
	--END
		
	PRINT 'Database updated to version ' + CAST(@targetVersion AS VARCHAR(10));
END;
GO
EXEC updateSchemaToVersion @targetVersion=0;
SELECT* FROM PSYCHOLOGIST
SELECT* FROM COURSE
SELECT* FROM THERAPYSESSION
Select* from CLIENT

SELECT* FROM ProceduresTable
SELECT* FROM crtVersion


drop procedure RemoveCandidateKeyFullName
drop procedure RemoveColumnFromPsychologist
drop procedure RemoveDefaultConstraintTSPrice
drop procedure RemoveForeignKeyCid
drop procedure RemovePrimaryKeyLID
drop procedure RevertCoursePriceColumn
drop procedure ModifyCoursePriceColumn
drop procedure DropTableLecturer
drop procedure AddCandidateKeyFullName
drop procedure AddColumnToPsychologist
drop procedure AddDefaultConstraintExperience
drop procedure AddForeignKeyCid
drop procedure AddPrimaryKeyLID
drop procedure AddTableLecturer
drop procedure updateSchemaToVersion

Delete from crtVersion

SELECT O.name,C.*
FROM sys.objects O 
INNER JOIN sys.columns C on O.object_id=C.object_id
WHERE type='U'