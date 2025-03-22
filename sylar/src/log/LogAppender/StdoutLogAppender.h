/*
 * @Author: 123han12 2146298774@qq.com
 * @Date: 2025-03-22 10:40:48
 * @LastEditors: 123han12 2146298774@qq.com
 * @LastEditTime: 2025-03-22 17:26:45
 * @FilePath: /masplove/sylar/src/log/LogAppender/StdoutLogAppender.h
 * @Description: 
 * 
 * Copyright (c) 2025 by ${git_name_email}, All Rights Reserved. 
 */
#ifndef __STDOUT_LOGAPPENDER_H__
#define __STDOUT_LOGAPPENDER_H__

#include <memory>
#include <fstream>

#include "LogAppender.hpp"
#include "LogLevel.h"
#include "LogEvent.h"


namespace sylar{

class StdoutLogAppender: public LogAppender{
public:
    using ptr = std::shared_ptr<StdoutLogAppender>;
    StdoutLogAppender();
    ~StdoutLogAppender();
    void log(LogLevel::Level level, const LogEvent::ptr event) override;
};

};


#endif