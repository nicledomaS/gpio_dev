cmake_minimum_required(VERSION 3.7)

project(example)

set(CMAKE_CXX_STANDARD 14)

executable(${PROJECT_NAME}
            SOURCES "./"
            MODULES gpio_dev)
