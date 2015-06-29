/***************************************************************************
 * 
 * Copyright (c) 2015 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file configArray.h
 * @author wuzhibin(com@baidu.com)
 * @date 2015/06/08 14:52:17
 * @brief 
 *  
 **/




#ifndef  __CONFIGARRAY_H_
#define  __CONFIGARRAY_H_

#include "configGroup.h"
#include <vector>

namespace WU{

    class ConfigArray:public ConfigGroup{
        
        public:
                ConfigArray(const char* name,ConfigGroup* father=NULL);
                virtual ~ConfigArray();
                virtual int push(str_t key,ConfigUnit* unit);
                virtual int selfType() const;
                void print();
                const ConfigUnit& operator[] (int idx) const;
                
        public:
                std::vector<ConfigUnit*> _vec;


    };


}

#endif  //__CONFIGARRAY_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
