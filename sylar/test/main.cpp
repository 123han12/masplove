/*
 * @Author: 123han12 2146298774@qq.com
 * @Date: 2024-08-27 22:07:12
 * @LastEditors: 123han12 2146298774@qq.com
 * @LastEditTime: 2025-03-23 18:06:28
 * @FilePath: /masplove/test/main.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include <iostream>
#include "Logger.h"

int main()
{
    sylar::Logger::ptr logger(new sylar::Logger);
    logger->addAppender(sylar::LogAppender::ptr(new sylar::StdoutLogAppender));
    std::string str_message("hello sylar");
    sylar::LogEvent::ptr event(new sylar::LogEvent(__FILE__ , __LINE__ 
    , 0 , 0 , 0 , time(0) , str_message
    ) );

    logger->log(sylar::LogLevel::DEBUG , event);


    return 0;
}