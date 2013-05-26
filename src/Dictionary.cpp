/*
 * Dictionary.cpp
 *
 *  Created on: 2013-5-27
 *      Author: qiong
 */

#include "Dictionary.h"

Dictionary::Dictionary() {
	ifstream infile("wordlexicon"); // 打开词典
	if (!infile.is_open()) // 打开词典失败则退出程序
	{
		cerr << "Unable to open input file: " << "wordlexicon"
				<< " -- bailing out!" << endl;
		exit(-1);
	}
	while (getline(infile, strtmp, '\\n')) // 读入词典的每一行并将其添加入哈希中
	{
		istringstream istr(strtmp);
		istr >> word; //读入每行第一个词
		wordhash.insert(sipair(word, 1)); //插入到哈希中
	}
}

Dictionary::~Dictionary() {
	// TODO Auto-generated destructor stub
}

//在哈希词典中查找词，若找到，则返回，否则返回
int Dictionary::FindWord(string w) {
	if (wordhash.find(w) != wordhash.end()) {
		return 1;
	} else {
		return 0;
	}
}
