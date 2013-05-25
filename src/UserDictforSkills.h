/*
 * UserDictforSkills.h
 *
 *  Created on: 2013-5-25
 *      Author: qiong
 */

#ifndef USERDICTFORSKILLS_H_
#define USERDICTFORSKILLS_H_
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;
class UserDictforSkills {
public:
	UserDictforSkills();
	virtual ~UserDictforSkills();
	bool is_match(string word);
	void add_words(unordered_set<string> words);
private:
	int doc_num;
	unordered_map<string,int> df;//document frequency

};
const char FILE_NAME[]="usrDictSkills.txt";
#endif /* USERDICTFORSKILLS_H_ */
