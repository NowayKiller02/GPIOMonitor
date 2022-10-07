How to make the databse?
Make sure to make a user that only has access to the database you want to use.
CREATE USER 'webuser'@'localhost' IDENTIFIED BY 'Yourpassword';


create database GPIOLoggings;
use GPIOLoggings;
CREATE TABLE `GPIOLoggings`.`logs` (   `id` INT NOT NULL AUTO_INCREMENT,   `GPIO` VARCHAR(45) NOT NULL,   `time` TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP,   `state` TINYINT(1) NOT NULL,   PRIMARY KEY (`id`));
GRANT ALL ON GPIOLoggings.* TO 'webuser'@'localhost';

to start the program add two parameters: 
sudo ./GPIOMonitor hostname  password 
