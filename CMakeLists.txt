cmake_minimum_required(VERSION 3.24)
project(FileEmpower)

set(CMAKE_CXX_STANDARD 20)

set(Boost_USE_STATIC_LIBS   ON)
set(Boost_USE_MULTITHREADED ON)
find_package(Boost REQUIRED COMPONENTS system thread filesystem)
FIND_PACKAGE(Threads)
include_directories(${Boost_INCLUDE_DIRS})
add_executable(FileEmpower
        main.cpp
        Data.h
        Color.h
        OutputFE.cpp
        OutputFE.h
        Logger.h)
target_link_libraries(FileEmpower ${Boost_LIBRARIES})
