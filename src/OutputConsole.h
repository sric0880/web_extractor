/*
 * OutputXml.h
 *
 *  Created on: 2013-5-24
 *      Author: qiong
 */

#ifndef OUTPUTCONSOLE_H_
#define OUTPUTCONSOLE_H_

#include "Output.h"

class OutputConsole: public Output{
public:
	void output(const Data& entry){
		if (entry.company != NULL)
			printf("company:%s\n", entry.company);
		if (entry.position != NULL)
			printf("position:%s\n", entry.position);
		if (entry.publish_time != NULL)
			printf("publish_time:%s\n", entry.publish_time);
		if (entry.workplace != NULL)
			printf("workplace:%s\n", entry.workplace);
		if (entry.need_num != 0)
			printf("need_num:%d\n", entry.need_num);
		if (entry.email != NULL)
			printf("email:%s\n", entry.email);
		if (entry.tel != NULL)
			printf("tel:%s\n", entry.tel);
		if (entry.skills != NULL)
			printf("skills:%s\n", entry.skills);
		if(entry.raw_text!=NULL)
			printf("raw_text:%s\n", entry.raw_text);
	}
};


#endif /* OUTPUTCONSOLE_H_ */
