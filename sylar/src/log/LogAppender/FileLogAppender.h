/*
 * @Author: 123han12 2146298774@qq.com
 * @Date: 2025-03-22 10:41:13
 * @LastEditors: 123han12 2146298774@qq.com
 * @LastEditTime: 2025-03-22 17:26:15
 * @FilePath: /masplove/sylar/src/log/LogAppender/FileLogAppender.h
 * @Description: 文件输出流
 * 
 * Copyright (c) 2025 by ${git_name_email}, All Rights Reserved. 
 */
#ifndef __FILE_LOGAPPENDER_H__
#define __FILE_LOGAPPENDER_H__

#include <fstream>
#include "LogAppender.hpp"

namespace sylar{


class FileLogAppender: public LogAppender{
public:
    using ptr = std::shared_ptr<FileLogAppender> ; 
    FileLogAppender(const std::string& file_name);
    ~FileLogAppender();
    void log(LogLevel::Level level, const LogEvent::ptr event) override;
    bool reopen();
private:
    std::ofstream m_fileStream;
    std::string m_filename;
};

}


#endif 