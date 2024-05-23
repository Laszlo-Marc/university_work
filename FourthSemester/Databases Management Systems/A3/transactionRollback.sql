Use [Psychology Center]
Go
CREATE TABLE LogLocks(
	currentTime DATETIME,
	info VARCHAR(100),

	resource_type VARCHAR(100),
	request_mode VARCHAR(100),
	request_type VARCHAR(100),
	request_status VARCHAR(100),
	request_session_id INT
)

CREATE TABLE LogChanges(
	currentTime DATETIME,
	info VARCHAR(100),
	oldData VARCHAR(100),
	newData VARCHAR(100)
)

GO
CREATE OR ALTER PROCEDURE sp_log_locks
	@info VARCHAR(100)
AS
BEGIN
	INSERT INTO LogLocks (currentTime, info, resource_type, request_mode, request_type, request_status, request_session_id)
	SELECT GETDATE(), @info, resource_type, request_mode, request_type, request_status, request_session_id
	FROM sys.dm_tran_locks
	WHERE request_owner_type = 'TRANSACTION'

END
GO

CREATE OR ALTER PROCEDURE sp_log_changes
	@oldData VARCHAR(100),
	@newData VARCHAR(100),
	@info VARCHAR(100)
AS
BEGIN
	INSERT INTO LogChanges (currentTime, oldData, newData, info) VALUES
	(GETDATE(), @oldData, @newData, @info)
END
GO


Go
create or alter procedure addRowClient(@fname varchar(100), @lname varchar(100), @dob Date) as
    DECLARE @maxId INT
	SET @maxId = 0
	SELECT TOP 1 @maxId = ClientID + 1 FROM CLIENT ORDER BY ClientID DESC
	IF (@fname is null)
	BEGIN
		RAISERROR('Client first name must not be null', 24, 1);
	END
	IF (@lname is null)
	BEGIN
		RAISERROR('Client last name must not be null', 24, 1);
	END
	IF (@dob is null)
	BEGIN
		RAISERROR('Client date of birth must not be null', 24, 1);
	END
	insert into Client (ClientID, FName, LName, DOB) values (@maxId, @fname, @lname, @dob)
    EXEC sp_log_changes null, @fname, 'Added row to client'
go

create or alter procedure addRowCondition (@name Varchar(50),@description varchar(100)) as
    DECLARE @maxId INT
	SET @maxId = 0
	SELECT TOP 1 @maxId = ConID + 1 FROM CONDITION ORDER BY ConID DESC
	IF (@name is null)
	BEGIN
		RAISERROR('Condition name must not be null', 24, 1);
	END
	IF (@description is null)
	BEGIN
		RAISERROR('Condition description must not be null', 24, 1);
	END
    insert into CONDITION(ConID,ConName,CDescription) values (@maxId,@name, @description)
    exec sp_log_changes null, @maxId, 'Added row to Condition'
go

CREATE OR ALTER PROCEDURE addRowHasCondition(@ClientName VARCHAR(50) ,@ConName Varchar(50))
AS
	IF (@ClientName is null)
	BEGIN
		RAISERROR('Client name must not be null', 24, 1);
	END

	IF (@ConName is null)
	BEGIN
		RAISERROR('Condition name must not be null', 24, 1);
	END

	DECLARE @ClientID INT
	SET @ClientID = (SELECT ClientID FROM CLIENT WHERE LName=@ClientName)
	DECLARE @ConID INT
	SET @ConID = (SELECT ConId FROM CONDITION WHERE ConName = @ConName)
	IF (@ClientID is null)
	BEGIN
		RAISERROR('Client does not exist', 24, 1);
	END
	IF (@ConID is null)
	BEGIN
		RAISERROR('Condition does not exist', 24, 1);
	END
	INSERT INTO HASCondition VALUES (@ClientID, @ConID)
	declare @newData varchar(100)
    set @newData = @ClientName + ' ' + @ConName
	exec sp_log_changes null, @newData, 'Connected condition with client'
GO

CREATE OR ALTER PROCEDURE rollbackScenarioFail
AS
	BEGIN TRAN
	BEGIN TRY
		EXEC addRowClient 'Laszlo', 'Marc', '2024-03-21'
		EXEC addRowCondition 'Depression', 'Depression is a state in which you are sad and hopeless'
		EXEC addRowHasCondition 'Marc', 'Trauma'
	END TRY
	BEGIN CATCH
		ROLLBACK TRAN
		RETURN
	END CATCH
	COMMIT TRAN
GO
CREATE OR ALTER PROCEDURE rollbackScenarioNoFail
AS
	BEGIN TRAN
	BEGIN TRY
		EXEC addRowClient 'Laszlo', 'Marc', '2024-03-21'
		EXEC addRowCondition 'Depression', 'Depression is a state in which you are sad and hopeless'
		EXEC addRowHasCondition 'Marc', 'Depression'
	END TRY
	BEGIN CATCH
		ROLLBACK TRAN
		RETURN
	END CATCH
	COMMIT TRAN
GO

CREATE OR ALTER PROCEDURE noRollbackScenarioManyToManyNoFail
AS
	DECLARE @ERRORS INT
	SET @ERRORS = 0
	BEGIN TRY
		EXEC addRowClient 'Laszlo', 'Marc', '2024-03-21'
	END TRY
	BEGIN CATCH
		SET @ERRORS = @ERRORS + 1
	END CATCH

	BEGIN TRY
		EXEC  addRowCondition 'Depression', 'Depression is a state in which you are sad and hopeless'
	END TRY
	BEGIN CATCH
		SET @ERRORS = @ERRORS + 1
	END CATCH

	IF (@ERRORS = 0) BEGIN
		BEGIN TRY
			EXEC addRowHasCondition 'Marc', 'Depression'
		END TRY
		BEGIN CATCH
		END CATCH
	END
GO

CREATE OR ALTER PROCEDURE noRollbackScenarioManyToManyFail
AS
	DECLARE @ERRORS INT
	SET @ERRORS = 0
	BEGIN TRY
		EXEC addRowClient 'Laszlo', 'Marc', '2024-03-21'
	END TRY
	BEGIN CATCH
		SET @ERRORS = @ERRORS + 1
	END CATCH

	BEGIN TRY
		EXEC  addRowCondition 'Depression', 'Depression is a state in which you are sad and hopeless'
	END TRY
	BEGIN CATCH
		SET @ERRORS = @ERRORS + 1
	END CATCH

	IF (@ERRORS = 0) BEGIN
		BEGIN TRY
			EXEC addRowHasCondition 'Jon', 'Trauma'
		END TRY
		BEGIN CATCH
		END CATCH
	END
GO

select * from CLIENT
select * from CONDITION
select * from HASCondition
DELETE FROM HASCondition
DELETE FROM CLIENT
DELETE FROM CONDITION

exec rollbackScenarioFail
exec rollbackScenarioNoFail
exec noRollbackScenarioManyToManyFail
exec noRollbackScenarioManyToManyNoFail

Drop table LogChanges
Drop table LogLocks