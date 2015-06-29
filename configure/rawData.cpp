/***************************************************************************
 * 
 * Copyright (c) 2015 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file rawData.cpp
 * @author map(com@baidu.com)
 * @date 2015/06/08 18:24:39
 * @brief 
 *
 **/

#ifndef  __RAWDATA_CPP_
#define  __RAWDATA_CPP_

#include "rawData.h"
#include <iostream>
#include <fstream>
#include "log.h"
using namespace std;

namespace WU{
	RawData::RawData() {
		_lnum = 0;
		_file = NULL;
		_file_original = NULL;
		_fsize = 0;
		_bufsize = 0;
	}

	RawData::~RawData(){
		if(_file){
			free(_file);
		}
		if(_file_original){
			free(_file_original);
		}
	}

	size_t RawData::lineNum() const {
		return _lnum;
	}

	size_t RawData::size() const {
		return _fsize;
	}

	int RawData::load(const char* filename) {
		filebuf * pbuf;
		ifstream filestr;
		// 要读入整个文件，必须采用二进制打开 
		filestr.open (filename, ios::binary);
		// 获取filestr对应buffer对象的指针 
		pbuf = filestr.rdbuf();
		if (pbuf == NULL)
		{
			/* code */
			LOG_FATAL("open file %s fail", filename);
			return -1;
		}
		
		_fsize = pbuf->pubseekoff(0, ios::end, ios::in);
		_bufsize = ((_fsize >> 12) + 1) << 12;
		_file = (char *)malloc(_bufsize);
		if (_file == NULL)
		{
			LOG_FATAL("file %s is NULL", filename);
			return -1;
		}

		pbuf->pubseekpos (0, ios::in);
		 
		// 获取文件内容
		if (pbuf->sgetn(_file, _fsize) != (ssize_t) _fsize) {
			LOG_FATAL("get content of file %s fail", filename);
			free(_file);
			_file = NULL;
			return -1;
		}

		return rebuild();
	}

	const char* RawData::getLine(int idx) {
		if(idx < 0 || (size_t)idx >= lineNum()){
			return NULL;
		}
		return (const char *)(_file + _line[idx]);
	}

	int RawData::rebuild() {
		if(_fsize == 0) {
			return -1;
		}
		if(_file_original != NULL) {
			free(_file_original);
			_file_original = NULL;
		}
		_file_original = (char *)malloc(_bufsize);
		if(_file_original != NULL) {
			memcpy(_file_original, _file, _bufsize);
		} else {
			LOG_FATAL("fail to create a copy of file");
			return -1;
		}
		_line.clear();
		_line.push_back(0);
		for(size_t i = 0; i < _fsize; ++i) {
			if(_file[i] == '\n' || _file[i] == '\r' || _file[i] == '\0'){
				_file[i] = '\0';
				_line.push_back(i+1);
			}
		}
		_file[_fsize] = '\0';
		_lnum = _line.size();
		_line.push_back(_fsize);//多余的一行的位置，便于计算最后一行的长度
		return 0;
	}

}
#endif  //__RAWDATA_CPP_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
