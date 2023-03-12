cmake_minimum_required(VERSION 3.5)

project(OtusHomework_7_Interpreter LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(OtusHomework_7_Interpreter main.cpp)

install(TARGETS OtusHomework_7_Interpreter
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
