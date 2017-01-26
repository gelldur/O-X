//
// Created by Dawid Drozd aka Gelldur on 26/01/17.
//
#include <cstdlib>
#include "Game.h"
//////////////////////////////////

Game::Game()
		: _playerA(GameBoard::Mark::X)
		, _playerB(GameBoard::Mark::O)
{
}

GameState::State Game::getGameState() const
{
	auto gameState = _gameState.getState();
	if (gameState == GameState::State::PLAY)
	{
		auto boardState = _gameBoard.getBoardState();
		if (boardState == GameBoard::State::NONE)
		{
			return gameState;
		}
	}

	return gameState;
}

bool Game::makeMove(Player* player, int x, int y)
{
	if (player != _active)
	{
		return false;//Not your turn
	}
	if (_gameBoard.placeMark(player->getMark(), x, y) == false)
	{
		return false;
	}

	switchTurn();
	auto boardState = _gameBoard.getBoardState();
	if (boardState != GameBoard::State::NONE)
	{
		_gameState.gameEnd();
	}

	return true;
}

void Game::switchTurn()
{
	//Switch turn
	if (_active == nullptr)
	{
		//Pick who starts
		_active = (rand() % 2) ? &_playerA : &_playerB;
		_gameState.playerPicked();
	}
	else if (_active == &_playerA)
	{
		_active = &_playerB;
	}
	else if (_active == &_playerB)
	{
		_active = &_playerA;
	}
}

int Game::getPlayerAPoints() const
{
	return _playerA.getPoints();
}

int Game::getPlayerBPoints() const
{
	return _playerB.getPoints();
}
