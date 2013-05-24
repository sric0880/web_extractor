/*
 * HtmlProcessor.h
 *
 *  Created on: 2013-5-20
 *      Author: qiong
 */

#ifndef HTMLPROCESSOR_H_
#define HTMLPROCESSOR_H_

#include <string>
#include <pthread.h>
#include <stdio.h>
#include "SafeQueue.h"
#include "Thread.h"
#include "TextExtractor.h"
#include "InfoExtractor.h"
#include "OutputXml.h"
using namespace std;

class HtmlProcessor:public Thread {
public:
	HtmlProcessor();
	virtual ~HtmlProcessor();
	void addHtml(string html);
private:
	SafeQueue<string> queue_html;
	TextExtractor text_ext;
	bool flag;
protected:
	void run();
	void over();
};

#endif /* HTMLPROCESSOR_H_ */
