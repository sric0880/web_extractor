/*
 * TextExtractor.cpp
 *
 *  Created on: 2013-5-19
 *      Author: qiong
 */
#include <vector>
#include "TextExtractor.h"
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string.hpp>

TextExtractor::TextExtractor(int threshold, int blocks_width):
_threshold(threshold),
_blocks_width(blocks_width),
e("(?is)(<!DOCTYPE.*?>)|(<!--.*?-->)|"
		"(<script.*?>.*?</script>)|"
		"(<style.*?>.*?</style>)|"
		"(&.{2,5};|&#.{2,5};)|"
		"(<.*?>)",regex::perl),
e2("(?is)(\\s+)|(\\/+)",regex::normal),
e3("<title>(.*)</title>",regex::normal){
	// TODO Auto-generated constructor stub
}

TextExtractor::~TextExtractor() {
	// TODO Auto-generated destructor stub

}

string TextExtractor::extract(string html){
//	printf("before:\n%s\n",html.c_str());
	cmatch ma;
	string title;
	if(regex_search(html.c_str(),ma,e3))
	{
		title = ma[0];
		title=title.substr(7,title.length()-15);//
		title = regex_replace(title,e2," ",match_default | format_all);
	}
	html = regex_replace(html,e,"",match_default | format_all);
//	printf("after:\n%s\n",html.c_str());

	int i;
	vector<string> lines;
	using namespace boost::algorithm;
	split(lines,html,is_any_of("\n"));
	int num_lines = lines.size();
	int dist[num_lines];//distribution
	for(i=0; i< num_lines; ++i)
	{
		lines[i] = regex_replace(lines[i],e2," ",match_default | format_all);
		trim(lines[i]);
//		printf("%s\n",lines[i].c_str());
	}
	smatch mat;
	//统计每一行的标点符号，标点符号给予超大的权重
	for(i=0; i< num_lines; ++i)//初始化为0
	{
		size_t found = 0;
		int count=0;
		for(int j =0;j<_len;++j){
			while((found=lines[i].find(biaodian[j],found+1))!=std::string::npos)
				++count;
		}
		dist[i] = count*20;//一个标点符号加20个权重
	}
	for(i=0; i < num_lines-_blocks_width;++i)
	{
		for(int j = i; j<i+_blocks_width;++j)
		{
			dist[i]+=lines[j].length();
		}
		printf("%d\t",dist[i]);
	}
	printf("\n");
	int start_line,end_line;
	int max = 0;
	for(i=0; i<num_lines-1; ++i){//求最大行块
		if(dist[i]>max){
			max = dist[i];
			start_line = i;
		}
	}
	end_line = start_line+1;
	for (i = start_line + 1; i < num_lines; ++i) {//结束位置
		if (dist[i] == 0) {
			end_line = i;
			break;
		}
	}
	for(int i=start_line-1; i>0; --i){//开始位置
		if(dist[i] < _threshold){
			start_line = i+1;
			break;
		}
	}

	//开始与结束位置前后各取20/10行为正文
	start_line-=20;
	end_line+=10;
	if(start_line<0) start_line=0;
	if(end_line>num_lines) end_line=num_lines;
	string res;
	res.append(title);
	res.append("^");
	for (i = start_line; i <= end_line; ++i) {
		res.append(lines[i]);
		res.append(" ");
	}
	res = regex_replace(res,e2," ",match_default | format_all);
	trim(res);
	return res;
}
