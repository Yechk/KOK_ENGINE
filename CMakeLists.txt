cmake_minimum_required(VERSION 2.6)
project(test_project)

find_package(Freetype REQUIRED)
include_directories(${FREETYPE_INCLUDE_DIRS})

add_subdirectory(KOK_GRAPHICS)
add_subdirectory(KOK_CORE)

include_directories(${CMAKE_SOURCE_DIR}/KOK_GRAPHICS/src)
include_directories(${CMAKE_SOURCE_DIR}/KOK_CORE/src)

set(CMAKE_CXX_FLAGS "-std=c++17 -Ofast -mfma -mavx")

add_executable(test2 ./tests/gui.cpp)


target_link_libraries(test2 ${FREETYPE_LIBRARIES})
target_link_libraries(test2 KOKg)
target_link_libraries(test2 KOKc)
