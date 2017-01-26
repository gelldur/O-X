//
// Created by Dawid Drozd aka Gelldur on 26/01/17.
//
#pragma once

#include <string>

class GameState
{
public:
	enum class State
	{
		PICK_PLAYER, PLAY, END_GAME
	};

	void playerPicked();
	void gameEnd();
	void reset();

	State getState() const;

	//For debug
	std::string toString() const;

private:
	State _state = State::PICK_PLAYER;
};


