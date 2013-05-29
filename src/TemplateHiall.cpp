/*
 * TemplateHiall.cpp
 *
 *  Created on: 2013-5-24
 *      Author: qiong
 */

#include "TemplateHiall.h"

TemplateHiall::TemplateHiall():Template() {
	// TODO Auto-generated constructor stub
}

TemplateHiall::~TemplateHiall() {
	// TODO Auto-generated destructor stub
}

void TemplateHiall::match_time(Data& entry,const string& str){
	string keyword("更新时间：");
	std::size_t i  =str.find(keyword);
	if(i!=string::npos){
		i += (keyword.length());
		int j = str.find_first_of(" ", i);
		string r = str.substr(i, j - i);
		int len = r.length();
		entry.publish_time = new char[len + 1];
		strcpy(entry.publish_time, r.c_str());
	}
}
void TemplateHiall::match_workplace(Data& entry,const string& str){
	string keyword("工作地区：");
	std::size_t i =str.find(keyword);
	if (i != string::npos) {
		i += (keyword.length());
		int j = str.find_first_of(" ", i);
		string r = str.substr(i, j - i);
		int len = r.length();
		entry.workplace = new char[len + 1];
		strcpy(entry.workplace, r.c_str());
	}
}
void TemplateHiall::match_company(Data& entry,const string& str){
	size_t found;
	string r;
	if (((found = str.find("招聘")) != string::npos || (found = str.find("诚招"))
			!= string::npos || (found = str.find("诚聘")) != string::npos)) {
		r = str.substr(0, found);
	}else if((found = str.find("公司")) != string::npos){
		r = str.substr(0, found+6);
	}
	trim(r);
	boost::regex re("\\d+.*");
	r = regex_replace(r,re,"");
	int len = r.length();
	if (len != 0) {
		algorithm::to_lower(r);
		entry.company = new char[len + 1];
		strcpy(entry.company, r.c_str());
	}
}
void TemplateHiall::match_position(Data& entry,const string& str){
	size_t title_tail = str.find_first_of('^');
	size_t end;
	size_t found;
	if(((found = str.find("招聘"))!=string::npos||
			(found = str.find("诚招"))!=string::npos||
			(found = str.find("诚聘"))!=string::npos)&&
			found<title_tail&&
			(end = str.find_first_of("-",found))!=string::npos){
		size_t len = end-found-6;
		string r = str.substr(found+6,len);
		trim(r);
		len = r.length();
		if(len!=0){
			algorithm::to_lower(r);
			boost::regex re("\\s+");
			r = regex_replace(r,re,"\n");
			NLPIR_AddUserWord(r.c_str());//标题中提取的职位名称保存到用户词典中
			NLPIR_SaveTheUsrDic();
			entry.position = new char[len + 1];
			strcpy(entry.position, r.c_str());
		}
		else{
			Template::match_position(entry,str);
		}
	}else{
		Template::match_position(entry,str);
	}
}
