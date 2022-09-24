cmake_minimum_required(VERSION 3.22)
project(task)
set(CMAKE_CXX_STANDARD 14)

include(FindPackageHandleStandardArgs)
include(SelectLibraryConfigurations)

find_package(RdKafka REQUIRED)
find_path(CPPKAFKA_INCLUDES NAMES cppkafka.h HINTS ${CURRENT_INSTALLED_DIR} PATH_SUFFIXES cppkafka)
find_library(CPPKAFKA_LIBRARY_DEBUG NAMES cppkafka PATH_SUFFIXES lib PATHS "${_VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}" NO_DEFAULT_PATH REQUIRED)
find_library(CPPKAFKA_LIBRARY_RELEASE NAMES cppkafka PATH_SUFFIXES lib PATHS "${_VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}/debug" NO_DEFAULT_PATH REQUIRED)
select_library_configurations(CPPKAFKA)

include_directories(.)

add_executable(producer server.cpp)
target_include_directories(producer PRIVATE ${CPPKAFKA_INCLUDES}/..)
target_link_libraries(producer PRIVATE ${CPPKAFKA_LIBRARY} RdKafka::rdkafka++)

add_executable(consumer client.cpp)
target_include_directories(consumer PRIVATE ${CPPKAFKA_INCLUDES}/..)
target_link_libraries(consumer PRIVATE ${CPPKAFKA_LIBRARY} RdKafka::rdkafka++)
