cmake_minimum_required(VERSION 3.16)

project(leetcode)


#   添加库头文件
include_directories(include)

#   创建库
add_library(tire src/cmu15445/tire/tire.cc)

# add_library()

#   创建可执行文件，并链接希望链接的库
add_executable(test_tire example/test_tire.cpp)
target_link_libraries(test_tire tire)


add_executable(test_huawei example/test_huawei.cpp)