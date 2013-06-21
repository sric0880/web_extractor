/*
 * Dictionary.h
 *	双数组trie树实现
 *  Created on: 2013-5-27
 *      Author: qiong
 */

#ifndef DICTIONARY_H_
#define DICTIONARY_H_
#include <string>
#include <string.h>
#include <stdio.h>
#include <fstream>
using namespace std;
const int ALPSIZE = 256;
const int MAXSIZE = 10000;
typedef struct _my_datrie
{
    long base_[MAXSIZE];
    long check_[MAXSIZE];
    long max_size;
    long numofnodes;
}my_datrie;
#define ALP_ID(x) ((x)+1)
#define ID_ALP(x) (x-1)
#define ISEMPTY(x,y) ((y)->base_[(x)]==0&&(y)->check_[(x)]<0)
class Dictionary {
public:
	Dictionary();
	virtual ~Dictionary();
	int da_insert(const unsigned char * word);
	int da_delete(const unsigned char * word);
	long da_find(const unsigned char * word);
	void da_print();
private:
	my_datrie * datrie;
	void da_init();
	long find_suitable_position(long s, unsigned char c);
	void relocate(long s,long newbase);
	int have_child(long s);
	long da_abs(long a);
};
const char filename[]="skill_dict.txt";
#endif /* DICTIONARY_H_ */
