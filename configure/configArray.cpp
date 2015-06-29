/***************************************************************************
 * 
 * Copyright (c) 2015 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file configArray.cpp
 * @author map(com@baidu.com)
 * @date 2015/06/09 18:42:24
 * @brief 
 *  
 **/



#ifndef  __CONFIGARRAY_CPP_
#define  __CONFIGARRAY_CPP_

#include "configGroup.h"
#include "configArray.h"
#include "log.h"

#include <vector>

namespace WU{
	ConfigArray::ConfigArray(const char* name, ConfigGroup* father) {
		create(name, father);
	}

	ConfigArray::~ConfigArray() {
		for(int i = 0; i < (int)_vec.size(); ++i){
			delete _vec[i];
		}
	}

	int ConfigArray::selfType() const {
		return CONFIG_ARRAY_TYPE;
	}

	void ConfigArray::print() {
		printf("Array--------[%s] : {\n", getName());
		for(int i = 0; i < (int)_vec.size(); ++i){
			_vec[i]->print();
		}
		printf("}\n");
	}

	const ConfigUnit& ConfigArray::operator[] (int idx) const {
		if(idx < (int)_vec.size()){
			return *_vec[idx];
		}
		return *_g_unit;
	}

	int ConfigArray::push(str_t key,ConfigUnit* unit) {
		_vec.push_back(unit);
		return 0;
	}
}

#endif  //__CONFIGARRAY_CPP_


/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
