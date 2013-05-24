/*
 * OutputXml.h
 *
 *  Created on: 2013-5-24
 *      Author: qiong
 */

#ifndef OUTPUTXML_H_
#define OUTPUTXML_H_

#include "Output.h"

class OutputXml: public Output{
public:
	void output(Data entry){
		printf("output xml start\n");
	}
};


#endif /* OUTPUTXML_H_ */
