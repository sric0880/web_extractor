/*
 * Dictionary.cpp
 *
 *  Created on: 2013-5-27
 *      Author: qiong
 */

#include "Dictionary.h"

Dictionary::Dictionary() {
	datrie = (my_datrie *) malloc(sizeof(my_datrie));
	da_init();
	ifstream infile(filename); // 打开词典
	if (!infile.is_open()) // 打开词典失败则退出程序
	{
		printf("Unable to open input file: %s\n", filename);
	}
	string word; //保存每个词
	while (getline(infile, word)) // 读入词典的每一行并将其添加入哈希中
	{
		da_insert((const unsigned char *)word.c_str());
	}
}

Dictionary::~Dictionary() {
}

void Dictionary::da_init() {
	datrie->max_size = 0;
	datrie->numofnodes = 1;
	long i;
	for (i = 0; i < MAXSIZE; i++) {
		datrie->base_[i] = 0;
		datrie->check_[i] = -1;
	}
}

int Dictionary::da_insert(const unsigned char * word) {
	long s = 0, t = 0;
	size_t i;
	for (i = 0; i < strlen((const char*)word); i++) {
		unsigned char ch = (unsigned char) (*(word + i));
		t = da_abs(datrie->base_[s]) + ALP_ID(ch);
		if ((ALP_ID(ch) < 1) || (ALP_ID(ch) > ALPSIZE)) {
			return -2;
		}
		if (t >= MAXSIZE - ALPSIZE)
			return -1;
		if (datrie->check_[t] == s) {
			s = t;
		} else if (ISEMPTY(t,datrie)) {
			datrie->base_[t] = t;
			datrie->check_[t] = s;
			datrie->max_size = (t > datrie->max_size) ? t : datrie->max_size;
			datrie->numofnodes++;
			s = t;
		} else {
			//如果当前偏移位置已经被占用了
			long newposition = find_suitable_position(s, ALP_ID(ch));
			if (newposition > 0) {
				relocate(s, newposition);
				//重新分配之后回到上一状态
				i--;
			} else {
				return -1;
			}

		}
	}
	//负数表示终止状态
	datrie->base_[s] = -1 * (da_abs(datrie->base_[s]));
	return 0;
}

long Dictionary::find_suitable_position(long s,unsigned char c) {
	if (da_abs(datrie->base_[s]) + c >= MAXSIZE - ALPSIZE) {
		return -1;
	}
	long bases = da_abs(datrie->base_[s]);
	//首先检测s状态在收入字符c之后的的位置是否已经被占用了。
	//建立一个数组来存储当前已经有的兄弟节点和新要加入的节点c
	unsigned char sonofs[ALPSIZE] = { 0 };
	long i;
	int ns = 0;
	for (i = bases + 1; i <= bases + ALPSIZE; i++) {
		if ((datrie->check_[i]) == s) {
			sonofs[ns++] = i - bases;
		}
	}
	sonofs[ns++] = c;

	//下面的循环可能比较耗费时间。可以采用G-link来进行优化
	while (bases++ < MAXSIZE - ALPSIZE) {
		int j = 0;
		for (j = 0; j < ns; j++) {
			if (datrie->check_[bases + sonofs[j]] == -1) {
				if (j == (ns - 1)) {
					return bases;
				}
			} else {
				break;
			}
		}
	}
	return -1;
}
void Dictionary::relocate(long s, long newbase) {
	int i, ns = 0, num;
	long bases = da_abs(datrie->base_[s]);
	unsigned char sonofs[ALPSIZE] = { 0 };
	for (i = 1; i <= ALPSIZE; i++) {
		if ((datrie->check_[bases + i]) == s)
			sonofs[ns++] = i;
	}
	for (num = 0; num < ns; num++) {
		datrie->check_[newbase + sonofs[num]] = s;
		datrie->base_[newbase + sonofs[num]] = datrie->base_[bases
				+ sonofs[num]];
		int j, ngs = 0, grandnum;
		unsigned char grandsonofs[ALPSIZE] = { 0 };
		for (j = 1; j <= ALPSIZE; j++) {
			if ((datrie->check_[da_abs(datrie->base_[bases + sonofs[num]]) + j])
					== (bases + sonofs[num]))
				grandsonofs[ngs++] = j;
		}
		for (grandnum = 0; grandnum < ngs; grandnum++) {
			datrie->check_[da_abs(datrie->base_[bases + sonofs[num]])
					+ grandsonofs[grandnum]] = newbase + sonofs[num];
		}
		datrie->check_[bases + sonofs[num]] = -1;
		datrie->base_[bases + sonofs[num]] = 0;
	}
	datrie->base_[s] = newbase * (datrie->base_[s] >= 0 ? 1 : -1);
	return;
}

long Dictionary::da_find(const unsigned char * word) {
	unsigned char c;
	long s = 0, t;
	int len = strlen((const char*)word);
	while ((c = *(word++)) != 0) {
		t = da_abs(datrie->base_[s]) + ALP_ID(c);
		if (datrie->check_[t] == s) {
			s = t;
			len--;
			if(len == 0){
				if ((datrie->base_[s] < 0))
					return s;
				else
					return 0;
			}
		} else {
			return -1;
		}
	}
	return -1;
}

int Dictionary::da_delete(const unsigned char * word) {
	//首先在datrie中查找对应的字符串
	long s = -1;
	int i;
	if ((s = da_find(word)) < 0)
		return -1;
	for (i = 1; i <= ALPSIZE; i++) {
		if (datrie->check_[da_abs(datrie->base_[s]) + i] == s) {
			//表示有子节点则将base_[s]值置为正数然后返回
			datrie->base_[s] *= -1;
			return 0;
		}
	}
	//如果没有子节点则删除该节点
	//是不是正确的?
	//p为s的父节点
	long p;
	p = da_abs(datrie->check_[s]);
	//删除s节点
	datrie->check_[s] = -1;
	datrie->base_[s] = 0;
	//如果没有子节点
	long temp = 0;
	while (have_child(p) && (datrie->base_[p] >= 0)) {
		if (p > 0) {
			temp = datrie->check_[p];
			datrie->check_[p] = -1;
			datrie->base_[p] = 0;
			p = temp;
		} else {
			break;
		}
	}
	return 0;
}

int Dictionary::have_child(long s) {
	int l;
	for (l = 1; l <= ALPSIZE; l++) {
		if (datrie->check_[da_abs(datrie->base_[s]) + l] == s)
			return 0;
	}
	return -1;
}

long Dictionary::da_abs(long a) {
	if (a < 0)
		return -a;
	else {
		return a;
	}
}

void Dictionary::da_print() {
	long l;
	printf("base:\n");
	for (l = 0; l <= datrie->max_size; l++) {
		if (datrie->base_[l] != 0)
			printf("%-5ld ", datrie->base_[l]);
		if (l == 0)
			printf("\n");
	}
	printf("max_size=%ld\n", datrie->max_size);
	printf("check:=\n");
	for (l = 0; l <= datrie->max_size; l++) {
		if (-1 != datrie->check_[l])
			printf("%-5ld ", datrie->check_[l]);
		if (l == 0)
			printf("\n");
	}
	printf("max_size=%ld\n", datrie->max_size);
}
