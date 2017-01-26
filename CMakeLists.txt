CMAKE_MINIMUM_REQUIRED(VERSION 3.6)
PROJECT(O_X)

SET(CMAKE_CXX_STANDARD 11)

FIND_PACKAGE(Qt5 REQUIRED COMPONENTS Core Quick)

# Instruct CMake to run moc automatically when needed.
SET(CMAKE_AUTOMOC ON)

QT5_ADD_RESOURCES(RESOURCES res/qml.qrc)

SET(SOURCE_FILES
		src/core/Game.cpp src/core/Game.h
		src/core/GameBoard.cpp src/core/GameBoard.h
		src/core/GameState.cpp src/core/GameState.h
		src/core/Player.cpp src/core/Player.h
		src/GameController.cpp src/GameController.h
		)
ADD_EXECUTABLE(O_X main.cpp ${SOURCE_FILES} ${RESOURCES})

TARGET_COMPILE_OPTIONS(O_X PRIVATE
		-Wall -pedantic -Werror
		-Wno-unused-private-field -Wnon-virtual-dtor)

TARGET_INCLUDE_DIRECTORIES(O_X PRIVATE
		./src
		${CMAKE_CURRENT_BINARY_DIR}
		./
		)

TARGET_LINK_LIBRARIES(O_X Qt5::Core Qt5::Quick)

######################################################################################
# TESTS ##############################################################################
######################################################################################

ADD_SUBDIRECTORY(lib/googletest)

SET(TEST_SOURCE_FILES
		test/gtest/GameBoardTest.cpp
		test/gtest/GameTest.cpp
		)

ADD_EXECUTABLE(O_X-test ${SOURCE_FILES} ${TEST_SOURCE_FILES})
TARGET_LINK_LIBRARIES(O_X-test
		gtest gtest_main
		gmock
		)

TARGET_INCLUDE_DIRECTORIES(O_X-test PRIVATE
		./src
		googletest/googletest/include
		)

TARGET_COMPILE_OPTIONS(O_X-test PRIVATE
		-Wall -pedantic -Werror
		-Wno-unused-private-field -Wnon-virtual-dtor)
