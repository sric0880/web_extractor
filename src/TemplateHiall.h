/*
 * TemplateHiall.h
 *
 *  Created on: 2013-5-24
 *      Author: qiong
 */

#ifndef TEMPLATEHIALL_H_
#define TEMPLATEHIALL_H_
#include "Template.h"

class TemplateHiall: public Template {
public:
	TemplateHiall();
	virtual ~TemplateHiall();
	void match_company(Data& entry,const string& str);
	void match_position(Data& entry,const string& str);
	void match_time(Data& entry,const string& str);
	void match_workplace(Data& entry,const string& str);
};

#endif /* TEMPLATEHIALL_H_ */
