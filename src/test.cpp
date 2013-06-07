//============================================================================
// Name        : web_extractor.cpp
// Author      : luo zhouqiong
// Version     :
// Copyright   : Copyright@luozhouqiong.ss.pku
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <string.h>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <unordered_map>
#include <set>
#include "OutputXml.h"
#include "OutputConsole.h"
#include "OutputMysql.h"
#include "TemplateHiall.h"
#include "TemplatePongo.h"
#include "HtmlProcessor.h"
using namespace std;

int main(int argv, char * args[]) {

	if(argv!= 7){
		printf("web_extractor -o [console|mysql|xml] -t [hiall|pongo] -dir [input path]\n");
		return 0;
	}
	char folder[20];
	Output* output;
	Template* temt;
	int i =1;
	while(i<7){
		if(strcmp(args[i],"-o")==0){
			++i;
			if(strcmp(args[i],"console")==0){
				output = new OutputConsole();
			}else if(strcmp(args[i],"mysql")==0){
				output = new OutputMysql();
			}else if(strcmp(args[i],"xml")==0){
				output = new OutputXml();
			}else
			{
				printf("input [console|mysql|xml]\n");
				return 0;
			}
		} else if (strcmp(args[i], "-t") == 0) {
			++i;
			if (strcmp(args[i], "hiall") == 0) {
				temt = new TemplateHiall();
			} else if (strcmp(args[i], "pongo") == 0) {
				temt = new TemplatePongo();
			}
			else{
				printf("input [hiall|pongo]\n");
				return 0;
			}
		}else if(strcmp(args[i], "-dir") == 0){
			++i;
			strcpy(folder,args[i]);
		}
		++i;
	}
	DIR * dir;
	if((dir = opendir(folder)) ==NULL){
		printf("open dir %s failed!\n",folder);
		return 0;
	}
	char index[20];
	strcpy(index,folder);
	strcat(index, "index");
	unordered_map<int,string> urls;
	ifstream index_file;
	index_file.open(index,ifstream::in);
	string line;
	while(getline(index_file,line)){
		stringstream ss;
		ss.str(line);
		int id;
		string url;
		ss>>id>>url;
		urls[id]=url;
	}
	if(urls.size()==0){
		printf("no index file!\n");
		return 0;
	}
	output->set_urls(urls);
	struct dirent* dir_ent;
	set<string> files;
	while((dir_ent = readdir(dir))!=NULL){
		if(strcmp(dir_ent->d_name,".")==0
			||strcmp(dir_ent->d_name,"..")==0
			||strcmp(dir_ent->d_name,"index")==0)
			continue;
		char filename[20];
		strcpy(filename,folder);
		strcat(filename, dir_ent->d_name);
		files.insert(filename);
	}
	closedir(dir);
	i = 0;
	HtmlProcessor htmlpro(output, temt);
	htmlpro.start();
	set<string>::iterator iter = files.begin();
	for(;iter!=files.end();++iter){
		printf("%s\n", iter->c_str());
		ifstream ifs(*iter);
		string content;
		if (ifs) {
			stringstream ss;
			ss << ifs.rdbuf();
			content = ss.str();
			htmlpro.addHtml(content);
		}
		ifs.close();
		++i;
	}
	htmlpro.join();
	return 0;
}
