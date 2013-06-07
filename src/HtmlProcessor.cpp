/*
 * HtmlProcessor.cpp
 *html文档处理核心模块
 *实现多线程 线程安全列队
 *  Created on: 2013-5-20
 *      Author: qiong
 */

#include "HtmlProcessor.h"

HtmlProcessor::HtmlProcessor(Output* output, Template * temt):
info_ext(output,temt),queue_html(), text_ext(280, 6),flag(false) {
	if (!NLPIR_Init(".", UTF8_CODE))//Data文件夹所在的路径，默认为GBK编码的分词
	{
		printf("ICTCLAS INIT FAILED!\n");
	}
//	NLPIR_ImportUserDict("position.txt");
//	NLPIR_SaveTheUsrDic();
}

HtmlProcessor::~HtmlProcessor() {
	//释放分词组件资源
	NLPIR_Exit();
}

void HtmlProcessor::addHtml(string html){
	queue_html.push(html);
}

void HtmlProcessor::run(){
	int i = 0;
	while(1){
		if(flag&&queue_html.isEmpty()){
			printf("html process over!\n");
			break;
		}
		//从列队中取html
		string input;
		input = queue_html.front_pop();
		//正文提取
		input = text_ext.extract(input);
		info_ext.infoExtract(i,input);//提取结构化信息 并输出
		++i;
	}
	pthread_exit( NULL);
}

void HtmlProcessor::over(){
	flag = true;
}
