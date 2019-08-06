#include <SFML/Graphics.hpp>
#include <iomanip>
#include <iostream>
#include"Game.h"
#include<map>
#include<fstream>
using namespace std;

void draw(int x, int y, vector<string>* m, sf::RenderWindow* window);
void drawCurrent(Game game, map<char, vector<string>*> m, sf::RenderWindow* window);
void drawbombcounter( int n ,sf::RenderWindow* window);
void debugMode(map<char, vector<string>*> m);
//void drawLostGame(Game game, )
//void drawNewGame(Game game, map<char, vector<string>*> m, sf::RenderWindow* window);
//void GenerateBaseTable(Game game, sf::RenderWindow* window);


int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Minesweeper");
	//sf::CircleShape shape(100.f);
	//shape.setFillColor(sf::Color::Green);

	sf::Texture texture; //load file
	sf::Sprite sprite; //paint the file

	Game game;
	map<char, vector<string>*> imageMap;
	imageMap['X'] = new vector<string>{ "images/tile_hidden.png" }; //Hidden
	imageMap['x'] = new vector<string>{ "images/tile_revealed.png", "images/mine.png" }; //Revealed
	imageMap['-'] = new vector<string>{ "images/tile_hidden.png" };
	imageMap['O'] = new vector<string>{ "images/tile_revealed.png" };
	imageMap['1'] = new vector<string>{ "images/tile_revealed.png", "images/number_1.png" };
	imageMap['2'] = new vector<string>{ "images/tile_revealed.png", "images/number_2.png" };
	imageMap['3'] = new vector<string>{ "images/tile_revealed.png", "images/number_3.png" };
	imageMap['4'] = new vector<string>{ "images/tile_revealed.png", "images/number_4.png" };
	imageMap['5'] = new vector<string>{ "images/tile_revealed.png", "images/number_5.png" };
	imageMap['6'] = new vector<string>{ "images/tile_revealed.png", "images/number_6.png" };
	imageMap['7'] = new vector<string>{ "images/tile_revealed.png", "images/number_7.png" };
	imageMap['8'] = new vector<string>{ "images/tile_revealed.png", "images/number_8.png" };
	imageMap['F'] = new vector<string>{ "images/tile_hidden.png", "images/flag.png" };

	window.display();

	//GenerateBaseTable(game, &window);

	/*for (unsigned int i = 0; i < 800; i += 32) {
		for (unsigned int j = 0; j < 512; j += 32) {
			draw(i, j, imageMap['O'], &window);
			//draw(i, j, imageMap['-'], &window);
			if (game.table[i / 32][j / 32]->isMine())
				draw(i, j, imageMap['X'], &window);
			draw(i, j, imageMap['-'], &window);

		}
	}*/
	drawCurrent(game, imageMap, &window);
	drawbombcounter(game.mines, &window);

	//draw face
	//texture.loadFromFile("images/face_happy.png");
	//sprite.setTexture(texture);
	//sprite.setPosition(sf::Vector2f(400, 512));
	//window.draw(sprite);

		//draw1(0, 0, "images/tile_revealed.png", &window);

	window.display();

	while (window.isOpen())
	{

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::MouseButtonPressed) {
				sf::Vector2<int> position = sf::Mouse::getPosition(window);
				int row = position.x / 32;
				int col = position.y / 32;
				window.clear();

				if (event.mouseButton.button == sf::Mouse::Button::Left) {
#pragma region Controls
					//New Game, Face Click
					if (position.x > 328 && position.x < 392 && position.y > 512 && position.y < 576) {
						game = *new Game;
						drawCurrent(game, imageMap, &window);
						drawbombcounter(game.mines, &window);
					}
					//Load Test 1
					else if (position.x > 520 && position.x < 584 && position.y > 512 && position.y < 576) {
						game = *new Game("boards/testboard1.brd");
					}
					//Load Test 2
					else if (position.x > 584 && position.x < 648 && position.y > 512 && position.y < 576) {
						game = *new Game("boards/testboard2.brd");
					}
					//Load Test 2
					else if (position.x > 648 && position.x < 712 && position.y > 512 && position.y < 576) {
						game = *new Game("boards/testboard3.brd");
					}
					//Debug Mode
					else if (position.x > 456 && position.x < 520 && position.y > 512 && position.y < 576 && !game.gameWon) {
						game.debugMode = !game.debugMode;
						drawCurrent(game, imageMap, &window);
						drawbombcounter(game.mines, &window);
					}
#pragma endregion

//Board
					else if (position.y < 512 && !game.gameWon && !game.gameLost && !game.table[row][col]->isFlagged() && !game.table[row][col]->isChecked()) {
						if (game.table[row][col]->isMine()) { //<----------checking for game lost
							game.gameLost = true;
							drawCurrent(game,imageMap,&window); 
							drawbombcounter(game.mines, &window);
						}
						else {
							game.table[row][col]->checked = true;
							game.neighbors(dynamic_cast<Tile*>(game.table[row][col]), game.table, game.w, game.l);
							drawCurrent(game, imageMap, &window);
							drawbombcounter(game.mines, &window);
						}
					}
				}
				else if (event.mouseButton.button == sf::Mouse::Button::Right && !game.gameLost && !game.gameWon) {
					//drawCurrent(game, imageMap, &window);
					//drawbombcounter(game.mines, &window);

					if (position.y < 512 && !game.table[row][col]->isChecked()) {
						if (game.table[row][col]->isFlagged()) {
							game.table[row][col]->flag = false;
							draw(game.table[row][col]->x * 32, game.table[row][col]->y * 32, imageMap['-'], &window);
							game.mines++;
							game.flags--;
						}
						else {
							game.table[row][col]->flag = true;
							draw(game.table[row][col]->x * 32, game.table[row][col]->y * 32, imageMap['F'], &window);
							game.mines--;
							game.flags++;
						}
					}
				}
				game.checkGame();
				cout << "Number of Mines:" <<game.mines<< endl;
				cout << "Number of Flags:" <<game.flags<< endl;
				cout << "Win? :" << game.gameWon <<endl;
				cout << "Lost? :" << game.gameLost<<endl;
				cout << endl;

				drawCurrent(game, imageMap, &window);
				drawbombcounter(game.mines, &window);
				window.display();
			}
		}
	}
	return 0;
}


		//window.clear();

		//window.display();
