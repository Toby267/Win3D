cmake_minimum_required(VERSION "3.25.1")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_CXX_STANDARD 20)

project(Win3D)

file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/core/*.cpp")
add_executable(Win3D "${MY_SOURCES}")
target_include_directories(Win3D PUBLIC "${CMAKE_SOURCE_DIR}/core")
target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC RESOURCES_PATH="./resources/")

add_subdirectory(${CMAKE_SOURCE_DIR}/thirdparty/raylib-5.0)

target_link_libraries("${CMAKE_PROJECT_NAME}" PRIVATE 
	raylib_static
)