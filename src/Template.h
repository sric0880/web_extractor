/*
 * Output.h
 *
 *  Created on: 2013-5-24
 *      Author: qiong
 */

#ifndef TEMPLATE_H_
#define TEMPLATE_H_
#include "DataEntry.h"
#include <string>
#include <string.h>
#include <boost/regex.hpp>
using namespace std;
using namespace boost;
class Template{
public:
	Template();
	virtual ~Template();
	virtual void match_time(Data& entry,const string& str);
	virtual void match_company(Data& entry,const string& str);
	virtual void match_position(Data& entry,const string& str);
	virtual void match_workplace(Data& entry,const string& str);
	virtual void match_need_num(Data& entry,const string& str);
	virtual void match_skills(Data& entry,const string& str);
	virtual void match_email(Data& entry,const string& str);
	virtual void match_tel(Data& entry,const string& str);
private:
	regex regex_email,regex_tel;
};

#endif /* TEMPLATE_H_ */
