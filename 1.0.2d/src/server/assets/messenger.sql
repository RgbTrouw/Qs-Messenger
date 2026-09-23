-- phpMyAdmin SQL Dump
-- version 4.9.5deb2
-- https://www.phpmyadmin.net/
--
-- Host: localhost:3306
-- Generation Time: Jan 05, 2026 at 04:18 AM
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
(13, NULL, NULL, 1, 'Friends', 'isabelle@qsmessenger.com', 'steve@qsmessenger.com'),
(14, NULL, NULL, 1, 'Friends', 'isabelle@qsmessenger.com', 'isabelle@qsmessenger.com'),
(15, NULL, NULL, 1, 'Friends', 'francesca@qsmessenger.com', 'isabelle@qsmessenger.com'),
(16, NULL, NULL, 1, 'Friends', 'francesca@qsmessenger.com', 'isabelle@qsmessenger.com'),
(17, NULL, NULL, 1, 'Friends', 'sara@qsmessenger.com', 'isabelle@qsmessenger.com'),
(18, NULL, NULL, 1, 'Work', 'sara@qsmessenger.com', 'steve@qsmessenger.com'),
(19, NULL, NULL, 1, 'Work', 'isabelle@qsmessenger.com', 'sara@qsmessenger.com'),
(20, NULL, NULL, 1, 'Friends', 'sara@qsmessenger.com', 'steve@qsmessenger.com'),
(21, NULL, NULL, 1, 'Friends', 'isabelle@qsmessenger.com', 'steve@qsmessenger.com');

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
(8, NULL, 'Friends', 'steve@qsmessenger.com,andrew@qsmessenger.com,samantha@qsmessenger.com,emma@qsmessenger.com,elizabeth@qsmessenger.com,jennifer@qsmessenger.com,monica@qsmessenger.com,smith@qsmessenger.com,peter@qsmessenger.com,margaret@qsmessenger.com,danielle@qsmessenger.com,kathy@qsmessenger.com,francesca@qsmessenger.com,jacqueline@qsmessenger.com,gerald@qsmessenger.com,jordan@qsmessenger.com,stephan@qsmessenger.com,jonathan@qsmessenger.com,eve@qsmessenger.com,samia@qsmessenger.com,jeff@qsmessenger.com,christian@qsmessenger.com,isabelle@qsmessenger.com,britney@qsmessenger.com', 'steve@qsmessenger.com'),
(24, NULL, 'Work', 'michael@qsmessenger.com,robert@qsmessenger.com,patricia@qsmessenger.com,jessica@qsmessenger.com,sandra@qsmessenger.com,stephanie@qsmessenger.com,laura@qsmessenger.com,anna@qsmessenger.com', 'steve@qsmessenger.com'),
(25, NULL, 'Gaming', 'amy@qsmessenger.com,thomas@qsmessenger.com,richard@qsmessenger.com,bob@qsmessenger.com,helen@qsmessenger.com,sara@qsmessenger.com,diana@qsmessenger.com,scottt@qsmessenger.com,arthur@qsmessenger.com,alice@qsmessenger.com', 'steve@qsmessenger.com'),
(26, NULL, 'Friends', 'steve@qsmessenger.com,andrew@qsmessenger.com,samantha@qsmessenger.com,emma@qsmessenger.com,elizabeth@qsmessenger.com,jennifer@qsmessenger.com,monica@qsmessenger.com,smith@qsmessenger.com,peter@qsmessenger.com,margaret@qsmessenger.com,danielle@qsmessenger.com,kathy@qsmessenger.com,francesca@qsmessenger.com,jacqueline@qsmessenger.com,gerald@qsmessenger.com,jordan@qsmessenger.com,stephan@qsmessenger.com,jonathan@qsmessenger.com,eve@qsmessenger.com,samia@qsmessenger.com,jeff@qsmessenger.com,christian@qsmessenger.com,isabelle@qsmessenger.com,britney@qsmessenger.com', 'andrew@qsmessenger.com'),
(27, NULL, 'Work', 'michael@qsmessenger.com,robert@qsmessenger.com,patricia@qsmessenger.com,jessica@qsmessenger.com,sandra@qsmessenger.com,stephanie@qsmessenger.com,laura@qsmessenger.com,anna@qsmessenger.com', 'andrew@qsmessenger.com'),
(28, NULL, 'Gaming', 'amy@qsmessenger.com,thomas@qsmessenger.com,richard@qsmessenger.com,bob@qsmessenger.com,helen@qsmessenger.com,sara@qsmessenger.com,diana@qsmessenger.com,scottt@qsmessenger.com,arthur@qsmessenger.com,alice@qsmessenger.com', 'andrew@qsmessenger.com'),
(29, NULL, 'Friends', 'steve@qsmessenger.com,andrew@qsmessenger.com,samantha@qsmessenger.com,emma@qsmessenger.com,elizabeth@qsmessenger.com,jennifer@qsmessenger.com,monica@qsmessenger.com,smith@qsmessenger.com,peter@qsmessenger.com,margaret@qsmessenger.com,danielle@qsmessenger.com,kathy@qsmessenger.com,francesca@qsmessenger.com,jacqueline@qsmessenger.com,gerald@qsmessenger.com,jordan@qsmessenger.com,stephan@qsmessenger.com,jonathan@qsmessenger.com,eve@qsmessenger.com,samia@qsmessenger.com,jeff@qsmessenger.com,christian@qsmessenger.com,isabelle@qsmessenger.com,britney@qsmessenger.com', 'britney@qsmessenger.com'),
(30, NULL, 'Work', 'michael@qsmessenger.com,robert@qsmessenger.com,patricia@qsmessenger.com,jessica@qsmessenger.com,sandra@qsmessenger.com,stephanie@qsmessenger.com,laura@qsmessenger.com,anna@qsmessenger.com', 'britney@qsmessenger.com'),
(31, NULL, 'Gaming', 'amy@qsmessenger.com,thomas@qsmessenger.com,richard@qsmessenger.com,bob@qsmessenger.com,helen@qsmessenger.com,sara@qsmessenger.com,diana@qsmessenger.com,scottt@qsmessenger.com,arthur@qsmessenger.com,alice@qsmessenger.com', 'britney@qsmessenger.com'),
(32, NULL, 'Friends', 'steve@qsmessenger.com,andrew@qsmessenger.com,samantha@qsmessenger.com,emma@qsmessenger.com,elizabeth@qsmessenger.com,jennifer@qsmessenger.com,monica@qsmessenger.com,smith@qsmessenger.com,peter@qsmessenger.com,margaret@qsmessenger.com,danielle@qsmessenger.com,kathy@qsmessenger.com,francesca@qsmessenger.com,jacqueline@qsmessenger.com,gerald@qsmessenger.com,jordan@qsmessenger.com,stephan@qsmessenger.com,jonathan@qsmessenger.com,eve@qsmessenger.com,samia@qsmessenger.com,jeff@qsmessenger.com,christian@qsmessenger.com,isabelle@qsmessenger.com,britney@qsmessenger.com', 'christian@qsmessenger.com'),
(33, NULL, 'Work', 'michael@qsmessenger.com,robert@qsmessenger.com,patricia@qsmessenger.com,jessica@qsmessenger.com,sandra@qsmessenger.com,stephanie@qsmessenger.com,laura@qsmessenger.com,anna@qsmessenger.com', 'christian@qsmessenger.com'),
(34, NULL, 'Gaming', 'amy@qsmessenger.com,thomas@qsmessenger.com,richard@qsmessenger.com,bob@qsmessenger.com,helen@qsmessenger.com,sara@qsmessenger.com,diana@qsmessenger.com,scottt@qsmessenger.com,arthur@qsmessenger.com,alice@qsmessenger.com', 'christian@qsmessenger.com'),
(35, NULL, 'Friends', 'steve@qsmessenger.com,andrew@qsmessenger.com,samantha@qsmessenger.com,emma@qsmessenger.com,elizabeth@qsmessenger.com,jennifer@qsmessenger.com,monica@qsmessenger.com,smith@qsmessenger.com,peter@qsmessenger.com,margaret@qsmessenger.com,danielle@qsmessenger.com,kathy@qsmessenger.com,francesca@qsmessenger.com,jacqueline@qsmessenger.com,gerald@qsmessenger.com,jordan@qsmessenger.com,stephan@qsmessenger.com,jonathan@qsmessenger.com,eve@qsmessenger.com,samia@qsmessenger.com,jeff@qsmessenger.com,christian@qsmessenger.com,isabelle@qsmessenger.com,britney@qsmessenger.com', 'danielle@qsmessenger.com'),
(36, NULL, 'Work', 'michael@qsmessenger.com,robert@qsmessenger.com,patricia@qsmessenger.com,jessica@qsmessenger.com,sandra@qsmessenger.com,stephanie@qsmessenger.com,laura@qsmessenger.com,anna@qsmessenger.com', 'danielle@qsmessenger.com'),
(37, NULL, 'Gaming', 'amy@qsmessenger.com,thomas@qsmessenger.com,richard@qsmessenger.com,bob@qsmessenger.com,helen@qsmessenger.com,sara@qsmessenger.com,diana@qsmessenger.com,scottt@qsmessenger.com,arthur@qsmessenger.com,alice@qsmessenger.com', 'danielle@qsmessenger.com'),
(38, NULL, 'Friends', 'steve@qsmessenger.com,andrew@qsmessenger.com,samantha@qsmessenger.com,emma@qsmessenger.com,elizabeth@qsmessenger.com,jennifer@qsmessenger.com,monica@qsmessenger.com,smith@qsmessenger.com,peter@qsmessenger.com,margaret@qsmessenger.com,danielle@qsmessenger.com,kathy@qsmessenger.com,francesca@qsmessenger.com,jacqueline@qsmessenger.com,gerald@qsmessenger.com,jordan@qsmessenger.com,stephan@qsmessenger.com,jonathan@qsmessenger.com,eve@qsmessenger.com,samia@qsmessenger.com,jeff@qsmessenger.com,christian@qsmessenger.com,isabelle@qsmessenger.com,britney@qsmessenger.com', 'elizabeth@qsmessenger.com'),
(39, NULL, 'Work', 'michael@qsmessenger.com,robert@qsmessenger.com,patricia@qsmessenger.com,jessica@qsmessenger.com,sandra@qsmessenger.com,stephanie@qsmessenger.com,laura@qsmessenger.com,anna@qsmessenger.com', 'elizabeth@qsmessenger.com'),
(40, NULL, 'Gaming', 'amy@qsmessenger.com,thomas@qsmessenger.com,richard@qsmessenger.com,bob@qsmessenger.com,helen@qsmessenger.com,sara@qsmessenger.com,diana@qsmessenger.com,scottt@qsmessenger.com,arthur@qsmessenger.com,alice@qsmessenger.com', 'elizabeth@qsmessenger.com'),
(41, NULL, 'Friends', 'steve@qsmessenger.com,andrew@qsmessenger.com,samantha@qsmessenger.com,emma@qsmessenger.com,elizabeth@qsmessenger.com,jennifer@qsmessenger.com,monica@qsmessenger.com,smith@qsmessenger.com,peter@qsmessenger.com,margaret@qsmessenger.com,danielle@qsmessenger.com,kathy@qsmessenger.com,francesca@qsmessenger.com,jacqueline@qsmessenger.com,gerald@qsmessenger.com,jordan@qsmessenger.com,stephan@qsmessenger.com,jonathan@qsmessenger.com,eve@qsmessenger.com,samia@qsmessenger.com,jeff@qsmessenger.com,christian@qsmessenger.com,isabelle@qsmessenger.com,britney@qsmessenger.com', 'emma@qsmessenger.com'),
(42, NULL, 'Work', 'michael@qsmessenger.com,robert@qsmessenger.com,patricia@qsmessenger.com,jessica@qsmessenger.com,sandra@qsmessenger.com,stephanie@qsmessenger.com,laura@qsmessenger.com,anna@qsmessenger.com', 'emma@qsmessenger.com'),
(43, NULL, 'Gaming', 'amy@qsmessenger.com,thomas@qsmessenger.com,richard@qsmessenger.com,bob@qsmessenger.com,helen@qsmessenger.com,sara@qsmessenger.com,diana@qsmessenger.com,scottt@qsmessenger.com,arthur@qsmessenger.com,alice@qsmessenger.com', 'emma@qsmessenger.com'),
(44, NULL, 'Friends', 'steve@qsmessenger.com,andrew@qsmessenger.com,samantha@qsmessenger.com,emma@qsmessenger.com,elizabeth@qsmessenger.com,jennifer@qsmessenger.com,monica@qsmessenger.com,smith@qsmessenger.com,peter@qsmessenger.com,margaret@qsmessenger.com,danielle@qsmessenger.com,kathy@qsmessenger.com,francesca@qsmessenger.com,jacqueline@qsmessenger.com,gerald@qsmessenger.com,jordan@qsmessenger.com,stephan@qsmessenger.com,jonathan@qsmessenger.com,eve@qsmessenger.com,samia@qsmessenger.com,jeff@qsmessenger.com,christian@qsmessenger.com,isabelle@qsmessenger.com,britney@qsmessenger.com', 'eve@qsmessenger.com'),
(45, NULL, 'Work', 'michael@qsmessenger.com,robert@qsmessenger.com,patricia@qsmessenger.com,jessica@qsmessenger.com,sandra@qsmessenger.com,stephanie@qsmessenger.com,laura@qsmessenger.com,anna@qsmessenger.com', 'eve@qsmessenger.com'),
(46, NULL, 'Gaming', 'amy@qsmessenger.com,thomas@qsmessenger.com,richard@qsmessenger.com,bob@qsmessenger.com,helen@qsmessenger.com,sara@qsmessenger.com,diana@qsmessenger.com,scottt@qsmessenger.com,arthur@qsmessenger.com,alice@qsmessenger.com', 'eve@qsmessenger.com'),
(47, NULL, 'Friends', 'steve@qsmessenger.com,andrew@qsmessenger.com,samantha@qsmessenger.com,emma@qsmessenger.com,elizabeth@qsmessenger.com,jennifer@qsmessenger.com,monica@qsmessenger.com,smith@qsmessenger.com,peter@qsmessenger.com,margaret@qsmessenger.com,danielle@qsmessenger.com,kathy@qsmessenger.com,francesca@qsmessenger.com,jacqueline@qsmessenger.com,gerald@qsmessenger.com,jordan@qsmessenger.com,stephan@qsmessenger.com,jonathan@qsmessenger.com,eve@qsmessenger.com,samia@qsmessenger.com,jeff@qsmessenger.com,christian@qsmessenger.com,isabelle@qsmessenger.com,britney@qsmessenger.com', 'francesca@qsmessenger.com'),
(48, NULL, 'Work', 'michael@qsmessenger.com,robert@qsmessenger.com,patricia@qsmessenger.com,jessica@qsmessenger.com,sandra@qsmessenger.com,stephanie@qsmessenger.com,laura@qsmessenger.com,anna@qsmessenger.com', 'francesca@qsmessenger.com'),
(49, NULL, 'Gaming', 'amy@qsmessenger.com,thomas@qsmessenger.com,richard@qsmessenger.com,bob@qsmessenger.com,helen@qsmessenger.com,sara@qsmessenger.com,diana@qsmessenger.com,scottt@qsmessenger.com,arthur@qsmessenger.com,alice@qsmessenger.com', 'francesca@qsmessenger.com'),
(50, NULL, 'Friends', 'steve@qsmessenger.com,andrew@qsmessenger.com,samantha@qsmessenger.com,emma@qsmessenger.com,elizabeth@qsmessenger.com,jennifer@qsmessenger.com,monica@qsmessenger.com,smith@qsmessenger.com,peter@qsmessenger.com,margaret@qsmessenger.com,danielle@qsmessenger.com,kathy@qsmessenger.com,francesca@qsmessenger.com,jacqueline@qsmessenger.com,gerald@qsmessenger.com,jordan@qsmessenger.com,stephan@qsmessenger.com,jonathan@qsmessenger.com,eve@qsmessenger.com,samia@qsmessenger.com,jeff@qsmessenger.com,christian@qsmessenger.com,isabelle@qsmessenger.com,britney@qsmessenger.com', 'gerald@qsmessenger.com'),
(51, NULL, 'Work', 'michael@qsmessenger.com,robert@qsmessenger.com,patricia@qsmessenger.com,jessica@qsmessenger.com,sandra@qsmessenger.com,stephanie@qsmessenger.com,laura@qsmessenger.com,anna@qsmessenger.com', 'gerald@qsmessenger.com'),
(52, NULL, 'Gaming', 'amy@qsmessenger.com,thomas@qsmessenger.com,richard@qsmessenger.com,bob@qsmessenger.com,helen@qsmessenger.com,sara@qsmessenger.com,diana@qsmessenger.com,scottt@qsmessenger.com,arthur@qsmessenger.com,alice@qsmessenger.com', 'gerald@qsmessenger.com'),
(53, NULL, 'Friends', 'steve@qsmessenger.com,andrew@qsmessenger.com,samantha@qsmessenger.com,emma@qsmessenger.com,elizabeth@qsmessenger.com,jennifer@qsmessenger.com,monica@qsmessenger.com,smith@qsmessenger.com,peter@qsmessenger.com,margaret@qsmessenger.com,danielle@qsmessenger.com,kathy@qsmessenger.com,francesca@qsmessenger.com,jacqueline@qsmessenger.com,gerald@qsmessenger.com,jordan@qsmessenger.com,stephan@qsmessenger.com,jonathan@qsmessenger.com,eve@qsmessenger.com,samia@qsmessenger.com,jeff@qsmessenger.com,christian@qsmessenger.com,isabelle@qsmessenger.com,britney@qsmessenger.com', 'isabelle@qsmessenger.com'),
(54, NULL, 'Work', 'michael@qsmessenger.com,robert@qsmessenger.com,patricia@qsmessenger.com,jessica@qsmessenger.com,sandra@qsmessenger.com,stephanie@qsmessenger.com,laura@qsmessenger.com,anna@qsmessenger.com', 'isabelle@qsmessenger.com'),
(55, NULL, 'Gaming', 'amy@qsmessenger.com,thomas@qsmessenger.com,richard@qsmessenger.com,bob@qsmessenger.com,helen@qsmessenger.com,sara@qsmessenger.com,diana@qsmessenger.com,scottt@qsmessenger.com,arthur@qsmessenger.com,alice@qsmessenger.com', 'isabelle@qsmessenger.com'),
(56, NULL, 'Friends', 'steve@qsmessenger.com,andrew@qsmessenger.com,samantha@qsmessenger.com,emma@qsmessenger.com,elizabeth@qsmessenger.com,jennifer@qsmessenger.com,monica@qsmessenger.com,smith@qsmessenger.com,peter@qsmessenger.com,margaret@qsmessenger.com,danielle@qsmessenger.com,kathy@qsmessenger.com,francesca@qsmessenger.com,jacqueline@qsmessenger.com,gerald@qsmessenger.com,jordan@qsmessenger.com,stephan@qsmessenger.com,jonathan@qsmessenger.com,eve@qsmessenger.com,samia@qsmessenger.com,jeff@qsmessenger.com,christian@qsmessenger.com,isabelle@qsmessenger.com,britney@qsmessenger.com', 'jacqueline@qsmessenger.com'),
(57, NULL, 'Work', 'michael@qsmessenger.com,robert@qsmessenger.com,patricia@qsmessenger.com,jessica@qsmessenger.com,sandra@qsmessenger.com,stephanie@qsmessenger.com,laura@qsmessenger.com,anna@qsmessenger.com', 'jacqueline@qsmessenger.com'),
(58, NULL, 'Gaming', 'amy@qsmessenger.com,thomas@qsmessenger.com,richard@qsmessenger.com,bob@qsmessenger.com,helen@qsmessenger.com,sara@qsmessenger.com,diana@qsmessenger.com,scottt@qsmessenger.com,arthur@qsmessenger.com,alice@qsmessenger.com', 'jacqueline@qsmessenger.com'),
(59, NULL, 'Friends', 'steve@qsmessenger.com,andrew@qsmessenger.com,samantha@qsmessenger.com,emma@qsmessenger.com,elizabeth@qsmessenger.com,jennifer@qsmessenger.com,monica@qsmessenger.com,smith@qsmessenger.com,peter@qsmessenger.com,margaret@qsmessenger.com,danielle@qsmessenger.com,kathy@qsmessenger.com,francesca@qsmessenger.com,jacqueline@qsmessenger.com,gerald@qsmessenger.com,jordan@qsmessenger.com,stephan@qsmessenger.com,jonathan@qsmessenger.com,eve@qsmessenger.com,samia@qsmessenger.com,jeff@qsmessenger.com,christian@qsmessenger.com,isabelle@qsmessenger.com,britney@qsmessenger.com', 'jeff@qsmessenger.com'),
(60, NULL, 'Work', 'michael@qsmessenger.com,robert@qsmessenger.com,patricia@qsmessenger.com,jessica@qsmessenger.com,sandra@qsmessenger.com,stephanie@qsmessenger.com,laura@qsmessenger.com,anna@qsmessenger.com', 'jeff@qsmessenger.com'),
(61, NULL, 'Gaming', 'amy@qsmessenger.com,thomas@qsmessenger.com,richard@qsmessenger.com,bob@qsmessenger.com,helen@qsmessenger.com,sara@qsmessenger.com,diana@qsmessenger.com,scottt@qsmessenger.com,arthur@qsmessenger.com,alice@qsmessenger.com', 'jeff@qsmessenger.com'),
(62, NULL, 'Friends', 'steve@qsmessenger.com,andrew@qsmessenger.com,samantha@qsmessenger.com,emma@qsmessenger.com,elizabeth@qsmessenger.com,jennifer@qsmessenger.com,monica@qsmessenger.com,smith@qsmessenger.com,peter@qsmessenger.com,margaret@qsmessenger.com,danielle@qsmessenger.com,kathy@qsmessenger.com,francesca@qsmessenger.com,jacqueline@qsmessenger.com,gerald@qsmessenger.com,jordan@qsmessenger.com,stephan@qsmessenger.com,jonathan@qsmessenger.com,eve@qsmessenger.com,samia@qsmessenger.com,jeff@qsmessenger.com,christian@qsmessenger.com,isabelle@qsmessenger.com,britney@qsmessenger.com', 'jennifer@qsmessenger.com'),
(63, NULL, 'Work', 'michael@qsmessenger.com,robert@qsmessenger.com,patricia@qsmessenger.com,jessica@qsmessenger.com,sandra@qsmessenger.com,stephanie@qsmessenger.com,laura@qsmessenger.com,anna@qsmessenger.com', 'jennifer@qsmessenger.com'),
(64, NULL, 'Gaming', 'amy@qsmessenger.com,thomas@qsmessenger.com,richard@qsmessenger.com,bob@qsmessenger.com,helen@qsmessenger.com,sara@qsmessenger.com,diana@qsmessenger.com,scottt@qsmessenger.com,arthur@qsmessenger.com,alice@qsmessenger.com', 'jennifer@qsmessenger.com'),
(65, NULL, 'Friends', 'steve@qsmessenger.com,andrew@qsmessenger.com,samantha@qsmessenger.com,emma@qsmessenger.com,elizabeth@qsmessenger.com,jennifer@qsmessenger.com,monica@qsmessenger.com,smith@qsmessenger.com,peter@qsmessenger.com,margaret@qsmessenger.com,danielle@qsmessenger.com,kathy@qsmessenger.com,francesca@qsmessenger.com,jacqueline@qsmessenger.com,gerald@qsmessenger.com,jordan@qsmessenger.com,stephan@qsmessenger.com,jonathan@qsmessenger.com,eve@qsmessenger.com,samia@qsmessenger.com,jeff@qsmessenger.com,christian@qsmessenger.com,isabelle@qsmessenger.com,britney@qsmessenger.com', 'jonathan@qsmessenger.com'),
(66, NULL, 'Work', 'michael@qsmessenger.com,robert@qsmessenger.com,patricia@qsmessenger.com,jessica@qsmessenger.com,sandra@qsmessenger.com,stephanie@qsmessenger.com,laura@qsmessenger.com,anna@qsmessenger.com', 'jonathan@qsmessenger.com'),
(67, NULL, 'Gaming', 'amy@qsmessenger.com,thomas@qsmessenger.com,richard@qsmessenger.com,bob@qsmessenger.com,helen@qsmessenger.com,sara@qsmessenger.com,diana@qsmessenger.com,scottt@qsmessenger.com,arthur@qsmessenger.com,alice@qsmessenger.com', 'jonathan@qsmessenger.com'),
(68, NULL, 'Friends', 'steve@qsmessenger.com,andrew@qsmessenger.com,samantha@qsmessenger.com,emma@qsmessenger.com,elizabeth@qsmessenger.com,jennifer@qsmessenger.com,monica@qsmessenger.com,smith@qsmessenger.com,peter@qsmessenger.com,margaret@qsmessenger.com,danielle@qsmessenger.com,kathy@qsmessenger.com,francesca@qsmessenger.com,jacqueline@qsmessenger.com,gerald@qsmessenger.com,jordan@qsmessenger.com,stephan@qsmessenger.com,jonathan@qsmessenger.com,eve@qsmessenger.com,samia@qsmessenger.com,jeff@qsmessenger.com,christian@qsmessenger.com,isabelle@qsmessenger.com,britney@qsmessenger.com', 'jordan@qsmessenger.com'),
(69, NULL, 'Work', 'michael@qsmessenger.com,robert@qsmessenger.com,patricia@qsmessenger.com,jessica@qsmessenger.com,sandra@qsmessenger.com,stephanie@qsmessenger.com,laura@qsmessenger.com,anna@qsmessenger.com', 'jordan@qsmessenger.com'),
(70, NULL, 'Gaming', 'amy@qsmessenger.com,thomas@qsmessenger.com,richard@qsmessenger.com,bob@qsmessenger.com,helen@qsmessenger.com,sara@qsmessenger.com,diana@qsmessenger.com,scottt@qsmessenger.com,arthur@qsmessenger.com,alice@qsmessenger.com', 'jordan@qsmessenger.com'),
(71, NULL, 'Friends', 'steve@qsmessenger.com,andrew@qsmessenger.com,samantha@qsmessenger.com,emma@qsmessenger.com,elizabeth@qsmessenger.com,jennifer@qsmessenger.com,monica@qsmessenger.com,smith@qsmessenger.com,peter@qsmessenger.com,margaret@qsmessenger.com,danielle@qsmessenger.com,kathy@qsmessenger.com,francesca@qsmessenger.com,jacqueline@qsmessenger.com,gerald@qsmessenger.com,jordan@qsmessenger.com,stephan@qsmessenger.com,jonathan@qsmessenger.com,eve@qsmessenger.com,samia@qsmessenger.com,jeff@qsmessenger.com,christian@qsmessenger.com,isabelle@qsmessenger.com,britney@qsmessenger.com', 'kathy@qsmessenger.com'),
(72, NULL, 'Work', 'michael@qsmessenger.com,robert@qsmessenger.com,patricia@qsmessenger.com,jessica@qsmessenger.com,sandra@qsmessenger.com,stephanie@qsmessenger.com,laura@qsmessenger.com,anna@qsmessenger.com', 'kathy@qsmessenger.com'),
(73, NULL, 'Gaming', 'amy@qsmessenger.com,thomas@qsmessenger.com,richard@qsmessenger.com,bob@qsmessenger.com,helen@qsmessenger.com,sara@qsmessenger.com,diana@qsmessenger.com,scottt@qsmessenger.com,arthur@qsmessenger.com,alice@qsmessenger.com', 'kathy@qsmessenger.com'),
(74, NULL, 'Friends', 'steve@qsmessenger.com,andrew@qsmessenger.com,samantha@qsmessenger.com,emma@qsmessenger.com,elizabeth@qsmessenger.com,jennifer@qsmessenger.com,monica@qsmessenger.com,smith@qsmessenger.com,peter@qsmessenger.com,margaret@qsmessenger.com,danielle@qsmessenger.com,kathy@qsmessenger.com,francesca@qsmessenger.com,jacqueline@qsmessenger.com,gerald@qsmessenger.com,jordan@qsmessenger.com,stephan@qsmessenger.com,jonathan@qsmessenger.com,eve@qsmessenger.com,samia@qsmessenger.com,jeff@qsmessenger.com,christian@qsmessenger.com,isabelle@qsmessenger.com,britney@qsmessenger.com', 'margaret@qsmessenger.com'),
(75, NULL, 'Work', 'michael@qsmessenger.com,robert@qsmessenger.com,patricia@qsmessenger.com,jessica@qsmessenger.com,sandra@qsmessenger.com,stephanie@qsmessenger.com,laura@qsmessenger.com,anna@qsmessenger.com', 'margaret@qsmessenger.com'),
(76, NULL, 'Gaming', 'amy@qsmessenger.com,thomas@qsmessenger.com,richard@qsmessenger.com,bob@qsmessenger.com,helen@qsmessenger.com,sara@qsmessenger.com,diana@qsmessenger.com,scottt@qsmessenger.com,arthur@qsmessenger.com,alice@qsmessenger.com', 'margaret@qsmessenger.com'),
(77, NULL, 'Friends', 'steve@qsmessenger.com,andrew@qsmessenger.com,samantha@qsmessenger.com,emma@qsmessenger.com,elizabeth@qsmessenger.com,jennifer@qsmessenger.com,monica@qsmessenger.com,smith@qsmessenger.com,peter@qsmessenger.com,margaret@qsmessenger.com,danielle@qsmessenger.com,kathy@qsmessenger.com,francesca@qsmessenger.com,jacqueline@qsmessenger.com,gerald@qsmessenger.com,jordan@qsmessenger.com,stephan@qsmessenger.com,jonathan@qsmessenger.com,eve@qsmessenger.com,samia@qsmessenger.com,jeff@qsmessenger.com,christian@qsmessenger.com,isabelle@qsmessenger.com,britney@qsmessenger.com', 'monica@qsmessenger.com'),
(78, NULL, 'Work', 'michael@qsmessenger.com,robert@qsmessenger.com,patricia@qsmessenger.com,jessica@qsmessenger.com,sandra@qsmessenger.com,stephanie@qsmessenger.com,laura@qsmessenger.com,anna@qsmessenger.com', 'monica@qsmessenger.com'),
(79, NULL, 'Gaming', 'amy@qsmessenger.com,thomas@qsmessenger.com,richard@qsmessenger.com,bob@qsmessenger.com,helen@qsmessenger.com,sara@qsmessenger.com,diana@qsmessenger.com,scottt@qsmessenger.com,arthur@qsmessenger.com,alice@qsmessenger.com', 'monica@qsmessenger.com'),
(80, NULL, 'Friends', 'steve@qsmessenger.com,andrew@qsmessenger.com,samantha@qsmessenger.com,emma@qsmessenger.com,elizabeth@qsmessenger.com,jennifer@qsmessenger.com,monica@qsmessenger.com,smith@qsmessenger.com,peter@qsmessenger.com,margaret@qsmessenger.com,danielle@qsmessenger.com,kathy@qsmessenger.com,francesca@qsmessenger.com,jacqueline@qsmessenger.com,gerald@qsmessenger.com,jordan@qsmessenger.com,stephan@qsmessenger.com,jonathan@qsmessenger.com,eve@qsmessenger.com,samia@qsmessenger.com,jeff@qsmessenger.com,christian@qsmessenger.com,isabelle@qsmessenger.com,britney@qsmessenger.com', 'peter@qsmessenger.com'),
(81, NULL, 'Work', 'michael@qsmessenger.com,robert@qsmessenger.com,patricia@qsmessenger.com,jessica@qsmessenger.com,sandra@qsmessenger.com,stephanie@qsmessenger.com,laura@qsmessenger.com,anna@qsmessenger.com', 'peter@qsmessenger.com'),
(82, NULL, 'Gaming', 'amy@qsmessenger.com,thomas@qsmessenger.com,richard@qsmessenger.com,bob@qsmessenger.com,helen@qsmessenger.com,sara@qsmessenger.com,diana@qsmessenger.com,scottt@qsmessenger.com,arthur@qsmessenger.com,alice@qsmessenger.com', 'peter@qsmessenger.com'),
(83, NULL, 'Friends', 'steve@qsmessenger.com,andrew@qsmessenger.com,samantha@qsmessenger.com,emma@qsmessenger.com,elizabeth@qsmessenger.com,jennifer@qsmessenger.com,monica@qsmessenger.com,smith@qsmessenger.com,peter@qsmessenger.com,margaret@qsmessenger.com,danielle@qsmessenger.com,kathy@qsmessenger.com,francesca@qsmessenger.com,jacqueline@qsmessenger.com,gerald@qsmessenger.com,jordan@qsmessenger.com,stephan@qsmessenger.com,jonathan@qsmessenger.com,eve@qsmessenger.com,samia@qsmessenger.com,jeff@qsmessenger.com,christian@qsmessenger.com,isabelle@qsmessenger.com,britney@qsmessenger.com', 'samantha@qsmessenger.com'),
(84, NULL, 'Work', 'michael@qsmessenger.com,robert@qsmessenger.com,patricia@qsmessenger.com,jessica@qsmessenger.com,sandra@qsmessenger.com,stephanie@qsmessenger.com,laura@qsmessenger.com,anna@qsmessenger.com', 'samantha@qsmessenger.com'),
(85, NULL, 'Gaming', 'amy@qsmessenger.com,thomas@qsmessenger.com,richard@qsmessenger.com,bob@qsmessenger.com,helen@qsmessenger.com,sara@qsmessenger.com,diana@qsmessenger.com,scottt@qsmessenger.com,arthur@qsmessenger.com,alice@qsmessenger.com', 'samantha@qsmessenger.com'),
(86, NULL, 'Friends', 'steve@qsmessenger.com,andrew@qsmessenger.com,samantha@qsmessenger.com,emma@qsmessenger.com,elizabeth@qsmessenger.com,jennifer@qsmessenger.com,monica@qsmessenger.com,smith@qsmessenger.com,peter@qsmessenger.com,margaret@qsmessenger.com,danielle@qsmessenger.com,kathy@qsmessenger.com,francesca@qsmessenger.com,jacqueline@qsmessenger.com,gerald@qsmessenger.com,jordan@qsmessenger.com,stephan@qsmessenger.com,jonathan@qsmessenger.com,eve@qsmessenger.com,samia@qsmessenger.com,jeff@qsmessenger.com,christian@qsmessenger.com,isabelle@qsmessenger.com,britney@qsmessenger.com', 'samia@qsmessenger.com'),
(87, NULL, 'Work', 'michael@qsmessenger.com,robert@qsmessenger.com,patricia@qsmessenger.com,jessica@qsmessenger.com,sandra@qsmessenger.com,stephanie@qsmessenger.com,laura@qsmessenger.com,anna@qsmessenger.com', 'samia@qsmessenger.com'),
(88, NULL, 'Gaming', 'amy@qsmessenger.com,thomas@qsmessenger.com,richard@qsmessenger.com,bob@qsmessenger.com,helen@qsmessenger.com,sara@qsmessenger.com,diana@qsmessenger.com,scottt@qsmessenger.com,arthur@qsmessenger.com,alice@qsmessenger.com', 'samia@qsmessenger.com'),
(89, NULL, 'Friends', 'steve@qsmessenger.com,andrew@qsmessenger.com,samantha@qsmessenger.com,emma@qsmessenger.com,elizabeth@qsmessenger.com,jennifer@qsmessenger.com,monica@qsmessenger.com,smith@qsmessenger.com,peter@qsmessenger.com,margaret@qsmessenger.com,danielle@qsmessenger.com,kathy@qsmessenger.com,francesca@qsmessenger.com,jacqueline@qsmessenger.com,gerald@qsmessenger.com,jordan@qsmessenger.com,stephan@qsmessenger.com,jonathan@qsmessenger.com,eve@qsmessenger.com,samia@qsmessenger.com,jeff@qsmessenger.com,christian@qsmessenger.com,isabelle@qsmessenger.com,britney@qsmessenger.com', 'smith@qsmessenger.com'),
(90, NULL, 'Work', 'michael@qsmessenger.com,robert@qsmessenger.com,patricia@qsmessenger.com,jessica@qsmessenger.com,sandra@qsmessenger.com,stephanie@qsmessenger.com,laura@qsmessenger.com,anna@qsmessenger.com', 'smith@qsmessenger.com'),
(91, NULL, 'Gaming', 'amy@qsmessenger.com,thomas@qsmessenger.com,richard@qsmessenger.com,bob@qsmessenger.com,helen@qsmessenger.com,sara@qsmessenger.com,diana@qsmessenger.com,scottt@qsmessenger.com,arthur@qsmessenger.com,alice@qsmessenger.com', 'smith@qsmessenger.com'),
(92, NULL, 'Friends', 'steve@qsmessenger.com,andrew@qsmessenger.com,samantha@qsmessenger.com,emma@qsmessenger.com,elizabeth@qsmessenger.com,jennifer@qsmessenger.com,monica@qsmessenger.com,smith@qsmessenger.com,peter@qsmessenger.com,margaret@qsmessenger.com,danielle@qsmessenger.com,kathy@qsmessenger.com,francesca@qsmessenger.com,jacqueline@qsmessenger.com,gerald@qsmessenger.com,jordan@qsmessenger.com,stephan@qsmessenger.com,jonathan@qsmessenger.com,eve@qsmessenger.com,samia@qsmessenger.com,jeff@qsmessenger.com,christian@qsmessenger.com,isabelle@qsmessenger.com,britney@qsmessenger.com', 'stephanie@qsmessenger.com'),
(93, NULL, 'Work', 'michael@qsmessenger.com,robert@qsmessenger.com,patricia@qsmessenger.com,jessica@qsmessenger.com,sandra@qsmessenger.com,stephanie@qsmessenger.com,laura@qsmessenger.com,anna@qsmessenger.com', 'stephanie@qsmessenger.com'),
(94, NULL, 'Gaming', 'amy@qsmessenger.com,thomas@qsmessenger.com,richard@qsmessenger.com,bob@qsmessenger.com,helen@qsmessenger.com,sara@qsmessenger.com,diana@qsmessenger.com,scottt@qsmessenger.com,arthur@qsmessenger.com,alice@qsmessenger.com', 'stephanie@qsmessenger.com'),
(95, NULL, 'Friends', 'steve@qsmessenger.com,andrew@qsmessenger.com,samantha@qsmessenger.com,emma@qsmessenger.com,elizabeth@qsmessenger.com,jennifer@qsmessenger.com,monica@qsmessenger.com,smith@qsmessenger.com,peter@qsmessenger.com,margaret@qsmessenger.com,danielle@qsmessenger.com,kathy@qsmessenger.com,francesca@qsmessenger.com,jacqueline@qsmessenger.com,gerald@qsmessenger.com,jordan@qsmessenger.com,stephan@qsmessenger.com,jonathan@qsmessenger.com,eve@qsmessenger.com,samia@qsmessenger.com,jeff@qsmessenger.com,christian@qsmessenger.com,isabelle@qsmessenger.com,britney@qsmessenger.com', 'stephan@qsmessenger.com'),
(96, NULL, 'Work', 'michael@qsmessenger.com,robert@qsmessenger.com,patricia@qsmessenger.com,jessica@qsmessenger.com,sandra@qsmessenger.com,stephanie@qsmessenger.com,laura@qsmessenger.com,anna@qsmessenger.com', 'stephan@qsmessenger.com'),
(97, NULL, 'Gaming', 'amy@qsmessenger.com,thomas@qsmessenger.com,richard@qsmessenger.com,bob@qsmessenger.com,helen@qsmessenger.com,sara@qsmessenger.com,diana@qsmessenger.com,scottt@qsmessenger.com,arthur@qsmessenger.com,alice@qsmessenger.com', 'stephan@qsmessenger.com'),
(98, NULL, 'Friends', 'steve@qsmessenger.com,andrew@qsmessenger.com,samantha@qsmessenger.com,emma@qsmessenger.com,elizabeth@qsmessenger.com,jennifer@qsmessenger.com,monica@qsmessenger.com,smith@qsmessenger.com,peter@qsmessenger.com,margaret@qsmessenger.com,danielle@qsmessenger.com,kathy@qsmessenger.com,francesca@qsmessenger.com,jacqueline@qsmessenger.com,gerald@qsmessenger.com,jordan@qsmessenger.com,stephan@qsmessenger.com,jonathan@qsmessenger.com,eve@qsmessenger.com,samia@qsmessenger.com,jeff@qsmessenger.com,christian@qsmessenger.com,isabelle@qsmessenger.com,britney@qsmessenger.com', 'anna@qsmessenger.com'),
(99, NULL, 'Work', 'michael@qsmessenger.com,robert@qsmessenger.com,patricia@qsmessenger.com,jessica@qsmessenger.com,sandra@qsmessenger.com,stephanie@qsmessenger.com,laura@qsmessenger.com,anna@qsmessenger.com', 'anna@qsmessenger.com'),
(100, NULL, 'Gaming', 'amy@qsmessenger.com,thomas@qsmessenger.com,richard@qsmessenger.com,bob@qsmessenger.com,helen@qsmessenger.com,sara@qsmessenger.com,diana@qsmessenger.com,scottt@qsmessenger.com,arthur@qsmessenger.com,alice@qsmessenger.com', 'anna@qsmessenger.com'),
(101, NULL, 'Friends', 'steve@qsmessenger.com,andrew@qsmessenger.com,samantha@qsmessenger.com,emma@qsmessenger.com,elizabeth@qsmessenger.com,jennifer@qsmessenger.com,monica@qsmessenger.com,smith@qsmessenger.com,peter@qsmessenger.com,margaret@qsmessenger.com,danielle@qsmessenger.com,kathy@qsmessenger.com,francesca@qsmessenger.com,jacqueline@qsmessenger.com,gerald@qsmessenger.com,jordan@qsmessenger.com,stephan@qsmessenger.com,jonathan@qsmessenger.com,eve@qsmessenger.com,samia@qsmessenger.com,jeff@qsmessenger.com,christian@qsmessenger.com,isabelle@qsmessenger.com,britney@qsmessenger.com', 'jessica@qsmessenger.com'),
(102, NULL, 'Work', 'michael@qsmessenger.com,robert@qsmessenger.com,patricia@qsmessenger.com,jessica@qsmessenger.com,sandra@qsmessenger.com,stephanie@qsmessenger.com,laura@qsmessenger.com,anna@qsmessenger.com', 'jessica@qsmessenger.com'),
(103, NULL, 'Gaming', 'amy@qsmessenger.com,thomas@qsmessenger.com,richard@qsmessenger.com,bob@qsmessenger.com,helen@qsmessenger.com,sara@qsmessenger.com,diana@qsmessenger.com,scottt@qsmessenger.com,arthur@qsmessenger.com,alice@qsmessenger.com', 'jessica@qsmessenger.com'),
(104, NULL, 'Friends', 'steve@qsmessenger.com,andrew@qsmessenger.com,samantha@qsmessenger.com,emma@qsmessenger.com,elizabeth@qsmessenger.com,jennifer@qsmessenger.com,monica@qsmessenger.com,smith@qsmessenger.com,peter@qsmessenger.com,margaret@qsmessenger.com,danielle@qsmessenger.com,kathy@qsmessenger.com,francesca@qsmessenger.com,jacqueline@qsmessenger.com,gerald@qsmessenger.com,jordan@qsmessenger.com,stephan@qsmessenger.com,jonathan@qsmessenger.com,eve@qsmessenger.com,samia@qsmessenger.com,jeff@qsmessenger.com,christian@qsmessenger.com,isabelle@qsmessenger.com,britney@qsmessenger.com', 'laura@qsmessenger.com'),
(105, NULL, 'Work', 'michael@qsmessenger.com,robert@qsmessenger.com,patricia@qsmessenger.com,jessica@qsmessenger.com,sandra@qsmessenger.com,stephanie@qsmessenger.com,laura@qsmessenger.com,anna@qsmessenger.com', 'laura@qsmessenger.com'),
(106, NULL, 'Gaming', 'amy@qsmessenger.com,thomas@qsmessenger.com,richard@qsmessenger.com,bob@qsmessenger.com,helen@qsmessenger.com,sara@qsmessenger.com,diana@qsmessenger.com,scottt@qsmessenger.com,arthur@qsmessenger.com,alice@qsmessenger.com', 'laura@qsmessenger.com'),
(107, NULL, 'Friends', 'steve@qsmessenger.com,andrew@qsmessenger.com,samantha@qsmessenger.com,emma@qsmessenger.com,elizabeth@qsmessenger.com,jennifer@qsmessenger.com,monica@qsmessenger.com,smith@qsmessenger.com,peter@qsmessenger.com,margaret@qsmessenger.com,danielle@qsmessenger.com,kathy@qsmessenger.com,francesca@qsmessenger.com,jacqueline@qsmessenger.com,gerald@qsmessenger.com,jordan@qsmessenger.com,stephan@qsmessenger.com,jonathan@qsmessenger.com,eve@qsmessenger.com,samia@qsmessenger.com,jeff@qsmessenger.com,christian@qsmessenger.com,isabelle@qsmessenger.com,britney@qsmessenger.com', 'michael@qsmessenger.com'),
(108, NULL, 'Work', 'michael@qsmessenger.com,robert@qsmessenger.com,patricia@qsmessenger.com,jessica@qsmessenger.com,sandra@qsmessenger.com,stephanie@qsmessenger.com,laura@qsmessenger.com,anna@qsmessenger.com', 'michael@qsmessenger.com'),
(109, NULL, 'Gaming', 'amy@qsmessenger.com,thomas@qsmessenger.com,richard@qsmessenger.com,bob@qsmessenger.com,helen@qsmessenger.com,sara@qsmessenger.com,diana@qsmessenger.com,scottt@qsmessenger.com,arthur@qsmessenger.com,alice@qsmessenger.com', 'michael@qsmessenger.com'),
(110, NULL, 'Friends', 'steve@qsmessenger.com,andrew@qsmessenger.com,samantha@qsmessenger.com,emma@qsmessenger.com,elizabeth@qsmessenger.com,jennifer@qsmessenger.com,monica@qsmessenger.com,smith@qsmessenger.com,peter@qsmessenger.com,margaret@qsmessenger.com,danielle@qsmessenger.com,kathy@qsmessenger.com,francesca@qsmessenger.com,jacqueline@qsmessenger.com,gerald@qsmessenger.com,jordan@qsmessenger.com,stephan@qsmessenger.com,jonathan@qsmessenger.com,eve@qsmessenger.com,samia@qsmessenger.com,jeff@qsmessenger.com,christian@qsmessenger.com,isabelle@qsmessenger.com,britney@qsmessenger.com', 'patricia@qsmessenger.com'),
(111, NULL, 'Work', 'michael@qsmessenger.com,robert@qsmessenger.com,patricia@qsmessenger.com,jessica@qsmessenger.com,sandra@qsmessenger.com,stephanie@qsmessenger.com,laura@qsmessenger.com,anna@qsmessenger.com', 'patricia@qsmessenger.com'),
(112, NULL, 'Gaming', 'amy@qsmessenger.com,thomas@qsmessenger.com,richard@qsmessenger.com,bob@qsmessenger.com,helen@qsmessenger.com,sara@qsmessenger.com,diana@qsmessenger.com,scottt@qsmessenger.com,arthur@qsmessenger.com,alice@qsmessenger.com', 'patricia@qsmessenger.com'),
(113, NULL, 'Friends', 'steve@qsmessenger.com,andrew@qsmessenger.com,samantha@qsmessenger.com,emma@qsmessenger.com,elizabeth@qsmessenger.com,jennifer@qsmessenger.com,monica@qsmessenger.com,smith@qsmessenger.com,peter@qsmessenger.com,margaret@qsmessenger.com,danielle@qsmessenger.com,kathy@qsmessenger.com,francesca@qsmessenger.com,jacqueline@qsmessenger.com,gerald@qsmessenger.com,jordan@qsmessenger.com,stephan@qsmessenger.com,jonathan@qsmessenger.com,eve@qsmessenger.com,samia@qsmessenger.com,jeff@qsmessenger.com,christian@qsmessenger.com,isabelle@qsmessenger.com,britney@qsmessenger.com', 'robert@qsmessenger.com'),
(114, NULL, 'Work', 'michael@qsmessenger.com,robert@qsmessenger.com,patricia@qsmessenger.com,jessica@qsmessenger.com,sandra@qsmessenger.com,stephanie@qsmessenger.com,laura@qsmessenger.com,anna@qsmessenger.com', 'robert@qsmessenger.com'),
(115, NULL, 'Gaming', 'amy@qsmessenger.com,thomas@qsmessenger.com,richard@qsmessenger.com,bob@qsmessenger.com,helen@qsmessenger.com,sara@qsmessenger.com,diana@qsmessenger.com,scottt@qsmessenger.com,arthur@qsmessenger.com,alice@qsmessenger.com', 'robert@qsmessenger.com'),
(116, NULL, 'Friends', 'steve@qsmessenger.com,andrew@qsmessenger.com,samantha@qsmessenger.com,emma@qsmessenger.com,elizabeth@qsmessenger.com,jennifer@qsmessenger.com,monica@qsmessenger.com,smith@qsmessenger.com,peter@qsmessenger.com,margaret@qsmessenger.com,danielle@qsmessenger.com,kathy@qsmessenger.com,francesca@qsmessenger.com,jacqueline@qsmessenger.com,gerald@qsmessenger.com,jordan@qsmessenger.com,stephan@qsmessenger.com,jonathan@qsmessenger.com,eve@qsmessenger.com,samia@qsmessenger.com,jeff@qsmessenger.com,christian@qsmessenger.com,isabelle@qsmessenger.com,britney@qsmessenger.com', 'sandra@qsmessenger.com'),
(117, NULL, 'Work', 'michael@qsmessenger.com,robert@qsmessenger.com,patricia@qsmessenger.com,jessica@qsmessenger.com,sandra@qsmessenger.com,stephanie@qsmessenger.com,laura@qsmessenger.com,anna@qsmessenger.com', 'sandra@qsmessenger.com'),
(118, NULL, 'Gaming', 'amy@qsmessenger.com,thomas@qsmessenger.com,richard@qsmessenger.com,bob@qsmessenger.com,helen@qsmessenger.com,sara@qsmessenger.com,diana@qsmessenger.com,scottt@qsmessenger.com,arthur@qsmessenger.com,alice@qsmessenger.com', 'sandra@qsmessenger.com'),
(119, NULL, 'Friends', 'steve@qsmessenger.com,andrew@qsmessenger.com,samantha@qsmessenger.com,emma@qsmessenger.com,elizabeth@qsmessenger.com,jennifer@qsmessenger.com,monica@qsmessenger.com,smith@qsmessenger.com,peter@qsmessenger.com,margaret@qsmessenger.com,danielle@qsmessenger.com,kathy@qsmessenger.com,francesca@qsmessenger.com,jacqueline@qsmessenger.com,gerald@qsmessenger.com,jordan@qsmessenger.com,stephan@qsmessenger.com,jonathan@qsmessenger.com,eve@qsmessenger.com,samia@qsmessenger.com,jeff@qsmessenger.com,christian@qsmessenger.com,isabelle@qsmessenger.com,britney@qsmessenger.com', 'alice@qsmessenger.com'),
(120, NULL, 'Work', 'michael@qsmessenger.com,robert@qsmessenger.com,patricia@qsmessenger.com,jessica@qsmessenger.com,sandra@qsmessenger.com,stephanie@qsmessenger.com,laura@qsmessenger.com,anna@qsmessenger.com', 'alice@qsmessenger.com'),
(121, NULL, 'Gaming', 'amy@qsmessenger.com,thomas@qsmessenger.com,richard@qsmessenger.com,bob@qsmessenger.com,helen@qsmessenger.com,sara@qsmessenger.com,diana@qsmessenger.com,scottt@qsmessenger.com,arthur@qsmessenger.com,alice@qsmessenger.com', 'alice@qsmessenger.com'),
(122, NULL, 'Friends', 'steve@qsmessenger.com,andrew@qsmessenger.com,samantha@qsmessenger.com,emma@qsmessenger.com,elizabeth@qsmessenger.com,jennifer@qsmessenger.com,monica@qsmessenger.com,smith@qsmessenger.com,peter@qsmessenger.com,margaret@qsmessenger.com,danielle@qsmessenger.com,kathy@qsmessenger.com,francesca@qsmessenger.com,jacqueline@qsmessenger.com,gerald@qsmessenger.com,jordan@qsmessenger.com,stephan@qsmessenger.com,jonathan@qsmessenger.com,eve@qsmessenger.com,samia@qsmessenger.com,jeff@qsmessenger.com,christian@qsmessenger.com,isabelle@qsmessenger.com,britney@qsmessenger.com', 'amy@qsmessenger.com'),
(123, NULL, 'Work', 'michael@qsmessenger.com,robert@qsmessenger.com,patricia@qsmessenger.com,jessica@qsmessenger.com,sandra@qsmessenger.com,stephanie@qsmessenger.com,laura@qsmessenger.com,anna@qsmessenger.com', 'amy@qsmessenger.com'),
(124, NULL, 'Gaming', 'amy@qsmessenger.com,thomas@qsmessenger.com,richard@qsmessenger.com,bob@qsmessenger.com,helen@qsmessenger.com,sara@qsmessenger.com,diana@qsmessenger.com,scottt@qsmessenger.com,arthur@qsmessenger.com,alice@qsmessenger.com', 'amy@qsmessenger.com'),
(125, NULL, 'Friends', 'steve@qsmessenger.com,andrew@qsmessenger.com,samantha@qsmessenger.com,emma@qsmessenger.com,elizabeth@qsmessenger.com,jennifer@qsmessenger.com,monica@qsmessenger.com,smith@qsmessenger.com,peter@qsmessenger.com,margaret@qsmessenger.com,danielle@qsmessenger.com,kathy@qsmessenger.com,francesca@qsmessenger.com,jacqueline@qsmessenger.com,gerald@qsmessenger.com,jordan@qsmessenger.com,stephan@qsmessenger.com,jonathan@qsmessenger.com,eve@qsmessenger.com,samia@qsmessenger.com,jeff@qsmessenger.com,christian@qsmessenger.com,isabelle@qsmessenger.com,britney@qsmessenger.com', 'arthur@qsmessenger.com'),
(126, NULL, 'Work', 'michael@qsmessenger.com,robert@qsmessenger.com,patricia@qsmessenger.com,jessica@qsmessenger.com,sandra@qsmessenger.com,stephanie@qsmessenger.com,laura@qsmessenger.com,anna@qsmessenger.com', 'arthur@qsmessenger.com'),
(127, NULL, 'Gaming', 'amy@qsmessenger.com,thomas@qsmessenger.com,richard@qsmessenger.com,bob@qsmessenger.com,helen@qsmessenger.com,sara@qsmessenger.com,diana@qsmessenger.com,scottt@qsmessenger.com,arthur@qsmessenger.com,alice@qsmessenger.com', 'arthur@qsmessenger.com'),
(128, NULL, 'Friends', 'steve@qsmessenger.com,andrew@qsmessenger.com,samantha@qsmessenger.com,emma@qsmessenger.com,elizabeth@qsmessenger.com,jennifer@qsmessenger.com,monica@qsmessenger.com,smith@qsmessenger.com,peter@qsmessenger.com,margaret@qsmessenger.com,danielle@qsmessenger.com,kathy@qsmessenger.com,francesca@qsmessenger.com,jacqueline@qsmessenger.com,gerald@qsmessenger.com,jordan@qsmessenger.com,stephan@qsmessenger.com,jonathan@qsmessenger.com,eve@qsmessenger.com,samia@qsmessenger.com,jeff@qsmessenger.com,christian@qsmessenger.com,isabelle@qsmessenger.com,britney@qsmessenger.com', 'bob@qsmessenger.com'),
(129, NULL, 'Work', 'michael@qsmessenger.com,robert@qsmessenger.com,patricia@qsmessenger.com,jessica@qsmessenger.com,sandra@qsmessenger.com,stephanie@qsmessenger.com,laura@qsmessenger.com,anna@qsmessenger.com', 'bob@qsmessenger.com'),
(130, NULL, 'Gaming', 'amy@qsmessenger.com,thomas@qsmessenger.com,richard@qsmessenger.com,bob@qsmessenger.com,helen@qsmessenger.com,sara@qsmessenger.com,diana@qsmessenger.com,scottt@qsmessenger.com,arthur@qsmessenger.com,alice@qsmessenger.com', 'bob@qsmessenger.com'),
(131, NULL, 'Friends', 'steve@qsmessenger.com,andrew@qsmessenger.com,samantha@qsmessenger.com,emma@qsmessenger.com,elizabeth@qsmessenger.com,jennifer@qsmessenger.com,monica@qsmessenger.com,smith@qsmessenger.com,peter@qsmessenger.com,margaret@qsmessenger.com,danielle@qsmessenger.com,kathy@qsmessenger.com,francesca@qsmessenger.com,jacqueline@qsmessenger.com,gerald@qsmessenger.com,jordan@qsmessenger.com,stephan@qsmessenger.com,jonathan@qsmessenger.com,eve@qsmessenger.com,samia@qsmessenger.com,jeff@qsmessenger.com,christian@qsmessenger.com,isabelle@qsmessenger.com,britney@qsmessenger.com', 'diana@qsmessenger.com'),
(132, NULL, 'Work', 'michael@qsmessenger.com,robert@qsmessenger.com,patricia@qsmessenger.com,jessica@qsmessenger.com,sandra@qsmessenger.com,stephanie@qsmessenger.com,laura@qsmessenger.com,anna@qsmessenger.com', 'diana@qsmessenger.com'),
(133, NULL, 'Gaming', 'amy@qsmessenger.com,thomas@qsmessenger.com,richard@qsmessenger.com,bob@qsmessenger.com,helen@qsmessenger.com,sara@qsmessenger.com,diana@qsmessenger.com,scottt@qsmessenger.com,arthur@qsmessenger.com,alice@qsmessenger.com', 'diana@qsmessenger.com'),
(134, NULL, 'Friends', 'steve@qsmessenger.com,andrew@qsmessenger.com,samantha@qsmessenger.com,emma@qsmessenger.com,elizabeth@qsmessenger.com,jennifer@qsmessenger.com,monica@qsmessenger.com,smith@qsmessenger.com,peter@qsmessenger.com,margaret@qsmessenger.com,danielle@qsmessenger.com,kathy@qsmessenger.com,francesca@qsmessenger.com,jacqueline@qsmessenger.com,gerald@qsmessenger.com,jordan@qsmessenger.com,stephan@qsmessenger.com,jonathan@qsmessenger.com,eve@qsmessenger.com,samia@qsmessenger.com,jeff@qsmessenger.com,christian@qsmessenger.com,isabelle@qsmessenger.com,britney@qsmessenger.com', 'helen@qsmessenger.com'),
(135, NULL, 'Work', 'michael@qsmessenger.com,robert@qsmessenger.com,patricia@qsmessenger.com,jessica@qsmessenger.com,sandra@qsmessenger.com,stephanie@qsmessenger.com,laura@qsmessenger.com,anna@qsmessenger.com', 'helen@qsmessenger.com'),
(136, NULL, 'Gaming', 'amy@qsmessenger.com,thomas@qsmessenger.com,richard@qsmessenger.com,bob@qsmessenger.com,helen@qsmessenger.com,sara@qsmessenger.com,diana@qsmessenger.com,scottt@qsmessenger.com,arthur@qsmessenger.com,alice@qsmessenger.com', 'helen@qsmessenger.com'),
(137, NULL, 'Friends', 'steve@qsmessenger.com,andrew@qsmessenger.com,samantha@qsmessenger.com,emma@qsmessenger.com,elizabeth@qsmessenger.com,jennifer@qsmessenger.com,monica@qsmessenger.com,smith@qsmessenger.com,peter@qsmessenger.com,margaret@qsmessenger.com,danielle@qsmessenger.com,kathy@qsmessenger.com,francesca@qsmessenger.com,jacqueline@qsmessenger.com,gerald@qsmessenger.com,jordan@qsmessenger.com,stephan@qsmessenger.com,jonathan@qsmessenger.com,eve@qsmessenger.com,samia@qsmessenger.com,jeff@qsmessenger.com,christian@qsmessenger.com,isabelle@qsmessenger.com,britney@qsmessenger.com', 'richard@qsmessenger.com'),
(138, NULL, 'Work', 'michael@qsmessenger.com,robert@qsmessenger.com,patricia@qsmessenger.com,jessica@qsmessenger.com,sandra@qsmessenger.com,stephanie@qsmessenger.com,laura@qsmessenger.com,anna@qsmessenger.com', 'richard@qsmessenger.com'),
(139, NULL, 'Gaming', 'amy@qsmessenger.com,thomas@qsmessenger.com,richard@qsmessenger.com,bob@qsmessenger.com,helen@qsmessenger.com,sara@qsmessenger.com,diana@qsmessenger.com,scottt@qsmessenger.com,arthur@qsmessenger.com,alice@qsmessenger.com', 'richard@qsmessenger.com'),
(140, NULL, 'Friends', 'steve@qsmessenger.com,andrew@qsmessenger.com,samantha@qsmessenger.com,emma@qsmessenger.com,elizabeth@qsmessenger.com,jennifer@qsmessenger.com,monica@qsmessenger.com,smith@qsmessenger.com,peter@qsmessenger.com,margaret@qsmessenger.com,danielle@qsmessenger.com,kathy@qsmessenger.com,francesca@qsmessenger.com,jacqueline@qsmessenger.com,gerald@qsmessenger.com,jordan@qsmessenger.com,stephan@qsmessenger.com,jonathan@qsmessenger.com,eve@qsmessenger.com,samia@qsmessenger.com,jeff@qsmessenger.com,christian@qsmessenger.com,isabelle@qsmessenger.com,britney@qsmessenger.com', 'sara@qsmessenger.com'),
(141, NULL, 'Work', 'michael@qsmessenger.com,robert@qsmessenger.com,patricia@qsmessenger.com,jessica@qsmessenger.com,sandra@qsmessenger.com,stephanie@qsmessenger.com,laura@qsmessenger.com,anna@qsmessenger.com', 'sara@qsmessenger.com'),
(142, NULL, 'Gaming', 'amy@qsmessenger.com,thomas@qsmessenger.com,richard@qsmessenger.com,bob@qsmessenger.com,helen@qsmessenger.com,sara@qsmessenger.com,diana@qsmessenger.com,scottt@qsmessenger.com,arthur@qsmessenger.com,alice@qsmessenger.com', 'sara@qsmessenger.com'),
(143, NULL, 'Friends', 'steve@qsmessenger.com,andrew@qsmessenger.com,samantha@qsmessenger.com,emma@qsmessenger.com,elizabeth@qsmessenger.com,jennifer@qsmessenger.com,monica@qsmessenger.com,smith@qsmessenger.com,peter@qsmessenger.com,margaret@qsmessenger.com,danielle@qsmessenger.com,kathy@qsmessenger.com,francesca@qsmessenger.com,jacqueline@qsmessenger.com,gerald@qsmessenger.com,jordan@qsmessenger.com,stephan@qsmessenger.com,jonathan@qsmessenger.com,eve@qsmessenger.com,samia@qsmessenger.com,jeff@qsmessenger.com,christian@qsmessenger.com,isabelle@qsmessenger.com,britney@qsmessenger.com', 'thomas@qsmessenger.com'),
(144, NULL, 'Work', 'michael@qsmessenger.com,robert@qsmessenger.com,patricia@qsmessenger.com,jessica@qsmessenger.com,sandra@qsmessenger.com,stephanie@qsmessenger.com,laura@qsmessenger.com,anna@qsmessenger.com', 'thomas@qsmessenger.com'),
(145, NULL, 'Gaming', 'amy@qsmessenger.com,thomas@qsmessenger.com,richard@qsmessenger.com,bob@qsmessenger.com,helen@qsmessenger.com,sara@qsmessenger.com,diana@qsmessenger.com,scottt@qsmessenger.com,arthur@qsmessenger.com,alice@qsmessenger.com', 'thomas@qsmessenger.com');

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
  `toEmail` text NOT NULL,
  `ownerEmail` text NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `messages`
