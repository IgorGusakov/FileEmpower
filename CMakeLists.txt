cmake_minimum_required(VERSION 3.16.3)
project(FileEmpower)
message(STATUS "Current OS: ${CMAKE_SYSTEM_NAME}")
option(BOOST_LIB "Builds app with boost::filesystem, we can use that when use c++11." OFF)

set(CMAKE_C_COMPILER "/usr/bin/clang")
set(CMAKE_CPP_COMPILER "/usr/bin/clang++")
set(CMAKE_CXX_STANDARD 20)

if (BOOST_LIB)
    message("Turned on BOOST LIB")
    add_definitions(-DBOOST_LIB)
    set(Boost_USE_STATIC_LIBS   ON)
    set(Boost_USE_MULTITHREADED ON)
    find_package(Boost REQUIRED COMPONENTS system thread filesystem)
    include_directories(${Boost_INCLUDE_DIRS})
endif ()


FIND_PACKAGE(Threads)

add_executable(FileEmpower
        main.cpp
        Data.h
        Color.h
        output_viewer/OutputConsoleFE.h
        Logger.h
        FileSystem.cpp
        FileSystem.h
        adapter_fs/FileSystemInterface.h
        adapter_fs/BoostFileSystemAdapter.h
        adapter_fs/StdFileSystemAdapter.h output_viewer/OutputCRTPViewer.h)

if (BOOST_LIB)
    target_link_libraries(FileEmpower ${Boost_LIBRARIES})
endif ()
