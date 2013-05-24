/*
 * HtmlProcessor.cpp
 *html文档处理核心模块
 *实现多线程 线程安全列队
 *  Created on: 2013-5-20
 *      Author: qiong
 */

#include "HtmlProcessor.h"

HtmlProcessor::HtmlProcessor(Output* output, Template * temt):
info_ext(output,temt),queue_html(), text_ext(100, 5),flag(false) {
}

HtmlProcessor::~HtmlProcessor() {
}

void HtmlProcessor::addHtml(string html){
	queue_html.push(html);
}

void HtmlProcessor::run(){
	while(1){
		if(flag&&queue_html.isEmpty()){
			printf("html process over!\n");
			break;
		}
		//从列队中取html
		string input;
		input = *queue_html.front_pop();
		//正文提取
		input = text_ext.extract(input);
		//定义输出格式
		info_ext.infoExtract(input);
	}
	pthread_exit( NULL);
}

void HtmlProcessor::over(){
	flag = true;
}
