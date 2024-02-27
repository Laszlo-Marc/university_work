USE [Psychology Center]
GO

CREATE OR ALTER PROCEDURE  runTest
   @testName VARCHAR(50)
AS
BEGIN
	
	DECLARE @tableName VARCHAR(50),@noOfRows INT,@tableID INT,
	@viewName VARCHAR(50),@viewID INT,@testRunID INT,@command VARCHAR(300)
    DECLARE @StartTimeInserts DATETIME, @EndTimeInserts DATETIME, @startViews DATETIME, @endViews DATETIME,@STARTALL DATETIME,@ENDALL DATETIME
	
	DECLARE @testID INT
	SET @testID=(SELECT T.TestID FROM Tests T WHERE T.Name=@testName)
	INSERT INTO TestRuns(Description) Values (@testName)
	SET @testRunID=CONVERT(INT,(SELECT last_value FROM sys.identity_columns WHERE name='TestRunId'))
    
	DECLARE TABLECURSOR CURSOR SCROLL FOR
	SELECT T.TableID,T.Name,TT.NoOfRows
	FROM TestTables TT
	INNER JOIN Tables T ON T.TableID=TT.TableID
	WHERE TT.TestID=@testID
	ORDER BY TT.Position

	DECLARE VIEWCURSOR CURSOR SCROLL FOR
	SELECT  V.ViewID,V.Name
	FROM Views V
	INNER JOIN TestViews TV ON TV.ViewID=V.ViewID
	WHERE TV.TestID=@testID
	
	OPEN TABLECURSOR
	FETCH FIRST FROM TABLECURSOR
	INTO @tableID,@tableName,@noOfRows

	SET @STARTALL=SYSDATETIME()
	WHILE @@FETCH_STATUS=0
	BEGIN
		SET @StartTimeInserts=SYSDATETIME()
		SET @command='insertIntoTable'+char(39)+@tableName+char(39)+','+CONVERT(VARCHAR(30),@noOfRows)
		EXEC (@command)
		SET @EndTimeInserts=SYSDATETIME()
		INSERT INTO TestRunTables VALUES(@testRunID,@tableID,@StartTimeInserts,@EndTimeInserts)
		PRINT @testRunID+' '+ @tableID+' '+@StartTimeInserts+' '+@EndTimeInserts
		FETCH NEXT FROM TABLECURSOR INTO @tableID,@tableName,@noOfRows
	END
	CLOSE TABLECURSOR

	OPEN VIEWCURSOR
	FETCH FROM VIEWCURSOR INTO @viewID,@viewName
	WHILE @@FETCH_STATUS=0
	BEGIN
		SET @StartTimeInserts=SYSDATETIME()
		DECLARE @viewCommand VARCHAR(256)
		SET @viewCommand='SELECT* FROM '+@viewName
		EXEC(@viewCommand)
		SET @EndTimeInserts=SYSDATETIME()
		INSERT INTO TestRunViews VALUES(@testRunID,@viewID,@StartTimeInserts,@EndTimeInserts)
		PRINT @testRunID+' '+ @viewID+' '+@StartTimeInserts+' '+@EndTimeInserts
		FETCH NEXT FROM VIEWCURSOR INTO @viewID,@viewName
	END
	CLOSE VIEWCURSOR
	DEALLOCATE VIEWCURSOR
	
	
	OPEN TABLECURSOR
	FETCH LAST FROM TABLECURSOR INTO @tableID,@tableName,@noOfRows
	WHILE @@FETCH_STATUS=0
	BEGIN
		EXEC clearTable @tableName
		FETCH PRIOR FROM TABLECURSOR INTO @tableID,@tableName,@noOfRows
	END
	CLOSE TABLECURSOR
	DEALLOCATE TABLECURSOR
	
	SET @ENDALL=SYSDATETIME()
	UPDATE TestRuns SET StartAt=@STARTALL,EndAt=@ENDALL WHERE TestRunID=@testRunID

END
GO



--FIRST TEST:Inserting into all tables and testing all views
INSERT INTO Tables VALUES('PSYCHOLOGIST'),('COURSE'),('SPECIALIZATION'),('ObtainedSpecialization')
INSERT INTO Views VALUES('view1'),('view2'),('view3')
INSERT INTO Tests VALUES('FIRSTTEST')
INSERT INTO TestTables VALUES(1,1,1000,0),(1,2,1000,2),(1,3,1000,1),(1,4,1000,3)
INSERT INTO TestViews VALUES(1,1),(1,2),(1,3)
EXEC runTest FIRSTTEST


--Second Test:Inserting into Specialization and testing all views
INSERT INTO Tests VALUES('SECONDTEST')
INSERT INTO TestTables VALUES(2,3,10000,0)
INSERT INTO TestViews VALUES(2,1),(2,2),(2,3)
EXEC runTest SECONDTEST

--Third test:Inserting into psychologist,specialization,ObtainedSpecialization,view1,view2
INSERT INTO Tests VALUES('THIRDTEST')
INSERT INTO TestTables VALUES(3,1,10000,0),(3,3,10000,1),(3,4,10000,2)
INSERT INTO TestViews VALUES(3,1),(3,2)
EXEC runTest THIRDTEST


SELECT* FROM TestRunTables
SELECT* FROM TestRunViews
SELECT* FROM TestRuns

DELETE FROM TestRunViews
DELETE FROM TestRunTables
DELETE FROM TestRuns

DBCC CHECKIDENT ('Views', RESEED, 0)
DBCC CHECKIDENT ('Tests', RESEED, 0)
DBCC CHECKIDENT ('Tables', RESEED, 0)