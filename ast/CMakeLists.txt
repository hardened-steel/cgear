cmake_minimum_required(VERSION 3.5)
project(cgear-ast)

set(CMAKE_CXX_STANDARD 14)

find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

file(GLOB SRC_LIST
	"*.cpp"
	"function/*.cpp"
	"operations/*.cpp"
	"operators/*.cpp"
	"statement/*.cpp"
	"types/*.cpp"
)

add_library(${PROJECT_NAME} STATIC ${SRC_LIST})
target_link_libraries(${PROJECT_NAME} ${GTEST_BOTH_LIBRARIES})
