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
#include "Output.h"
#include "Template.h"
using namespace std;

class HtmlProcessor:public Thread {
public:
	HtmlProcessor(Output* output, Template * temt);//输出格式 //网站模板
	virtual ~HtmlProcessor();
	void addHtml(string html);
private:
	InfoExtractor info_ext;
	SafeQueue<string> queue_html;
	TextExtractor text_ext;
	bool flag;
protected:
	void run();
	void over();
};

#endif /* HTMLPROCESSOR_H_ */
