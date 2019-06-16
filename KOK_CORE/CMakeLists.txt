cmake_minimum_required (VERSION 2.6)
project(KOK_CORE)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE "RelWithDebInfo")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-Ofast -mfma4 -mavx")

add_library(KOKc SHARED ./src/KOK_Message.cpp)

install(TARGETS KOKc DESTINATION lib)
install(FILES ./src/KOK_Message.h ./src/KOK_Actor.h ./src/KOK_Controller.h DESTINATION include)
