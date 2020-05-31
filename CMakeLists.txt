cmake_minimum_required(VERSION 3.7)

project(gpio_dev)

set(CMAKE_CXX_STANDARD 14)

file(GLOB INCLUDE "include/*")
file(GLOB SOURCES "src/*")

add_library(${PROJECT_NAME} SHARED ${INCLUDES} ${SOURCES})

if(WITH_EXAMPLES)
    add_subdirectory(examples)
endif()
