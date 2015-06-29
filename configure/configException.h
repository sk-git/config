/***************************************************************************
 * 
 * Copyright (c) 2015 Baidu.com, Inc. All Rights Reserved
 * 
 **************************************************************************/
 
 
 
/**
 * @file configException.h
 * @author map(com@baidu.com)
 * @date 2015/06/10 16:07:15
 * @brief 
 *  
 **/




#ifndef  __CONFIGEXCEPTION_H_
#define  __CONFIGEXCEPTION_H_


namespace WU {

	class ConfigExcepction  
	{  
	public:  
	 
	    // 构造函数,参数为错误代码  
	    ConfigExcepction(const char*);

		~ConfigExcepction(){} 
	}; 

}

#endif  //__CONFIGEXCEPTION_H_

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
