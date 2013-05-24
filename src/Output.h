/*
 * Output.h
 *
 *  Created on: 2013-5-24
 *      Author: qiong
 */

#ifndef OUTPUT_H_
#define OUTPUT_H_
#include <string>
struct Data{
	const char* company;
	const char* position;
	const char* publish_time;
	const char* workplace;
	int need_num;
	const char* skills;
	const char* email;
	const char* raw_text;
};

class Output{
public:
	virtual void output(Data entry) =0;
};

#endif /* OUTPUT_H_ */
