/***************************************************************************
 * 
 * Copyright (c) 2015 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file configGroup.h
 * @author wuzhibin(com@baidu.com)
 * @date 2015/06/08 14:37:32
 * @brief 
 *  
 **/




#ifndef  __CONFIGGROUP_H_
#define  __CONFIGGROUP_H_

#include "configUnit.h"
#include <map>
#include <vector>

namespace WU{

    class ConfigGroup:public ConfigUnit{
        
        public:
                ConfigGroup(const char* name,ConfigGroup* father=NULL);
                ConfigGroup(){}
                virtual ~ConfigGroup();
                virtual const ConfigUnit& operator[] (const char*) const;
                virtual const ConfigUnit& operator[] (const str_t&) const;
                virtual void print() const;
                virtual ConfigUnit* relativeSection(str_t, int*);
                virtual int push(const str_t key,ConfigUnit* unit);
                ConfigGroup* getFather() const;
                str_t getName() const;
                virtual int selfType() const;
                int getLevel() const;

        protected:
                int _level;
                ConfigGroup* _father;
                str_t _name;
                std::map<str_t,ConfigUnit*> _map;
                /**
                * 存放所有key
                */
                std::vector <str_t > _list;
                typedef std::map<str_t, ConfigUnit*>::iterator itr_t;
                typedef std::map<str_t, ConfigUnit*>::const_iterator const_itr_t;
        protected:
                virtual void create(const char* name,ConfigGroup* father=NULL);
    };


}

#endif  //__CONFIGGROUP_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
