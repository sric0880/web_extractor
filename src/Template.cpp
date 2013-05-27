/*
 * Template.cpp
 *
 *  Created on: 2013-5-24
 *      Author: qiong
 */
#include "Template.h"
#include <unordered_set>

Template::Template():
//regex_email("\\w+",regex::normal),
regex_email("\\w+([-+.]\\w+)*@\\w+([-.]\\w+)*\\.\\w+([-.]\\w+)*"),
regex_tel("(\\(?[0]\\d{2,3}\\)?-?\\d{6,7})|"
		"(\\+?(86)?\\s?-?\\s?(13|15|18|14)[0-9]\\d{8})"),
regex_need_num("(\\d+)\\s*-*\\s*(\\d*)\\s*"){
}
Template::~Template(){
}

void Template::match_time(Data& entry,const string& str){}

void Template::match_company(Data& entry,const string& str){}

void Template::match_position(Data& entry,const string& str){
	int nCount;
	//分词的高级功能
	//该函数功能为：输入字符串，输出分词结果的result_t结构体数组，nCout为数组大小
	//返回的数组结果由系统自行维护，用户直接调用即可
	const result_t *pResult = NLPIR_ParagraphProcessA(str.c_str(), &nCount,true);
	int i = 1;
	unordered_set<string> pset;
	for (i = 0; i < nCount; ++i) {//逐个答应分词结果的内容
		if(pResult[i].word_type==1){
			string p = str.substr(pResult[i].start, pResult[i].length);
			if(pResult[i-1].iPOS==21||pResult[i-1].iPOS==93){
				string pre = str.substr(pResult[i-1].start, pResult[i-1].length);
				pre.append(p);
				pset.insert(pre);
			}
			else
				pset.insert(p);
		}
	}
	string r;
	for(auto& s : pset){
		r.append(s);
		r.append(" ");
	}
	if (r != "") {
		trim(r);
		algorithm::to_lower(r);
		int len = r.length();
		entry.position = new char[len + 1];
		strcpy(entry.position, r.c_str());
	}
}

void Template::match_workplace(Data& entry,const string& str){}

void Template::match_need_num(Data& entry,const string& str){
	//需要多少人
	smatch mat;
	std::string::const_iterator begin = str.begin();
	std::string::const_iterator end = str.end();
	int need = 0;
	while (regex_search(begin, end, mat, regex_need_num)) {
		std::string r(mat[0].first - 15, mat[0].second + 3);
		if (r.find("人数") != string::npos) {
			std::string s(mat[1].first, mat[1].second);
			std::string s1(mat[2].first, mat[2].second);
			if (s1 != "")
				need += atoi(s1.c_str());
			else
				need += atoi(s.c_str());
		}
		begin = mat[0].second;
	}
	if (need != 0) {
		entry.need_num = need;
	}
}

void Template::match_skills(Data& entry, const string& str) {
	int nCount;
	const result_t *pResult = NLPIR_ParagraphProcessA(str.c_str(), &nCount,true);
//	copy[str.length()]='\0';
	unordered_set<string> pset;
	int j=0;
	while(j<nCount){
		int i =0;
		int s,pre_s;
		string w,pre_w;
		w = str.substr(pResult[j+i].start, pResult[j+i].length);
		algorithm::to_lower(w);
		while((s=dict.da_find((const unsigned char*)w.c_str()))>=0&&(j+i)<nCount){
			++i;
			pre_w = w;
			pre_s = s;
			if(pResult[j+i-1].iPOS==93&&pResult[j+i].iPOS==93)//english
			{
				w.append(" ");
			}
			w.append(str.substr(pResult[j+i].start,pResult[j+i].length));
			algorithm::to_lower(w);
		}
		if(i>0&&pre_s>0){
			pset.insert(pre_w);
		}
		j+=(i+1);
	}
	string r;
	for(auto& s : pset) {
		r.append(s);
		r.append(" ");
	}
	if(r!=""){
		trim(r);
		int len = r.length();
		entry.skills = new char[len + 1];
		strcpy(entry.skills, r.c_str());
	}
}

void Template::match_email(Data& entry, const string& str) {
	//regex
	string r;
	match_results<std::string::const_iterator> mat;
	std::string::const_iterator begin = str.begin();
	std::string::const_iterator end = str.end();
	while (regex_search(begin, end, mat, regex_email)) {
		r.append(mat[0]);
		r.append(" ");
		begin = mat[0].second;
	}
	if (r != "") {
		trim(r);
		int len = r.length();
		entry.email = new char[len + 1];
		strcpy(entry.email, r.c_str());
	}
}
void Template::match_tel(Data& entry,const string& str){
	string r;
	match_results<std::string::const_iterator> mat;
	std::string::const_iterator begin = str.begin();
	std::string::const_iterator end = str.end();
	while (regex_search(begin,end, mat, regex_tel)) {
		r.append(mat[0]);
		r.append(" ");
		begin = mat[0].second;
	}
	if (r != "") {
		trim(r);
		int len = r.length();
		entry.tel = new char[len + 1];
		strcpy(entry.tel, r.c_str());
	}
}
