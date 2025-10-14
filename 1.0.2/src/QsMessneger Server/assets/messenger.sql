-- phpMyAdmin SQL Dump
-- version 5.1.1deb5ubuntu1
-- https://www.phpmyadmin.net/
--
-- Host: localhost:3306
-- Generation Time: Jun 19, 2025 at 04:44 PM
-- Server version: 8.0.42-0ubuntu0.22.04.1
-- PHP Version: 8.1.2-1ubuntu2.21

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
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
  `ffrom` int NOT NULL,
  `fto` int NOT NULL,
  `fstatus` int NOT NULL,
  `groupName` varchar(12) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `friendship_requests`
--

INSERT INTO `friendship_requests` (`id`, `ffrom`, `fto`, `fstatus`, `groupName`) VALUES
(2, 46, 46, 1, 'Friends');

-- --------------------------------------------------------

--
-- Table structure for table `friends_list`
--

CREATE TABLE `friends_list` (
  `id` int NOT NULL,
  `owner_id` int NOT NULL,
  `group_name` varchar(24) CHARACTER SET latin1 COLLATE latin1_swedish_ci NOT NULL DEFAULT 'Friends',
  `list` text
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `friends_list`
--

INSERT INTO `friends_list` (`id`, `owner_id`, `group_name`, `list`) VALUES
(1, 1, 'Friends', '1,2,3,4,5,6,7,8,9,10,11,12,15,18,19,23,24,25,26,28,29,30,31,32,33,34,35,37,39,40,41,42,43,44'),
(3, 1, 'Work', ',14,20,22,36,38,16,17,27'),
(4, 1, 'Gaming', ',13,21'),
(5, 46, 'Friends', '46');

-- --------------------------------------------------------

--
-- Table structure for table `messages`
--

CREATE TABLE `messages` (
  `id` int NOT NULL,
  `msg_from` text NOT NULL,
  `msg_to` text NOT NULL,
  `txt_message` text NOT NULL,
  `time` bigint DEFAULT NULL,
  `has_read` int NOT NULL DEFAULT '1',
  `server_sent` int NOT NULL DEFAULT '0',
  `read_time` bigint DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `messages`
--

INSERT INTO `messages` (`id`, `msg_from`, `msg_to`, `txt_message`, `time`, `has_read`, `server_sent`, `read_time`) VALUES
(1, '1', '2', '3c64696e673e', 1750334867051, 1, 1, 1750334868890);

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
(1, 'Steve', 'steve', NULL, 'male', 'Romania', 'steve@qsmessenger.com', '113459eb7bb31bddee85ade5230d6ad5d8b2fb52879e00a84ff6ae1067a210d3', 2, NULL, '', '48642bc6103b8ab15755d30e0d329c1aa535e7364025e6b47b1de753f35702d867fa34732cdabb4c', 1, '01/01/1990', 0),
(3, 'Andrew', 'andrew', NULL, 'male', 'Romania', 'andrew@qsmessenger.com', '113459eb7bb31bddee85ade5230d6ad5d8b2fb52879e00a84ff6ae1067a210d3', 3, NULL, '', '48642bc6103b8ab15755d30e0d329c1aa535e7364025e6b47b1de753f35702d867fa34732cdabb4c', 1, '01/01/1990', 0),
(4, 'Samantha', 'samantha', NULL, 'female', 'Romania', 'samantha@qsmessenger.com', '113459eb7bb31bddee85ade5230d6ad5d8b2fb52879e00a84ff6ae1067a210d3', 0, NULL, '', '48642bc6103b8ab15755d30e0d329c1aa535e7364025e6b47b1de753f35702d867fa34732cdabb4c', 1, '01/01/1990', 0),
(5, 'Emma', 'emma', NULL, 'female', 'Romania', 'emma@qsmessenger.com', '113459eb7bb31bddee85ade5230d6ad5d8b2fb52879e00a84ff6ae1067a210d3', 3, NULL, '', '48642bc6103b8ab15755d30e0d329c1aa535e7364025e6b47b1de753f35702d867fa34732cdabb4c', 1, '01/01/1990', 0),
(6, 'Elizabeth', 'elizabeth', NULL, 'female', 'Romania', 'elizabeth@qsmessenger.com', '113459eb7bb31bddee85ade5230d6ad5d8b2fb52879e00a84ff6ae1067a210d3', 3, NULL, '', '48642bc6103b8ab15755d30e0d329c1aa535e7364025e6b47b1de753f35702d867fa34732cdabb4c', 1, '01/01/1990', 0),
(7, 'Jennifer', 'jennifer', NULL, 'female', 'Romania', 'jennifer@qsmessenger.com', '113459eb7bb31bddee85ade5230d6ad5d8b2fb52879e00a84ff6ae1067a210d3', 3, NULL, '', '48642bc6103b8ab15755d30e0d329c1aa535e7364025e6b47b1de753f35702d867fa34732cdabb4c', 1, '01/01/1990', 0),
(8, 'Monica', 'monica', NULL, 'female', 'Romania', 'monica@qsmessenger.com', '113459eb7bb31bddee85ade5230d6ad5d8b2fb52879e00a84ff6ae1067a210d3', 1, NULL, '', '48642bc6103b8ab15755d30e0d329c1aa535e7364025e6b47b1de753f35702d867fa34732cdabb4c', 1, '01/01/1990', 0),
(9, 'Smith', 'smith', NULL, 'male', 'Romania', 'smith@qsmessenger.com', '113459eb7bb31bddee85ade5230d6ad5d8b2fb52879e00a84ff6ae1067a210d3', 3, NULL, '', '48642bc6103b8ab15755d30e0d329c1aa535e7364025e6b47b1de753f35702d867fa34732cdabb4c', 1, '01/01/1990', 0),
(10, 'Peter', 'peter', NULL, 'male', 'Romania', 'peter@qsmessenger.com', '113459eb7bb31bddee85ade5230d6ad5d8b2fb52879e00a84ff6ae1067a210d3', 0, NULL, '', '48642bc6103b8ab15755d30e0d329c1aa535e7364025e6b47b1de753f35702d867fa34732cdabb4c', 1, '01/01/1990', 0),
(11, 'Margaret', 'margaret', NULL, 'female', 'Romania', 'margaret@qsmessenger.com', '113459eb7bb31bddee85ade5230d6ad5d8b2fb52879e00a84ff6ae1067a210d3', 1, NULL, '', '48642bc6103b8ab15755d30e0d329c1aa535e7364025e6b47b1de753f35702d867fa34732cdabb4c', 1, '01/01/1990', 0),
(12, 'Amy', 'amy', NULL, 'female', 'Romania', 'amy@qsmessenger.com', '113459eb7bb31bddee85ade5230d6ad5d8b2fb52879e00a84ff6ae1067a210d3', 1, NULL, '7a7a5a5a7a', '48642bc6103b8ab15755d30e0d329c1aa535e7364025e6b47b1de753f35702d867fa34732cdabb4c', 1, '01/01/1990', 0),
(13, 'Thomas', 'thomas', NULL, 'male', 'Romania', 'thomas@qsmessenger.com', '113459eb7bb31bddee85ade5230d6ad5d8b2fb52879e00a84ff6ae1067a210d3', 3, NULL, '', '48642bc6103b8ab15755d30e0d329c1aa535e7364025e6b47b1de753f35702d867fa34732cdabb4c', 1, '01/01/1990', 0),
(14, 'Richard', 'richard', NULL, 'male', 'Romania', 'richard@qsmessenger.com', '113459eb7bb31bddee85ade5230d6ad5d8b2fb52879e00a84ff6ae1067a210d3', 3, NULL, '', '48642bc6103b8ab15755d30e0d329c1aa535e7364025e6b47b1de753f35702d867fa34732cdabb4c', 1, '01/01/1990', 0),
(15, 'Bob', 'bob', NULL, 'male', 'Romania', 'bob@qsmessenger.com', '113459eb7bb31bddee85ade5230d6ad5d8b2fb52879e00a84ff6ae1067a210d3', 0, NULL, '', '48642bc6103b8ab15755d30e0d329c1aa535e7364025e6b47b1de753f35702d867fa34732cdabb4c', 1, '01/01/1990', 0),
(16, 'Michael', 'michael', NULL, 'male', 'Romania', 'michael@qsmessenger.com', '113459eb7bb31bddee85ade5230d6ad5d8b2fb52879e00a84ff6ae1067a210d3', 3, NULL, '', '48642bc6103b8ab15755d30e0d329c1aa535e7364025e6b47b1de753f35702d867fa34732cdabb4c', 1, '01/01/1990', 0),
(17, 'Robert', 'robert', NULL, 'male', 'Romania', 'robert@qsmessenger.com', '113459eb7bb31bddee85ade5230d6ad5d8b2fb52879e00a84ff6ae1067a210d3', 3, NULL, '', '48642bc6103b8ab15755d30e0d329c1aa535e7364025e6b47b1de753f35702d867fa34732cdabb4c', 1, '01/01/1990', 0),
(18, 'Patricia', 'patricia', NULL, 'female', 'Romania', 'patricia@qsmessenger.com', '113459eb7bb31bddee85ade5230d6ad5d8b2fb52879e00a84ff6ae1067a210d3', 3, NULL, '', '48642bc6103b8ab15755d30e0d329c1aa535e7364025e6b47b1de753f35702d867fa34732cdabb4c', 1, '01/01/1990', 0),
(19, 'Jessica', 'jessica', NULL, 'female', 'Romania', 'jessica@qsmessenger.com', '113459eb7bb31bddee85ade5230d6ad5d8b2fb52879e00a84ff6ae1067a210d3', 0, NULL, '', '48642bc6103b8ab15755d30e0d329c1aa535e7364025e6b47b1de753f35702d867fa34732cdabb4c', 1, '01/01/1990', 0),
(20, 'Sandra', 'sandra', NULL, 'female', 'Romania', 'sandra@qsmessenger.com', '113459eb7bb31bddee85ade5230d6ad5d8b2fb52879e00a84ff6ae1067a210d3', 3, NULL, '', '48642bc6103b8ab15755d30e0d329c1aa535e7364025e6b47b1de753f35702d867fa34732cdabb4c', 1, '01/01/1990', 0),
(21, 'Stephanie', 'stephanie', NULL, 'female', 'Romania', 'stephanie@qsmessenger.com', '113459eb7bb31bddee85ade5230d6ad5d8b2fb52879e00a84ff6ae1067a210d3', 3, NULL, '', '48642bc6103b8ab15755d30e0d329c1aa535e7364025e6b47b1de753f35702d867fa34732cdabb4c', 1, '01/01/1990', 0),
(22, 'Laura', 'laura', NULL, 'female', 'Romania', 'laura@qsmessenger.com', '113459eb7bb31bddee85ade5230d6ad5d8b2fb52879e00a84ff6ae1067a210d3', 0, NULL, '', '48642bc6103b8ab15755d30e0d329c1aa535e7364025e6b47b1de753f35702d867fa34732cdabb4c', 1, '01/01/1990', 0),
(23, 'Anna', 'anna', NULL, 'female', 'Romania', 'anna@qsmessenger.com', '113459eb7bb31bddee85ade5230d6ad5d8b2fb52879e00a84ff6ae1067a210d3', 3, NULL, '', '48642bc6103b8ab15755d30e0d329c1aa535e7364025e6b47b1de753f35702d867fa34732cdabb4c', 1, '01/01/1990', 0),
(24, 'Helen', 'helen', NULL, 'female', 'Romania', 'helen@qsmessenger.com', '113459eb7bb31bddee85ade5230d6ad5d8b2fb52879e00a84ff6ae1067a210d3', 3, NULL, '', '48642bc6103b8ab15755d30e0d329c1aa535e7364025e6b47b1de753f35702d867fa34732cdabb4c', 1, '01/01/1990', 0),
(25, 'Sara', 'sara', NULL, 'female', 'Romania', 'sara@qsmessenger.com', '113459eb7bb31bddee85ade5230d6ad5d8b2fb52879e00a84ff6ae1067a210d3', 3, NULL, '', '48642bc6103b8ab15755d30e0d329c1aa535e7364025e6b47b1de753f35702d867fa34732cdabb4c', 1, '01/01/1990', 0),
(26, 'Diana', 'diana', NULL, 'female', 'Romania', 'diana@qsmessenger.com', '113459eb7bb31bddee85ade5230d6ad5d8b2fb52879e00a84ff6ae1067a210d3', 1, NULL, '', '48642bc6103b8ab15755d30e0d329c1aa535e7364025e6b47b1de753f35702d867fa34732cdabb4c', 1, '01/01/1990', 0),
(27, 'Scott', 'scott', NULL, 'male', 'Romania', 'scott@qsmessenger.com', '113459eb7bb31bddee85ade5230d6ad5d8b2fb52879e00a84ff6ae1067a210d3', 3, NULL, '', '48642bc6103b8ab15755d30e0d329c1aa535e7364025e6b47b1de753f35702d867fa34732cdabb4c', 1, '01/01/1990', 0),
(28, 'Arthur', 'arthur', NULL, 'male', 'Romania', 'arthur@qsmessenger.com', '113459eb7bb31bddee85ade5230d6ad5d8b2fb52879e00a84ff6ae1067a210d3', 3, NULL, '', '48642bc6103b8ab15755d30e0d329c1aa535e7364025e6b47b1de753f35702d867fa34732cdabb4c', 1, '01/01/1990', 0),
(29, 'Alice', 'alice', NULL, 'female', 'Romania', 'alice@qsmessenger.com', '113459eb7bb31bddee85ade5230d6ad5d8b2fb52879e00a84ff6ae1067a210d3', 3, NULL, '', '48642bc6103b8ab15755d30e0d329c1aa535e7364025e6b47b1de753f35702d867fa34732cdabb4c', 1, '01/01/1990', 0),
(31, 'Danielle', 'danielle', NULL, 'female', 'Romania', 'danielle@qsmessenger.com', '113459eb7bb31bddee85ade5230d6ad5d8b2fb52879e00a84ff6ae1067a210d3', 1, NULL, '646f206e6f742064697374757262', '48642bc6103b8ab15755d30e0d329c1aa535e7364025e6b47b1de753f35702d867fa34732cdabb4c', 1, '01/01/1990', 0),
(32, 'Kathy', 'kathy', NULL, 'female', 'Romania', 'kathy@qsmessenger.com', '113459eb7bb31bddee85ade5230d6ad5d8b2fb52879e00a84ff6ae1067a210d3', 0, NULL, '', '48642bc6103b8ab15755d30e0d329c1aa535e7364025e6b47b1de753f35702d867fa34732cdabb4c', 1, '01/01/1990', 0),
(33, 'Francesca', 'francesca', NULL, 'female', 'Romania', 'francesca@qsmessenger.com', '113459eb7bb31bddee85ade5230d6ad5d8b2fb52879e00a84ff6ae1067a210d3', 3, NULL, '', '48642bc6103b8ab15755d30e0d329c1aa535e7364025e6b47b1de753f35702d867fa34732cdabb4c', 1, '01/01/1990', 0),
(34, 'Jacqueline', 'jacqueline', NULL, 'female', 'Romania', 'jacqueline@qsmessenger.com', '113459eb7bb31bddee85ade5230d6ad5d8b2fb52879e00a84ff6ae1067a210d3', 3, NULL, '', '48642bc6103b8ab15755d30e0d329c1aa535e7364025e6b47b1de753f35702d867fa34732cdabb4c', 1, '01/01/1990', 0),
(35, 'Gerald', 'gerald', NULL, 'male', 'Romania', 'gerald@qsmessenger.com', '113459eb7bb31bddee85ade5230d6ad5d8b2fb52879e00a84ff6ae1067a210d3', 0, NULL, '', '48642bc6103b8ab15755d30e0d329c1aa535e7364025e6b47b1de753f35702d867fa34732cdabb4c', 1, '01/01/1990', 0),
(36, 'Jordan', 'jordan', NULL, 'male', 'Romania', 'jordan@qsmessenger.com', '113459eb7bb31bddee85ade5230d6ad5d8b2fb52879e00a84ff6ae1067a210d3', 3, NULL, '', '48642bc6103b8ab15755d30e0d329c1aa535e7364025e6b47b1de753f35702d867fa34732cdabb4c', 1, '01/01/1990', 0),
(37, 'Stephan', 'stephan', NULL, 'male', 'Romania', 'stephan@qsmessenger.com', '113459eb7bb31bddee85ade5230d6ad5d8b2fb52879e00a84ff6ae1067a210d3', 3, NULL, '', '48642bc6103b8ab15755d30e0d329c1aa535e7364025e6b47b1de753f35702d867fa34732cdabb4c', 1, '01/01/1990', 0),
(38, 'Jonathan', 'jonathan', NULL, 'male', 'Romania', 'jonathan@qsmessenger.com', '113459eb7bb31bddee85ade5230d6ad5d8b2fb52879e00a84ff6ae1067a210d3', 1, NULL, '776f726b696e67', '48642bc6103b8ab15755d30e0d329c1aa535e7364025e6b47b1de753f35702d867fa34732cdabb4c', 1, '01/01/1990', 0),
(39, 'Eve', 'eve', NULL, 'female', 'Romania', 'eve@qsmessenger.com', '113459eb7bb31bddee85ade5230d6ad5d8b2fb52879e00a84ff6ae1067a210d3', 3, NULL, '', '48642bc6103b8ab15755d30e0d329c1aa535e7364025e6b47b1de753f35702d867fa34732cdabb4c', 1, '01/01/1990', 0),
(40, 'Samia', 'samia', NULL, 'female', 'Romania', 'samia@qsmessenger.com', '113459eb7bb31bddee85ade5230d6ad5d8b2fb52879e00a84ff6ae1067a210d3', 3, NULL, '', '48642bc6103b8ab15755d30e0d329c1aa535e7364025e6b47b1de753f35702d867fa34732cdabb4c', 1, '01/01/1990', 0),
(41, 'Jeff', 'jeff', NULL, 'male', 'Romania', 'jeff@qsmessenger.com', '113459eb7bb31bddee85ade5230d6ad5d8b2fb52879e00a84ff6ae1067a210d3', 1, NULL, '', '48642bc6103b8ab15755d30e0d329c1aa535e7364025e6b47b1de753f35702d867fa34732cdabb4c', 1, '01/01/1990', 0),
(42, 'Christian', 'christian', NULL, 'male', 'Romania', 'christian@qsmessenger.com', '113459eb7bb31bddee85ade5230d6ad5d8b2fb52879e00a84ff6ae1067a210d3', 2, NULL, '', '48642bc6103b8ab15755d30e0d329c1aa535e7364025e6b47b1de753f35702d867fa34732cdabb4c', 1, '01/01/1990', 0),
(43, 'Isabelle', 'isabelle', NULL, 'female', 'Romania', 'isabelle@qsmessenger.com', '113459eb7bb31bddee85ade5230d6ad5d8b2fb52879e00a84ff6ae1067a210d3', 3, NULL, '', '48642bc6103b8ab15755d30e0d329c1aa535e7364025e6b47b1de753f35702d867fa34732cdabb4c', 1, '01/01/1990', 0),
(44, 'Britney', 'britney', NULL, 'female', 'Romania', 'britney@qsmessenger.com', '113459eb7bb31bddee85ade5230d6ad5d8b2fb52879e00a84ff6ae1067a210d3', 3, NULL, '', '48642bc6103b8ab15755d30e0d329c1aa535e7364025e6b47b1de753f35702d867fa34732cdabb4c', 1, '01/01/1990', 0);

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
  MODIFY `id` int NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=4;

--
-- AUTO_INCREMENT for table `friends_list`
--
ALTER TABLE `friends_list`
  MODIFY `id` int NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=6;

--
-- AUTO_INCREMENT for table `messages`
--
ALTER TABLE `messages`
  MODIFY `id` int NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=12;

--
-- AUTO_INCREMENT for table `users`
--
ALTER TABLE `users`
  MODIFY `id` int NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=47;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
