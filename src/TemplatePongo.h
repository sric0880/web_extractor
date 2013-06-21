/*
 * TemplatePongo.h
 *
 *  Created on: 2013-5-27
 *      Author: qiong
 */

#ifndef TEMPLATEPONGO_H_
#define TEMPLATEPONGO_H_
#include "Template.h"

class TemplatePongo : public Template{
public:
	TemplatePongo();
	virtual ~TemplatePongo();
	void match_company(Data& entry, const string& str);
	void match_position(Data& entry, const string& str);
	void match_time(Data& entry, const string& str);
	void match_workplace(Data& entry, const string& str);
};

#endif /* TEMPLATEPONGO_H_ */
