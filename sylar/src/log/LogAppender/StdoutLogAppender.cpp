/*
 * @Author: 123han12 2146298774@qq.com
 * @Date: 2025-03-22 10:40:54
 * @LastEditors: 123han12 2146298774@qq.com
 * @LastEditTime: 2025-03-22 18:01:47
 * @FilePath: /masplove/sylar/src/log/LogAppender/StdoutLogAppender.cpp
 * @Description: 
 * 
 * Copyright (c) 2025 by ${git_name_email}, All Rights Reserved. 
 */
#include "StdoutLogAppender.h"

#include <iostream>

namespace sylar{
    StdoutLogAppender::StdoutLogAppender()
{}

StdoutLogAppender::~StdoutLogAppender()
{
    
}

void StdoutLogAppender::log(LogLevel::Level level, const LogEvent::ptr event) 
{
    if(m_level >= level)
    {
        std::cout << m_format->format(event);
    }
}
};