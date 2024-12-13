-- Question 2
create table CLI (
    CodeCli number(5) constraint Cle_Cli primary key,
    NomCli char(20) constraint NomCli_Not_Null not null,
    Pays char(15) constraint Pays_Not_Nell not null
);

create table COM ( 
    NumCom number(5) constraint Cle_Com primary key,  
    CodeCli number(5) constraint Com_Ref_Cli references CLI,  
    FraisPort number(5) constraint FraisPort_Not_Null not null,
    AnCom number(4)
);

create table PROD (
    NumProd number(5) constraint Cle_Prod primary key,
    NomProd char(20),
    TypeProd char(20) constraint TypeProd_Not_Null not null
);

create table DET (
    NumCom number(5) constraint Det_Ref_Com references COM,
    NumProd number(5) constraint Det_Ref_Prod references PROD,
    Qte number(5) constraint Qte_Not_Null not null,
    Remise number(5) constraint Remise_Not_Null not null
);

-- Question 3
-- Il y a un ordre car certaines tables sont référencées dans d'autres : il faut les créer avant

-- Question 4
desc CLI
desc COM
desc DET
desc PROD

-- Question 5
alter table CLI modify (NomCli char(30));

-- Question 6
alter table CLI add (Tel number(10) constraint Tel_Not_Null not null);

-- Question 7
alter table PROD add (PrixUnit number(5) constraint PrixUnit not null);

-- Question 8 
alter table PROD modify (NomProd constraint NomProd_Not_Null not null);

-- Question 9 
insert into CLI values (
    0, 'Richard', 'France', '0123456789'
);
insert into CLI values (
    1, 'Steve', 'Angleterre', '9876543210'
);

INSERT INTO COM VALUES(
    0, 0, 120, 2001
);
INSERT INTO COM VALUES(
    1, 0, 20, 2020
);

INSERT INTO PROD VALUES(
    0, 'Chaussettes', 'Habits'
);
INSERT INTO PROD VALUES(
    1, 'Iphone 11', 'Smartphone'
);

INSERT INTO DET VALUES(
    0, 1, 500, 20
);
INSERT INTO DET VALUES(
    1, 0, 4, 0
);

-- Question 10
UPDATE CLI SET NomCli = UPPER(NomCli);

-- Question 11 
DELETE FROM DET *;
DELETE FROM PROD *;
DELETE FROM COM *;
DELETE FROM CLI *;

-- Suppression des tables
drop table DET;
drop table PROD;
drop table COM;
drop table CLI;