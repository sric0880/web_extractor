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

void InfoExtractor::infoExtract(string input){
	string title;
	string text;
	int pos = input.find_first_of('^');
	title=input.substr(0,pos);
	int len = input.length()-pos;
	text=input.substr(pos+1,len);
//	printf("%s\n",text.c_str());

	Data entry;
	temt->match_time(entry,text);
	temt->match_workplace(entry,text);
	temt->match_email(entry,text);
	temt->match_tel(entry,text);
	temt->match_need_num(entry,text);
	temt->match_position(entry,input);
	temt->match_company(entry,title);
	temt->match_skills(entry,text);
	entry.raw_text = new char[input.length()+1];
	strcpy(entry.raw_text,input.c_str());

	//主题分类判断是不是计算机实习信息
	if(entry.company==NULL&&entry.position==NULL){
		return;
	}else{
		if(!dup_removal.is_duplicate(entry.tostring()))//消重
		{
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
