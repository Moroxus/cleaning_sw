cmake_minimum_required(VERSION 3.5)
project(cleaning_sw)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CLEANING_SW_VERSION_MAJOR "1")
set(CLEANING_SW_VERSION_MINOR "0")

set(SOURCE_FILES main.cpp)
add_executable(cleaning_sw ${SOURCE_FILES})

find_package(Boost 1.55.0 REQUIRED COMPONENTS system filesystem)

target_link_libraries(cleaning_sw ${Boost_FILESYSTEM_LIBRARY} ${Boost_SYSTEM_LIBRARY})

install(TARGETS cleaning_sw RUNTIME DESTINATION bin COMPONENT cleaning_sw)

include(InstallRequiredSystemLibraries)

set(CPACK_PACKAGE_VERSION_MAJOR "${CLEANING_SW_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${CLEANING_SW_VERSION_MINOR}")
set(PACK_DEBIAN_PACKAGE_NAME "${PROJECT_NAME}")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Moroxus")
include(CPack)
