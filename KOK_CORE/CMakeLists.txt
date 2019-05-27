cmake_minimum_required (VERSION 2.6)
project(KOK_CORE)

set(CMAKE_CXX_FLAGS "-std=c++17 -Ofast -mfma -mavx")

add_library(KOKc SHARED ./src/KOK_Message.cpp)

install(TARGETS KOKc DESTINATION lib)
install(FILES ./src/KOK_Message.h ./src/KOK_Actor.h DESTINATION include)
