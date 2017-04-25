-- phpMyAdmin SQL Dump
-- Erstellungszeit: 17. Dezember 2015 um 12:37
-- Server Version: 5.1.41
SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;
-- --------------------------------------------------------
-- Database structure for module 'wrapper'
--
-- Replacements: {TABLE_PREFIX}, {TABLE_ENGINE}, {TABLE_COLLATION}
--
-- --------------------------------------------------------
--
-- Tabellenstruktur für Tabelle `mod_wrapper`
--
DROP TABLE IF EXISTS `{TABLE_PREFIX}mod_wrapper`;
CREATE TABLE IF NOT EXISTS `{TABLE_PREFIX}mod_wrapper` (
  `section_id` INT NOT NULL DEFAULT '0',
  `page_id` INT NOT NULL DEFAULT '0',
  `url` VARCHAR(512){FIELD_COLLATION} NOT NULL DEFAULT '',
  `height` INT NOT NULL DEFAULT '0',
  PRIMARY KEY ( `section_id` )
){TABLE_ENGINE};

-- ALTER TABLE `{TABLE_PREFIX}mod_wrapper` CHANGE `url` `url` VARCHAR(512){FIELD_COLLATION} NOT NULL DEFAULT '';

-- EndOfFile
