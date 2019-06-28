cmake_minimum_required (VERSION 2.6)
project(KOK_PHYSICS)

include_directories(../KOK_CORE/src)
include_directories(${CMAKE_SOURCE_DIR}/KOK_PHYSICS/PhysX_Debug/PhysX/include)
include_directories(${CMAKE_SOURCE_DIR}/KOK_PHYSICS/PhysX_Debug/PxShared/include)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE "RelWithDebInfo")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-Ofast -mfma4 -mavx")

add_library(KOKp SHARED ./src/KOK_PhysicsContext.cpp)

target_link_libraries(KOKp ${CMAKE_SOURCE_DIR}/KOK_PHYSICS/PhysX_Debug/PhysX/bin/linux.clang/debug/libPhysX_static_64.a)
target_link_libraries(KOKp ${CMAKE_SOURCE_DIR}/KOK_PHYSICS/PhysX_Debug/PhysX/bin/linux.clang/debug/libPhysXCommon_static_64.a)
target_link_libraries(KOKp ${CMAKE_SOURCE_DIR}/KOK_PHYSICS/PhysX_Debug/PhysX/bin/linux.clang/debug/libPhysXCharacterKinematic_static_64.a)
target_link_libraries(KOKp ${CMAKE_SOURCE_DIR}/KOK_PHYSICS/PhysX_Debug/PhysX/bin/linux.clang/debug/libPhysXCooking_static_64.a)
target_link_libraries(KOKp ${CMAKE_SOURCE_DIR}/KOK_PHYSICS/PhysX_Debug/PhysX/bin/linux.clang/debug/libPhysXExtensions_static_64.a)
target_link_libraries(KOKp ${CMAKE_SOURCE_DIR}/KOK_PHYSICS/PhysX_Debug/PhysX/bin/linux.clang/debug/libPhysXFoundation_static_64.a)
target_link_libraries(KOKp ${CMAKE_SOURCE_DIR}/KOK_PHYSICS/PhysX_Debug/PhysX/bin/linux.clang/debug/libPhysXPvdSDK_static_64.a)

target_link_libraries(KOKp "-lm -lGL -lglfw -lGLEW -lX11 -lXxf86vm -lXrandr -lpthread -lXi -lXinerama -lXcursor -ldl -lrt -lassimp")

install(TARGETS KOKp DESTINATION lib)
install(FILES ./src/KOK_PhysicsContext.h DESTINATION include)
