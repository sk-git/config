/***************************************************************************
 * 
 * Copyright (c) 2015 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file reader.cpp
 * @author map(com@baidu.com)
 * @date 2015/06/10 15:05:37
 * @brief 
 *  
 **/




#ifndef  __READER_CPP_
#define  __READER_CPP_

#include "rawData.h"
#include "reader.h"
#include <ctype.h>
#include <stdexcept>

namespace WU{
	int Reader::read(const char* file, Configure * cfg){
		if( _fd.load(file) != 0 ){
			return -1;
		}
		return build(cfg);
	}

	int Reader::keyParser(const char* buf, size_t length, struct pair_t* pair) {
		const char *p = buf;
		while(*p != 0 && *p != ':'){
			++p;
		}
		if(0 == *p || p == buf){ //到达末尾或在开头
			return -1;
		}
		if(getWord(buf, p, &(pair->key)) != 0) {
			return -1;
		}

		pair->value = p+1;
		pair->value = getMiddle(pair->value);
		//value : 引号转义？
		return 0;
	}

	int Reader::sectionParser(const char* buf, size_t length, str_t* str) {
		const char *p = buf;
		const char *end = buf;
		while(*end != 0 && *end != ']') {
			++end;
		}
		if(0 == *end || p+1 >= end) {
			return -1;
		}
		if(getWord(p+1, end, str) != 0){
			return -1;
		}
		++end;
		//检查末尾没有多余字符
		while(*end){
			if(*end == '#'){
				return 0;
			}
			if(!isspace(*end)){
				return -1;
			}
			++end;
		}
		return 0;
	}

	str_t Reader::getMiddle(const str_t& str) {
		int i, j;
		if(str.size() == 0){
			return str;
		}
		//以下两个循环除掉行中没必要的空格
		for(i = 0; i < (int)str.size(); ++i){
			if(!isspace(str[i])){
				break;
			}
		}
		for(j = (int)str.size() - 1; j >= 0; --j){
			if(!isspace(str[j])){
				break;
			}
		}
		return str.substr(i, j+1-i);
	}

	int Reader::getWord(const char * from, const char * to, str_t * str) {
		//左闭右开区间[from, to)
		int status = 0; //空格0->字符串1->空格2
		const char *f1 = from;
		const char *f2 = to;
		//以下循环除掉行中没必要的空格,但是如果字符串中有空格将返回-1
		for(const char *i = from; i < to; ++i) {
			if(isspace(*i)){
				if(status == 1){
					f2 = i;
					status = 2;
				}
			} else {
				if(status == 0) {
					status = 1;
					f1 = i;
				} else if(status == 2) {
					return -1;
				}
			}
		}
		if(f1 >= f2) {
			return -1;
		}
		str_t tmp;
		tmp.append(f1, f2-f1);
		*str = tmp;
		return 0;
	}

	int Reader::build(Configure *cfg) {
		int ret = 0;
		for(size_t i = 0; i < _fd.lineNum(); ++i){
			// _cur_line = i+1;
			size_t length;
			if(i != _fd.lineNum() - 1) {
				//继续读
				length = (size_t)_fd.getLine(i+1) - (size_t)_fd.getLine(i);
			} else {
				length = (size_t)_fd.size() - (size_t)_fd.getLine(i);
			}
			if(push(cfg, _fd.getLine(i), length) != 0){
				ret = -1;
			}
		}
		// _cur_line = -1;
		return ret;
	}

	int Reader::push(Configure * cfg, const char * buf, size_t length) {
		const char *p = buf;
		while(*p != 0 && isspace(*p)){
			++p;
		}
		try{
			if(*p == '#' || *p == 0){ //is comment or blank line
				return 0;
			} else if (*p == '['){ //must be section
				str_t str;
				if( sectionParser(p, length, &str) != 0 ){
					return -1;
				}
				cfg->changeSection(str);
			} else { // is config key-value pair
				struct pair_t pair;
				if( keyParser(p, length, &pair) != 0 ){
					return -1;
				}
				cfg->pushPair(pair.key, pair.value);
			}
		} catch(std::runtime_error){
			return -1;
		}
		return 0;
	}

}

#endif  //__READER_CPP_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
