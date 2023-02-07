cmake_minimum_required(VERSION 3.10)
project(GameQuark VERSION 0.0.1 DESCRIPTION "Just a game engine")
CMAKE_POLICY(SET CMP0072 NEW)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

set(CMAKE_EXE_LINKER_FLAGS_RELEASE_INIT "-Wall -O3")
set(CMAKE_EXE_LINKER_FLAGS_DEBUG_INIT "-Wall -O0 -g --no-stack-protector -ggdb")

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CMAKE_BINARY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/release)
else()
    set(CMAKE_BINARY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/debug)
endif()

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tests)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLFW REQUIRED)
find_package(GLM REQUIRED)

include_directories(${OpenGL_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS} ${GLFW_INCLUDE_DIRS} ${GLM_INCLUDE_DIRS})

file(GLOB_RECURSE LIB_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/core/*.cpp")
file(GLOB_RECURSE LIB_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/core/*.hpp")
file(GLOB TEST1_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/tests/test1.cpp")

add_library(game-quark SHARED ${LIB_SOURCES})
include_directories(game-quark ${CMAKE_CURRENT_SOURCE_DIR}/core)
set_target_properties(game-quark PROPERTIES VERSION ${PROJECT_VERSION} PUBLIC_HEADER core/engine.h)
target_link_libraries(game-quark ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} ${GLFW_LIBRARIES} ${GLM_LIBRARIES})

set(GameQuark_LIBRARIES ${CMAKE_BINARY_DIR}/lib/libgame-quark.so)
set(GameQuark_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/core)

add_custom_target(core)
add_dependencies(core game-quark)

enable_testing()

include_directories(test1 ${CMAKE_CURRENT_SOURCE_DIR}/tests ${GameQuark_INCLUDE_DIRS})
add_executable(test1 ${TEST1_SOURCES})
link_directories(test1 .)
target_link_libraries(test1 ${GameQuark_LIBRARIES} ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} ${GLFW_LIBRARIES} ${GLM_LIBRARIES})
add_test(NAME test1 COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/test1)
set_tests_properties(test1 PROPERTIES PASS_REGULAR_EXPRESSION "Passed")

add_custom_target(tests)
add_dependencies(tests test1)

