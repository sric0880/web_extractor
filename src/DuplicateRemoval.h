/*
 * UserDictforSkills.h
 *
 *  Created on: 2013-5-25
 *      Author: qiong
 */

#ifndef DUPLICATEREMOVAL_H_
#define DUPLICATEREMOVAL_H_
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;
class DuplicateRemoval {
public:
	DuplicateRemoval();
	virtual ~DuplicateRemoval();
	bool is_match(string word);
	void add_words(unordered_set<string> words);
private:
	int doc_num;
	unordered_map<string,int> df;//document frequency

};
const char FILE_NAME[]="usrDictSkills.txt";
#endif /* DUPLICATEREMOVAL_H_ */
