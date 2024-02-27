USE [Psychology Center]
GO

DELETE FROM HoldsW;
DELETE FROM Workshop;
DELETE FROM ObtainedSpecialization;
DELETE FROM HASCondition;
DELETE FROM CONDITION;
DELETE FROM COURSE;
DELETE FROM THERAPYSESSION;
DELETE FROM SPECIALIZATION;
DELETE FROM PSYCHOLOGIST;
DELETE FROM CLIENT;
GO


INSERT INTO PSYCHOLOGIST(PsychologistID,FName,LName,DOB) VALUES (1,'Jhon','Smith','1989-11-11')
 ,(2,'Sophia','Brown','1986-11-11') ,(3,'Olivia','Anderson','1995-12-21'),(4,'Emma','Willson','1991-7-12'),(5,'Ava','Taylor','1980-9-10')

INSERT INTO CLIENT(ClientID,FName,LName,DOB) VALUES(1,'Liam','Jhonson','1982-8-20')
,(2,'Noah','Beck','1983-9-20'),(3,'Oliver','Smith','2003-1-19'),(4,'William','Davis','2001-2-18')

INSERT INTO CONDITION(ConID,CDescription) VALUES(1,'Depression'),(2,'Social anxiety'),(3,'Childhood trauma'),(4,'Prone to panic attacks')

INSERT INTO HASCondition(CID,ConID) VALUES(1,1),(2,2),(2,1),(3,3),(3,2),(4,4)

INSERT INTO Workshop(Wid,WDescription,WName) VALUES(1,'This workshop focuses on teaching participants various strategies and techniques to manage and cope with stress effectively','Stress management workshop')
,(2,'This workshop helps individuals improve their interpersonal communication skills.','Comunications Skills Workshop'),(3,'Designed for parents, this workshop offers guidance on effective parenting techniques','Parenting skills workshop')

INSERT INTO THERAPYSESSION(TSid,TDate,Ttime,Price,Cid,Pid) VALUES(1,'2023-3-21','14:30:00',250,1,1)
,(2,'2023-3-22','14:30:00',250,1,1),(3,'2023-3-23','16:30:00',300,3,2),(4,'2023-4-23','16:30:00',300,3,2),(5,'2023-5-23','16:30:00',300,3,2),(6,'2023-6-23','16:30:00',250,2,3),(7,'2023-6-23','16:30:00',200,4,4),(8,'2023-6-23','16:30:00',200,4,5)

INSERT INTO SPECIALIZATION(SPECid,SName,SDesc) VALUES(1,'Clinical Psychology','Clinical psychologists assess and treat individuals who are dealing with emotional, mental, or behavioral disorders')
,(2,'Counselling Psychology','Counseling psychologists focus on helping people cope with everyday life challenges and transitions.')
,(3,'Forensic Psychology','Forensic psychologists apply psychological principles to the legal and criminal justice systems.')

INSERT INTO COURSE(CSid,CNmae,Price,Sid) VALUES(1,'Introduction to clinical psychology',300,1),(2,'Psychotherapy and Counseling Techniques',150,1),(3,'Abnormal Psychology',150,2),(4, 'Advanced Clinical Psychology', 400, 1),
(5, 'Advanced Psychotherapy Techniques', 350, 2)
INSERT INTO ObtainedSpecialization(SPECid,Pid) VALUES(1,1),(1,2),(1,3),(2,1),(2,2),(2,3),(3,1),(3,2),(3,3)
INSERT INTO HoldsW(Pid,Wid) VALUES(1,1),(1,3),(3,1),(4,3),(5,2)


UPDATE THERAPYSESSION
SET Price = Price + 50
WHERE Ttime = '14:30:00' AND Price = 200 OR  Price>200

UPDATE COURSE
SET Price=Price-50
WHERE Price IS NOT NULL

UPDATE COURSE
SET Price=Price-50
WHERE Price BETWEEN 100 AND 200

UPDATE SPECIALIZATION
SET SName = 'Updated'
WHERE SPECid IN (1, 3)

UPDATE PSYCHOLOGIST
SET FName = 'Updated'
WHERE LName = 'Harris' AND DOB = '1985-10-21'

