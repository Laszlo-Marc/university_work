Use [Psychology Center]
Go
-- query console 1
select @@SPID
select @@TRANCOUNT
DBCC USEROPTIONS


delete from COURSE
delete from SPECIALIZATION
insert into SPECIALIZATION(SPECid,SName,SDesc) Values(1,'Clinical Psychology','Psychology in a clinic')
insert into Course(CSid,CNmae,Price,Sid) Values(1,'Introduction to psy',200,1),(2,'Part 2 to psy',250,1)



begin tran
declare @oldData int
declare @newData int
waitfor delay '00:00:10'
update COURSE set @oldData=Price, Price=1000, @newData=Price where CSid=1
exec sp_log_changes @oldData, @newData, 'Non-Repeatable Reads 1: update'
exec sp_log_locks 'Non-Repeatable Reads 1: after update'
commit tran

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

Select * from LogChanges
Select* from LogLocks
delete from LogLocks
delete from LogChanges

select * from COURSE
select * from SPECIALIZATION