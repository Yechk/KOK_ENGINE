cmake_minimum_required(VERSION 2.6)
project(test_project)

find_package(Freetype REQUIRED)
include_directories(${FREETYPE_INCLUDE_DIRS})

add_subdirectory(KOK_GRAPHICS)
add_subdirectory(KOK_CORE)
add_subdirectory(KOK_ANGEL)
add_subdirectory(KOK_PHYSICS)

include_directories(${CMAKE_SOURCE_DIR}/KOK_GRAPHICS/src)
include_directories(${CMAKE_SOURCE_DIR}/KOK_EXTENDS/src)
include_directories(${CMAKE_SOURCE_DIR}/KOK_CORE/src)
include_directories(${CMAKE_SOURCE_DIR}/KOK_ANGEL/src)
include_directories(${CMAKE_SOURCE_DIR}/KOK_PHYSICS/src)
include_directories(${CMAKE_SOURCE_DIR}/KOK_PHYSICS/PhysX_Debug/PhysX/include)
include_directories(${CMAKE_SOURCE_DIR}/KOK_PHYSICS/PhysX_Debug/PxShared/include)
include_directories(${CMAKE_SOURCE_DIR}/Scripts)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE "RelWithDebInfo")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-Ofast -mfma4 -mavx")

add_executable(test2 ${CMAKE_SOURCE_DIR}/KOK_EXTENDS/src/KOK_EXT_CharacterBasic.cpp ${CMAKE_SOURCE_DIR}/tests/gui.cpp)

target_link_libraries(test2 ${FREETYPE_LIBRARIES})
target_link_libraries(test2 KOKg)
target_link_libraries(test2 KOKc)
target_link_libraries(test2 KOKa)
target_link_libraries(test2 KOKp)