UPDATE PSYCHOLOGIST
SET FName = 'Updated'
WHERE FName LIKE 'Em%';

DELETE FROM PSYCHOLOGIST
WHERE LName='Brown' AND DOB='1986-11-11'

DELETE FROM CLIENT
WHERE LName = 'Jhonson' OR LName = 'Beck'

DELETE FROM THERAPYSESSION
WHERE NOT (Price >= 300);

DELETE FROM SPECIALIZATION
WHERE SPECid IN (1, 3);

DELETE FROM COURSE
WHERE Price BETWEEN 150 AND 250;

DELETE FROM PSYCHOLOGIST
WHERE FName LIKE 'Em%';

SELECT PsychologistID, FName, LName FROM PSYCHOLOGIST
UNION ALL
SELECT ClientID, FName, LName FROM CLIENT;

SELECT DISTINCT FName, LName FROM PSYCHOLOGIST
WHERE PsychologistID = 1 OR PsychologistID = 2
OR PsychologistID = 3
OR PsychologistID IS  NULL
OR NOT (PsychologistID = 6);


SELECT DISTINCT FName FROM PSYCHOLOGIST
INTERSECT
SELECT DISTINCT Pid FROM THERAPYSESSION
WHERE TDate = '2023-3-23'
ORDER BY PsychologistID

SELECT DISTINCT ClientID,FName FROM CLIENT
EXCEPT
SELECT Cid,TDate FROM THERAPYSESSION
WHERE TDate='2023-03-21'
ORDER BY ClientID

SELECT *
FROM CLIENT
WHERE ClientID IN (SELECT Cid FROM THERAPYSESSION WHERE TDate = '2023-3-22')


SELECT PsychologistID, FName, LName FROM PSYCHOLOGIST
WHERE PsychologistID NOT IN (SELECT Pid FROM THERAPYSESSION WHERE TDate = '2023-3-21');


SELECT *
FROM PSYCHOLOGIST P FULL JOIN THERAPYSESSION TS ON P.PsychologistID=TS.Pid

SELECT *
FROM CLIENT C
LEFT JOIN HASCondition HC ON C.ClientID = HC.CID
LEFT JOIN CONDITION CON ON HC.ConID = CON.ConID;

SELECT W.WName, W.WDescription, P.FName, P.LName
FROM Workshop W
RIGHT JOIN HoldsW HW ON W.Wid = HW.Wid
RIGHT JOIN PSYCHOLOGIST P ON HW.Pid = P.PsychologistID
ORDER BY WName

SELECT C.ClientID, C.FName, TS.TSid, TS.TDate, P.PsychologistID, P.FName AS PsychologistFName,
       S.SPECid, S.SName, Cn.ConID, Cn.CDescription
FROM CLIENT C
FULL JOIN HASCondition HC ON C.ClientID = HC.CID
FULL JOIN CONDITION Cn ON HC.ConID = Cn.ConID
FULL JOIN THERAPYSESSION TS ON C.ClientID = TS.Cid
FULL JOIN PSYCHOLOGIST P ON TS.Pid = P.PsychologistID
FULL JOIN ObtainedSpecialization OS ON P.PsychologistID = OS.Pid
FULL JOIN SPECIALIZATION S ON OS.SPECid = S.SPECid
WHERE (Cn.CDescription = 'Depression' OR Cn.CDescription IS NULL)
  AND (S.SName = 'Counselling Psychology' OR S.SName IS NULL)
ORDER BY C.FName



SELECT ClientID, FName, LName
FROM CLIENT
WHERE ClientID IN (SELECT CID FROM HASCondition WHERE ConID = 2);

SELECT ClientID, FName, LName
FROM CLIENT
WHERE ClientID IN  (SELECT CID 
					FROM HASCondition 
					WHERE ConID IN (SELECT ConID 
									FROM CONDITION 
									WHERE CDescription = 'Depression'));

SELECT PsychologistID, FName, LName
FROM PSYCHOLOGIST P
WHERE EXISTS (SELECT 1 FROM THERAPYSESSION TS WHERE P.PsychologistID = TS.Pid);


SELECT PsychologistID, FName, LName
FROM PSYCHOLOGIST P
WHERE EXISTS (SELECT * FROM ObtainedSpecialization OS WHERE P.PsychologistID = OS.Pid AND OS.SPECid = 1);

