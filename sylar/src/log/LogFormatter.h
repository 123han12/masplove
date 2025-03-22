/*
 * @Author: 123han12 2146298774@qq.com
 * @Date: 2025-03-22 10:46:11
 * @LastEditors: 123han12 2146298774@qq.com
 * @LastEditTime: 2025-03-22 17:31:35
 * @FilePath: /masplove/sylar/src/log/LogFormatter.h
 * @Description: 
 * 
 * Copyright (c) 2025 by ${git_name_email}, All Rights Reserved. 
 */
#ifndef __LOG_FORMATTER_H_
#define __LOG_FORMATTER_H_

#include <string>
#include <memory>
#include "LogEvent.h"

namespace sylar{

// 日志输出格式
class LogFormatter{
public:
    using ptr = std::shared_ptr<LogFormatter> ;
    std::string format(sylar::LogEvent::ptr event); // 根据传入的log事件返回对应的log的格式

};


}


#endif