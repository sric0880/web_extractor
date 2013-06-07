/*
 * InfoExtractor.cpp
 *
 *  Created on: 2013-5-24
 *      Author: qiong
 */

#include "InfoExtractor.h"

InfoExtractor::InfoExtractor(Output* out,Template* temt):
out(out),temt(temt){}

InfoExtractor::~InfoExtractor() {
}

void InfoExtractor::infoExtract(int url_id, string input){
	string title;
	string text;
	int pos = input.find_first_of('^');
	title=input.substr(0,pos);
	int len = input.length()-pos;
	text=input.substr(pos+1,len);
	// printf("title:%s.\ntext:%s\n",title.c_str(),text.c_str());

	Data entry;
	// printf("match_time intern info!\n");
	temt->match_time(entry,text);
	// printf("match_workplace intern info!\n");
	temt->match_workplace(entry,text);
	// printf("match_email intern info!\n");
	temt->match_email(entry,text);
	// if (entry.email != NULL)
	// 	printf("email:%s\n", entry.email);
	// else
	// 	printf("email:%s\n", "null");
	temt->match_tel(entry,text);
	// printf("match_need_num intern info!\n");
	temt->match_need_num(entry,text);
	// printf("match_position intern info!\n");
	temt->match_position(entry,input);
	// if (entry.position != NULL)
	// 	printf("position:%s\n", entry.position);
	// else
	// 	printf("position:%s\n", "null");
	temt->match_company(entry,title);
	// if (entry.company != NULL)
	// 	printf("company:%s\n", entry.company);
	// else
	// 	printf("company:%s\n", "null");
	temt->match_skills(entry,text);
//	printf("raw_text intern info!\n");
	entry.raw_text = new char[input.length()+1];
	strcpy(entry.raw_text,input.c_str());
	entry.id = url_id;

	//主题分类判断是不是计算机实习信息
	if(entry.company==NULL&&entry.position==NULL){
		printf("%d:not intern info!\n",entry.id);
		return;
	}else{
		if(dup_removal.is_duplicate(entry.tostring()))//消重
		{
			printf("%d:duplication\n",entry.id);
		}else{
			printf("%d:output\n", entry.id);
			out->output(entry);//结构化数据输出
			release(entry);
		}
	}
}

void InfoExtractor::release(Data & entry){
	if (entry.company != NULL)
		delete []entry.company;
	if (entry.position != NULL)
		delete []entry.position;
	if (entry.publish_time != NULL)
		delete []entry.publish_time;
	if (entry.workplace != NULL)
		delete []entry.workplace;
	if (entry.email != NULL)
		delete []entry.email;
	if (entry.tel != NULL)
		delete []entry.tel;
	if (entry.skills != NULL)
		delete []entry.skills;
	if (entry.raw_text != NULL)
		delete []entry.raw_text;
}
