//
// Created by Dawid Drozd aka Gelldur on 26/01/17.
//
#pragma once

#include <string>

#include "Player.h"
#include "GameBoard.h"
#include "GameState.h"

class Game
{
public:
	Game();

	bool makeMove(Player* player, int x, int y);

	GameState::State getGameState() const;

	int getPlayerAPoints() const;
	int getPlayerBPoints() const;

	//For debug
	std::string toString() const;

	/**
	 * @return nullptr if no player is active, else return active player
	 */
	Player* getActivePlayer() const;

	void pickPlayer();

	GameBoard::Mark getMark(int x, int y) const;

private:
	Player* _active = nullptr;
	Player _playerA;
	Player _playerB;
	GameBoard _gameBoard;
	GameState _gameState;

	void switchTurn();
};


