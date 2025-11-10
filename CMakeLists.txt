cmake_minimum_required(VERSION 3.14)
project(ServerManager)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDLL")
endif()


# ---GoogleTest---
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

enable_testing()

include_directories(include)

add_library(ServerManager
    src/ServerManager.cpp
    include/ServerManager.h
)

add_executable(runTests
    tests/test_ServerManager.cpp
)

if(MSVC)
    set_target_properties(ServerManager runTests gtest gtest_main gmock gmock_main
        PROPERTIES
        MSVC_RUNTIME_LIBRARY "MultiThreadedDLL"
    )
endif()

target_link_libraries(runTests
    ServerManager
    gtest_main
)

include(GoogleTest)
gtest_discover_tests(runTests)
