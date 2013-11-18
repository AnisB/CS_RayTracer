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
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
FIND_PACKAGE (X11 REQUIRED)
set(CORELIBS  ${GLEW_LIBRARY} ${OPENGL_LIBRARIES}
 ${X11_Xxf86vm_LIB} ${X11_Xrandr_LIB} ${X11_Xi_LIB} )
include_directories(${SOURCES} ${OPENGL_INCLUDE_DIRS} ${GLFW_INCLUDE_DIR} )
ENDIF()


add_executable(CS_RayTracer ${PROGRAM}/main.cpp ${Source_File})
TARGET_LINK_LIBRARIES(CS_RayTracer ${CORELIBS})
