//
// Created by Dawid Drozd aka Gelldur on 26/01/17.
//
#include "Player.h"
//////////////////////////////////

Player::Player(GameBoard::Mark mark)
		: _mark(mark)
{
}

int Player::getPoints() const
{
	return _points;
}

GameBoard::Mark Player::getMark() const
{
	return _mark;
}

void Player::addPoints(int points)
{
	_points += points;
}
