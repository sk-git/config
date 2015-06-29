/***************************************************************************
 * 
 * Copyright (c) 2015 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file rawData.h
 * @author wuzhibin(com@baidu.com)
 * @date 2015/06/08 13:59:21
 * @brief 
 *  
 **/




#ifndef  __RAWDATA_H_
#define  __RAWDATA_H_

#include <sys/stat.h>
#include <fcntl.h>
#include <vector>

namespace WU{

    class RawData{
        
        public:
                RawData();
                ~RawData();
                int load(const char*);
                size_t lineNum() const; 
                size_t size() const;
                const char* getLine(int);


        protected:
                std::vector<size_t> _line;
                size_t _lnum;
                char* _file;
                char* _file_original;
                size_t _fsize; // 文件实际大小
                size_t _bufsize; // 给文件申请的缓冲区大小
                int rebuild();


    };


}
#endif  //__RAWDATA_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
