--query console 2
select @@SPID
select @@TRANCOUNT
DBCC USEROPTIONS

begin tran
declare @oldData2 int
declare @newData2 int
update COURSE set @oldData2=Price, Price=1000, @newData2=Price where CSid=1
exec sp_log_changes @oldData2, @newData2, 'Dirty reads 1: update'
exec sp_log_locks 'Dirty reads 1: after update'
waitfor delay '00:00:10'
update COURSE set @oldData2=Price, Price=1500, @newData2=Price where CSid=1
exec sp_log_changes @oldData2, @newData2, 'Dirty reads 1: update'
exec sp_log_locks 'Dirty reads 1: after update'
waitfor delay '00:00:10'
commit tran