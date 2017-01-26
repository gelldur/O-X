//
// Created by Dawid Drozd aka Gelldur on 26/01/17.
//
#include <iostream>

#include <gtest/gtest.h>

#include <core/Game.h>

using Mark = GameBoard::Mark;
using State = GameBoard::State;

TEST(GameTest, sample)
{
	srand(12);
	Game game;
	std::cout << game.toString();

	EXPECT_EQ(GameState::State::PICK_PLAYER, game.getGameState());
	EXPECT_EQ(nullptr, game.getActivePlayer());
	EXPECT_EQ(0, game.getPlayerAPoints());
	EXPECT_EQ(0, game.getPlayerBPoints());

	game.pickPlayer();
	EXPECT_NE(nullptr, game.getActivePlayer());
	EXPECT_EQ(GameBoard::Mark::O, game.getActivePlayer()->getMark());
	std::cout << game.toString();

	EXPECT_EQ(GameState::State::PLAY, game.getGameState());

	EXPECT_TRUE(game.makeMove(game.getActivePlayer(), 0, 0));
	EXPECT_EQ(GameBoard::Mark::O, game.getMark(0, 0));

	//Player should be switched
	EXPECT_EQ(GameBoard::Mark::X, game.getActivePlayer()->getMark());
	std::cout << game.toString();

	EXPECT_EQ(GameBoard::Mark::X, game.getActivePlayer()->getMark());
	EXPECT_TRUE(game.makeMove(game.getActivePlayer(), 0, 1));
	EXPECT_EQ(GameBoard::Mark::O, game.getActivePlayer()->getMark());
	EXPECT_TRUE(game.makeMove(game.getActivePlayer(), 1, 0));
	EXPECT_TRUE(game.makeMove(game.getActivePlayer(), 0, 2));
	EXPECT_TRUE(game.makeMove(game.getActivePlayer(), 2, 0));
	std::cout << game.toString();

	//We should win now
	EXPECT_EQ(nullptr, game.getActivePlayer());//no active player
	EXPECT_EQ(0, game.getPlayerAPoints());//points should be added
	EXPECT_EQ(1, game.getPlayerBPoints());
	EXPECT_EQ(GameState::State::END_GAME, game.getGameState());

	//We can't make move, we arte in bad state
	EXPECT_FALSE(game.makeMove(game.getActivePlayer(), 1, 1));
}

TEST(GameTest, checkTie)
{
	srand(12);
	Game game;
	std::cout << game.toString();

	EXPECT_EQ(GameState::State::PICK_PLAYER, game.getGameState());
	EXPECT_EQ(nullptr, game.getActivePlayer());
	EXPECT_EQ(0, game.getPlayerAPoints());
	EXPECT_EQ(0, game.getPlayerBPoints());

	game.pickPlayer();
	EXPECT_NE(nullptr, game.getActivePlayer());
	EXPECT_EQ(GameBoard::Mark::O, game.getActivePlayer()->getMark());
	std::cout << game.toString();

	EXPECT_EQ(GameState::State::PLAY, game.getGameState());
	EXPECT_TRUE(game.makeMove(game.getActivePlayer(), 0, 0));//O
	EXPECT_TRUE(game.makeMove(game.getActivePlayer(), 1, 0));//X
	EXPECT_TRUE(game.makeMove(game.getActivePlayer(), 2, 0));//O

	EXPECT_TRUE(game.makeMove(game.getActivePlayer(), 1, 1));//X
	EXPECT_TRUE(game.makeMove(game.getActivePlayer(), 0, 1));//O
	EXPECT_TRUE(game.makeMove(game.getActivePlayer(), 2, 1));//X

	EXPECT_TRUE(game.makeMove(game.getActivePlayer(), 1, 2));//O
	EXPECT_TRUE(game.makeMove(game.getActivePlayer(), 0, 2));//X
	EXPECT_TRUE(game.makeMove(game.getActivePlayer(), 2, 2));//O

	std::cout << game.toString();

	//This is last move
	EXPECT_EQ(GameState::State::END_GAME, game.getGameState());
	EXPECT_EQ(nullptr, game.whoWins());

	//Ended with tie
	EXPECT_EQ(0, game.getPlayerAPoints());
	EXPECT_EQ(0, game.getPlayerBPoints());

	game.resetBoard();//We can play second round
	std::cout << game.toString();//empty map

	EXPECT_EQ(GameState::State::PICK_PLAYER, game.getGameState());
	EXPECT_EQ(nullptr, game.getActivePlayer());
	EXPECT_EQ(0, game.getPlayerAPoints());
	EXPECT_EQ(0, game.getPlayerBPoints());

	game.pickPlayer();
	EXPECT_NE(nullptr, game.getActivePlayer());
	EXPECT_EQ(GameBoard::Mark::O, game.getActivePlayer()->getMark());
	std::cout << game.toString();

	EXPECT_EQ(GameState::State::PLAY, game.getGameState());

	EXPECT_TRUE(game.makeMove(game.getActivePlayer(), 0, 0));
	EXPECT_EQ(GameBoard::Mark::O, game.getMark(0, 0));

	//Player should be switched
	EXPECT_EQ(GameBoard::Mark::X, game.getActivePlayer()->getMark());
	std::cout << game.toString();

	EXPECT_EQ(GameBoard::Mark::X, game.getActivePlayer()->getMark());
	EXPECT_TRUE(game.makeMove(game.getActivePlayer(), 0, 1));
	EXPECT_EQ(GameBoard::Mark::O, game.getActivePlayer()->getMark());
	EXPECT_TRUE(game.makeMove(game.getActivePlayer(), 1, 0));
	EXPECT_TRUE(game.makeMove(game.getActivePlayer(), 0, 2));
	EXPECT_TRUE(game.makeMove(game.getActivePlayer(), 2, 0));
	std::cout << game.toString();

	//We should win now
	EXPECT_EQ(nullptr, game.getActivePlayer());//no active player
	EXPECT_EQ(0, game.getPlayerAPoints());//points should be added
	EXPECT_EQ(1, game.getPlayerBPoints());
	EXPECT_EQ(GameState::State::END_GAME, game.getGameState());

	//We can't make move, we arte in bad state
	EXPECT_FALSE(game.makeMove(game.getActivePlayer(), 1, 1));
}
