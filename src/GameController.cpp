//
// Created by Dawid Drozd aka Gelldur on 26/01/17.
//
#include "GameController.h"
//////////////////////////////////

#include <iostream>

GameController::GameController(QObject* parent)
		: inherited(parent)
{
	actionButton();//On start we pick starting player
}

bool GameController::clickField(int x, int y)
{
	std::cout << "Clicked: " << x << " " << y << std::endl;
	return _game.makeMove(_game.getActivePlayer(), x, y);
}

char GameController::getField(int x, int y)
{
	return static_cast<char>(_game.getMark(x, y));
}

std::string GameController::getMyInformation()
{
	if (_game.getGameState() == GameState::State::PLAY)
	{
		std::string message = "Now will move: ";
		message += static_cast<char>(_game.getActivePlayer()->getMark());
		return message;
	}
	else if (_game.getGameState() == GameState::State::PICK_PLAYER)
	{
		return "Please press start";
	}
	else if (_game.getGameState() == GameState::State::END_GAME)
	{
		auto winningPlayer = _game.whoWins();
		if (winningPlayer == nullptr)
		{
			return "We have TIE!\nHit next game";
		}
		else
		{
			std::string message = "Player: ";
			message += static_cast<char>(winningPlayer->getMark());
			return message + " wins!\nHit next game";
		}
	}

	return "nothing funny";
}

QString GameController::getInformation()
{
	return QString(getMyInformation().c_str());
}

QString GameController::getPlayerAText()
{
	std::string name = "Player A as ";
	name += static_cast<char>(_game.getPlayerA().getMark());
	name += "\npoints: ";
	name += std::to_string(_game.getPlayerAPoints());
	return QString(name.c_str());
}

QString GameController::getPlayerBText()
{
	std::string name = "Player B as ";
	name += static_cast<char>(_game.getPlayerB().getMark());
	name += "\npoints: ";
	name += std::to_string(_game.getPlayerBPoints());
	return QString(name.c_str());
}

void GameController::actionButton()
{
	if (_game.getGameState() == GameState::State::PICK_PLAYER)
	{
		_game.pickPlayer();
	}
	else if (_game.getGameState() == GameState::State::END_GAME || _game.getGameState() == GameState::State::PLAY)
	{
		_game.resetBoard();
		_game.pickPlayer();//We want it automatically
	}
}

QString GameController::actionButtonText()
{
	if (_game.getGameState() == GameState::State::PICK_PLAYER)
	{
		return QString("Start");
	}
	else if (_game.getGameState() == GameState::State::END_GAME)
	{
		return QString("Next game");
	}
	else if (_game.getGameState() == GameState::State::PLAY)
	{
		return QString("Reset round");
	}
	return QString("UPS!!!");
}

