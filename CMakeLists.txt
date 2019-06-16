cmake_minimum_required(VERSION 2.6)
project(test_project)

find_package(Freetype REQUIRED)
include_directories(${FREETYPE_INCLUDE_DIRS})

add_subdirectory(KOK_GRAPHICS)
add_subdirectory(KOK_CORE)
add_subdirectory(KOK_ANGEL)

include_directories(${CMAKE_SOURCE_DIR}/KOK_GRAPHICS/src)
include_directories(${CMAKE_SOURCE_DIR}/KOK_CORE/src)
include_directories(${CMAKE_SOURCE_DIR}/KOK_ANGEL/src)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE "RelWithDebInfo")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-Ofast -mfma4 -mavx")

add_executable(test2 ./tests/gui.cpp)

target_link_libraries(test2 ${FREETYPE_LIBRARIES})
target_link_libraries(test2 KOKg)
target_link_libraries(test2 KOKc)
target_link_libraries(test2 KOKa)
