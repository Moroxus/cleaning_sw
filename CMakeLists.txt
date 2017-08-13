cmake_minimum_required(VERSION 3.5)
project(Cleaning_SW)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(SOURCE_FILES main.cpp Environment.h)
add_executable(Cleaning_SW ${SOURCE_FILES})

find_package(Boost COMPONENTS system filesystem REQUIRED)

target_link_libraries(Cleaning_SW
        ${Boost_FILESYSTEM_LIBRARY}
        ${Boost_SYSTEM_LIBRARY}
        )
