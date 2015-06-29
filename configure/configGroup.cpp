/***************************************************************************
 * 
 * Copyright (c) 2015 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file configGroup.cpp
 * @author map(com@baidu.com)
 * @date 2015/06/09 15:53:48
 * @brief 
 *  
 **/




#ifndef  __CONFIGGROUP_CPP_
#define  __CONFIGGROUP_CPP_

#include "configGroup.h"
#include "configArray.h"
#include "log.h"
#include <stdexcept>
#include <ctype.h>
#include <map>

namespace WU {
	ConfigGroup::ConfigGroup(const char* name, ConfigGroup* father) {
		create(name, father);
	}

	ConfigGroup::~ConfigGroup(){
		itr_t itr = _map.begin();
		while(itr != _map.end()){
			delete itr->second;
			++itr;
		}
	}

	const ConfigUnit& ConfigGroup::operator[] (const char* str) const {
		return (*this)[str_t(str)];
	}

	const ConfigUnit& ConfigGroup::operator[] (const str_t& str) const{
		const_itr_t itr = _map.find(str);
		if(itr != _map.end()){
			return *(itr->second);
		}
		return *_g_unit;
	}

	void ConfigGroup::print() const {
		str_t sec = getName();
		ConfigGroup * tmp = getFather();
		while(tmp != NULL){
			sec = str_t(tmp->getName()).append(".").append(sec);
			tmp = tmp->getFather();
		}
		printf("Section-------[%s]\n", sec.c_str());
		for(int i = 0; i < (int)_list.size(); ++i){
			if(_map.find(_list[i])-> second -> selfType() == CONFIG_UNIT_TYPE){
				_map.find(_list[i]) -> second -> print();
			}
		}
		for(int i = 0; i < (int)_list.size(); ++i){
			if(_map.find(_list[i]) -> second -> selfType() == CONFIG_ARRAY_TYPE){
				_map.find(_list[i]) -> second -> print();
		        LOG_DEBUG("ConfigArray print()");
			}
		}
		for(int i = 0; i < (int)_list.size(); ++i){
			if(_map.find(_list[i]) -> second -> selfType() == CONFIG_GROUP_TYPE){
				_map.find(_list[i]) -> second -> print();
			}
		}
	}

	ConfigUnit* ConfigGroup::relativeSection(str_t str, int* depth) {
		if(str == ""){
			return this;
		}
		// str_t child;
		// size_t global_len = strlen(CONFIG_GLOBAL);
		// if(str.substr(0, global_len) == str_t(CONFIG_GLOBAL) && 
		// 		(str.size() == global_len || str[global_len] == '.')){
		// 	ConfigGroup * sec = this;
		// 	while(sec->getFather()){
		// 		sec = sec->getFather();
		// 	}
		// 	(*depth) = 0;
		// 	str = str.size() > global_len ? str.substr(global_len+1) : "";
		// 	return sec->relativeSection(str, depth);
		// }
		// for(int i = 0; i < (int)str.size(); ++i){
		//	if(str[i] == '.'){
		//		str = str.substr(i+1);
		//		++(*depth);
		//		return (itr->second)->relativeSection(str, depth);
		//	}
		// }
		itr_t itr = _map.find(str);
		if(itr == _map.end()){
			ConfigGroup * tmp = new ConfigGroup(str.c_str(), this);
			++(*depth);
			push(str, tmp);
			return tmp;
		} else {
			++(*depth);
			if((itr->second)->selfType() != CONFIG_GROUP_TYPE){
				throw std::runtime_error("_section is not a group type");
			}
		    LOG_DEBUG("ConfigArray relativeSection()");
			return itr->second;
		}
	}

	int ConfigGroup::push(const str_t key,ConfigUnit* unit) {
		if(key[0] != '@'){
			//非字典和数组类型
			if(_map.find(key) == _map.end()){
				_map[key] = unit;
				_list.push_back(key);
			} else{
				return -1;
			}
		} else {
			//字典或数组
			itr_t itr = _map.find(key.substr(1));
			if(itr != _map.end()) {
				if(itr->second->selfType() == CONFIG_ARRAY_TYPE){
					((ConfigArray*)(itr->second))->push(key, unit);
				} else{
					return -1;
				}
			} else {
				//插入一个字典
				ConfigArray* array = new ConfigArray(key.c_str() + 1, this);
				if(this->push(key.substr(1), array) == 0) {
					array->push(key, unit);
				}
			}
		}
		return 0;
	}

	ConfigGroup* ConfigGroup::getFather() const {
		return _father;
	}

	str_t ConfigGroup::getName() const {
		return _name;
	}

	int ConfigGroup::selfType() const {
		return CONFIG_GROUP_TYPE;
	}

	int ConfigGroup::getLevel() const {
		return _level;
	}

	void ConfigGroup::create(const char* name,ConfigGroup* father) {
		_father = father;
		_name = name;
		if(_father) {
			_level = _father->getLevel() + 1;
		} else {
			_level = 0;
		}
	}
}

#endif  //__CONFIGGROUP_CPP_


/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
