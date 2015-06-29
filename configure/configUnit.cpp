/***************************************************************************
 * 
 * Copyright (c) 2015 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file configUnit.cpp
 * @author map(com@baidu.com)
 * @date 2015/06/09 15:15:34
 * @brief 
 *  
 **/



#ifndef  __CONFIGUNIT_CPP_
#define  __CONFIGUNIT_CPP_

#include "log.h"
#include "configUnit.h"
#include <stdlib.h>

namespace WU{
	ConfigUnit::ConfigUnit(const str_t& key,const str_t& value) {
		_key = key;
		_value = value;
	}

    ConfigUnit* ConfigUnit::_g_unit = new ConfigUnit();

	const ConfigUnit& ConfigUnit::operator[] (const char* str) const {
		return *_g_unit;
	}

	const ConfigUnit& ConfigUnit::operator[] (const str_t& str) const {
		return *_g_unit;
	}

	const ConfigUnit& ConfigUnit::operator[] (int idx) const {
		return *_g_unit;
	}

	void ConfigUnit::print() const {
			printf("_key=[%s], _value=[%s]\n", _key.c_str(), _value.c_str());
	}

	int ConfigUnit::selfType() const {
		return CONFIG_UNIT_TYPE;
	}

	int ConfigUnit::get_char(char* value) {
    	LOG_DEBUG("Config : Get char from _key [%s]", _key.c_str());
		if(_value == ""){
			LOG_WARNING("_value of _key %s is empty", _key.c_str());
			return -1;
		}
        strcpy(value, _value.c_str());

		return 0;
	}

	int ConfigUnit::get_int(int* value) {
		LOG_DEBUG("Config : Get char from _key [%s]", _key.c_str());
		if(_value == ""){
			LOG_WARNING("_value of _key %s is empty", _key.c_str());
			return -1;
		}
		*value = atoi(_value.c_str());

		return 0;
	}

	int ConfigUnit::get_std_string(str_t* value) {
		LOG_DEBUG("Config : Get char from _key [%s]", _key.c_str());
		if(_value == ""){
			LOG_WARNING("_value of _key %s is empty", _key.c_str());
			return -1;
		}

		value = &_value;
		return 0;
	}

    ConfigUnit* ConfigUnit::relativeSection(str_t str, int* idx) {
        return NULL;
    }

}

#endif  //__CONFIGUNIT_CPP_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */


















/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
