cmake_minimum_required(VERSION 3.10)

project(String)

set(SOURCE main.cpp MemoryHandler.cpp String.cpp)
set(CMAKE_CXX_STANDART 11)
set(CMAKE_CXX_STANDART_REQUIRED True)

set(CMAKE_CXX_COMPILER g++)

add_executable(String ${SOURCE})