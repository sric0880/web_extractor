/*
 * DataEntryh
 *
 *  Created on: 2013-5-24
 *      Author: qiong
 */

#ifndef DATAENTRY_H_
#define DATAENTRY_H_
#include <stdio.h>
#include <sstream>
#include <string>
using namespace std;
struct Data{
	int id;
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
		id = 0;
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
	string tostring(){
		stringstream str;
		if (company != NULL){
			str<<company<<" ";
		}if (position != NULL){
			str<<position<<" ";
		}if (publish_time != NULL){
			str<<publish_time<<" ";
		}if (workplace != NULL){
			str<<workplace<<" ";
		}if (need_num != 0){
			str<<need_num<<" ";
		}if (email != NULL){
			str<<email<<" ";
		}if (tel != NULL){
			str<<tel<<" ";
		}if (skills != NULL){
			str<<skills<<" ";
		}
		return str.str();
	}
};
#endif /* DATAENTRY_H_ */
