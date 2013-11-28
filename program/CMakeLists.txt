
add_executable(CS_RayTracer ${PROGRAM}/main.cpp)
TARGET_LINK_LIBRARIES(CS_RayTracer ${CORELIBS} Lumina_lib)

add_custom_command(
    TARGET CS_RayTracer POST_BUILD
    COMMAND ln -sf ${PROJECT_SOURCE_DIR}/data ${PROJECT_BINARY_DIR}
) 