SELECT TOP 5 C.ClientID, C.FName, COUNT(TS.TSid) AS SessionCount
FROM CLIENT C
LEFT JOIN (SELECT Cid, TSid FROM THERAPYSESSION WHERE TDate = '2023-3-21') TS
ON C.ClientID = TS.Cid
GROUP BY C.ClientID, C.FName;

SELECT TOP 5 P.PsychologistID, P.FName, COUNT(TS.TSid) AS SessionCount
FROM PSYCHOLOGIST P
LEFT JOIN THERAPYSESSION TS ON P.PsychologistID = TS.Pid
GROUP BY P.PsychologistID, P.FName
HAVING COUNT(TS.TSid) > 1;

SELECT TOP 5 C.ClientID,C.FName,C.LName,SUM(TS.Price) AS TOTALSPENT
FROM CLIENT C
LEFT JOIN THERAPYSESSION TS ON C.ClientID=TS.Cid
GROUP BY C.ClientID,C.FName,C.LName
HAVING SUM(TS.Price)>0;

SELECT P.PsychologistID,P.FName,P.LName ,MIN(TS.TDate) AS closestSession
FROM PSYCHOLOGIST P 
LEFT JOIN THERAPYSESSION TS ON P.PsychologistID=TS.Pid
GROUP BY P.PsychologistID,P.FName,P.LName
HAVING MIN(TS.TDate) IS NOT NULL;

SELECT P.PsychologistID,P.FName,P.LName ,MAX(TS.TDate) AS furthestSession
FROM PSYCHOLOGIST P 
LEFT JOIN THERAPYSESSION TS ON P.PsychologistID=TS.Pid
GROUP BY P.PsychologistID,P.FName,P.LName
HAVING MAX(TS.TDate) IS NOT NULL;


SELECT DISTINCT S.SPECid,S.SName,AVG(TS.Price) AS avgSessionPrice
FROM SPECIALIZATION S
LEFT JOIN ObtainedSpecialization OS ON S.SPECid=OS.SPECid
LEFT JOIN THERAPYSESSION TS ON OS.Pid=TS.Pid
GROUP BY S.SPECid,S.SName
HAVING AVG(TS.Price)>=(SELECT AVG(Price) FROM THERAPYSESSION);


SELECT P.*,TS.*
FROM PSYCHOLOGIST P
JOIN THERAPYSESSION TS ON TS.Pid = P.PsychologistID
WHERE TS.Price > ALL (SELECT Price FROM THERAPYSESSION WHERE Pid <> P.PsychologistID);

SELECT FName, LName
FROM PSYCHOLOGIST
WHERE PsychologistID = ALL (SELECT Pid FROM THERAPYSESSION WHERE Price > (SELECT AVG(Price) FROM THERAPYSESSION));

SELECT FName, LName
FROM PSYCHOLOGIST
WHERE PsychologistID = ANY (SELECT Pid FROM THERAPYSESSION WHERE Price >= 250);

SELECT C.*
FROM COURSE C
JOIN SPECIALIZATION S ON S.SPECid = C.Sid
WHERE C.Price > ANY (SELECT Price FROM COURSE WHERE Sid <> S.SPECid);


SELECT FName, LName
FROM PSYCHOLOGIST
WHERE PsychologistID = (SELECT MAX(Pid) FROM THERAPYSESSION WHERE Price > (SELECT AVG(Price) FROM THERAPYSESSION));

SELECT C.*
FROM COURSE C
JOIN SPECIALIZATION S ON S.SPECid = C.Sid
WHERE C.Price >  (SELECT MIN(Price) FROM COURSE WHERE Sid <> S.SPECid);

SELECT FName, LName
FROM PSYCHOLOGIST
WHERE PsychologistID IN (SELECT Pid FROM THERAPYSESSION WHERE Price >= 250);

SELECT P.*,TS.*
FROM PSYCHOLOGIST P
JOIN THERAPYSESSION TS ON TS.Pid = P.PsychologistID
WHERE TS.Price NOT IN (SELECT Price FROM THERAPYSESSION WHERE Pid <> P.PsychologistID);