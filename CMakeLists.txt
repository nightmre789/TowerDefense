cmake_minimum_required(VERSION 3.13)
set(PROJECT_NAME TowerDefense)

project(${PROJECT_NAME})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -static")
set(CMAKE_CXX_STANDARD 14)

add_executable(${PROJECT_NAME} src/main.cpp src/Animation.cpp src/Animation.h)

set(SFML_STATIC_LIBRARIES TRUE)

find_package(SFML 2 COMPONENTS graphics audio REQUIRED)
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-audio)