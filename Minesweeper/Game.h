#pragma once
#include "Box.h"
#include <iostream>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

class Game
{
public:
	unsigned int w = 25;
	int flags;
	bool gameWon;
	bool gameLost;
	bool debugMode;
	unsigned int l = 16;
	unsigned int mines;
	Box*** table = new Box * *[w];
	vector<int> tempRemove;
	vector<int> tempAdd;
	unsigned int tempRand = 0;

	Game();
	Game(string s);
	void terminateGame(Game game);
	void neighbors(Tile* tile, Box*** table_, int w, int l);
	bool isValid(int x, int y, int w, int l);
	void checkGame();
};

