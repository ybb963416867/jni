cmake_minimum_required(VERSION 3.4.1)


# 创建一个变量 source_file 它的值就是src/main/cpp/ 所有的.cpp文件
file(GLOB source src/main/cpp/*.cpp)

add_library(
        native-lib
        SHARED
        ${source}
)
target_link_libraries(
        native-lib
        log
)