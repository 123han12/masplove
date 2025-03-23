/*
 * @Author: 123han12 2146298774@qq.com
 * @Date: 2025-03-22 10:40:07
 * @LastEditors: 123han12 2146298774@qq.com
 * @LastEditTime: 2025-03-23 17:57:15
 * @FilePath: /masplove/sylar/src/log/LogFormatter.cpp
 * @Description: 日志格式器输出
 * 
 * Copyright (c) 2025 by ${git_name_email}, All Rights Reserved. 
 */
#include "LogFormatter.h"
#include <sstream>
#include "Logger.h"
#include <map>
#include <functional>
// 如何实现这个formatter 

namespace sylar{

// 消息体 %m 
class MessageFormatItem : public LogFormatter::FormatterItem {
public:
    MessageFormatItem(const std::string& str = "") {}
    void format(std::shared_ptr<Logger> logger ,std::ostream& os, LogLevel::Level level, LogEvent::ptr event) override
    {
        os << event->getContent();
    }
};

// level %p
class LevelFormatItem : public LogFormatter::FormatterItem {
public:
    LevelFormatItem(const std::string& str = "") {}
    void format(std::shared_ptr<Logger> logger ,std::ostream& os , LogLevel::Level level, LogEvent::ptr event) override 
    {
        os << LogLevel::toString(level);
    }
};

// 程序启动时间 %r 
class ElapseFormatItem : public LogFormatter::FormatterItem{
public:
    ElapseFormatItem(const std::string& str = "") {}
    void format(std::shared_ptr<Logger> logger ,std::ostream& os , LogLevel::Level level ,LogEvent::ptr event) override 
    {
        os << event->getElapse();
    }
};


class LoggerNameFormatItem : public LogFormatter::FormatterItem {
public:
    LoggerNameFormatItem(const std::string& str = "") {}
    void format(std::shared_ptr<Logger> logger ,std::ostream& os , LogLevel::Level level ,LogEvent::ptr event) override{
        os << logger->getLogName();
    } 
};

// %t 线程id
class ThreadIdFormatItem : public LogFormatter::FormatterItem {
public:
    ThreadIdFormatItem(const std::string& str = "") {}
    void format(std::shared_ptr<Logger> logger ,std::ostream& os , LogLevel::Level level ,LogEvent::ptr event) override 
    {
        os << event->getThreadId();
    }
};


class FiberIdFormatItem : public LogFormatter::FormatterItem {
public:
    FiberIdFormatItem(const std::string& str = "") {}
    void format(std::shared_ptr<Logger> logger ,std::ostream& os , LogLevel::Level level ,LogEvent::ptr event) override 
    {
        os << event->getFiberId();
    }
};

// %d 时间
class DateTimeFormatItem : public LogFormatter::FormatterItem {
public:
    DateTimeFormatItem(const std::string& str = "", const std::string& format = "%Y:%m:%d %H:%M:%S")
    : m_date_format(format)
    {
        
    }
    void format(std::shared_ptr<Logger> logger ,std::ostream& os , LogLevel::Level level ,LogEvent::ptr event) override 
    {
        os << event->getTimeStamp();
    }
private:
    std::string m_date_format;
};

// %f 文件名
class FileNameFormatItem : public LogFormatter::FormatterItem {
public:
    FileNameFormatItem(const std::string& str = "") {}
    void format(std::shared_ptr<Logger> logger ,std::ostream& os , LogLevel::Level level ,LogEvent::ptr event) override 
    {
        os << event->getFile();
    }
};

// %l 行号
class LineFormatItem : public LogFormatter::FormatterItem {
public:
    LineFormatItem(const std::string& str = "") {}
    void format(std::shared_ptr<Logger> logger ,std::ostream& os , LogLevel::Level level ,LogEvent::ptr event) override 
    {
        os << event->getLine();
    }
};

// %n 换行
class NextLineFormatItem : public LogFormatter::FormatterItem {
public:
    NextLineFormatItem(const std::string& str = "") {}
    void format(std::shared_ptr<Logger> logger ,std::ostream& os , LogLevel::Level level ,LogEvent::ptr event) override 
    {
        os << std::endl;
    }
};

class StringFormatItem : public LogFormatter::FormatterItem {
public:
    StringFormatItem(const std::string& str = "") {m_str = str;}
    void format(std::shared_ptr<Logger> logger ,std::ostream& os , LogLevel::Level level ,LogEvent::ptr event) override 
    {
        os << m_str;
    }
private:
    std::string m_str;
};


/*----------------------------------------------------------------*/
LogFormatter::LogFormatter(const std::string& pattern) 
: m_pattern(pattern){
    init(); // 根据m_pattern 内容生成FormatterItem 对象到 m_items 格式容器内
}

std::string LogFormatter::format(std::shared_ptr<Logger> logger ,LogLevel::Level level ,sylar::LogEvent::ptr event)
{
    std::stringstream ss;
    for(auto& i: m_items)
    {
        i->format(logger, ss ,level, event);
    }
    return ss.str();
}

/// @brief 根据m_pattern 获取对应的对象放入到m_items 中去
// %xxx %xxx{xxx} %%  主要是这三种格式
void LogFormatter::init()
{
    // "%d [%p] %f %l %m %n"

    // str format type
    std::vector<std::tuple<std::string, std::string, int>> vec;
    std::string normal_str;
    for(size_t i = 0 ; i < m_pattern.size() ; i++)
    {
        if(m_pattern[i] != '%')
        {
            normal_str.append(1 , m_pattern[i]);
            continue;
        }

        if( i + 1 < m_pattern.size() && m_pattern[i + 1] == '%')
        {
            normal_str.append(1 , '%');
            continue;
        }

        // 遇到上述三种格式,此时pattern[i] = '%'
        size_t n = i + 1;
        int format_status = 0;   // 结束时0 和 2 都是合法状态，1为非法状态
        std::string str;
        std::string format;
        int i_fmt_begin;
        while(n < m_pattern.size())
        {
            if(!isalpha(m_pattern[n]) && m_pattern[n] != '{' && m_pattern[n] != '}') // 不是字母就终止解析
            {
                break;
            }
            if(0 == format_status)
            {
                if(m_pattern[n] == '{')
                {
                    str = m_pattern.substr(i + 1 , n - i - 1);
                    format_status = 1;
                    i_fmt_begin = n;
                }
                n ++;
            }
            else if(1 == format_status)
            {
                if(m_pattern[n] == '}')
                {
                    format = m_pattern.substr(i_fmt_begin , n - i_fmt_begin - 1);
                    format_status = 2;  // 结束状态
                    break;
                }
                n++;
            }
        }

        if(format_status == 0 )
        {   
            if(normal_str.size())
            {
                vec.push_back(std::make_tuple(normal_str , "" , 0));
                normal_str.clear();
            }
            str = m_pattern.substr(i + 1, n - i - 1);
            vec.push_back(std::make_tuple(str , format, 1));
            i = n - 1;
        }
        else if(format_status == 1)
        {
            std::cout << "pattern parse error: " << m_pattern << "-" << m_pattern.substr(i) << std::endl;
            vec.push_back(std::make_tuple("<<pattern_error>>" ,format,0));
            break;
        }
        else if(format_status == 2)
        {
            if(normal_str.size())
            {
                vec.push_back(std::make_tuple(normal_str , "" , 0));
                normal_str.clear();
            }
            vec.push_back(std::make_tuple(str , format , 2));
            i = n - 1;
        }
    }
    if(normal_str.size())
    {
        vec.push_back(std::make_tuple(normal_str , "" , 0));
    }

    // 当函数被多次调用时，static 能节省大量的开辟内存的时间
    static std::map<std::string , std::function<FormatterItem::ptr(const std::string& str)>> map_format_items
    {
#define XX(str , className)                                      \
        {#str , [](const std::string& fmt)->FormatterItem::ptr { \
            return FormatterItem::ptr(new className(fmt));       \
        }}, 

        XX(m , MessageFormatItem)
        XX(p , LevelFormatItem)
        XX(r , ElapseFormatItem)
        XX(c , LoggerNameFormatItem)
        XX(t , ThreadIdFormatItem)
        XX(n , NextLineFormatItem)
        XX(d , DateTimeFormatItem)
        XX(f , FileNameFormatItem)
        XX(l , LineFormatItem)

#undef XX
    };

    for(const std::tuple<std::string , std::string , int>& tup : vec)
    {
        int i_type = std::get<2>(tup);
        if(i_type == 0 )
        {
            m_items.push_back(FormatterItem::ptr(new StringFormatItem(std::get<0>(tup))));
        }
        else
        {
            std::string str = std::get<0>(tup);
            std::string fmt = std::get<1>(tup);
            if(map_format_items.find(str) == map_format_items.end())
            {
                m_items.push_back(FormatterItem::ptr(new StringFormatItem("<<error format %" + std::get<1>(tup) + ">>")));
            }
            else
            {
                m_items.push_back(map_format_items[str](fmt));
            }
        }

        // 输出解析出来的东西
        std::cout << std::get<0>(tup) << " - " << std::get<1>(tup) << " - " << std::get<2>(tup) << std::endl;
    }

}



}