--

INSERT INTO `messages` (`id`, `msg_from`, `msg_to`, `txt_message`, `time`, `has_read`, `server_sent`, `read_time`, `fromEmail`, `toEmail`, `ownerEmail`) VALUES
(471, NULL, NULL, '3c64696e673e', 1767576908077, 1, 1, 1767576913393, 'isabelle@qsmessenger.com', 'sara@qsmessenger.com', 'isabelle@qsmessenger.com'),
(472, NULL, NULL, '3c64696e673e', 1767576908077, 1, 1, 1767576913393, 'isabelle@qsmessenger.com', 'sara@qsmessenger.com', 'sara@qsmessenger.com');

-- --------------------------------------------------------

--
-- Table structure for table `settings`
--

CREATE TABLE `settings` (
  `id` int NOT NULL,
  `ownerEmail` text NOT NULL,
  `property` text NOT NULL,
  `value` text NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

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
(1, 'Steve', 'steve', NULL, 'male', '', 'steve@qsmessenger.com', 'aeb90a944c71f3ea003df498f7870dc5441b67496501756321927e4b26585d21', 1, NULL, '', '48642bc6103b8ab15755d30e0d329c1aa535e7364025e6b47b1de753f35702d867fa34732cdabb4c', 1, '01/01/1990', 1767577939606),
(3, 'Andrew', 'andrew', NULL, 'male', '', 'andrew@qsmessenger.com', 'aeb90a944c71f3ea003df498f7870dc5441b67496501756321927e4b26585d21', 3, NULL, '', '48642bc6103b8ab15755d30e0d329c1aa535e7364025e6b47b1de753f35702d867fa34732cdabb4c', 1, '01/01/1990', 0),
(4, 'Samantha', 'samantha', NULL, 'female', '', 'samantha@qsmessenger.com', 'aeb90a944c71f3ea003df498f7870dc5441b67496501756321927e4b26585d21', 3, NULL, '', '48642bc6103b8ab15755d30e0d329c1aa535e7364025e6b47b1de753f35702d867fa34732cdabb4c', 1, '01/01/1990', 0),
(5, 'Emma', 'emma', NULL, 'female', '', 'emma@qsmessenger.com', 'aeb90a944c71f3ea003df498f7870dc5441b67496501756321927e4b26585d21', 3, NULL, '', '48642bc6103b8ab15755d30e0d329c1aa535e7364025e6b47b1de753f35702d867fa34732cdabb4c', 1, '01/01/1990', 0),
(6, 'Elizabeth', 'elizabeth', NULL, 'female', '', 'elizabeth@qsmessenger.com', 'aeb90a944c71f3ea003df498f7870dc5441b67496501756321927e4b26585d21', 3, NULL, '', '48642bc6103b8ab15755d30e0d329c1aa535e7364025e6b47b1de753f35702d867fa34732cdabb4c', 1, '01/01/1990', 0),
(7, 'Jennifer', 'jennifer', NULL, 'female', '', 'jennifer@qsmessenger.com', 'aeb90a944c71f3ea003df498f7870dc5441b67496501756321927e4b26585d21', 3, NULL, '', '48642bc6103b8ab15755d30e0d329c1aa535e7364025e6b47b1de753f35702d867fa34732cdabb4c', 1, '01/01/1990', 0),
(8, 'Monica', 'monica', NULL, 'female', '', 'monica@qsmessenger.com', 'aeb90a944c71f3ea003df498f7870dc5441b67496501756321927e4b26585d21', 3, NULL, '', '48642bc6103b8ab15755d30e0d329c1aa535e7364025e6b47b1de753f35702d867fa34732cdabb4c', 1, '01/01/1990', 0),
(9, 'Smith', 'smith', NULL, 'male', '', 'smith@qsmessenger.com', 'aeb90a944c71f3ea003df498f7870dc5441b67496501756321927e4b26585d21', 3, NULL, '', '48642bc6103b8ab15755d30e0d329c1aa535e7364025e6b47b1de753f35702d867fa34732cdabb4c', 1, '01/01/1990', 0),
(10, 'Peter', 'peter', NULL, 'male', '', 'peter@qsmessenger.com', 'aeb90a944c71f3ea003df498f7870dc5441b67496501756321927e4b26585d21', 3, NULL, '', '48642bc6103b8ab15755d30e0d329c1aa535e7364025e6b47b1de753f35702d867fa34732cdabb4c', 1, '01/01/1990', 0),
(11, 'Margaret', 'margaret', NULL, 'female', '', 'margaret@qsmessenger.com', 'aeb90a944c71f3ea003df498f7870dc5441b67496501756321927e4b26585d21', 3, NULL, '', '48642bc6103b8ab15755d30e0d329c1aa535e7364025e6b47b1de753f35702d867fa34732cdabb4c', 1, '01/01/1990', 0),
(12, 'Amy', 'amy', NULL, 'female', '', 'amy@qsmessenger.com', 'aeb90a944c71f3ea003df498f7870dc5441b67496501756321927e4b26585d21', 3, NULL, '', '48642bc6103b8ab15755d30e0d329c1aa535e7364025e6b47b1de753f35702d867fa34732cdabb4c', 1, '01/01/1990', 0),
(13, 'Thomas', 'thomas', NULL, 'male', '', 'thomas@qsmessenger.com', 'aeb90a944c71f3ea003df498f7870dc5441b67496501756321927e4b26585d21', 3, NULL, '', '48642bc6103b8ab15755d30e0d329c1aa535e7364025e6b47b1de753f35702d867fa34732cdabb4c', 1, '01/01/1990', 0),
(14, 'Richard', 'richard', NULL, 'male', '', 'richard@qsmessenger.com', 'aeb90a944c71f3ea003df498f7870dc5441b67496501756321927e4b26585d21', 3, NULL, '', '48642bc6103b8ab15755d30e0d329c1aa535e7364025e6b47b1de753f35702d867fa34732cdabb4c', 1, '01/01/1990', 0),
(15, 'Bob', 'bob', NULL, 'male', '', 'bob@qsmessenger.com', 'aeb90a944c71f3ea003df498f7870dc5441b67496501756321927e4b26585d21', 3, NULL, '', '48642bc6103b8ab15755d30e0d329c1aa535e7364025e6b47b1de753f35702d867fa34732cdabb4c', 1, '01/01/1990', 1767463085263),
(16, 'Michael', 'michael', NULL, 'male', '', 'michael@qsmessenger.com', 'aeb90a944c71f3ea003df498f7870dc5441b67496501756321927e4b26585d21', 3, NULL, '', '48642bc6103b8ab15755d30e0d329c1aa535e7364025e6b47b1de753f35702d867fa34732cdabb4c', 1, '01/01/1990', 0),
(17, 'Robert', 'robert', NULL, 'male', '', 'robert@qsmessenger.com', 'aeb90a944c71f3ea003df498f7870dc5441b67496501756321927e4b26585d21', 3, NULL, '', '48642bc6103b8ab15755d30e0d329c1aa535e7364025e6b47b1de753f35702d867fa34732cdabb4c', 1, '01/01/1990', 0),
(18, 'Patricia', 'patricia', NULL, 'female', '', 'patricia@qsmessenger.com', 'aeb90a944c71f3ea003df498f7870dc5441b67496501756321927e4b26585d21', 3, NULL, '', '48642bc6103b8ab15755d30e0d329c1aa535e7364025e6b47b1de753f35702d867fa34732cdabb4c', 1, '01/01/1990', 0),
(19, 'Jessica', 'jessica', NULL, 'female', '', 'jessica@qsmessenger.com', 'aeb90a944c71f3ea003df498f7870dc5441b67496501756321927e4b26585d21', 3, NULL, '', '48642bc6103b8ab15755d30e0d329c1aa535e7364025e6b47b1de753f35702d867fa34732cdabb4c', 1, '01/01/1990', 0),
(20, 'Sandra', 'sandra', NULL, 'female', '', 'sandra@qsmessenger.com', 'aeb90a944c71f3ea003df498f7870dc5441b67496501756321927e4b26585d21', 3, NULL, '', '48642bc6103b8ab15755d30e0d329c1aa535e7364025e6b47b1de753f35702d867fa34732cdabb4c', 1, '01/01/1990', 0),
(21, 'Stephanie', 'stephanie', NULL, 'female', '', 'stephanie@qsmessenger.com', 'aeb90a944c71f3ea003df498f7870dc5441b67496501756321927e4b26585d21', 3, NULL, '', '48642bc6103b8ab15755d30e0d329c1aa535e7364025e6b47b1de753f35702d867fa34732cdabb4c', 1, '01/01/1990', 0),
(22, 'Laura', 'laura', NULL, 'female', '', 'laura@qsmessenger.com', 'aeb90a944c71f3ea003df498f7870dc5441b67496501756321927e4b26585d21', 3, NULL, '', '48642bc6103b8ab15755d30e0d329c1aa535e7364025e6b47b1de753f35702d867fa34732cdabb4c', 1, '01/01/1990', 0),
(23, 'Anna', 'anna', NULL, 'female', '', 'anna@qsmessenger.com', 'aeb90a944c71f3ea003df498f7870dc5441b67496501756321927e4b26585d21', 3, NULL, '', '48642bc6103b8ab15755d30e0d329c1aa535e7364025e6b47b1de753f35702d867fa34732cdabb4c', 1, '01/01/1990', 0),
(24, 'Helen', 'helen', NULL, 'female', '', 'helen@qsmessenger.com', 'aeb90a944c71f3ea003df498f7870dc5441b67496501756321927e4b26585d21', 3, NULL, '', '48642bc6103b8ab15755d30e0d329c1aa535e7364025e6b47b1de753f35702d867fa34732cdabb4c', 1, '01/01/1990', 0),
(25, 'Sara', 'sara', NULL, 'female', '', 'sara@qsmessenger.com', 'aeb90a944c71f3ea003df498f7870dc5441b67496501756321927e4b26585d21', 3, NULL, '', '48642bc6103b8ab15755d30e0d329c1aa535e7364025e6b47b1de753f35702d867fa34732cdabb4c', 1, '01/01/1990', 1767576566635),
(26, 'Diana', 'diana', NULL, 'female', '', 'diana@qsmessenger.com', 'aeb90a944c71f3ea003df498f7870dc5441b67496501756321927e4b26585d21', 3, NULL, '', '48642bc6103b8ab15755d30e0d329c1aa535e7364025e6b47b1de753f35702d867fa34732cdabb4c', 1, '01/01/1990', 1767403775470),
(27, 'Scott', 'scott', NULL, 'male', '', 'scott@qsmessenger.com', 'aeb90a944c71f3ea003df498f7870dc5441b67496501756321927e4b26585d21', 3, NULL, '', '48642bc6103b8ab15755d30e0d329c1aa535e7364025e6b47b1de753f35702d867fa34732cdabb4c', 1, '01/01/1990', 0),
(28, 'Arthur', 'arthur', NULL, 'male', '', 'arthur@qsmessenger.com', 'aeb90a944c71f3ea003df498f7870dc5441b67496501756321927e4b26585d21', 3, NULL, '', '48642bc6103b8ab15755d30e0d329c1aa535e7364025e6b47b1de753f35702d867fa34732cdabb4c', 1, '01/01/1990', 0),
(29, 'Alice', 'alice', NULL, 'female', '', 'alice@qsmessenger.com', 'aeb90a944c71f3ea003df498f7870dc5441b67496501756321927e4b26585d21', 3, NULL, '', '48642bc6103b8ab15755d30e0d329c1aa535e7364025e6b47b1de753f35702d867fa34732cdabb4c', 1, '01/01/1990', 0),
(31, 'Danielle', 'danielle', NULL, 'female', '', 'danielle@qsmessenger.com', 'aeb90a944c71f3ea003df498f7870dc5441b67496501756321927e4b26585d21', 3, NULL, '', '48642bc6103b8ab15755d30e0d329c1aa535e7364025e6b47b1de753f35702d867fa34732cdabb4c', 1, '01/01/1990', 0),
(32, 'Kathy', 'kathy', NULL, 'female', '', 'kathy@qsmessenger.com', 'aeb90a944c71f3ea003df498f7870dc5441b67496501756321927e4b26585d21', 3, NULL, '', '48642bc6103b8ab15755d30e0d329c1aa535e7364025e6b47b1de753f35702d867fa34732cdabb4c', 1, '01/01/1990', 0),
(33, 'Francesca', 'francesca', NULL, 'female', '', 'francesca@qsmessenger.com', 'aeb90a944c71f3ea003df498f7870dc5441b67496501756321927e4b26585d21', 3, NULL, '', '48642bc6103b8ab15755d30e0d329c1aa535e7364025e6b47b1de753f35702d867fa34732cdabb4c', 1, '01/01/1990', 1767388997581),
(34, 'Jacqueline', 'jacqueline', NULL, 'female', '', 'jacqueline@qsmessenger.com', 'aeb90a944c71f3ea003df498f7870dc5441b67496501756321927e4b26585d21', 3, NULL, '', '48642bc6103b8ab15755d30e0d329c1aa535e7364025e6b47b1de753f35702d867fa34732cdabb4c', 1, '01/01/1990', 0),
(35, 'Gerald', 'gerald', NULL, 'male', '', 'gerald@qsmessenger.com', 'aeb90a944c71f3ea003df498f7870dc5441b67496501756321927e4b26585d21', 3, NULL, '', '48642bc6103b8ab15755d30e0d329c1aa535e7364025e6b47b1de753f35702d867fa34732cdabb4c', 1, '01/01/1990', 0),
(36, 'Jordan', 'jordan', NULL, 'male', '', 'jordan@qsmessenger.com', 'aeb90a944c71f3ea003df498f7870dc5441b67496501756321927e4b26585d21', 3, NULL, '', '48642bc6103b8ab15755d30e0d329c1aa535e7364025e6b47b1de753f35702d867fa34732cdabb4c', 1, '01/01/1990', 0),
(37, 'Stephan', 'stephan', NULL, 'male', '', 'stephan@qsmessenger.com', 'aeb90a944c71f3ea003df498f7870dc5441b67496501756321927e4b26585d21', 3, NULL, '', '48642bc6103b8ab15755d30e0d329c1aa535e7364025e6b47b1de753f35702d867fa34732cdabb4c', 1, '01/01/1990', 0),
(38, 'Jonathan', 'jonathan', NULL, 'male', '', 'jonathan@qsmessenger.com', 'aeb90a944c71f3ea003df498f7870dc5441b67496501756321927e4b26585d21', 3, NULL, '', '48642bc6103b8ab15755d30e0d329c1aa535e7364025e6b47b1de753f35702d867fa34732cdabb4c', 1, '01/01/1990', 0),
(39, 'Eve', 'eve', NULL, 'female', '', 'eve@qsmessenger.com', 'aeb90a944c71f3ea003df498f7870dc5441b67496501756321927e4b26585d21', 3, NULL, '', '48642bc6103b8ab15755d30e0d329c1aa535e7364025e6b47b1de753f35702d867fa34732cdabb4c', 1, '01/01/1990', 0),
(40, 'Samia', 'samia', NULL, 'female', '', 'samia@qsmessenger.com', 'aeb90a944c71f3ea003df498f7870dc5441b67496501756321927e4b26585d21', 3, NULL, '', '48642bc6103b8ab15755d30e0d329c1aa535e7364025e6b47b1de753f35702d867fa34732cdabb4c', 1, '01/01/1990', 0),
(41, 'Jeff', 'jeff', NULL, 'male', '', 'jeff@qsmessenger.com', 'aeb90a944c71f3ea003df498f7870dc5441b67496501756321927e4b26585d21', 3, NULL, '', '48642bc6103b8ab15755d30e0d329c1aa535e7364025e6b47b1de753f35702d867fa34732cdabb4c', 1, '01/01/1990', 0),
(42, 'Christian', 'christian', NULL, 'male', '', 'christian@qsmessenger.com', 'aeb90a944c71f3ea003df498f7870dc5441b67496501756321927e4b26585d21', 3, NULL, '', '48642bc6103b8ab15755d30e0d329c1aa535e7364025e6b47b1de753f35702d867fa34732cdabb4c', 1, '01/01/1990', 0),
(43, 'Isabelle', 'isabelle', NULL, 'female', '', 'isabelle@qsmessenger.com', 'aeb90a944c71f3ea003df498f7870dc5441b67496501756321927e4b26585d21', 3, NULL, '', '48642bc6103b8ab15755d30e0d329c1aa535e7364025e6b47b1de753f35702d867fa34732cdabb4c', 1, '01/01/1990', 1767576541874),
(44, 'Britney', 'britney', NULL, 'female', '', 'britney@qsmessenger.com', 'aeb90a944c71f3ea003df498f7870dc5441b67496501756321927e4b26585d21', 3, NULL, '', '48642bc6103b8ab15755d30e0d329c1aa535e7364025e6b47b1de753f35702d867fa34732cdabb4c', 1, '01/01/1990', 0);

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
-- Indexes for table `settings`
--
ALTER TABLE `settings`
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
  MODIFY `id` int NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=22;

--
-- AUTO_INCREMENT for table `friends_list`
--
ALTER TABLE `friends_list`
  MODIFY `id` int NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=146;

--
-- AUTO_INCREMENT for table `messages`
--
ALTER TABLE `messages`
  MODIFY `id` int NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=473;

--
-- AUTO_INCREMENT for table `settings`
--
ALTER TABLE `settings`
  MODIFY `id` int NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT for table `users`
--
ALTER TABLE `users`
  MODIFY `id` int NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=49;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
