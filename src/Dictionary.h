/*
 * Dictionary.h
 *
 *  Created on: 2013-5-27
 *      Author: qiong
 */

#ifndef DICTIONARY_H_
#define DICTIONARY_H_
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <unordered_map>
using namespace std;
class Dictionary {
public:
	Dictionary();
	virtual ~Dictionary();
	int findWord(string w);	 //在哈希词典中查找词
private:
	string strtmp; //读取词典的每一行
	string word; //保存每个词
	unordered_map<string, int> wordhash; // 用于读取词典后的哈希
	unordered_map<string, int>::iterator worditer; //
	typedef pair<string, int> sipair;
};

#endif /* DICTIONARY_H_ */
