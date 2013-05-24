/*
 * TextExtractor.h
 *
 *  Created on: 2013-5-19
 *      Author: qiong
 */

#ifndef TEXTEXTRACTOR_H_
#define TEXTEXTRACTOR_H_

#include <string>
#include <boost/regex.hpp>
using namespace std;
using namespace boost;

class TextExtractor {
public:
	TextExtractor(int threshold, int blocks_width);
	virtual ~TextExtractor();
	string extract(string html);
private:
	int _threshold;
	int _blocks_width;
	regex e,e2,e3;
};

const int _len = 22;
const string biaodian[_len]={"，","。","？","：","；","‘","’","！","“","”",
		"—","……","、","《","》","{","}","【","】","－","（","）"};

#endif /* TEXTEXTRACTOR_H_ */
