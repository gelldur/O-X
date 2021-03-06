//
// Created by Dawid Drozd aka Gelldur on 26/01/17.
//
#include "Game.h"
//////////////////////////////////

#include <cstdlib>
#include <sstream>
#include <cassert>
#include <dotconf.h>

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
		if (boardState == GameBoard::State::DUNO)
		{
			return gameState;
		}
	}

	return gameState;
}

bool Game::makeMove(Player* player, int x, int y)
{
	if (_gameState.getState() != GameState::State::PLAY)
	{
		return false;//Invalid state for making move
	}
	if (player == nullptr)
	{
		throw std::runtime_error("Disallowed!");
	}
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
	if (boardState != GameBoard::State::DUNO)
	{
		auto playerWhoWins = whoWins(boardState);
		if (playerWhoWins != nullptr)
		{
			playerWhoWins->addPoints(1);
		}

		_gameState.gameEnd();
		_active = nullptr;
	}

	return true;
}

void Game::switchTurn()
{
	//Switch turn
	assert(_active);
	if (_active == &_playerA)
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

std::string Game::toString() const
{
	std::stringstream stream;

	stream << "State: [" << _gameState.toString() << "]\n";
	stream << "PlayerA:[" << (char) _playerA.getMark() << "] " << _playerA.getPoints() << "p, is moving: "
		   << (_active == &_playerA) << "\n";
	stream << "PlayerB:[" << (char) _playerB.getMark() << "] " << _playerB.getPoints() << "p, is moving: "
		   << (_active == &_playerB) << "\n";
	stream << "Map:\n" << _gameBoard.toString();

	return stream.str();
}

Player* Game::getActivePlayer() const
{
	return _active;
}

void Game::pickPlayer()
{
	assert(_active == nullptr);

	//Pick who starts
	_active = (rand() % 2) ? &_playerA : &_playerB;
	_gameState.playerPicked();
}

GameBoard::Mark Game::getMark(int x, int y) const
{
	return _gameBoard.getSafe(x, y);
}

Player* Game::getPlayer(GameBoard::Mark mark)
{
	if (_playerA.getMark() == mark)
	{
		return &_playerA;
	}
	else if (_playerB.getMark() == mark)
	{
		return &_playerB;
	}
	return nullptr;
}

int Game::getBoardWidth() const
{
	return _gameBoard.getWidth();
}

int Game::getBoardHeight() const
{
	return _gameBoard.getHeight();
}

Player* Game::whoWins()
{
	return whoWins(_gameBoard.getBoardState());
}

Player* Game::whoWins(GameBoard::State state)
{
	if (state == GameBoard::State::WIN_X)
	{
		return getPlayer(GameBoard::Mark::X);
	}
	else if (state == GameBoard::State::WIN_O)
	{
		return getPlayer(GameBoard::Mark::O);
	}
	return nullptr;
}

GameBoard::State Game::getBoardState() const
{
	return _gameBoard.getBoardState();
}

void Game::resetBoard()
{
	_gameBoard.reset();
	_gameState.reset();
	_active = nullptr;//extra reset (probably we don't have to but why not :P)
}

const Player& Game::getPlayerA() const
{
	return _playerA;
}

const Player& Game::getPlayerB() const
{
	return _playerB;
}
