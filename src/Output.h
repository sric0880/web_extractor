/*
 * Output.h
 *
 *  Created on: 2013-5-24
 *      Author: qiong
 */

#ifndef OUTPUT_H_
#define OUTPUT_H_
#include <string>
#include "DataEntry.h"
class Output{
public:
	virtual void output(const Data& entry) =0;
};

#endif /* OUTPUT_H_ */
