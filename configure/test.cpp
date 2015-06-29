/***************************************************************************
 * 
 * Copyright (c) 2015 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file test.cpp
 * @author shengkuang01(com@baidu.com)
 * @date 2015/05/21 19:46:35
 * @brief 
 *  
 **/
#include "rawData.h"
#include <iostream>
#include "log.h"
#include "configure.h"

using namespace WU;

int main(){
    // Log::init("./log/configure");
    Log::init("./out.log");
    Configure c;
    c.load("test.conf");
    c.print();
    std::cout<<std::endl<<std::endl;
    c["dict"]["arr"][0].print();

    return 0;
}

    











/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
