cmake_minimum_required(VERSION 3.15)

project(ECS)

set(PROJECT_NAME unit_tests)

set(
  TESTS_SRCS
  tests/doctest.cpp
  tests/test_registry.cpp
  tests/components/test_position.cpp
  tests/components/test_velocity.cpp
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "../")

if(NOT WIN32)
  add_compile_options(-Wall -Wextra)
  option(ENABLE_COVERAGE ON)
endif(NOT WIN32)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ---- Add doctest dependency ----
include(ExternalProject)
find_package(Git REQUIRED)
ExternalProject_Add(
    doctest
    PREFIX ${CMAKE_BINARY_DIR}/doctest
    GIT_REPOSITORY https://github.com/doctest/doctest.git
    TIMEOUT 10
    UPDATE_COMMAND ${GIT_EXECUTABLE} pull
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
    LOG_DOWNLOAD ON
)
ExternalProject_Get_Property(doctest source_dir)
set(DOCTEST_INCLUDE_DIR ${source_dir}/doctest CACHE STRING "Path to include folder for doctest")

add_executable(${PROJECT_NAME} ${TESTS_SRCS})

if(NOT WIN32)
  set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/dependencies/CMake-codecov/cmake" ${CMAKE_MODULE_PATH})
  find_package(codecov)
  add_coverage(${PROJECT_NAME})
endif(NOT WIN32)

target_include_directories(${PROJECT_NAME} PUBLIC src/ecs/)
target_include_directories(${PROJECT_NAME} PUBLIC src/ecs/components/)
target_include_directories(${PROJECT_NAME} PUBLIC ${DOCTEST_INCLUDE_DIR})