/*
 * InfoExtractor.h
 *
 *  Created on: 2013-5-24
 *      Author: qiong
 */

#ifndef INFOEXTRACTOR_H_
#define INFOEXTRACTOR_H_
#include <string>
#include <string.h>
#include "Output.h"
#include "NLPIR.h"
using namespace std;
class InfoExtractor {
public:
	InfoExtractor(Output* out);
	virtual ~InfoExtractor();
	void infoExtract(string input);
private:
	Output* out;
	CNLPIR* cnlpir;
	inline bool pos_filter(int pos_id);
};
const int POS_LEN = 14;
const int pos_ids[POS_LEN]={18,20,21,22,29,30,31,32,37,52,53,57,74,97};//需要保留的词性
#endif /* INFOEXTRACTOR_H_ */
