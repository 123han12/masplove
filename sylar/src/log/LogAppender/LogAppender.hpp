/*
 * @Author: 123han12 2146298774@qq.com
 * @Date: 2025-03-22 10:38:33
 * @LastEditors: 123han12 2146298774@qq.com
 * @LastEditTime: 2025-03-22 18:04:04
 * @FilePath: /masplove/sylar/src/log/LogAppender/LogAppender.hpp
 * @Description: 日志输出地，抽象基类，可能存在多个子类 
 * 
 * Copyright (c) 2025 by ${git_name_email}, All Rights Reserved. 
 */
#ifndef __LOGAPPENDER_H__ 
#define __LOGAPPENDER_H__

#include "LogLevel.h"
#include "LogFormatter.h"
namespace sylar{

class LogAppender{
public:
    using ptr = std::shared_ptr<LogAppender>;
    LogAppender(){};
    void setFormatter(LogFormatter::ptr val) {m_format = val;}
    void setLevel(LogLevel::Level val){m_level = val;}
    virtual ~LogAppender(){}
    virtual void log(LogLevel::Level level, const LogEvent::ptr event) = 0 ;
protected:
    LogLevel::Level m_level;        // 日志级别,只有日志的级别>= m_level 时才会输出日志
    LogFormatter::ptr m_format;     // 日志格式
};


}; 

#endif 