# 注，当添加新的模块到项目中去需要经过以下流程，
# 1、添加到aux_source_directory(${PROJECT_SOURCE_DIR}/src/mode_name mode_name) 
# 2、set 添加对应的${mode_name} 到此处,从而实现源文件的快速搜索

cmake_minimum_required(VERSION 3.0)
project(sylar)

# 配置cmake 编译选项
set(CMAKE_VERSION_MAKEFILE ON)
set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -rdynamic -O3 -g -std=c++11 -Wall -Wno-deprecated -Werror -Wno-unused-function")

# 指出包含的头文件
include_directories(${PROJECT_SOURCE_DIR}/src/log)
include_directories(${PROJECT_SOURCE_DIR}/src/log/LogAppender)

# 设置可执行程序的输出路径为bin路径
set(HOME ${PROJECT_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${HOME})

#设置库文件输出路径
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)


# 源文件
file(GLOB  entry ${PROJECT_SOURCE_DIR}/src/*.cpp)           # 程序入口
file(GLOB_RECURSE log ${PROJECT_SOURCE_DIR}/src/log/*.cpp ) # 日志系统

#打印各个子模块的源文件内容，防止后期少编译源文件
message(STATUS "enrty src: ${entry}")
message(STATUS "log src: ${log}")

set(SRC_LIST ${entry};${log})
set(LIB_LIST ${log})


# 生成可执行文件
add_executable(app ${SRC_LIST})

# 生成库文件
add_executable(test ${PROJECT_SOURCE_DIR}/test/main.cpp)
add_library(sylar SHARED ${LIB_LIST})
add_dependencies(test sylar)
target_link_libraries(test sylar)  # 指定目标在链接时需要链接的库文件
