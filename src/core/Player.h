//
// Created by Dawid Drozd aka Gelldur on 26/01/17.
//
#pragma once

#include "GameBoard.h"

class Player
{
public:
	Player(GameBoard::Mark mark);

	int getPoints() const;
	void addPoints(int points);
	GameBoard::Mark getMark() const;

private:
	int _points = 0;
	const GameBoard::Mark _mark;
};


