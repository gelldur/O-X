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
}
