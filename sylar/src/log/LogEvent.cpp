/*
 * @Author: 123han12 2146298774@qq.com
 * @Date: 2025-03-22 10:39:16
 * @LastEditors: 123han12 2146298774@qq.com
 * @LastEditTime: 2025-03-23 17:40:50
 * @FilePath: /masplove/sylar/src/log/LogEvent.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "LogEvent.h"

sylar::LogEvent::LogEvent(const char *file,  int32_t line, uint32_t threadId, 
uint32_t fiberId, uint32_t elapse, uint64_t time , const std::string& context)
{
    m_file = file;
    m_line = line;
    m_threadId = threadId;
    m_fiberId = fiberId;
    m_elapse = elapse;
    m_time = time;
    m_content = context;
}
