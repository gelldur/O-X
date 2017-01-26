//
// Created by Dawid Drozd aka Gelldur on 26/01/17.
//
#include "GameBoard.h"
//////////////////////////////////

#include <algorithm>

GameBoard::GameBoard()
{
	reset();
}

void GameBoard::reset()
{
	for (auto& row : _board)
	{
		row.fill(Mark::EMPTY);
	}
}

bool GameBoard::placeMark(GameBoard::Mark mark, ushort x, ushort y)
{
	if (mark != Mark::X && mark != Mark::O)
	{
		return false;//We can only place X & O
	}
	if (getHeight() < y + 1 || getWidth() < x + 1)
	{
		return false;//Out of board
	}

	if (at(x, y) == Mark::EMPTY)
	{
		at(x, y) = mark;//place mark
		return true;
	}
	return false;
}

GameBoard::State GameBoard::getBoardState() const
{
	if (checkMarkWins(Mark::X))
	{
		return State::WIN_X;
	}
	if (checkMarkWins(Mark::O))
	{
		return State::WIN_O;
	}
	//Nobody wins? Check for TIE. Simply is any EMPTY field left ?
	if (getMarkPositions(Mark::EMPTY).empty())
	{
		return State::TIE;
	}
	return State::DUNO;
}

GameBoard::Mark GameBoard::get(ushort x, ushort y) const
{
	return _board.at(y).at(x);
}

GameBoard::Mark& GameBoard::at(ushort x, ushort y)
{
	return _board.at(y).at(x);
}

ushort GameBoard::getWidth() const
{
	return static_cast<ushort>(_board.front().size());
}

ushort GameBoard::getHeight() const
{
	return static_cast<ushort>(_board.size());
}

std::vector<std::pair<ushort, ushort>> GameBoard::getMarkPositions(GameBoard::Mark searchMark) const
{
	std::vector<std::pair<ushort, ushort>> positions;
	for (ushort y = 0; y < getHeight(); ++y)
	{
		for (ushort x = 0; x < getWidth(); ++x)
		{
			if (get(x, y) == searchMark)
			{
				positions.emplace_back(x, y);
			}
		}
	}
	return positions;
}

bool GameBoard::checkMarkWins(GameBoard::Mark mark) const
{
	auto positions = getMarkPositions(mark);
	//Check do we have 3 in the same X or Y position
	std::vector<int> countInX(getWidth(), 0);
	std::vector<int> countInY(getHeight(), 0);
	for (const auto& element : positions)
	{
		if (++countInX.at(element.first) >= NEED_TO_WIN)
		{
			return true;
		}
		if (++countInY.at(element.second) >= NEED_TO_WIN)
		{
			return true;
		}
	}

	//Check cross from every point. We could optimize this simply by removing visited places
	for (const auto& markPresent : positions)
	{
		int countCross = 1;
		//Cross to right
		//Yes it could overflow here but we are secure for that case
		while (getSafe(markPresent.first + countCross, markPresent.second + countCross) == mark)
		{
			if (++countCross >= NEED_TO_WIN)
			{
				return true;
			}
		}

		//Cross to left
		countCross = 1;
		//Yes it could overflow here but we are secure for that case
		while (getSafe(markPresent.first - countCross, markPresent.second + countCross) == mark)
		{
			if (++countCross >= NEED_TO_WIN)
			{
				return true;
			}
		}
	}

	return false;
}

GameBoard::Mark GameBoard::getSafe(ushort x, ushort y) const
{
	if (getHeight() < y + 1 || getWidth() < x + 1)
	{
		return Mark::NONE;//Out of board
	}
	return get(x, y);
}

std::string GameBoard::toString() const
{
	std::string boardString;

	for (int y = getHeight() - 1; y > -1; --y)
	{
		for (ushort x = 0; x < getWidth(); ++x)
		{
			boardString += (char) get(x, y);
		}
		boardString += "\n";
	}

	return boardString;
}
