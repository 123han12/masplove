/*
 * @Author: 123han12 2146298774@qq.com
 * @Date: 2025-03-22 10:46:11
 * @LastEditors: 123han12 2146298774@qq.com
 * @LastEditTime: 2025-03-23 11:02:32
 * @FilePath: /masplove/sylar/src/log/LogFormatter.h
 * @Description: 
 * 
 * Copyright (c) 2025 by ${git_name_email}, All Rights Reserved. 
 */
#ifndef __LOG_FORMATTER_H_
#define __LOG_FORMATTER_H_

#include <string>
#include <memory>
#include <vector>
#include "LogEvent.h"
#include <iostream>

namespace sylar{
class Logger;
// 日志输出格式
class LogFormatter{
public:
    using ptr = std::shared_ptr<LogFormatter> ;

    LogFormatter(const std::string& pattern);

    /// @brief 根据传入的日志事件，按照固定的格式返回出字符串
    /// @param event 
    /// @return 一条日志
    std::string format(std::shared_ptr<Logger> logger ,LogLevel::Level level , sylar::LogEvent::ptr event); // 根据传入的log事件返回对应的log的格式

public:
    class FormatterItem {   // 解析event 中的部分
    public:
        using ptr = std::shared_ptr<FormatterItem>;
        FormatterItem(const std::string& fmt = "") {}
        virtual ~FormatterItem(){};
        virtual void format(std::shared_ptr<Logger> logger ,std::ostream& os, LogLevel::Level level , LogEvent::ptr event) = 0 ;
    };

private:
    void init();
private:
    std::string m_pattern;                    // 用来初始化日志格式器
    std::vector<FormatterItem::ptr> m_items;   // 日志格式器的输出项
};


}


#endif