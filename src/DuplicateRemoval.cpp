/*
 * UserDictforSkills.cpp
 *
 *  Created on: 2013-5-25
 *      Author: qiong
 */

#include "DuplicateRemoval.h"

DuplicateRemoval::UserDictforSkills()
{
	//load file
	ifstream in;
	in.open(FILE_NAME,ifstream::in);
	string line;
	getline(in,line);
	doc_num=atoi(line.c_str());
	while(getline(in,line)){
		stringstream sline;
		sline.str(line);
		string s_name;
		int s_df;
		sline>>s_name>>s_df;
		df[s_name]=s_df;
	}
	in.close();
}

DuplicateRemoval::~UserDictforSkills() {
	//write to file
	ofstream out;
	out.open(FILE_NAME, ofstream::out);
	out<<doc_num<<"\n";
	for(auto& w:df) {
		out<<w.first<<" "<<w.second<<"\n";
	}
	out.flush();
	out.close();
}

bool DuplicateRemoval::is_match(string str){

	return true;
}

void DuplicateRemoval::add_words(unordered_set<string> words){
	for(auto& w: words){
		++df[w];
	}
	++doc_num;
	printf("doc_num: %d\n",doc_num);
}
