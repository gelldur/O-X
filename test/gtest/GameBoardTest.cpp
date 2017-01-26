//
// Created by Dawid Drozd aka Gelldur on 26/01/17.
//
#include <gtest/gtest.h>

#include <limits>

#include <core/GameBoard.h>

using Mark = GameBoard::Mark;
using State = GameBoard::State;

TEST(GameBoardTest, sample)
{
	GameBoard gameBoard;
	for (int x = 0; x < gameBoard.getWidth(); ++x)
	{
		for (int y = 0; y < gameBoard.getHeight(); ++y)
		{
			EXPECT_EQ(Mark::EMPTY, gameBoard.getSafe(x, y));
		}
	}

	EXPECT_NO_FATAL_FAILURE(gameBoard.getSafe(-1, -1));
	EXPECT_NO_FATAL_FAILURE(gameBoard.getSafe(-1, 0));
	EXPECT_NO_FATAL_FAILURE(gameBoard.getSafe(0, -1));
	//-Werror=overflow we must do it explicit
	EXPECT_NO_FATAL_FAILURE(gameBoard.getSafe((GameBoard::ushort) INT64_MIN, (GameBoard::ushort) INT64_MAX));
	EXPECT_NO_FATAL_FAILURE(gameBoard.getSafe((GameBoard::ushort) INT64_MAX, (GameBoard::ushort) INT64_MIN));
	EXPECT_EQ(Mark::NONE, gameBoard.getSafe(-1, -1));
}

TEST(GameBoardTest, setMark)
{
	GameBoard gameBoard;
	EXPECT_TRUE(gameBoard.placeMark(Mark::O, 0, 0));
	EXPECT_EQ(Mark::O, gameBoard.getSafe(0, 0));
	EXPECT_FALSE(gameBoard.placeMark(Mark::X, 0, 0));
	EXPECT_FALSE(gameBoard.placeMark(Mark::O, 0, 0));
	EXPECT_FALSE(gameBoard.placeMark(Mark::EMPTY, 0, 0));
	EXPECT_FALSE(gameBoard.placeMark(Mark::NONE, 0, 0));

	EXPECT_TRUE(gameBoard.placeMark(Mark::X, 1, 1));
	EXPECT_EQ(Mark::X, gameBoard.getSafe(1, 1));
}

TEST(GameBoardTest, resetCheck)
{
	GameBoard gameBoard;
	for (int x = 0; x < gameBoard.getWidth(); ++x)
	{
		for (int y = 0; y < gameBoard.getHeight(); ++y)
		{
			EXPECT_EQ(Mark::EMPTY, gameBoard.getSafe(x, y));
		}
	}
	for (int x = 0; x < gameBoard.getWidth(); ++x)
	{
		for (int y = 0; y < gameBoard.getHeight(); ++y)
		{
			gameBoard.placeMark(Mark::O, x, y);
			EXPECT_EQ(Mark::O, gameBoard.getSafe(x, y));
		}
	}
	gameBoard.reset();
	for (int x = 0; x < gameBoard.getWidth(); ++x)
	{
		for (int y = 0; y < gameBoard.getHeight(); ++y)
		{
			EXPECT_EQ(Mark::EMPTY, gameBoard.getSafe(x, y));
		}
	}
}

TEST(GameBoardTest, disallowedMarks)
{
	GameBoard gameBoard;
	//We can't place such marks
	EXPECT_FALSE(gameBoard.placeMark(Mark::EMPTY, 0, 0));
	EXPECT_FALSE(gameBoard.placeMark(Mark::NONE, 0, 0));
	EXPECT_TRUE(gameBoard.placeMark(Mark::O, 0, 0));
}

TEST(GameBoardTest, winDetectionHorizontal)
{
	GameBoard gameBoard;
	EXPECT_TRUE(gameBoard.placeMark(Mark::O, 0, 0));
	EXPECT_EQ(State::NONE, gameBoard.getBoardState());

	EXPECT_TRUE(gameBoard.placeMark(Mark::O, 0, 1));
	EXPECT_EQ(State::NONE, gameBoard.getBoardState());

	EXPECT_TRUE(gameBoard.placeMark(Mark::O, 0, 2));
	EXPECT_EQ(State::WIN_O, gameBoard.getBoardState());

	gameBoard.reset();
	EXPECT_EQ(State::NONE, gameBoard.getBoardState());
}

TEST(GameBoardTest, winDetectionVertical)
{
	GameBoard gameBoard;
	EXPECT_TRUE(gameBoard.placeMark(Mark::X, 0, 0));
	EXPECT_EQ(State::NONE, gameBoard.getBoardState());

	EXPECT_TRUE(gameBoard.placeMark(Mark::X, 1, 0));
	EXPECT_EQ(State::NONE, gameBoard.getBoardState());

	EXPECT_TRUE(gameBoard.placeMark(Mark::X, 2, 0));
	EXPECT_EQ(State::WIN_X, gameBoard.getBoardState());

	gameBoard.reset();
	EXPECT_EQ(State::NONE, gameBoard.getBoardState());
}

TEST(GameBoardTest, winDetectionCross)
{
	GameBoard gameBoard;
	EXPECT_TRUE(gameBoard.placeMark(Mark::X, 2, 0));
	EXPECT_EQ(State::NONE, gameBoard.getBoardState());

	EXPECT_TRUE(gameBoard.placeMark(Mark::X, 1, 1));
	EXPECT_EQ(State::NONE, gameBoard.getBoardState());

	EXPECT_TRUE(gameBoard.placeMark(Mark::X, 0, 2));
	EXPECT_EQ(State::WIN_X, gameBoard.getBoardState());

	gameBoard.reset();
	EXPECT_EQ(State::NONE, gameBoard.getBoardState());

	EXPECT_TRUE(gameBoard.placeMark(Mark::O, 2, 2));
	EXPECT_EQ(State::NONE, gameBoard.getBoardState());

	EXPECT_TRUE(gameBoard.placeMark(Mark::O, 1, 1));
	EXPECT_EQ(State::NONE, gameBoard.getBoardState());

	EXPECT_TRUE(gameBoard.placeMark(Mark::O, 0, 0));
	EXPECT_EQ(State::WIN_O, gameBoard.getBoardState());

	gameBoard.reset();
	EXPECT_EQ(State::NONE, gameBoard.getBoardState());
}

TEST(GameBoardTest, checkTie)
{
	GameBoard gameBoard;
	for (int y = 0; y < gameBoard.getHeight(); ++y)
	{
		for (int x = 0; x < gameBoard.getWidth(); ++x)
		{
			if (y % 2)
			{
				gameBoard.placeMark((x % 3) ? Mark::X : Mark::O, x, y);
			}
			else
			{
				gameBoard.placeMark((x % 3) ? Mark::O : Mark::X, x, y);
			}
		}
	}
	EXPECT_EQ(State::TIE, gameBoard.getBoardState());
}
