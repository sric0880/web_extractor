/*
 * OutputMysql.cpp
 *
 *  Created on: 2013-5-28
 *      Author: qiong
 */
#include "OutputMysql.h"

OutputMysql::OutputMysql(){
	MySQL_Driver *driver;
	driver = get_mysql_driver_instance();// 初始化驱动
	con = driver->connect("tcp://127.0.0.1:3306", "root", "");// 建立链接
	sql::Statement *stmt = con->createStatement();
	stmt->execute("use interninfo");
}

OutputMysql::~OutputMysql(){
	delete con;
}

void OutputMysql::output(const Data& entry) {
	sql::PreparedStatement * prep_stmt;
	prep_stmt= con->prepareStatement("INSERT INTO sedata (com_name,position,skills,email,tel,need_num,workplace,publish_time,raw_text,url) VALUES (?,?,?,?,?,?,?,?,?,?)");
	if (entry.company != NULL)
		prep_stmt->setString(1, entry.company);
	else
		prep_stmt->setString(1, "");
	if (entry.position != NULL){
		prep_stmt->setString(2, entry.position);
	}
	else
		prep_stmt->setString(2, "");
	if (entry.skills != NULL){
		prep_stmt->setString(3, entry.skills);
	}
	else
		prep_stmt->setString(3, "");
	if (entry.email != NULL)
		prep_stmt->setString(4, entry.email);
	else
		prep_stmt->setString(4, "");
	if (entry.tel != NULL)
		prep_stmt->setString(5, entry.tel);
	else
		prep_stmt->setString(5, "");
	if (entry.need_num != 0)
		prep_stmt->setInt(6, entry.need_num);
	else
		prep_stmt->setInt(6, 0);
	if (entry.workplace != NULL)
		prep_stmt->setString(7, entry.workplace);
	else
		prep_stmt->setString(7, "");
	if (entry.publish_time != NULL)
		prep_stmt->setString(8, entry.publish_time);
	else
		prep_stmt->setString(8, "");
	if (entry.raw_text != NULL)
		prep_stmt->setString(9, entry.raw_text);
	else
		prep_stmt->setString(9, "");
	prep_stmt->setString(10, urls[entry.id]);
	//插入
	prep_stmt->executeUpdate();
	delete prep_stmt;
}
