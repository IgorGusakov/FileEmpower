cmake_minimum_required(VERSION 3.24)
project(FileEmpower)
message(STATUS "Current OS: ${CMAKE_SYSTEM_NAME}")
option(BOOST_LIB "Builds app with boost::filesystem, we can use that when use c++11." OFF)



if (BOOST_LIB)
    message("Turned on BOOST LIB")
    add_definitions(-DBOOST_LIB)
    set(Boost_USE_STATIC_LIBS   ON)
    set(Boost_USE_MULTITHREADED ON)
    find_package(Boost REQUIRED COMPONENTS system thread filesystem)
    include_directories(${Boost_INCLUDE_DIRS})
endif ()

set(CMAKE_CXX_STANDARD 20)
FIND_PACKAGE(Threads)

add_executable(FileEmpower
        main.cpp
        Data.h
        Color.h
        OutputConsoleFE.cpp
        OutputConsoleFE.h
        Logger.h
        FileSystem.cpp
        FileSystem.h
        adapter_fs/FileSystemInterface.h
        adapter_fs/BoostFileSystemAdapter.h
        adapter_fs/StdFileSystemAdapter.h)

if (BOOST_LIB)
    target_link_libraries(FileEmpower ${Boost_LIBRARIES})
endif ()
