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
#include "Template.h"
using namespace std;
class InfoExtractor {
public:
	InfoExtractor(Output* out,Template* temt);
	virtual ~InfoExtractor();
	void infoExtract(string input);
private:
	Output* out;
	Template* temt;
	void release(Data &entry);
};
#endif /* INFOEXTRACTOR_H_ */
