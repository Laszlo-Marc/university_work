-- query console 2
select @@SPID
select @@TRANCOUNT
DBCC USEROPTIONS

set transaction isolation level read committed
--set transaction isolation level repeatable read --solution
begin tran
select * from COURSE
exec sp_log_locks 'Non-Repeatable Reads 2: between selects'
waitfor delay '00:00:10'
select * from COURSE
exec sp_log_locks 'Non-Repeatable Reads 2: after both selects'
commit tran 
