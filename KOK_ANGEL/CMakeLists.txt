cmake_minimum_required (VERSION 2.6)
project(KOK_ANGEL)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE "RelWithDebInfo")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-Ofast -mfma4 -mavx -fno-strict-aliasing")

file(GLOB_RECURSE source_list "./src/*.cpp")
file(GLOB_RECURSE include_list "./src/*.h" "./src/*.asm" "./src/*.S")

add_library(KOKa SHARED ${source_list})

set_target_properties(KOKa PROPERTIES LINKER_LANGUAGE CXX)

install(TARGETS KOKa DESTINATION lib)
install(FILES ${include_list}  DESTINATION include)
