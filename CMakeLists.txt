cmake_minimum_required(VERSION 3.26)

include(FetchContent)
enable_testing()

FetchContent_Declare(
    zlib
    URL https://github.com/madler/zlib/releases/download/v1.3/zlib-1.3.tar.gz
    OVERRIDE_FIND_PACKAGE
)

FetchContent_GetProperties(zlib)
find_package(ZLIB REQUIRED)
add_library(ZLIB::ZLIB ALIAS zlibstatic)
target_include_directories(zlibstatic PUBLIC ${zlib_SOURCE_DIR} ${zlib_BINARY_DIR})

set(BOOST_IOSTREAMS_ENABLE_ZLIB ON CACHE INTERNAL "")
FetchContent_Declare(
    boost
    URL https://github.com/boostorg/boost/releases/download/boost-1.83.0/boost-1.83.0.tar.gz
)

set(LLVM_ENABLE_EH ON CACHE INTERNAL "")
set(LLVM_ENABLE_RTTI ON CACHE INTERNAL "")
set(LLVM_INCLUDE_TESTS OFF CACHE INTERNAL "")
set(LLVM_INCLUDE_BENCHMARKS OFF CACHE INTERNAL "")
set(LLVM_ENABLE_OCAMLDOC OFF CACHE INTERNAL "")
set(LLVM_ENABLE_BINDINGS OFF CACHE INTERNAL "")
FetchContent_Declare(
    llvm
    URL https://github.com/llvm/llvm-project/releases/download/llvmorg-16.0.6/llvm-project-16.0.6.src.tar.xz
    SOURCE_SUBDIR llvm
)
FetchContent_MakeAvailable(boost llvm)

project(cgear LANGUAGES CXX C VERSION 0.0.1)


add_executable(${PROJECT_NAME} main.cpp)
set_target_properties(${PROJECT_NAME}
    PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS YES
        C_STANDARD 11
        C_STANDARD_REQUIRED YES
        C_EXTENSIONS YES
)
target_link_libraries(${PROJECT_NAME} PUBLIC Boost::headers Boost::iostreams Boost::program_options Boost::fiber)

include(CPack)
