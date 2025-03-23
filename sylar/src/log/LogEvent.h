/*
 * @Author: 123han12 2146298774@qq.com
 * @Date: 2025-03-22 10:39:09
 * @LastEditors: 123han12 2146298774@qq.com
 * @LastEditTime: 2025-03-23 17:41:06
 * @FilePath: /masplove/sylar/src/log/LogEvent.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#ifndef __LOG_EVENT_H__
#define __LOG_EVENT_H__

#include <string>
#include <stdint.h>
#include <memory>
#include "LogLevel.h"
namespace sylar{

// 将每条日志抽象为一个对象
class LogEvent {
public:
    using ptr = std::shared_ptr<LogEvent> ;
    LogEvent(const char* file , int32_t line ,
    uint32_t threadId , uint32_t fiberId , uint32_t elapse , uint64_t time , const std::string& context);

    const char* getFile() const {return m_file;}
    
    int32_t getLine() const {return m_line;}
    uint32_t getThreadId() const {return m_threadId;}
    uint32_t getFiberId() const {return m_fiberId;}
    uint32_t getElapse() const {return m_elapse;}
    uint64_t getTimeStamp() const {return m_time;}
    const std::string& getContent() const {return m_content;}
private:
    const char* m_file = nullptr; // 文件名
    int32_t m_line = 0;           // 行号
    uint32_t m_threadId = 0;      // 线程id
    uint32_t m_fiberId = 0;       // 协程id
    uint32_t m_elapse = 0;        // 程序启动到现在的毫秒数
    uint64_t  m_time;             // 时间戳
    std::string m_content;        // 内容
};

}


#endif