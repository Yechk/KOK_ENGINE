# Install script for directory: /home/bodhi/KOK_ENGINE/KOK_ENGINE/KOK_ENGINE_0_1/KOK_ANGEL

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
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libKOKa.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libKOKa.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libKOKa.so"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/home/bodhi/KOK_ENGINE/KOK_ENGINE/KOK_ENGINE_0_1/KOK_ANGEL/libKOKa.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libKOKa.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libKOKa.so")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libKOKa.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE FILE FILES
    "/home/bodhi/KOK_ENGINE/KOK_ENGINE/KOK_ENGINE_0_1/KOK_ANGEL/./src/angelscript.h"
    "/home/bodhi/KOK_ENGINE/KOK_ENGINE/KOK_ENGINE_0_1/KOK_ANGEL/./src/as_array.h"
    "/home/bodhi/KOK_ENGINE/KOK_ENGINE/KOK_ENGINE_0_1/KOK_ANGEL/./src/as_atomic.h"
    "/home/bodhi/KOK_ENGINE/KOK_ENGINE/KOK_ENGINE_0_1/KOK_ANGEL/./src/as_builder.h"
    "/home/bodhi/KOK_ENGINE/KOK_ENGINE/KOK_ENGINE_0_1/KOK_ANGEL/./src/as_bytecode.h"
    "/home/bodhi/KOK_ENGINE/KOK_ENGINE/KOK_ENGINE_0_1/KOK_ANGEL/./src/as_callfunc.h"
    "/home/bodhi/KOK_ENGINE/KOK_ENGINE/KOK_ENGINE_0_1/KOK_ANGEL/./src/as_compiler.h"
    "/home/bodhi/KOK_ENGINE/KOK_ENGINE/KOK_ENGINE_0_1/KOK_ANGEL/./src/as_config.h"
    "/home/bodhi/KOK_ENGINE/KOK_ENGINE/KOK_ENGINE_0_1/KOK_ANGEL/./src/as_configgroup.h"
    "/home/bodhi/KOK_ENGINE/KOK_ENGINE/KOK_ENGINE_0_1/KOK_ANGEL/./src/as_context.h"
    "/home/bodhi/KOK_ENGINE/KOK_ENGINE/KOK_ENGINE_0_1/KOK_ANGEL/./src/as_criticalsection.h"
    "/home/bodhi/KOK_ENGINE/KOK_ENGINE/KOK_ENGINE_0_1/KOK_ANGEL/./src/as_datatype.h"
    "/home/bodhi/KOK_ENGINE/KOK_ENGINE/KOK_ENGINE_0_1/KOK_ANGEL/./src/as_debug.h"
    "/home/bodhi/KOK_ENGINE/KOK_ENGINE/KOK_ENGINE_0_1/KOK_ANGEL/./src/as_gc.h"
    "/home/bodhi/KOK_ENGINE/KOK_ENGINE/KOK_ENGINE_0_1/KOK_ANGEL/./src/as_generic.h"
    "/home/bodhi/KOK_ENGINE/KOK_ENGINE/KOK_ENGINE_0_1/KOK_ANGEL/./src/as_map.h"
    "/home/bodhi/KOK_ENGINE/KOK_ENGINE/KOK_ENGINE_0_1/KOK_ANGEL/./src/as_memory.h"
    "/home/bodhi/KOK_ENGINE/KOK_ENGINE/KOK_ENGINE_0_1/KOK_ANGEL/./src/as_module.h"
    "/home/bodhi/KOK_ENGINE/KOK_ENGINE/KOK_ENGINE_0_1/KOK_ANGEL/./src/as_namespace.h"
    "/home/bodhi/KOK_ENGINE/KOK_ENGINE/KOK_ENGINE_0_1/KOK_ANGEL/./src/as_objecttype.h"
    "/home/bodhi/KOK_ENGINE/KOK_ENGINE/KOK_ENGINE_0_1/KOK_ANGEL/./src/as_outputbuffer.h"
    "/home/bodhi/KOK_ENGINE/KOK_ENGINE/KOK_ENGINE_0_1/KOK_ANGEL/./src/as_parser.h"
    "/home/bodhi/KOK_ENGINE/KOK_ENGINE/KOK_ENGINE_0_1/KOK_ANGEL/./src/as_property.h"
    "/home/bodhi/KOK_ENGINE/KOK_ENGINE/KOK_ENGINE_0_1/KOK_ANGEL/./src/as_restore.h"
    "/home/bodhi/KOK_ENGINE/KOK_ENGINE/KOK_ENGINE_0_1/KOK_ANGEL/./src/as_scriptcode.h"
    "/home/bodhi/KOK_ENGINE/KOK_ENGINE/KOK_ENGINE_0_1/KOK_ANGEL/./src/as_scriptengine.h"
    "/home/bodhi/KOK_ENGINE/KOK_ENGINE/KOK_ENGINE_0_1/KOK_ANGEL/./src/as_scriptfunction.h"
    "/home/bodhi/KOK_ENGINE/KOK_ENGINE/KOK_ENGINE_0_1/KOK_ANGEL/./src/as_scriptnode.h"
    "/home/bodhi/KOK_ENGINE/KOK_ENGINE/KOK_ENGINE_0_1/KOK_ANGEL/./src/as_scriptobject.h"
    "/home/bodhi/KOK_ENGINE/KOK_ENGINE/KOK_ENGINE_0_1/KOK_ANGEL/./src/as_string.h"
    "/home/bodhi/KOK_ENGINE/KOK_ENGINE/KOK_ENGINE_0_1/KOK_ANGEL/./src/as_string_util.h"
    "/home/bodhi/KOK_ENGINE/KOK_ENGINE/KOK_ENGINE_0_1/KOK_ANGEL/./src/as_symboltable.h"
    "/home/bodhi/KOK_ENGINE/KOK_ENGINE/KOK_ENGINE_0_1/KOK_ANGEL/./src/as_texts.h"
    "/home/bodhi/KOK_ENGINE/KOK_ENGINE/KOK_ENGINE_0_1/KOK_ANGEL/./src/as_thread.h"
    "/home/bodhi/KOK_ENGINE/KOK_ENGINE/KOK_ENGINE_0_1/KOK_ANGEL/./src/as_tokendef.h"
    "/home/bodhi/KOK_ENGINE/KOK_ENGINE/KOK_ENGINE_0_1/KOK_ANGEL/./src/as_tokenizer.h"
    "/home/bodhi/KOK_ENGINE/KOK_ENGINE/KOK_ENGINE_0_1/KOK_ANGEL/./src/as_typeinfo.h"
    "/home/bodhi/KOK_ENGINE/KOK_ENGINE/KOK_ENGINE_0_1/KOK_ANGEL/./src/as_variablescope.h"
    "/home/bodhi/KOK_ENGINE/KOK_ENGINE/KOK_ENGINE_0_1/KOK_ANGEL/./src/scriptarray.h"
    "/home/bodhi/KOK_ENGINE/KOK_ENGINE/KOK_ENGINE_0_1/KOK_ANGEL/./src/scriptbuilder.h"
    "/home/bodhi/KOK_ENGINE/KOK_ENGINE/KOK_ENGINE_0_1/KOK_ANGEL/./src/scripthandle.h"
    "/home/bodhi/KOK_ENGINE/KOK_ENGINE/KOK_ENGINE_0_1/KOK_ANGEL/./src/scriptstdstring.h"
    "/home/bodhi/KOK_ENGINE/KOK_ENGINE/KOK_ENGINE_0_1/KOK_ANGEL/./src/as_callfunc_arm_msvc.asm"
    "/home/bodhi/KOK_ENGINE/KOK_ENGINE/KOK_ENGINE_0_1/KOK_ANGEL/./src/as_callfunc_x64_msvc_asm.asm"
    "/home/bodhi/KOK_ENGINE/KOK_ENGINE/KOK_ENGINE_0_1/KOK_ANGEL/./src/as_callfunc_arm_gcc.S"
    "/home/bodhi/KOK_ENGINE/KOK_ENGINE/KOK_ENGINE_0_1/KOK_ANGEL/./src/as_callfunc_arm_vita.S"
    "/home/bodhi/KOK_ENGINE/KOK_ENGINE/KOK_ENGINE_0_1/KOK_ANGEL/./src/as_callfunc_arm_xcode.S"
    )
endif()

