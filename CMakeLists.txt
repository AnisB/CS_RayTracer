cmake_minimum_required(VERSION 2.6)

#Project name
project(CS_RayTracer)

#Source directory
set(SOURCES "${PROJECT_SOURCE_DIR}/src/")


#Program directory
set(PROGRAM "${PROJECT_SOURCE_DIR}/program/")

#Test directory
set(TEST "${PROJECT_SOURCE_DIR}/test/")

#Debug flag
SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")

#Cmake module path
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/;${CMAKE_MODULE_PATH}")


#Recursive file parsing
file(
        GLOB_RECURSE
        Source_File
        ${SOURCES}/*.h
        ${SOURCES}/*.ih
        ${SOURCES}/*.cpp
    )


IF(UNIX AND NOT APPLE)
add_definitions( -D__posix__ )
add_definitions( -D LINUX )
add_definitions( -DGLFW_EXPOSE_NATIVE_X11 )
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
FIND_PACKAGE (X11 REQUIRED)
set(CORELIBS  ${GLEW_LIBRARY} ${OPENGL_LIBRARIES}
 ${X11_Xxf86vm_LIB} ${X11_Xrandr_LIB} ${X11_Xi_LIB} "${PROJECT_SOURCE_DIR}/external/linux/libglfw3.a" pthread)
include_directories(${SOURCES} ${OPENGL_INCLUDE_DIRS} ${PROJECT_SOURCE_DIR}/external/linux/GLFW)
ENDIF()



IF(APPLE)
	add_definitions( -DMACOSX)
   INCLUDE_DIRECTORIES ( /System/Library/Frameworks )
   FIND_LIBRARY(COCOA_LIBRARY Cocoa)
   FIND_LIBRARY(IOKIT_LIBRARY IOKit)
   FIND_LIBRARY(OpenGL_LIBRARY OpenGL )
	find_package(GLEW REQUIRED)

   MARK_AS_ADVANCED (COCOA_LIBRARY
                     GLFW_LIBRARY
                     OpenGL_LIBRARY
                     IOKIT_LIBRARY)
   SET(CORELIBS ${COCOA_LIBRARY} ${GLEW_LIBRARY} ${OpenGL_LIBRARY} ${IOKIT_LIBRARY} "${PROJECT_SOURCE_DIR}/external/mac/libglfw3.a")
   include_directories(${SOURCES} ${OPENGL_INCLUDE_DIRS} ${PROJECT_SOURCE_DIR}/external/mac/GLFW)

ENDIF (APPLE)

add_subdirectory(program)
add_subdirectory(test)




