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
delete from COURSE
delete from SPECIALIZATION
insert into SPECIALIZATION(SPECid,SName,SDesc) Values(1,'Clinical Psychology','Psychology in a clinic')
insert into Course(CSid,CNmae,Price,Sid) Values(1,'Introduction to psy',200,1),(2,'Part 2 to psy',250,1)

begin tran
declare @oldData int 
declare @newData int
update Course set @oldData=Price,Price=500,@newData=Price where CSid=1
exec sp_log_changes @oldData,@newData,'Deadlock 1:Update 1'
exec sp_log_locks 'Deadlock 1:between updates'
waitfor delay '00:00:10'
update Course set @oldData=Price,Price=690,@newData=Price where CSid=2
exec sp_log_changes @oldData,@newData,'Deadlock 1:Update 2'
commit tran

begin tran
declare @oldData2 int 
declare @newData2 int
update Course set @oldData2=Price,Price=500,@newData2=Price where CSid=2
exec sp_log_changes @oldData,@newData,'Deadlock 2:Update 1'
exec sp_log_locks 'Deadlock 2:between updates'
waitfor delay '00:00:05'
update Course set @oldData2=Price,Price=690,@newData2=Price where CSid=1
exec sp_log_changes @oldData2,@newData2,'Deadlock 2:Update 2'
commit tran

select * from LogChanges
select * from LogLocks
delete from LogChanges
delete from LogLocks

select * from COURSE
select * from SPECIALIZATION