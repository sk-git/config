/***************************************************************************
 * 
 * Copyright (c) 2015 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file configure.h
 * @author wuzhibin(com@baidu.com)
 * @date 2015/06/08 14:57:10
 * @brief 
 *  
 **/




#ifndef  __CONFIGURE_H_
#define  __CONFIGURE_H_

#define CONFIG_GLOBAL "GLOBAL"

#include "configGroup.h"
#include "reader.h"

namespace WU{
    class Reader;

    class Configure:public ConfigGroup {

        public:
                Configure();
                ~Configure();
                /**
                 * @brief 从指定的文件中载入配置文件和约束文件
                 *
                 * @param filename   : const char* 配置文件文件名
                 * @return  int  0表示成功，其余为失败
                 * @retval   
                 * @see 
                 * @author shengkuang
                 * @date 2015/06/10 15:22
                 **/
                int load(const char* filename);
                int changeSection(str_t);
                void pushPair(const str_t& key,const str_t& value);
        private:
                Reader* _reader;
                ConfigGroup* _section;
                int _depth;

    };


}

#endif  //__CONFIGURE_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
