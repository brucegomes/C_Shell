cmake_minimum_required(VERSION 3.3)
project(HW8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    history/history.c
    history/history.h
    linkedlist/genericData.h
    linkedlist/linkedList.c
    linkedlist/linkedList.h
    linkedlist/listUtils.c
    linkedlist/listUtils.h
    linkedlist/requiredIncludes.h
    myDir/myDir.c
    myDir/myDir.h
    pipes/pipes.c
    pipes/pipes.h
    process/process.c
    process/process.h
    tokenize/makeArgs.c
    tokenize/makeArgs.h
    utils/fileUtils.c
    utils/fileUtils.h
    utils/myUtils.c
    utils/myUtils.h
    cscd340hw8.c
    cscd340hw8.h)

add_executable(HW8 ${SOURCE_FILES})