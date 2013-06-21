/*
 * UserDictforSkills.cpp
 *
 *  Created on: 2013-5-25
 *      Author: qiong
 */

#include "DuplicateRemoval.h"
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string.hpp>

DuplicateRemoval::DuplicateRemoval()
{
	//load file
	ifstream in;
	in.open(FILE_NAME,ifstream::in);
	string line;
	while(getline(in,line)){
		if(line=="")
			continue;
		stringstream sline;
		sline.str(line);
		int docid;
		size_m simhash;
		sline>>simhash>>docid;
		fingerprint[simhash]=docid;
	}
	in.close();
	out.open(FILE_NAME, ofstream::out|ofstream::app);
}

DuplicateRemoval::~DuplicateRemoval() {
	//write to file
	fingerprint.clear();
	out.close();
}

bool DuplicateRemoval::is_duplicate(string str){
	//特征抽取
	int i = 0;
	vector <string> words;
	using namespace boost::algorithm;
	trim(str);
	split(words, str , is_any_of(" "));
	int num_lines = words.size();
	//文档指纹生成
	int bitsize = sizeof(size_m)*8;
	int v[bitsize];
	for(i = 0; i<num_lines; ++i){
		size_m hash_val = hash_fn(words[i]);
//		cout<<bitset<64>(hash_val)<<endl;
//		printf("%llu\n",hash_val);
		size_m bitmask =0;
		for(int i = 0; i<bitsize; ++i){
			bitmask = (size_m)1<<i;
			if(bitmask & hash_val)
				++v[i];
			else
				--v[i];
		}
	}
	size_m fp = 0;
	for(int i = 0; i<bitsize; ++i){
		if(v[i]>=0){
			fp += (size_m)1<<i;
		}
	}
	//计算最小海明距离
	if(_hamming_distance(fp)>2){
		int docid = fingerprint.size();
		fingerprint[fp] = docid;
		out<<fp<<" "<<docid<<"\n";
		out.flush();
		return false;
	}else
		return true;
}

size_m DuplicateRemoval::hash_fn(string x){
	if(x=="") return 0;
	else{
		const unsigned int m = 0x5bd1e995;
		const unsigned int seed = 0xee6b27eb;
		const int r = 24;

		size_t len = x.length();
		unsigned int h1 = seed ^ len;
		unsigned int h2 = 0;

		const unsigned int * data = (const unsigned int *) x.c_str();

		while (len >= 8) {
			unsigned int k1 = *data++;
			k1 *= m;
			k1 ^= k1 >> r;
			k1 *= m;
			h1 *= m;
			h1 ^= k1;
			len -= 4;

			unsigned int k2 = *data++;
			k2 *= m;
			k2 ^= k2 >> r;
			k2 *= m;
			h2 *= m;
			h2 ^= k2;
			len -= 4;
		}

		if (len >= 4) {
			unsigned int k1 = *data++;
			k1 *= m;
			k1 ^= k1 >> r;
			k1 *= m;
			h1 *= m;
			h1 ^= k1;
			len -= 4;
		}

		switch (len) {
		case 3:
			h2 ^= ((unsigned char*) data)[2] << 16;
		case 2:
			h2 ^= ((unsigned char*) data)[1] << 8;
		case 1:
			h2 ^= ((unsigned char*) data)[0];
			h2 *= m;
		};

		h1 ^= h2 >> 18;
		h1 *= m;
		h2 ^= h1 >> 22;
		h2 *= m;
		h1 ^= h2 >> 17;
		h1 *= m;
		h2 ^= h1 >> 19;
		h2 *= m;

		unsigned long long h = h1;
		h = (h << 32) | h2;
		return h;
	}
}

//最小的距离 海明距离
int DuplicateRemoval::_hamming_distance(size_m &hash){
	int min_dis = sizeof(size_m)*8;
	for(auto & x: fingerprint){
		size_m p = (x.first^hash);
		int tot = 0;
		while(p){
			++tot;
			p &= (p-1);
		}
		if(min_dis>tot) min_dis = tot;
	}
	// printf("distance: %d\n", min_dis);
	return min_dis;
}

//inline bool DuplicateRemoval::_pos_filter(int pos_id){
//	for(int i =0;i<POS_LEN;++i){
//		if(pos_ids[i]==pos_id)
//			return true;
//	}
//	return false;
//}
