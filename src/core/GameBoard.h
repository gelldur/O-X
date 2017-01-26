//
// Created by Dawid Drozd aka Gelldur on 26/01/17.
//
#pragma once

#include <array>
#include <vector>

class GameBoard
{
public:
	using ushort = unsigned short;

	GameBoard();

	enum class Mark : char
	{
		X = 'X', O = 'O', EMPTY = ' ', NONE = '\0'
	};

	/**
	 * @param mark
	 * @return true if mark was successful placed, false otherwise
	 */
	bool placeMark(Mark mark, ushort x, ushort y);

	enum class State
	{
		TIE, NONE, WIN_X, WIN_O
	};

	/**
	 * @return State::NONE when no one wins, State::TIE if TIE, State::WIN_X when 'X' wins, State::WIN_O when 'O' wins
	 */
	State getBoardState() const;

	/**
	 * Reset whole board. For new game use
	 */
	void reset();

	ushort getWidth() const;
	ushort getHeight() const;

	/**
	 * @param x coordinate position
	 * @param y coordinate position
	 * @return Mark if such field exist if no it will return Mark::NONE
	 */
	Mark getSafe(ushort x, ushort y) const;

	//for debug
	std::string toString() const;

private:
	const ushort NEED_TO_WIN = 3;
	std::array<std::array<Mark, 3>, 3> _board;

	Mark get(ushort x, ushort y) const;
	Mark& at(ushort x, ushort y);

	std::vector<std::pair<ushort, ushort>> getMarkPositions(Mark searchMark) const;
	bool checkMarkWins(Mark mark) const;
};


