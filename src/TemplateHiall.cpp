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
		int j = str.find_first_of("|", i);
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
		int j = str.find_first_of("|", i);
		string r = str.substr(i, j - i);
		int len = r.length();
		entry.workplace = new char[len + 1];
		strcpy(entry.workplace, r.c_str());
	}
}
void TemplateHiall::match_company(Data& entry,const string& str){
	string keyword("");
	std::size_t i = str.find(keyword);
	if (i != string::npos) {
		i += (keyword.length());
		int j = str.find_first_of("|", i);
		string r = str.substr(i, j - i);
		int len = r.length();
		entry.workplace = new char[len + 1];
		strcpy(entry.workplace, r.c_str());
	}
}
void TemplateHiall::match_position(Data& entry,const string& str){
}

void TemplateHiall::match_need_num(Data& entry,const string& str){

}
