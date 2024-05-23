-- query console 1
select @@SPID
select @@TRANCOUNT
DBCC USEROPTIONS


delete from COURSE
delete from SPECIALIZATION
insert into SPECIALIZATION(SPECid,SName,SDesc) Values(1,'Clinical Psychology','Psychology in a clinic')
insert into Course(CSid,CNmae,Price,Sid) Values(1,'Introduction to psy',200,1),(2,'Part 2 to psy',250,1)


begin tran
waitfor delay '00:00:10'
insert into COURSE(CSid,CNmae,Price,Sid) values (3,'test',300,1)
exec sp_log_changes null, 3, 'Phantom 1: insert'
exec sp_log_locks 'Phantom 1: after insert'
commit tran

-- query console 2
select @@SPID
select @@TRANCOUNT
DBCC USEROPTIONS

set transaction isolation level repeatable read
--set transaction isolation level serializable --solution
begin tran
select * from COURSE
exec sp_log_locks 'Phantom 2: between selects'
waitfor delay '00:00:10'
select * from COURSE
exec sp_log_locks 'Phantom 2: after both selects'
commit tran 


Select * from LogChanges
Select* from LogLocks
delete from LogLocks
delete from LogChanges