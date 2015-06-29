/***************************************************************************
 * 
 * Copyright (c) 2015 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file reader.h
 * @author wuzhibin(com@baidu.com)
 * @date 2015/06/08 14:10:14
 * @brief 
 *  
 **/




#ifndef  __READER_H_
#define  __READER_H_

#include "rawData.h"
#include "configure.h"

namespace WU{
    class Configure;
    class Reader { 
        
        public:
                int read(const char*, Configure*);
                Reader(){}
                ~Reader(){}
        private:
                int build(Configure*);
                int push(Configure*, const char*, size_t);
                struct pair_t{
                    str_t key;
                    str_t value;
                };
                int sectionParser(const char*, size_t, str_t*);
                int keyParser(const char* buf,size_t length,pair_t* pair);
                int getWord(const char*, const char*, str_t*);
                str_t getMiddle(const str_t&);
                RawData _fd;
    };

}

#endif  //__READER_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
