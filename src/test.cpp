//============================================================================
// Name        : web_extractor.cpp
// Author      : luo zhouqiong
// Version     :
// Copyright   : Copyright@luozhouqiong.ss.pku
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include "OutputXml.h"
#include "OutputConsole.h"
#include "TemplateHiall.h"
#include "TemplatePongo.h"
#include "HtmlProcessor.h"
using namespace std;

int main() {

//	OutputXml xml;
	OutputConsole console;
	TemplateHiall hiall;
//	TemplatePongo pongo;
	HtmlProcessor htmlpro(&console, &hiall);
	htmlpro.start();
	for(int i =0;i<20;++i){
		char filename[20];
		sprintf(filename,"test/d00000/%d",i+1);
		printf("%s\n",filename);
		ifstream ifs(filename);
		string content;
		if(ifs){
			stringstream ss;
			ss<<ifs.rdbuf();
			content = ss.str();
			htmlpro.addHtml(content);
		}
		ifs.close();
	}
	htmlpro.join();
	return 0;
}
