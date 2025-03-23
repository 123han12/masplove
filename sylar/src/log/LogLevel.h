/*
 * @Author: 123han12 2146298774@qq.com
 * @Date: 2025-03-22 10:42:00
 * @LastEditors: 123han12 2146298774@qq.com
 * @LastEditTime: 2025-03-23 16:09:21
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
        UNKNOW = 0,
        DEBUG = 1,
        INFO = 2,
        WARN = 3,
        ERROR = 4,
        FATAL = 5
    };
    static const char* toString(LogLevel::Level level)
    {
        switch(level)
        {
#define XX(name)              \
        case Level::name:     \
        {                     \
            return #name;     \
        }
            XX(UNKNOW)
            XX(DEBUG)
            XX(INFO)
            XX(WARN)
            XX(ERROR)
            XX(FATAL)
#undef XX
        }
        return "UNKNOW LEVEL";
    }
};

}


#endif