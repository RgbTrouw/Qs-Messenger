-- phpMyAdmin SQL Dump
-- version 4.9.5deb2
-- https://www.phpmyadmin.net/
--
-- Host: localhost:3306
-- Generation Time: Dec 25, 2025 at 10:30 PM
-- Server version: 8.0.42-0ubuntu0.20.04.1
-- PHP Version: 7.4.3-4ubuntu2.29

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET AUTOCOMMIT = 0;
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `messenger`
--

-- --------------------------------------------------------

--
-- Table structure for table `friendship_requests`
--

CREATE TABLE `friendship_requests` (
  `id` int NOT NULL,
  `ffrom` int DEFAULT NULL,
  `fto` int DEFAULT NULL,
  `fstatus` int NOT NULL,
  `groupName` varchar(12) NOT NULL,
  `fromEmail` text NOT NULL,
  `toEmail` text NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `friendship_requests`
--

INSERT INTO `friendship_requests` (`id`, `ffrom`, `fto`, `fstatus`, `groupName`, `fromEmail`, `toEmail`) VALUES
(9, NULL, NULL, 1, 'Friends', 'steve@qsmessenger.com', 'steve@qsmessenger.com'),
(10, NULL, NULL, 1, 'Work', 'steve@qsmessenger.com', 'steve@qsmessenger.com'),
(11, NULL, NULL, 1, 'SomeGroup', 'steve@qsmessenger.com', 'steve@qsmessenger.com');

-- --------------------------------------------------------

--
-- Table structure for table `friends_list`
--

CREATE TABLE `friends_list` (
  `id` int NOT NULL,
  `owner_id` int DEFAULT NULL,
  `group_name` varchar(24) CHARACTER SET latin1 COLLATE latin1_swedish_ci NOT NULL DEFAULT 'Friends',
  `list` text,
  `ownerEmail` text NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `friends_list`
--

INSERT INTO `friends_list` (`id`, `owner_id`, `group_name`, `list`, `ownerEmail`) VALUES
(8, 1, 'Friends', 'francesca@qsmessenger.com,sara@qsmessenger.com,steve@qsmessenger.com', 'steve@qsmessenger.com'),
(11, NULL, 'Work', '', 'steve@qsmessenger.com'),
(12, NULL, 'Gaming', '', 'steve@qsmessenger.com');

-- --------------------------------------------------------

--
-- Table structure for table `messages`
--

CREATE TABLE `messages` (
  `id` int NOT NULL,
  `msg_from` text CHARACTER SET latin1 COLLATE latin1_swedish_ci,
  `msg_to` text CHARACTER SET latin1 COLLATE latin1_swedish_ci,
  `txt_message` text NOT NULL,
  `time` bigint DEFAULT NULL,
  `has_read` int NOT NULL DEFAULT '1',
  `server_sent` int NOT NULL DEFAULT '0',
  `read_time` bigint DEFAULT NULL,
  `fromEmail` text NOT NULL,
  `toEmail` text NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `messages`
--

INSERT INTO `messages` (`id`, `msg_from`, `msg_to`, `txt_message`, `time`, `has_read`, `server_sent`, `read_time`, `fromEmail`, `toEmail`) VALUES
(40, NULL, NULL, '666768', 1766547981544, 1, 1, 1766550852756, 'steve@qsmessenger.com', 'steve@qsmessenger.com'),
(41, NULL, NULL, '6467', 1766548257542, 1, 1, 1766550852756, 'steve@qsmessenger.com', 'steve@qsmessenger.com'),
(42, NULL, NULL, '68656c6c6f6f6f6f21', 1766548286649, 1, 1, 1766550852756, 'steve@qsmessenger.com', 'steve@qsmessenger.com'),
(43, NULL, NULL, '736466', 1766548574002, 1, 1, 1766550852756, 'steve@qsmessenger.com', 'steve@qsmessenger.com'),
(44, NULL, NULL, '676a', 1766550849403, 1, 1, 1766550852756, 'steve@qsmessenger.com', 'steve@qsmessenger.com'),
(45, NULL, NULL, '3c64696e673e', 1766550869660, 1, 1, 1766550871725, 'steve@qsmessenger.com', 'steve@qsmessenger.com'),
(46, NULL, NULL, '31323334', 1766552375616, 1, 1, 1766552378812, 'steve@qsmessenger.com', 'steve@qsmessenger.com'),
(47, NULL, NULL, '6376626362', 1766634478575, 1, 1, 1766635811915, 'steve@qsmessenger.com', 'steve@qsmessenger.com'),
(48, NULL, NULL, '73666467', 1766635809442, 1, 1, 1766635811915, 'steve@qsmessenger.com', 'steve@qsmessenger.com'),
(49, NULL, NULL, '64736667', 1766635827496, 1, 1, 1766635828711, 'steve@qsmessenger.com', 'steve@qsmessenger.com'),
(50, NULL, NULL, '64736667', 1766635830904, 1, 1, 1766635832112, 'steve@qsmessenger.com', 'steve@qsmessenger.com'),
(51, NULL, NULL, '7364666709090909', 1766635840145, 1, 1, 1766635841754, 'steve@qsmessenger.com', 'steve@qsmessenger.com'),
(52, NULL, NULL, '6466676667', 1766635856367, 1, 1, 1766640379090, 'steve@qsmessenger.com', 'steve@qsmessenger.com'),
(53, NULL, NULL, '646667646667', 1766635970209, 1, 1, 1766640379090, 'steve@qsmessenger.com', 'steve@qsmessenger.com');

-- --------------------------------------------------------

--
-- Table structure for table `users`
--

CREATE TABLE `users` (
  `id` int NOT NULL,
  `full_name` text CHARACTER SET latin1 COLLATE latin1_swedish_ci NOT NULL,
  `nickname` text CHARACTER SET latin1 COLLATE latin1_swedish_ci NOT NULL,
  `picture` text CHARACTER SET latin1 COLLATE latin1_swedish_ci,
  `gender` text CHARACTER SET latin1 COLLATE latin1_swedish_ci NOT NULL,
  `country` text CHARACTER SET latin1 COLLATE latin1_swedish_ci NOT NULL,
  `email` varchar(56) CHARACTER SET latin1 COLLATE latin1_swedish_ci NOT NULL,
  `password` text CHARACTER SET latin1 COLLATE latin1_swedish_ci NOT NULL,
  `availability` int DEFAULT '3',
  `last_msg_read_time` text CHARACTER SET latin1 COLLATE latin1_swedish_ci,
  `status_message` text CHARACTER SET latin1 COLLATE latin1_swedish_ci,
  `hex` text CHARACTER SET latin1 COLLATE latin1_swedish_ci NOT NULL,
  `status` int NOT NULL DEFAULT '0',
  `date_of_birth` text NOT NULL,
  `lastLogin` bigint NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `users`
--

INSERT INTO `users` (`id`, `full_name`, `nickname`, `picture`, `gender`, `country`, `email`, `password`, `availability`, `last_msg_read_time`, `status_message`, `hex`, `status`, `date_of_birth`, `lastLogin`) VALUES
(1, 'Steve', 'steve', NULL, 'male', '', 'steve@qsmessenger.com', '113459eb7bb31bddee85ade5230d6ad5d8b2fb52879e00a84ff6ae1067a210d3', 2, NULL, '', '48642bc6103b8ab15755d30e0d329c1aa535e7364025e6b47b1de753f35702d867fa34732cdabb4c', 1, '01/01/1990', 1766693858962),
(3, 'Andrew', 'andrew', NULL, 'male', '', 'andrew@qsmessenger.com', '113459eb7bb31bddee85ade5230d6ad5d8b2fb52879e00a84ff6ae1067a210d3', 3, NULL, '', '48642bc6103b8ab15755d30e0d329c1aa535e7364025e6b47b1de753f35702d867fa34732cdabb4c', 1, '01/01/1990', 0),
(4, 'Samantha', 'samantha', NULL, 'female', '', 'samantha@qsmessenger.com', '113459eb7bb31bddee85ade5230d6ad5d8b2fb52879e00a84ff6ae1067a210d3', 3, NULL, '', '48642bc6103b8ab15755d30e0d329c1aa535e7364025e6b47b1de753f35702d867fa34732cdabb4c', 1, '01/01/1990', 0),
(5, 'Emma', 'emma', NULL, 'female', '', 'emma@qsmessenger.com', '113459eb7bb31bddee85ade5230d6ad5d8b2fb52879e00a84ff6ae1067a210d3', 3, NULL, '', '48642bc6103b8ab15755d30e0d329c1aa535e7364025e6b47b1de753f35702d867fa34732cdabb4c', 1, '01/01/1990', 0),
(6, 'Elizabeth', 'elizabeth', NULL, 'female', '', 'elizabeth@qsmessenger.com', '113459eb7bb31bddee85ade5230d6ad5d8b2fb52879e00a84ff6ae1067a210d3', 3, NULL, '', '48642bc6103b8ab15755d30e0d329c1aa535e7364025e6b47b1de753f35702d867fa34732cdabb4c', 1, '01/01/1990', 0),
(7, 'Jennifer', 'jennifer', NULL, 'female', '', 'jennifer@qsmessenger.com', '113459eb7bb31bddee85ade5230d6ad5d8b2fb52879e00a84ff6ae1067a210d3', 3, NULL, '', '48642bc6103b8ab15755d30e0d329c1aa535e7364025e6b47b1de753f35702d867fa34732cdabb4c', 1, '01/01/1990', 0),
(8, 'Monica', 'monica', NULL, 'female', '', 'monica@qsmessenger.com', '113459eb7bb31bddee85ade5230d6ad5d8b2fb52879e00a84ff6ae1067a210d3', 3, NULL, '', '48642bc6103b8ab15755d30e0d329c1aa535e7364025e6b47b1de753f35702d867fa34732cdabb4c', 1, '01/01/1990', 0),
(9, 'Smith', 'smith', NULL, 'male', '', 'smith@qsmessenger.com', '113459eb7bb31bddee85ade5230d6ad5d8b2fb52879e00a84ff6ae1067a210d3', 3, NULL, '', '48642bc6103b8ab15755d30e0d329c1aa535e7364025e6b47b1de753f35702d867fa34732cdabb4c', 1, '01/01/1990', 0),
(10, 'Peter', 'peter', NULL, 'male', '', 'peter@qsmessenger.com', '113459eb7bb31bddee85ade5230d6ad5d8b2fb52879e00a84ff6ae1067a210d3', 3, NULL, '', '48642bc6103b8ab15755d30e0d329c1aa535e7364025e6b47b1de753f35702d867fa34732cdabb4c', 1, '01/01/1990', 0),
(11, 'Margaret', 'margaret', NULL, 'female', '', 'margaret@qsmessenger.com', '113459eb7bb31bddee85ade5230d6ad5d8b2fb52879e00a84ff6ae1067a210d3', 3, NULL, '', '48642bc6103b8ab15755d30e0d329c1aa535e7364025e6b47b1de753f35702d867fa34732cdabb4c', 1, '01/01/1990', 0),
(12, 'Amy', 'amy', NULL, 'female', '', 'amy@qsmessenger.com', '113459eb7bb31bddee85ade5230d6ad5d8b2fb52879e00a84ff6ae1067a210d3', 3, NULL, '2d207a7a5a5a7a', '48642bc6103b8ab15755d30e0d329c1aa535e7364025e6b47b1de753f35702d867fa34732cdabb4c', 1, '01/01/1990', 0),
(13, 'Thomas', 'thomas', NULL, 'male', '', 'thomas@qsmessenger.com', '113459eb7bb31bddee85ade5230d6ad5d8b2fb52879e00a84ff6ae1067a210d3', 3, NULL, '', '48642bc6103b8ab15755d30e0d329c1aa535e7364025e6b47b1de753f35702d867fa34732cdabb4c', 1, '01/01/1990', 0),
(14, 'Richard', 'richard', NULL, 'male', '', 'richard@qsmessenger.com', '113459eb7bb31bddee85ade5230d6ad5d8b2fb52879e00a84ff6ae1067a210d3', 3, NULL, '', '48642bc6103b8ab15755d30e0d329c1aa535e7364025e6b47b1de753f35702d867fa34732cdabb4c', 1, '01/01/1990', 0),
(15, 'Bob', 'bob', NULL, 'male', '', 'bob@qsmessenger.com', '113459eb7bb31bddee85ade5230d6ad5d8b2fb52879e00a84ff6ae1067a210d3', 3, NULL, '', '48642bc6103b8ab15755d30e0d329c1aa535e7364025e6b47b1de753f35702d867fa34732cdabb4c', 1, '01/01/1990', 0),
(16, 'Michael', 'michael', NULL, 'male', '', 'michael@qsmessenger.com', '113459eb7bb31bddee85ade5230d6ad5d8b2fb52879e00a84ff6ae1067a210d3', 3, NULL, '', '48642bc6103b8ab15755d30e0d329c1aa535e7364025e6b47b1de753f35702d867fa34732cdabb4c', 1, '01/01/1990', 0),
(17, 'Robert', 'robert', NULL, 'male', '', 'robert@qsmessenger.com', '113459eb7bb31bddee85ade5230d6ad5d8b2fb52879e00a84ff6ae1067a210d3', 3, NULL, '', '48642bc6103b8ab15755d30e0d329c1aa535e7364025e6b47b1de753f35702d867fa34732cdabb4c', 1, '01/01/1990', 0),
(18, 'Patricia', 'patricia', NULL, 'female', '', 'patricia@qsmessenger.com', '113459eb7bb31bddee85ade5230d6ad5d8b2fb52879e00a84ff6ae1067a210d3', 3, NULL, '', '48642bc6103b8ab15755d30e0d329c1aa535e7364025e6b47b1de753f35702d867fa34732cdabb4c', 1, '01/01/1990', 0),
(19, 'Jessica', 'jessica', NULL, 'female', '', 'jessica@qsmessenger.com', '113459eb7bb31bddee85ade5230d6ad5d8b2fb52879e00a84ff6ae1067a210d3', 3, NULL, '', '48642bc6103b8ab15755d30e0d329c1aa535e7364025e6b47b1de753f35702d867fa34732cdabb4c', 1, '01/01/1990', 0),
(20, 'Sandra', 'sandra', NULL, 'female', '', 'sandra@qsmessenger.com', '113459eb7bb31bddee85ade5230d6ad5d8b2fb52879e00a84ff6ae1067a210d3', 3, NULL, '', '48642bc6103b8ab15755d30e0d329c1aa535e7364025e6b47b1de753f35702d867fa34732cdabb4c', 1, '01/01/1990', 0),
(21, 'Stephanie', 'stephanie', NULL, 'female', '', 'stephanie@qsmessenger.com', '113459eb7bb31bddee85ade5230d6ad5d8b2fb52879e00a84ff6ae1067a210d3', 3, NULL, '', '48642bc6103b8ab15755d30e0d329c1aa535e7364025e6b47b1de753f35702d867fa34732cdabb4c', 1, '01/01/1990', 0),
(22, 'Laura', 'laura', NULL, 'female', '', 'laura@qsmessenger.com', '113459eb7bb31bddee85ade5230d6ad5d8b2fb52879e00a84ff6ae1067a210d3', 3, NULL, '', '48642bc6103b8ab15755d30e0d329c1aa535e7364025e6b47b1de753f35702d867fa34732cdabb4c', 1, '01/01/1990', 0),
(23, 'Anna', 'anna', NULL, 'female', '', 'anna@qsmessenger.com', '113459eb7bb31bddee85ade5230d6ad5d8b2fb52879e00a84ff6ae1067a210d3', 3, NULL, '', '48642bc6103b8ab15755d30e0d329c1aa535e7364025e6b47b1de753f35702d867fa34732cdabb4c', 1, '01/01/1990', 0),
(24, 'Helen', 'helen', NULL, 'female', '', 'helen@qsmessenger.com', '113459eb7bb31bddee85ade5230d6ad5d8b2fb52879e00a84ff6ae1067a210d3', 3, NULL, '', '48642bc6103b8ab15755d30e0d329c1aa535e7364025e6b47b1de753f35702d867fa34732cdabb4c', 1, '01/01/1990', 0),
(25, 'Sara', 'sara', NULL, 'female', '', 'sara@qsmessenger.com', '113459eb7bb31bddee85ade5230d6ad5d8b2fb52879e00a84ff6ae1067a210d3', 3, NULL, '', '48642bc6103b8ab15755d30e0d329c1aa535e7364025e6b47b1de753f35702d867fa34732cdabb4c', 1, '01/01/1990', 0),
(26, 'Diana', 'diana', NULL, 'female', '', 'diana@qsmessenger.com', '113459eb7bb31bddee85ade5230d6ad5d8b2fb52879e00a84ff6ae1067a210d3', 3, NULL, '', '48642bc6103b8ab15755d30e0d329c1aa535e7364025e6b47b1de753f35702d867fa34732cdabb4c', 1, '01/01/1990', 0),
(27, 'Scott', 'scott', NULL, 'male', '', 'scott@qsmessenger.com', '113459eb7bb31bddee85ade5230d6ad5d8b2fb52879e00a84ff6ae1067a210d3', 3, NULL, '', '48642bc6103b8ab15755d30e0d329c1aa535e7364025e6b47b1de753f35702d867fa34732cdabb4c', 1, '01/01/1990', 0),
(28, 'Arthur', 'arthur', NULL, 'male', '', 'arthur@qsmessenger.com', '113459eb7bb31bddee85ade5230d6ad5d8b2fb52879e00a84ff6ae1067a210d3', 3, NULL, '', '48642bc6103b8ab15755d30e0d329c1aa535e7364025e6b47b1de753f35702d867fa34732cdabb4c', 1, '01/01/1990', 0),
(29, 'Alice', 'alice', NULL, 'female', '', 'alice@qsmessenger.com', '113459eb7bb31bddee85ade5230d6ad5d8b2fb52879e00a84ff6ae1067a210d3', 3, NULL, '', '48642bc6103b8ab15755d30e0d329c1aa535e7364025e6b47b1de753f35702d867fa34732cdabb4c', 1, '01/01/1990', 0),
(31, 'Danielle', 'danielle', NULL, 'female', '', 'danielle@qsmessenger.com', '113459eb7bb31bddee85ade5230d6ad5d8b2fb52879e00a84ff6ae1067a210d3', 3, NULL, '2d20646f206e6f742064697374757262', '48642bc6103b8ab15755d30e0d329c1aa535e7364025e6b47b1de753f35702d867fa34732cdabb4c', 1, '01/01/1990', 0),
(32, 'Kathy', 'kathy', NULL, 'female', '', 'kathy@qsmessenger.com', '113459eb7bb31bddee85ade5230d6ad5d8b2fb52879e00a84ff6ae1067a210d3', 3, NULL, '', '48642bc6103b8ab15755d30e0d329c1aa535e7364025e6b47b1de753f35702d867fa34732cdabb4c', 1, '01/01/1990', 0),
(33, 'Francesca', 'francesca', NULL, 'female', '', 'francesca@qsmessenger.com', '113459eb7bb31bddee85ade5230d6ad5d8b2fb52879e00a84ff6ae1067a210d3', 3, NULL, '', '48642bc6103b8ab15755d30e0d329c1aa535e7364025e6b47b1de753f35702d867fa34732cdabb4c', 1, '01/01/1990', 0),
(34, 'Jacqueline', 'jacqueline', NULL, 'female', '', 'jacqueline@qsmessenger.com', '113459eb7bb31bddee85ade5230d6ad5d8b2fb52879e00a84ff6ae1067a210d3', 3, NULL, '', '48642bc6103b8ab15755d30e0d329c1aa535e7364025e6b47b1de753f35702d867fa34732cdabb4c', 1, '01/01/1990', 0),
(35, 'Gerald', 'gerald', NULL, 'male', '', 'gerald@qsmessenger.com', '113459eb7bb31bddee85ade5230d6ad5d8b2fb52879e00a84ff6ae1067a210d3', 3, NULL, '', '48642bc6103b8ab15755d30e0d329c1aa535e7364025e6b47b1de753f35702d867fa34732cdabb4c', 1, '01/01/1990', 0),
(36, 'Jordan', 'jordan', NULL, 'male', '', 'jordan@qsmessenger.com', '113459eb7bb31bddee85ade5230d6ad5d8b2fb52879e00a84ff6ae1067a210d3', 3, NULL, '', '48642bc6103b8ab15755d30e0d329c1aa535e7364025e6b47b1de753f35702d867fa34732cdabb4c', 1, '01/01/1990', 0),
(37, 'Stephan', 'stephan', NULL, 'male', '', 'stephan@qsmessenger.com', '113459eb7bb31bddee85ade5230d6ad5d8b2fb52879e00a84ff6ae1067a210d3', 3, NULL, '', '48642bc6103b8ab15755d30e0d329c1aa535e7364025e6b47b1de753f35702d867fa34732cdabb4c', 1, '01/01/1990', 0),
(38, 'Jonathan', 'jonathan', NULL, 'male', '', 'jonathan@qsmessenger.com', '113459eb7bb31bddee85ade5230d6ad5d8b2fb52879e00a84ff6ae1067a210d3', 3, NULL, '2d20776f726b696e67', '48642bc6103b8ab15755d30e0d329c1aa535e7364025e6b47b1de753f35702d867fa34732cdabb4c', 1, '01/01/1990', 0),
(39, 'Eve', 'eve', NULL, 'female', '', 'eve@qsmessenger.com', '113459eb7bb31bddee85ade5230d6ad5d8b2fb52879e00a84ff6ae1067a210d3', 3, NULL, '', '48642bc6103b8ab15755d30e0d329c1aa535e7364025e6b47b1de753f35702d867fa34732cdabb4c', 1, '01/01/1990', 0),
(40, 'Samia', 'samia', NULL, 'female', '', 'samia@qsmessenger.com', '113459eb7bb31bddee85ade5230d6ad5d8b2fb52879e00a84ff6ae1067a210d3', 3, NULL, '', '48642bc6103b8ab15755d30e0d329c1aa535e7364025e6b47b1de753f35702d867fa34732cdabb4c', 1, '01/01/1990', 0),
(41, 'Jeff', 'jeff', NULL, 'male', '', 'jeff@qsmessenger.com', '113459eb7bb31bddee85ade5230d6ad5d8b2fb52879e00a84ff6ae1067a210d3', 3, NULL, '', '48642bc6103b8ab15755d30e0d329c1aa535e7364025e6b47b1de753f35702d867fa34732cdabb4c', 1, '01/01/1990', 0),
(42, 'Christian', 'christian', NULL, 'male', '', 'christian@qsmessenger.com', '113459eb7bb31bddee85ade5230d6ad5d8b2fb52879e00a84ff6ae1067a210d3', 3, NULL, '', '48642bc6103b8ab15755d30e0d329c1aa535e7364025e6b47b1de753f35702d867fa34732cdabb4c', 1, '01/01/1990', 0),
(43, 'Isabelle', 'isabelle', NULL, 'female', '', 'isabelle@qsmessenger.com', '113459eb7bb31bddee85ade5230d6ad5d8b2fb52879e00a84ff6ae1067a210d3', 3, NULL, '', '48642bc6103b8ab15755d30e0d329c1aa535e7364025e6b47b1de753f35702d867fa34732cdabb4c', 1, '01/01/1990', 0),
(44, 'Britney', 'britney', NULL, 'female', '', 'britney@qsmessenger.com', '113459eb7bb31bddee85ade5230d6ad5d8b2fb52879e00a84ff6ae1067a210d3', 3, NULL, '', '48642bc6103b8ab15755d30e0d329c1aa535e7364025e6b47b1de753f35702d867fa34732cdabb4c', 1, '01/01/1990', 0),
(48, 'Radu Gabriel Balaban Grajdan', 'Bala', NULL, 'male', '', 'rgb.trust@gmail.com', '9bf1f69c229f3dd6410cafb89cd71f29e7791a5140bda9e40449d689f1a0ef0d', 3, NULL, '', '53d3448a0ef9d01e5b11c3c61334778de97c4542171b2afae15ba8951368217dffa34fe685500c29', 1, '29/11/1990', 1766360232434);

--
-- Indexes for dumped tables
--

--
-- Indexes for table `friendship_requests`
--
ALTER TABLE `friendship_requests`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `friends_list`
--
ALTER TABLE `friends_list`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `messages`
--
ALTER TABLE `messages`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `users`
--
ALTER TABLE `users`
  ADD PRIMARY KEY (`id`),
  ADD UNIQUE KEY `email` (`email`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `friendship_requests`
--
ALTER TABLE `friendship_requests`
  MODIFY `id` int NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=12;

--
-- AUTO_INCREMENT for table `friends_list`
--
ALTER TABLE `friends_list`
  MODIFY `id` int NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=14;

--
-- AUTO_INCREMENT for table `messages`
--
ALTER TABLE `messages`
  MODIFY `id` int NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=54;

--
-- AUTO_INCREMENT for table `users`
--
ALTER TABLE `users`
  MODIFY `id` int NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=49;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
