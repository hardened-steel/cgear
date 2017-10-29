cmake_minimum_required(VERSION 3.5)
project(cgear)

set(CMAKE_CXX_STANDARD 14)

find_package(Boost COMPONENTS REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
include_directories(${CMAKE_SOURCE_DIR})

find_package(Threads REQUIRED)

file(GLOB SRC_LIST "*.cpp")

add_subdirectory(ast)
add_subdirectory(lexer)
add_subdirectory(parser)
add_subdirectory(model)
add_subdirectory(backends)

add_executable(${PROJECT_NAME} ${SRC_LIST})
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} cgear-lexer cgear-parser cgear-ast cgear-model cgear-backends)

enable_testing()
add_subdirectory(test)