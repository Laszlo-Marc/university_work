
select @@SPID
select @@TRANCOUNT
DBCC USEROPTIONS


delete from COURSE
delete from SPECIALIZATION
insert into SPECIALIZATION(SPECid,SName,SDesc) Values(1,'Clinical Psychology','Psychology in a clinic')
insert into Course(CSid,CNmae,Price,Sid) Values(1,'Introduction to psy',200,1),(2,'Part 2 to psy',250,1)



--set transaction isolation level read uncommitted
set transaction isolation level read committed --solution

begin tran
select * from COURSE
exec sp_log_locks 'Dirty reads 2: after select'
waitfor delay '00:00:10'
select * from COURSE
waitfor delay '00:00:10'
select * from COURSE
commit tran

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

Select * from LogChanges
Select* from LogLocks
delete from LogLocks
delete from LogChanges

select * from COURSE
select * from SPECIALIZATION