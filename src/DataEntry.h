/*
 * DataEntry.h
 *
 *  Created on: 2013-5-24
 *      Author: qiong
 */

#ifndef DATAENTRY_H_
#define DATAENTRY_H_
#include <stdio.h>
struct Data{
	char* company;
	char* position;
	char* publish_time;
	char* workplace;
	int need_num;
	char* skills;
	char* email;
	char* tel;
	char* raw_text;
	Data(){
		company = NULL;
		email = NULL;
		need_num = 0;
		position = NULL;
		publish_time = NULL;
		raw_text = NULL;
		skills = NULL;
		tel = NULL;
		workplace = NULL;
	}
};
#endif /* DATAENTRY_H_ */
