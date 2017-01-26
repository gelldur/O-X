//
// Created by Dawid Drozd aka Gelldur on 26/01/17.
//
#pragma once

#include <QObject>

#include <core/Game.h>

class GameController : public QObject
{
Q_OBJECT
	using inherited = QObject;
public:
	explicit GameController(QObject* parent = nullptr);

	Q_INVOKABLE bool clickField(int x, int y);
	Q_INVOKABLE char getField(int x, int y);
	Q_INVOKABLE QString getInformation();

	Q_INVOKABLE QString getPlayerAText();
	Q_INVOKABLE QString getPlayerBText();

	Q_INVOKABLE void actionButton();
	Q_INVOKABLE QString actionButtonText();

private:
	Game _game;

	std::string getMyInformation();
};


