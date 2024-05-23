Use [Psychology Center]
Go
begin tran
declare @oldData int 
declare @newData int
update Course set @oldData=Price,Price=500,@newData=Price where CSid=2
exec sp_log_changes @oldData,@newData,'Deadlock 2:Update 1'
exec sp_log_locks 'Deadlock 2:between updates'
waitfor delay '00:00:05'
update Course set @oldData=Price,Price=690,@newData=Price where CSid=1
exec sp_log_changes @oldData,@newData,'Deadlock 2:Update 2'
commit tran