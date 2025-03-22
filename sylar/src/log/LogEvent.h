#ifndef __LOG_EVENT_H__
#define __LOG_EVENT_H__

#include <string>
#include <stdint.h>
#include <memory>

namespace sylar{

// 将每条日志抽象为一个对象
class LogEvent {
public:
    using ptr = std::shared_ptr<LogEvent> ;

    LogEvent();
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