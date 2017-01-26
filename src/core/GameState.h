//
// Created by Dawid Drozd aka Gelldur on 26/01/17.
//
#pragma once

class GameState
{
public:
	enum class State
	{
		PICK_PLAYER, PLAY, END_GAME
	};

	void playerPicked();
	void gameEnd();

	State getState() const;

private:
	State _state = State::PICK_PLAYER;
};


