/*
 * @Author: 123han12 2146298774@qq.com
 * @Date: 2025-03-22 10:37:20
 * @LastEditors: 123han12 2146298774@qq.com
 * @LastEditTime: 2025-03-23 17:14:18
 * @FilePath: /masplove/sylar/src/log/Logger.h
 * @Description: 
 * 
 * Copyright (c) 2025 by ${git_name_email}, All Rights Reserved. 
 */
#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <string>
#include <stdint.h>
#include <memory>
#include <vector>
#include <iostream>
#include <fstream>

#include "LogEvent.h"
#include "LogLevel.h"
#include "LogAppender.hpp"
#include "LogFormatter.h"
#include "StdoutLogAppender.h"
#include "FileLogAppender.h"

namespace sylar{

class LogFormatter;
// 日志输出器
class Logger : public std::enable_shared_from_this<Logger>
{
public:
    using ptr = std::shared_ptr<Logger>;
    Logger(const std::string& name = std::string(""));

    void log(LogLevel::Level evel, LogEvent::ptr event);

    void debug(LogEvent::ptr event);
    void info(LogEvent::ptr event);
    void warn(LogEvent::ptr event);
    void error(LogEvent::ptr event);
    void fatal(LogEvent::ptr event);

    void addAppender(LogAppender::ptr appender);
    void delAppender(LogAppender::ptr appender);
    
    void setLogLevel(const LogLevel::Level level);
    LogLevel::Level getLogLevel();

    void setLogName(const std::string& name) {m_name = name;}
    const std::string& getLogName() {return m_name;}

private:
    std::string m_name;                           // 日志器的名字
    LogLevel::Level m_level;                      // 日志器的级别,>= m_level 的日志才会被输出
    std::vector<LogAppender::ptr> m_vecAppender;  // 日志器输出地
    LogFormatter::ptr             m_formatter;    // 当appender 不存在formatter 时，使用此formatter
};  

}

#endif