/***************************************************************************
 * 
 * Copyright (c) 2015 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file configException.cpp
 * @author map(com@baidu.com)
 * @date 2015/06/10 16:06:57
 * @brief 
 *  
 **/



#ifndef  __CONFIGEXCEPTION_H_
#define  __CONFIGEXCEPTION_H_
 
#include <iostream>
#include "configException.h"

namespace WU {
	ConfigExcepction::ConfigExcepction(const char* errInfo) {  
	     	// 输出构造函数被调用信息  
	    std::cout<<errInfo<<std::endl;   
	}

}

#endif  //__CONFIGEXCEPTION_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
