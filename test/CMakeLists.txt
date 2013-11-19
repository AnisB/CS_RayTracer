
# Exemple de création de test
#add_executable(testFile ${TEST}/testFile.cpp ${Source_File})
#TARGET_LINK_LIBRARIES(testFile ${CORELIBS})


add_executable(basicwindow ${TEST}/basicwindow.cpp ${Source_File})
TARGET_LINK_LIBRARIES(basicwindow ${CORELIBS})
