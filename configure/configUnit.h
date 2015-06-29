/***************************************************************************
 * 
 * Copyright (c) 2015 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file configUnit.h
 * @author wuzhibin(com@baidu.com)
 * @date 2015/06/08 14:26:38
 * @brief 
 *  
 **/




#ifndef  __CONFIGUNIT_H_
#define  __CONFIGUNIT_H_

#include <string>

namespace WU{
    
    enum{
        CONFIG_UNIT_TYPE=0,
        CONFIG_GROUP_TYPE,
        CONFIG_ARRAY_TYPE,
        CONFIG_ERROR_TYPE
    };
    typedef std::string str_t;
    class ConfigUnit{
        
        public:
            ConfigUnit(const str_t& key,const str_t& value);
            ConfigUnit(){}
            virtual ~ConfigUnit(){}
            virtual const ConfigUnit& operator[] (const char*) const;
            virtual const ConfigUnit& operator[] (const str_t&) const;
            virtual const ConfigUnit& operator[] (int) const;
            virtual void print() const;
            virtual ConfigUnit* relativeSection(str_t,int*); // 寻找父块
            virtual int selfType() const;
            // 获取value
            virtual int get_char(char* value); // 获取字符值
            virtual int get_int(int* value); // 获取整数值
            virtual int get_std_string(str_t* value); // 获取string 值 
        protected:
            static ConfigUnit* _g_unit; // 默认空对象
            str_t _key;
            str_t _value;


    };

}

#endif  //__CONFIGUNIT_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
