/*
 * InfoExtractor.cpp
 *
 *  Created on: 2013-5-24
 *      Author: qiong
 */

#include "InfoExtractor.h"

InfoExtractor::InfoExtractor(Output* out,Template* temt):
out(out),temt(temt){
	if (!NLPIR_Init(".", UTF8_CODE))//Data文件夹所在的路径，默认为GBK编码的分词
	{
		printf("ICTCLAS INIT FAILED!\n");
	}
//	NLPIR_ImportUserDict("position.txt");
//	NLPIR_SaveTheUsrDic();
}

InfoExtractor::~InfoExtractor() {
	//释放分词组件资源
	NLPIR_Exit();
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
//	temt->match_time(entry,text);
//	temt->match_workplace(entry,text);
//	temt->match_email(entry,text);
//	temt->match_tel(entry,text);
//	temt->match_need_num(entry,text);
//	temt->match_position(entry,input);
//	temt->match_company(entry,title);
	temt->match_skills(entry,text);
//	entry.raw_text = new char[input.length()+1];
//	strcpy(entry.raw_text,input.c_str());
	//结构化数据输出
	out->output(entry);
	release(entry);
	//		//动态添加用户词
	//		printf("\n动态添加用户词后：\n");
	//		NLPIR_AddUserWord("测评活动   cepinghuodong");
	//		NLPIR_SaveTheUsrDic();
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
