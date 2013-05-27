/*
 * UserDictforSkills.h
 * 使用simHash去重算法
 *  Created on: 2013-5-25
 *      Author: qiong
 */

#ifndef DUPLICATEREMOVAL_H_
#define DUPLICATEREMOVAL_H_
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <bitset>
#include "NLPIR.h"
#include <limits.h>
using namespace std;
typedef unsigned long long size_m;
class DuplicateRemoval {
public:
	DuplicateRemoval();
	virtual ~DuplicateRemoval();
	bool is_duplicate(string str);
private:
	unordered_map<size_m,int> fingerprint;//document finger print
	int _hamming_distance(size_m &hash);
	size_m hash_fn(string x);
//	inline bool _pos_filter(int pos_id);
};
//const int POS_LEN = 14;
//const int pos_ids[POS_LEN]={21,22,32,74,93,29,30,31,52,53,57,18,20,97};//需要保留的词性
const char FILE_NAME[]="doc_finger.txt";
#endif /* DUPLICATEREMOVAL_H_ */
