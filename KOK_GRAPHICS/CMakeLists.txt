cmake_minimum_required (VERSION 2.6)
project(KOK_GRAPHICS)

find_package(Freetype REQUIRED)
include_directories(${FREETYPE_INCLUDE_DIRS})
include_directories(../KOK_CORE/src)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE "RelWithDebInfo")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-Ofast -mfma4 -mavx")

add_library(KOKg SHARED ./src/KOK_Imager.cpp ./src/KOK_Camera.cpp ./src/KOK_Director.cpp ./src/KOK_Light.cpp ./src/KOK_Picker.cpp ./src/KOK_TextManager.cpp
  ./src/KOK_TextConsole.cpp ./src/shader.cpp ./src/KOK_WindowManager.cpp ./src/KOK_Mesh.cpp ./src/KOK_Skeleton.cpp ./src/KOK_Model.cpp ./src/KOK_ParticleSystem.cpp)

target_link_libraries(KOKg ${FREETYPE_LIBRARIES})

target_link_libraries(KOKg "-lm -lGL -lglfw -lGLEW -lX11 -lXxf86vm -lXrandr -lpthread -lXi -lXinerama -lXcursor -ldl -lrt -lassimp -lnanogui")

install(TARGETS KOKg DESTINATION lib)
install(FILES ./src/KOK_Imager.h ./src/KOK_Camera.h ./src/KOK_Director.h ./src/KOK_Light.h ./src/KOK_Picker.h ./src/KOK_TextManager.h
  ./src/KOK_TextConsole.h ./src/shader.h ./src/KOK_WindowManager.h ./src/KOK_Mesh.h ./src/KOK_Skeleton.h ./src/KOK_Model.h
  ./src/KOK_ParticleSystem.h ./src/stb_image.h ./src/stb_image_resize.h DESTINATION include)
