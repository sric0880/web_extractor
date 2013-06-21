/*
 * OutputXml.h
 *
 *  Created on: 2013-5-24
 *      Author: qiong
 */

#ifndef OUTPUTMYSQL_H_
#define OUTPUTMYSQL_H_

#include "Output.h"
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/statement.h>
using namespace std;
using namespace sql::mysql;

class OutputMysql: public Output{
public:
	OutputMysql();
	virtual ~OutputMysql();
	void output(const Data& entry);
private:
	sql::Connection *con;
};


#endif /* OUTPUTMYSQL_H_ */
