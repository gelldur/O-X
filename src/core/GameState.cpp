//
// Created by Dawid Drozd aka Gelldur on 26/01/17.
//
#include "GameState.h"
//////////////////////////////////

#include <stdexcept>

GameState::State GameState::getState() const
{
	return _state;
}

std::string GameState::toString() const
{
	switch (_state)
	{
		case State::PLAY:
			return "play";
		case State::END_GAME:
			return "end game";
		case State::PICK_PLAYER:
			return "pick player";
		default:
			return "fix string for new state!";
	}
}

void GameState::playerPicked()
{
	if (_state != State::PICK_PLAYER)
	{
		throw std::runtime_error("Incorrect state transfer");
	}
	_state = State::PLAY;
}

void GameState::gameEnd()
{
	if (_state != State::PLAY)
	{
		throw std::runtime_error("Incorrect state transfer");
	}
	_state = State::END_GAME;
}

void GameState::reset()
{
	if (_state != State::END_GAME)
	{
		throw std::runtime_error("Incorrect state transfer");
	}
	_state = State::PICK_PLAYER;
}
