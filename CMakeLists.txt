CMAKE_MINIMUM_REQUIRED(VERSION 3.6)
PROJECT(O_X)

SET(CMAKE_CXX_STANDARD 11)

SET(SOURCE_FILES
		src/core/GameBoard.cpp src/core/GameBoard.h
		)
ADD_EXECUTABLE(O_X main.cpp ${SOURCE_FILES})

TARGET_COMPILE_OPTIONS(O_X PRIVATE
		-Wall -pedantic -Werror
		-Wno-unused-private-field -Wnon-virtual-dtor)

TARGET_INCLUDE_DIRECTORIES(O_X PRIVATE ./src)

ADD_SUBDIRECTORY(lib/googletest)

SET(TEST_SOURCE_FILES
		test/gtest/GameBoardTest.cpp
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
