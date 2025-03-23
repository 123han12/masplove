/*
 * @Author: 123han12 2146298774@qq.com
 * @Date: 2025-03-22 10:37:26
 * @LastEditors: 123han12 2146298774@qq.com
 * @LastEditTime: 2025-03-23 18:05:45
 * @FilePath: /masplove/sylar/src/log/Logger.cpp
 * @Description: Logger 具体实现
 * 
 * Copyright (c) 2025 by ${git_name_email}, All Rights Reserved. 
 */
#include "Logger.h"

namespace sylar{ 


Logger::Logger(const std::string& name)
: m_name(name),
m_level(LogLevel::DEBUG)
{
    m_vecAppender.clear();
    m_formatter.reset(new LogFormatter("%d [%p] [%f:%l]:%m %n")); 
    /*
        XX(m , MessageFormatItem)
        XX(p , LevelFormatItem)
        XX(r , ElapseFormatItem)
        XX(c , LoggerNameFormatItem)
        XX(t , ThreadIdFormatItem)
        XX(n , NextLineFormatItem)
        XX(d , DateTimeFormatItem)
        XX(f , FileNameFormatItem)
        XX(l , LineFormatItem)
    */
}

void Logger::log(LogLevel::Level level, LogEvent::ptr event)
{
    if(level >= m_level)
    {   
        for(auto iter : m_vecAppender)
        {
            iter->log(shared_from_this() , level , event);    // 日志输出地输出对应的日志
        }
    }
}

void Logger::debug(LogEvent::ptr event)
{
    log(LogLevel::DEBUG, event);
}
void Logger::info(LogEvent::ptr event)
{
    log(LogLevel::INFO, event);
}
void Logger::warn(LogEvent::ptr event){
    log(LogLevel::WARN, event);

}
void Logger::error(LogEvent::ptr event){
    log(LogLevel::ERROR, event);
}
void Logger::fatal(LogEvent::ptr event)
{
    log(LogLevel::FATAL, event);
}
void Logger::addAppender(LogAppender::ptr appender){
    for(auto iter : m_vecAppender)
    {
        if(iter == appender)  // 已经存在，就不再重复添加
        {
            return;
        }
    }
    if(nullptr == appender->getFormatter())
    {   
        appender->setFormatter(m_formatter);    
    }
    m_vecAppender.push_back(appender);  // 放入日志器
}

void Logger::delAppender(LogAppender::ptr appender){
    for(auto iter = m_vecAppender.begin() ; iter != m_vecAppender.end() ; ++iter)
    {
        if((*iter) == appender)  // 找到对应的日志器，删除该日志输出地
        {
            m_vecAppender.erase(iter);
            break;
        }
    }
}

void Logger::setLogLevel(const LogLevel::Level level){
    if(m_level == level){
        return;
    }
    m_level = level;
}

LogLevel::Level Logger::getLogLevel()
{
    return m_level;
}

};
