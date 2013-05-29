/*
 * TemplatePongo.cpp
 *
 *  Created on: 2013-5-27
 *      Author: qiong
 */

#include "TemplatePongo.h"

TemplatePongo::TemplatePongo() {
	// TODO Auto-generated constructor stub

}

TemplatePongo::~TemplatePongo() {
	// TODO Auto-generated destructor stub
}

void TemplatePongo::match_time(Data& entry,const string& str){
	string keyword("发布日期：");
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
void TemplatePongo::match_workplace(Data& entry,const string& str){
	string keyword("工作地点：");
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
void TemplatePongo::match_company(Data& entry,const string& str){
	size_t found,end;
	string r;
	string logo("庞果网-Pongo.cn");
	std::size_t i = str.find(logo);
	if ((found = str.find_first_of("-"))!=string::npos&&found<i
			&&(end = str.find_first_of("-",found+1))!=string::npos) {
		size_t len = end-found-1;
		r = str.substr(found+1, len);
		trim(r);
		len = r.length();
		if (len != 0) {
			algorithm::to_lower(r);
			entry.company = new char[len + 1];
			strcpy(entry.company, r.c_str());
		}
	}
}

void TemplatePongo::match_position(Data& entry,const string& str){
	size_t found;
	string r;
	string logo("庞果网-Pongo.cn");
	std::size_t i = str.find(logo);
	if ((found = str.find_first_of("-")) != string::npos&&
			found<i) {
		r = str.substr(0, found);
		trim(r);
		int len = r.length();
		if (len != 0) {
			algorithm::to_lower(r);
			NLPIR_AddUserWord(r.c_str());//标题中提取的职位名称保存到用户词典中
			NLPIR_SaveTheUsrDic();
			entry.position = new char[len + 1];
			strcpy(entry.position, r.c_str());
		}
	}
}
