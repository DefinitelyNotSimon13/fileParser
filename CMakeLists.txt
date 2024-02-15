cmake_minimum_required(VERSION 3.22)

set(PROJECT_NAME Task08-02-2024)

project(${PROJECT_NAME} VERSION 0.1.0)


set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SOURCES 
  src/main.cpp
  src/functions.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC
  "${PROJECT_BINARY_DIR}"
  "${PROJECT_SOURCE_DIR}/src"
)
