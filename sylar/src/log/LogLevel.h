/*
 * @Author: 123han12 2146298774@qq.com
 * @Date: 2025-03-22 10:42:00
 * @LastEditors: 123han12 2146298774@qq.com
 * @LastEditTime: 2025-03-22 17:28:52
 * @FilePath: /masplove/sylar/src/log/LogLevel.h
 * @Description: 日志级别定义
 * 
 * Copyright (c) 2025 by ${git_name_email}, All Rights Reserved. 
 */
#ifndef __LOG_LEVEL_H__
#define __LOG_LEVEL_H__

namespace sylar{

// 日志级别
class LogLevel{
public:
    enum Level{
        DEBUG = 1,
        INFO = 2,
        WARN = 3,
        ERROR = 4,
        FATAL = 5
    };
};

}


#endif