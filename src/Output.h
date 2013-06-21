/*
 * Output.h
 *
 *  Created on: 2013-5-24
 *      Author: qiong
 */

#ifndef OUTPUT_H_
#define OUTPUT_H_
#include <string>
#include <unordered_map>
#include "DataEntry.h"
class Output{
public:
	virtual void output(const Data& entry){}
	void set_urls(unordered_map<int,string> &urls){
		this->urls = urls;
	}
protected:
	unordered_map<int,string> urls;
};

#endif /* OUTPUT_H_ */
