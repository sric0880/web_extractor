/*
 * Template.cpp
 *
 *  Created on: 2013-5-24
 *      Author: qiong
 */
#include "Template.h"
#include <boost/algorithm/string.hpp>

Template::Template():
//regex_email("\\w+",regex::normal),
regex_email("(\\w+([-+.]\\w+)*@\\w+([-.]\\w+)*\\.\\w+([-.]\\w+)*)",regex::normal),
regex_tel("(\\d{3}-\\d{8}|\\d{4}-\\d{7})|"
		"((\\([0]\\d{2}|\\d{4}\\))(\\d{6,7}))|"
		"(\\+?(86)?\\s?-?\\s?(13|15|18|14)[0-9]\\d{8})"){
}
Template::~Template(){}

void Template::match_time(Data& entry,const string& str){
	//
}
void Template::match_company(Data& entry,const string& str){
	//
}
void Template::match_position(Data& entry,const string& str){
	//
}
void Template::match_workplace(Data& entry,const string& str){
	//
}
void Template::match_need_num(Data& entry,const string& str){
	//
}
void Template::match_skills(Data& entry,const string& str){
	//
}
void Template::match_email(Data& entry,const string& str){
	//regex
	cmatch mat;
	if(regex_search(str.c_str(),mat,regex_email)){
		string r;
		for (cmatch::iterator itr = mat.begin(); itr != mat.end(); ++itr) {
			r.append(*itr);
			r.append(" ");
		}
		trim(r);
		int len = r.length();
		entry.email = new char[len + 1];
		strcpy(entry.email, r.c_str());
	}
}
void Template::match_tel(Data& entry,const string& str){
	cmatch mat;
	if (regex_search(str.c_str(), mat, regex_tel)) {
		string r;
		for (cmatch::iterator itr = mat.begin(); itr != mat.end(); ++itr) {
			r.append(*itr);
			r.append(" ");
		}
		trim(r);
		int len = r.length();
		entry.tel = new char[len + 1];
		strcpy(entry.tel, r.c_str());
	}
}
