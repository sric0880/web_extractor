/*
Navicat MySQL Data Transfer

Source Server         : conn
Source Server Version : 50611
Source Host           : localhost:3306
Source Database       : interninfo

Target Server Type    : MYSQL
Target Server Version : 50611
File Encoding         : 65001

Date: 2013-06-14 02:54:04
*/

SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for sedata
-- ----------------------------
DROP TABLE IF EXISTS `sedata`;
CREATE TABLE `sedata` (
  `com_name` varchar(50) DEFAULT NULL,
  `position` text,
  `skills` varchar(400) DEFAULT NULL,
  `email` char(255) DEFAULT NULL,
  `tel` char(255) DEFAULT NULL,
  `need_num` int(11) DEFAULT NULL,
  `workplace` varchar(50) DEFAULT NULL,
  `publish_time` date DEFAULT NULL,
  `raw_text` mediumtext,
  `url` char(100) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
