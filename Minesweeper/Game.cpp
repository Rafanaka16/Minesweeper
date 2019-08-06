//
// Created by rafan on 4/21/2019.
//

#include "Game.h"
#include "Box.h"
#include <iostream>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include<fstream>
#include <string>

using namespace std;

bool Game::isValid(int x, int y, int w, int l) {
	return x >= 0 && x < w && y >= 0 && y < l;
}

void Game::neighbors(Tile* tile, Box*** table_, int w, int l) {
	int D_w[8] = { -1, 0, 1, 1, 1, 0, -1, -1 };
	int D_l[8] = { -1, -1, -1, 0, 1, 1, 1, 0 };
	vector<Tile*> toCheck;
	for (int i = 0; i < 8; i++) {
		int new_x = tile->x + D_w[i];
		int new_y = tile->y + D_l[i];
		if (isValid(new_x, new_y, w, l)) {
			//if (table_[new_x][new_y]->getImage() == 'F') continue;
			if (table_[new_x][new_y]->isMine()) {
				tile->increaseCounter();
			}

			else if (!table_[new_x][new_y]->isMine() && !table_[new_x][new_y]->isChecked() && !table_[new_x][new_y]->isFlagged()) {
				toCheck.push_back(dynamic_cast<Tile*>(table_[new_x][new_y]));
			}
		}
	}
	if (tile->counter == 0) {
		for (unsigned int i = 0; i < toCheck.size(); i++) {
			//if (toCheck[i]->image == 'F') { toCheck[i]->checked = false; }// <------------------ New
			 {
				tile->SetImage('O');
				toCheck[i]->checked = true;
				toCheck[i]->SetImage('O');
			}
		}
		for (unsigned int i = 0; i < toCheck.size(); i++) {
			neighbors(toCheck[i], table_, w, l);
		}
		tile->SetImage('O');
	}
	else
		tile->SetImage((char)tile->counter + 48);
}


void Game::checkGame() {
	int temp = 0;
	for (int i = 0; i < w; i++) {
		for (int j = 0; j < l; j++) {
			if (table[i][j]->isChecked())
				temp++;
		}
	}
	cout << "Checked box: " << temp << endl;
	cout << w << "*" << l << "-(" << mines << "+" << flags << ") = " << (w * l - (mines + flags))<< endl;
	gameWon = temp == w * l - (mines + flags);
}

Game::Game() {
	gameLost = false;
	flags = 0;
	mines = 50;
	debugMode = false;
	srand(time(NULL));
	for (unsigned int i = 0; i < w; i++) {
		table[i] = new Box * [l];
		for (unsigned int j = 0; j < l; j++) {
			table[i][j] = new Tile();
			table[i][j]->x = i;
			table[i][j]->y = j;
		}
	}

	for (unsigned int i = 0; i < w * l; i++) {
		tempRemove.push_back(i);
	}
	tempRand = 0;
	///random optimization
	for (unsigned int i = 0; i < mines; i++) {
		tempRand = rand() % tempRemove.size();
		tempAdd.push_back(tempRemove.at(tempRand));
		tempRemove.erase(tempRemove.begin() + tempRand);
	}

	for (unsigned int i = 0; i < tempAdd.size(); i++) {
		table[tempAdd.at(i) % w][tempAdd.at(i) / w] = new Mine();
	}


}

Game::Game(string s)
{
	gameLost = false;
	flags = 0;
	mines = 0;
	debugMode = false;
	string line;
	char temp;
	int count = 0;
	ifstream file;
	file.open(s);
	for (unsigned int i = 0; i < w; i++) {
		table[i] = new Box * [l];
		for (unsigned int j = 0; j < l; j++) {
			table[i][j] = new Tile();
			table[i][j]->x = i;
			table[i][j]->y = j;
		}
	}
	while (getline(file, line, '\n')) {
		for (unsigned int i = 0; i < line.length(); i++) {
			temp = line.at(i);
			if (temp == '1') {
				mines++;
				table[i][count] = new Mine();
			}
			//else{
				//table[i][count] = new Tile();
			//}
		}
		count++;
	}
}

void Game::terminateGame(Game game)
{
	
}


