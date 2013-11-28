
# Exemple de création de test
#add_executable(testFile ${TEST}/testFile.cpp ${Source_File})
#TARGET_LINK_LIBRARIES(testFile ${CORELIBS})


add_executable(basicwindow ${TEST}/basicwindow.cpp )
TARGET_LINK_LIBRARIES(basicwindow ${CORELIBS} Lumina_lib)

add_executable(basiccore ${TEST}/basiccore.cpp )
TARGET_LINK_LIBRARIES(basiccore ${CORELIBS} Lumina_lib)

add_executable(loadscene ${TEST}/loadscene.cpp )
TARGET_LINK_LIBRARIES(loadscene ${CORELIBS} Lumina_lib)
