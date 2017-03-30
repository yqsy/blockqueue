project(blockquque)
cmake_minimum_required(VERSION 2.8)

add_executable(blockqueue_test blockqueue.cpp blockqueue.h main.cpp)

add_executable(task_example blockqueue.cpp blockqueue.h task_example.cpp)

add_executable(task_example2 blockqueue.cpp blockqueue.h task_example2.cpp)