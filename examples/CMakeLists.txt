cmake_minimum_required(VERSION 3.7)

project(example)

set(CMAKE_CXX_STANDARD 14)

file(GLOB SOURCES "*.cpp")

include_directories(${gpio_dev_SOURCE_DIR}/include ${gpio_dev})

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} gpio_dev)
