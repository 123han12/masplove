/*
 * @Author: 123han12 2146298774@qq.com
 * @Date: 2025-03-22 10:41:09
 * @LastEditors: 123han12 2146298774@qq.com
 * @LastEditTime: 2025-03-23 10:44:44
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
{
    
}

void FileLogAppender::log(std::shared_ptr<Logger> logger , LogLevel::Level level, const LogEvent::ptr event)
{
    if(level >= m_level)
    {
        m_fileStream << m_formater->format(logger , level , event); 
    }
}

bool FileLogAppender::reopen()
{
    if(m_fileStream)
    {
        m_fileStream.close();
    }
    m_fileStream.open(m_filename);
    return !!m_fileStream;  // 先转化为0和1
}
}