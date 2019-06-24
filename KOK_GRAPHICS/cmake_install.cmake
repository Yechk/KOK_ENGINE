# Install script for directory: /home/bodhi/KOK_ENGINE/KOK_ENGINE/KOK_ENGINE_0_1/KOK_GRAPHICS

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "RelWithDebInfo")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libKOKg.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libKOKg.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libKOKg.so"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/home/bodhi/KOK_ENGINE/KOK_ENGINE/KOK_ENGINE_0_1/KOK_GRAPHICS/libKOKg.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libKOKg.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libKOKg.so")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libKOKg.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE FILE FILES
    "/home/bodhi/KOK_ENGINE/KOK_ENGINE/KOK_ENGINE_0_1/KOK_GRAPHICS/./src/KOK_Imager.h"
    "/home/bodhi/KOK_ENGINE/KOK_ENGINE/KOK_ENGINE_0_1/KOK_GRAPHICS/./src/KOK_Camera.h"
    "/home/bodhi/KOK_ENGINE/KOK_ENGINE/KOK_ENGINE_0_1/KOK_GRAPHICS/./src/KOK_Director.h"
    "/home/bodhi/KOK_ENGINE/KOK_ENGINE/KOK_ENGINE_0_1/KOK_GRAPHICS/./src/KOK_Light.h"
    "/home/bodhi/KOK_ENGINE/KOK_ENGINE/KOK_ENGINE_0_1/KOK_GRAPHICS/./src/KOK_Picker.h"
    "/home/bodhi/KOK_ENGINE/KOK_ENGINE/KOK_ENGINE_0_1/KOK_GRAPHICS/./src/KOK_TextManager.h"
    "/home/bodhi/KOK_ENGINE/KOK_ENGINE/KOK_ENGINE_0_1/KOK_GRAPHICS/./src/KOK_TextConsole.h"
    "/home/bodhi/KOK_ENGINE/KOK_ENGINE/KOK_ENGINE_0_1/KOK_GRAPHICS/./src/shader.h"
    "/home/bodhi/KOK_ENGINE/KOK_ENGINE/KOK_ENGINE_0_1/KOK_GRAPHICS/./src/KOK_WindowManager.h"
    "/home/bodhi/KOK_ENGINE/KOK_ENGINE/KOK_ENGINE_0_1/KOK_GRAPHICS/./src/KOK_Mesh.h"
    "/home/bodhi/KOK_ENGINE/KOK_ENGINE/KOK_ENGINE_0_1/KOK_GRAPHICS/./src/KOK_Skeleton.h"
    "/home/bodhi/KOK_ENGINE/KOK_ENGINE/KOK_ENGINE_0_1/KOK_GRAPHICS/./src/KOK_Model.h"
    "/home/bodhi/KOK_ENGINE/KOK_ENGINE/KOK_ENGINE_0_1/KOK_GRAPHICS/./src/KOK_ParticleSystem.h"
    "/home/bodhi/KOK_ENGINE/KOK_ENGINE/KOK_ENGINE_0_1/KOK_GRAPHICS/./src/stb_image.h"
    "/home/bodhi/KOK_ENGINE/KOK_ENGINE/KOK_ENGINE_0_1/KOK_GRAPHICS/./src/stb_image_resize.h"
    )
endif()

