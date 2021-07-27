--INSERT INTO dkanrjskdla. VALUES('asdf', 'qwer', '비둘기', '999999999', '둘기')


--ALTER TABLE customer ALTER COLUMN phone varchar(11) NOT NULL

--ALTER TABLE products ADD CHECK(pcode LIKE 'P%')

--ALTER TABLE orders ADD [id] varchar(20) NOT NULL FOREIGN KEY(id) REFERENCES customer
--ALTER TABLE orders ADD [pcode] varchar(20) NOT NULL FOREIGN KEY(pcode) REFERENCES products

--CREATE TABLE products
--(
--pcode varchar(20) PRIMARY KEY,
--pname varchar(20),
--price int DEFAULT 0
--)


--ALTER TABLE customer ALTER COLUMN phone varchar(11)


--CREATE TABLE orders
--(
--oseq int PRIMARY KEY IDENTITY(1, 1),
--quantity int DEFAULT 1,
--indate DATETIME DEFAULT CURRENT_TIMESTAMP,
--id varchar(20) NOT NULL FOREIGN KEY(id) REFERENCES customer,
--pcode varchar(20) NOT NULL FOREIGN KEY(pcode) REFERENCES products,
--)


--CREATE TABLE customer
--(
--id varchar(20) PRIMARY KEY,
--pwd varchar(20) NOT NULL,
--name varchar(20) NOT NULL,
--phone varchar(21) NOT NULL,
--register DATETIME DEFAULT CURRENT_TIMESTAMP,
--address varchar(100) NOT NULL
--)


--CREATE DATABASE dkanrjskdla1
--ON
--PRIMARY
--
--( NAME = dkanrjskdla1,
--FILENAME = 'C:\Users\A-12\Desktop\dkanrjskdla.mdf',
--SIZE = 100MB,
--MAXSIZE = 200,
--FILEGROWTH = 20 )
--
--
--LOG ON
--(
--NAME = dkanrjsdkla1_LOG,
--FILENAME = 'C:\Users\A-12\Desktop\dkanrjskdla.ldf',
--SIZE = 20MB,
--MAXSIZE = 50,
--FILEGROWTH = 10% )