/***************************************************************************
 * 
 * Copyright (c) 2015 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file configure.cpp
 * @author map(com@baidu.com)
 * @date 2015/06/10 15:05:48
 * @brief 
 *  
 **/


#ifndef  __CONFIGURE_CPP_
#define  __CONFIGURE_CPP_

#include "configure.h"
#include "log.h"
#include <stdexcept>

namespace WU{
	Configure::Configure() {
		create(CONFIG_GLOBAL);
		_section = this;
		_depth = 0;
		_reader = new Reader();
	}

	Configure::~Configure(){
	    delete _reader;
	}

	int Configure::load(const char* filename) {
        int ret = 0;
		if(filename == NULL){
			LOG_FATAL("filename %s is NULL", filename);
			return -1;
		}
		ret = _reader->read(filename, this);

		return ret;
	}

	int Configure::changeSection(str_t str) {
		//str是去除[]的部分
		if(str[0] != '.'){
			_section = this;
			_depth = 0;
		} else{
			int i;
			for(i = 0; i < (int)str.size(); ++i){
				if(str[i] != '.'){
					break;
				}
			}

			if((int)i > _depth){
				return -1;
			}
			str = str.substr(i);
			//--i;
			while(i < _depth){
				_section = _section->getFather();
				_depth--;
			}
		}

		ConfigGroup * _bak_section = _section;
		_section = (ConfigGroup*)_section->relativeSection(str, &_depth);
		if(_section == NULL){
			_section = _bak_section;
		}
	}

	void Configure::pushPair(const str_t& key,const str_t& value) {
		ConfigUnit* tmp = new ConfigUnit(key, value);
		if(_section && _section->push(key, tmp)){
			throw std::runtime_error("Confiure push fail");
		}
	}
}

#endif  //__CONFIGURE_CPP_



/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