void draw(int x, int y, vector<string>* m, sf::RenderWindow* window)
{
	//auto iter = m.begin();

	sf::Texture texture; //load file
	sf::Sprite sprite; //paint the file
	for (string s : *m) {
		texture.loadFromFile(s);
		sprite.setTexture(texture);
		sprite.setPosition(sf::Vector2f(x, y));
		window->draw(sprite);
	}
	
	//sprite.setTextureRect(sf::IntRect(x, y, 32, 32));

}

/*
void drawCurrent(Game game,  map<char, vector<string>*> m, sf::RenderWindow* window)
{
	//auto iter = m.begin();
	sf::Texture texture; //load file
	sf::Sprite sprite; //paint the file

	for (unsigned int i = 0; i < 800; i += 32) {
		for (unsigned int j = 0; j < 512; j += 32) {
			switch (game.table[i/32][j/32]->getImage()) {
			case 'X':{
				draw(i, j, m['X'], window);
				//draw(i, j, m['-'], window);
				break;
				}
			case '-': {
				draw(i, j, m['-'], window);
				break;
			}
			case 'O': {
				draw(i, j, m['O'], window);
				break;
			}
			case '1': {
				draw(i, j, m['1'], window);
				break;
			}
			case '2': {
				draw(i, j, m['2'], window);
				break;
			}
			case '3': {
				draw(i, j, m['3'], window);
				break;
			}
			case '4': {
				draw(i, j, m['4'], window);
				break;
			}
			case '5': {
				draw(i, j, m['5'], window);
				break;
			}
			case '6': {
				draw(i, j, m['6'], window);
				break;
			}
			case '7': {
				draw(i, j, m['7'], window);
				break;
			}
			case '8': {
				draw(i, j, m['8'], window);
				break;
			}
			case 'F': {
				draw(i, j, m['F'], window);
				break;
			}
			default:
				break;
			}			
		}
		vector<string>* s = new vector<string>{ "images/face_happy.png", "images/test_1.png", "images/test_2.png", "images/test_2.png" };
		for (int i = 328; i < 392; i+=64) {
			for (int j = 512; i < 576; i += 64) {
			}
		}
		draw(328, 512, new vector<string>{ "images/face_happy.png" }, window);
		draw(456, 512, new vector<string>{ "images/debug.png" }, window);
		draw(520, 512, new vector<string>{ "images/test_1.png" }, window);
		draw(584, 512, new vector<string>{ "images/test_2.png" }, window);
		draw(648, 512, new vector<string>{ "images/test_3.png" }, window);
	}
	
}
*/

void drawCurrent(Game game, map<char, vector<string>*> m, sf::RenderWindow* window)
{
	//auto iter = m.begin();
	sf::Texture texture; //load file
	sf::Sprite sprite; //paint the file

	for (unsigned int i = 0; i < 800; i += 32) {
		for (unsigned int j = 0; j < 512; j += 32) {
			char value = game.table[i / 32][j / 32]->getImage();
			if (value == 'X') {
				if ((game.gameLost || game.debugMode))
					value = 'x';
				else if (game.gameWon)
					value = 'F';
			}
			draw(i, j, m[value], window);
		}
		
		draw(456, 512, new vector<string>{ "images/debug.png" }, window);
		draw(520, 512, new vector<string>{ "images/test_1.png" }, window);
		draw(584, 512, new vector<string>{ "images/test_2.png" }, window);
		draw(648, 512, new vector<string>{ "images/test_3.png" }, window);

		if (game.gameLost) {
			draw(328, 512, new vector<string>{ "images/face_lose.png" }, window);
		}
		else if (game.gameWon) {
			draw(328, 512, new vector<string>{ "images/face_win.png" }, window);
		}
		else
			draw(328, 512, new vector<string>{ "images/face_happy.png" }, window);
	}

}


void drawbombcounter(int n, sf::RenderWindow* window)
{
	int temp = 0;
	sf::Texture texture; //load file
	sf::Sprite sprite; //paint the file
	//if (n >= 10) {
	texture.loadFromFile("images/digits.png");
	sprite.setTexture(texture);
	int variation = 0;
	if (n < 0) {
		n *= -1;
		variation = 1;
	}
	for (int i = 21 * (2+variation); i >= 0; i -= 21) {
		sprite.setPosition(sf::Vector2f(i, 512));
		temp = n % 10;
		sprite.setTextureRect(sf::IntRect(21 * temp, 0, 21, 32));
		window->draw(sprite);
		n = n / 10;
	}
	if (variation == 1) {
		sprite.setPosition(sf::Vector2f(0, 512));
		sprite.setTextureRect(sf::IntRect(21 * 10, 0, 21, 32));
		window->draw(sprite);
	}
}

void debugMode(map<char, vector<string>*> m)
{
	m.at('X')= new vector<string>{ "images/tile_revealed.png", "images/mine.png", };
}

