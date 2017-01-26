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
	GameBoard::State getBoardState() const;

	int getPlayerAPoints() const;
	int getPlayerBPoints() const;

	//For debug
	std::string toString() const;

	/**
	 * @return nullptr if no player is active, else return active player
	 */
	Player* getActivePlayer() const;
	const Player& getPlayerA() const;
	const Player& getPlayerB() const;

	void pickPlayer();

	GameBoard::Mark getMark(int x, int y) const;
	int getBoardWidth() const;
	int getBoardHeight() const;

	/**
	 * @return nullptr if no one currently wins or it is TIE, otherwise return who currently wins according to game board state
	 */
	Player* whoWins();

	void resetBoard();

private:
	Player* _active = nullptr;
	Player _playerA;
	Player _playerB;
	GameBoard _gameBoard;
	GameState _gameState;

	void switchTurn();
	/**
	 * @param mark
	 * @return if noone has such mark
	 */
	Player* getPlayer(GameBoard::Mark mark);

	/**
	 * @param state
	 * @return who wins for specyfic state, nullptr otherwise
	 */
	Player* whoWins(GameBoard::State state);
};


