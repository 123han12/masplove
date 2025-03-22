/*
 * @Author: 123han12 2146298774@qq.com
 * @Date: 2025-03-22 10:41:09
 * @LastEditors: 123han12 2146298774@qq.com
 * @LastEditTime: 2025-03-22 17:27:34
 * @FilePath: /masplove/sylar/src/log/LogAppender/FileLogAppender.cpp
 * @Description: 
 * 
 * Copyright (c) 2025 by ${git_name_email}, All Rights Reserved. 
 */

#include "FileLogAppender.h"


namespace sylar{

FileLogAppender::~FileLogAppender()
{
    if(m_fileStream.is_open())
    {
        m_fileStream.close();
    }
}

FileLogAppender::FileLogAppender(const std::string& file_path)
:m_filename(file_path)
{}

void FileLogAppender::log(LogLevel::Level level, const LogEvent::ptr event)
{
    if(m_level > level)  // 仅输出 level >= m_level 的日志 
    {
        return ;
    }

    std::string str_log = m_format->format(event);
    if(m_fileStream.is_open())
    {
        m_fileStream << str_log;   // 向打开的文件内写入log
    }
    else
    {
        m_fileStream.open(m_filename.c_str());
        m_fileStream << str_log;
    }
}

bool FileLogAppender::reopen()
{
    if(!m_fileStream.is_open())
    {
        m_fileStream.open(m_filename);
    }
    return m_fileStream.good();  // 成功打开文件的时候返回true
}
}