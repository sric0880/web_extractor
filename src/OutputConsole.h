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
	OutputConsole(){
		f= fopen("output_console.txt","w");
	}
	virtual ~OutputConsole(){
		fclose(f);
	}
	void output(const Data& entry){
		if (entry.company != NULL)
			fprintf(f,"company:%s\n", entry.company);
		if (entry.position != NULL)
			fprintf(f,"position:%s ", entry.position);
		if (entry.publish_time != NULL)
			fprintf(f,"publish_time:%s\n", entry.publish_time);
		if (entry.workplace != NULL)
			fprintf(f,"workplace:%s\n", entry.workplace);
		if (entry.need_num != 0)
			fprintf(f,"need_num:%d\n", entry.need_num);
		if (entry.email != NULL)
			fprintf(f,"email:%s\n", entry.email);
		if (entry.tel != NULL)
			fprintf(f,"tel:%s\n", entry.tel);
		if (entry.skills != NULL)
			fprintf(f,"skills:%s\n", entry.skills);
		if(entry.raw_text!=NULL)
			fprintf(f,"raw_text:%s\n", entry.raw_text);
		if(urls[entry.id]!="")
			fprintf(f,"url:%s\n", urls[entry.id].c_str());
		fprintf(f,"\n");
	}
private:
	FILE * f;
};


#endif /* OUTPUTCONSOLE_H_ */
