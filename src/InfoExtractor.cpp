/*
 * InfoExtractor.cpp
 *
 *  Created on: 2013-5-24
 *      Author: qiong
 */

#include "InfoExtractor.h"

InfoExtractor::InfoExtractor(Output* out,Template* temt):
out(out),temt(temt){
	if (!NLPIR_Init(".", UTF8_CODE))//Data文件夹所在的路径，默认为GBK编码的分词
	{
		printf("ICTCLAS INIT FAILED!\n");
	}
	cnlpir = GetActiveInstance();
}

InfoExtractor::~InfoExtractor() {
	//释放分词组件资源
	NLPIR_Exit();
}

void InfoExtractor::infoExtract(string input){
	string title;
	string text;
	int pos = input.find_first_of('\t');
	title=input.substr(0,pos);
	text=input.erase(0,pos+1);
//	printf("%s\n", title.c_str());
//	printf("%s\n", text.c_str());

	Data entry;
	temt->match_time(entry,text);
	temt->match_workplace(entry,text);
	temt->match_email(entry,text);
	temt->match_tel(entry,text);
	//先分词
	cnlpir->SetAvailable(false);
	int nCount;
	//分词的高级功能
	//该函数功能为：输入字符串，输出分词结果的result_t结构体数组，nCout为数组大小
	//返回的数组结果由系统自行维护，用户直接调用即可
	const result_t *pResult = cnlpir->ParagraphProcessA(input.c_str(), &nCount);
	const char * test;
	test = cnlpir->ParagraphProcess(input.c_str(), 1);
	printf("nCount=%d\n", nCount);//分词结果数目
	cnlpir->SetAvailable(true);

	printf("%s\n", test);
	//词性过滤

//	int i = 1;
//	string sWhichDic;
//	for (i = 0; i < nCount; ++i) {//逐个答应分词结果的内容
//		//			sWhichDic = "";
//		//			switch (pResult[i].word_type) {
//		//			case 0:
//		//				sWhichDic = "核心词典";
//		//				break;
//		//			case 1:
//		//				sWhichDic = "用户词典";
//		//				break;
//		//			case 2:
//		//				sWhichDic = "专业词典";
//		//				break;
//		//			default:
//		//				break;
//		//			}
//		if (pos_filter(pResult[i].iPOS))
//			//			printf(
//			//					"No.%d:start:%d, length:%d,POS_ID:%d,Word_ID:%d, UserDefine:%s, Word:%s\n",
//			//					i + 1, pResult[i].start, pResult[i].length,
//			//					pResult[i].iPOS, pResult[i].word_ID, sWhichDic.c_str(),
//			//					html.substr(pResult[i].start,pResult[i].length).c_str());
//			printf("No.%d:POS_ID:%d,Word:%s\n", i + 1, pResult[i].iPOS,
//					input.substr(pResult[i].start, pResult[i].length).c_str());
//	}

	//结构化数据输出
	out->output(entry);
	release(entry);

	//		//////////////////////////////////////////////////////////////////////////
	//		//下面开始测试用户词典功能
	//		//////////////////////////////////////////////////////////////////////////
	//		//导入用户词典前
	//		printf("未导入用户词典：\n");
	//		const char * sResult = NLPIR_ParagraphProcess(sSentence, 1);
	//		printf("%s\n", sResult);
	//		//导入用户词典后
	//		printf("\n导入用户词典后：\n");
	//		nCount = NLPIR_ImportUserDict("userdic.txt");//userdic.txt覆盖以前的用户词典
	//		//保存用户词典
	//		NLPIR_SaveTheUsrDic();
	//		printf("导入%d个用户词。\n", nCount);
	//		sResult = NLPIR_ParagraphProcess(sSentence, 1);
	//		printf("%s\n", sResult);
	//		//动态添加用户词
	//		printf("\n动态添加用户词后：\n");
	//		NLPIR_AddUserWord("测评活动   cepinghuodong");
	//		NLPIR_SaveTheUsrDic();
	//		sResult = NLPIR_ParagraphProcess(sSentence, 1);
	//		printf("%s\n", sResult);
}

inline bool InfoExtractor::pos_filter(int pos_id){
	for(int i =0;i<POS_LEN;++i){
		if(pos_ids[i]==pos_id)
			return true;
	}
	return false;
}

void InfoExtractor::release(Data & entry){
	if (entry.company != NULL)
		delete []entry.company;
	if (entry.position != NULL)
		delete []entry.position;
	if (entry.publish_time != NULL)
		delete []entry.publish_time;
	if (entry.workplace != NULL)
		delete []entry.workplace;
	if (entry.email != NULL)
		delete []entry.email;
	if (entry.tel != NULL)
		delete []entry.tel;
	if (entry.skills != NULL)
		delete []entry.skills;
	if (entry.raw_text != NULL)
		delete []entry.raw_text;
}
