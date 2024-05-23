set transaction isolation level serializable --solution
begin tran
select * from COURSE
exec sp_log_locks 'Phantom 2: between selects'
waitfor delay '00:00:10'
select * from COURSE
exec sp_log_locks 'Phantom 2: after both selects'
commit tran 