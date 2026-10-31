#include <SFML/Graphics.hpp>
#include <iostream>
#include<string>
#include <cstdlib>
#include<ctime>
#include<vector>
#include<algorithm>

const int size = 4;
const float TILE_SIZE = 150.f;
const float PADDING = 10.f;
const float offset = 50.f;

int board[size][size];
int score;

sf::Color getTileColor(int value) {
switch (value) {
case 0:return sf::Color(205, 193, 180);
case 2:return sf::Color(238, 228, 218);
case 4:return sf::Color(237, 224, 200);
case 8:return sf::Color(242, 177, 121);
case 16:return sf::Color(245, 149, 99);
case 32:return sf::Color(246, 124, 95);
case 64:return sf::Color(246, 94, 59);
case 128:return sf::Color(237, 207, 114);
case 256:return sf::Color(237, 204, 97);
case 512:return sf::Color(237, 200, 80);
case 1024:return sf::Color(237, 197, 63);
case 2048:return sf::Color(237, 194, 46);
default: return sf::Color(60, 58, 50);
	}
}

sf::Color getTextColor(int value) {
	if (value <= 4) return sf::Color(119, 110, 101);
	return sf::Color::White;
}

void initBoard() {
	for (int i = 0;i < size;i++) {
		for (int q = 0;q < size;q++) {
			board[i][q] = 0;
		}
	}
}

void addRandomTile() {
	std::vector<std::pair<int, int>> emptyCells;
	for (int i = 0;i < size;i++) {
		for (int q = 0;q < size;q++) {
			if (board[i][q] == 0) {
				emptyCells.push_back({ i,q });
			}
		}
	}
	if (emptyCells.empty()) return;

	int index = rand() % emptyCells.size();
	int row = emptyCells[index].first;
	int col = emptyCells[index].second;

	board[row][col] = (rand() % 10 == 0) ? 4 : 2;


}

void moveLeft() {
	for (int i = 0;i < size;i++) {
		//собираем не нулевые элементы
		std::vector<int> row;
		for (int q = 0;q < size;q++) {
			if (board[i][q] != 0) {
				row.push_back(board[i][q]);
			}
		}
		//сливаем одинаковые
		if (row.size() > 0) {
			for (size_t q = 0; q < row.size() - 1;q++) {
				if (row[q] == row[q + 1]) {
					row[q] *= 2;
					score += row[q];
					row[q + 1] = 0;
					q++;
				}
			}
		}
		//убираем нули
		std::vector<int> newRow;
		for (int val : row) {
			if (val != 0) {
				newRow.push_back(val);
			}
		}
		//заполняем строку
		for (int q = 0;q < size;q++) {
			if (q < newRow.size()) {
				board[i][q] = newRow[q];
			}
			else {
				board[i][q] = 0;
			}
		}
	}
}

void moveRight() {

	for (int i = 0;i < size;i++) {
		std::vector<int> row;
		for (int q = 0;q < size;q++) {
			if (board[i][q] != 0) {
				row.push_back(board[i][q]);
			}
		}
		if (row.size() > 0) {
			for (size_t q = 0;q < row.size() - 1;q++) {
				if (row[q] == row[q + 1]) {
					row[q] *= 2;
					score += row[q];
					row[q + 1] = 0;
					q++;
				}
			}
		}
		std::vector<int>newRow;
		for (int val : row) {
			if (val != 0) {
				newRow.push_back(val);
			}
		}
		std::reverse(newRow.begin(), newRow.end());
		int right = 3;
		for (int q = 0;q < size;q++) {
			if (q < newRow.size()) {
				board[i][right] = newRow[q];
			}
			else {
				board[i][right] = 0;
			}
			right--;
		}
	}
}

void moveUp() {
	for (int q = 0;q < size;q++) {
		std::vector<int> row;
		for (int i = 0;i < size;i++) {
			if (board[i][q] != 0) {
				row.push_back(board[i][q]);
			}
		}
		if (row.size() > 0) {
			for (size_t i = 0;i < row.size() - 1;i++) {
				if (row[i] == row[i + 1]) {
					row[i] *= 2;
					score += row[i];
					row[i + 1] = 0;
					i++;
				}
			}
		}
		std::vector<int> newRow;
		for (int val : row) {
			if (val != 0) {
				newRow.push_back(val);
			}
		}
		for (int i = 0;i < size;i++) {
			if (i < newRow.size()) {
				board[i][q] = newRow[i];
			}
			else {
				board[i][q] = 0;
			}
		}
	}
}

void moveDown() {
	for (int q = 0;q < size;q++) {
		std::vector<int>row;
		for (int i = 0;i < size;i++) {
			if (board[i][q] != 0) {
				row.push_back(board[i][q]);
			}
		}
		if (row.size() > 0) {
			for (size_t i = 0;i < row.size() - 1;i++) {
				if (row[i] == row[i + 1]) {
					row[i] *= 2;
					score += row[i];
					row[i + 1] = 0;
					i++;
				}
			}
			std::vector<int> newRow;
			for (int val : row) {
				if (val != 0) {
					newRow.push_back(val);
				}
			}
			std::reverse(newRow.begin(), newRow.end());
			int down = 3;
			for (int i = 0;i < size;i++) {
				if (i < newRow.size()) {
					board[down][q] = newRow[i];
				}
				else {
					board[down][q] = 0;
				}
				down--;
			}
		}
	}
}

bool isGameOver() {
	for (int i = 0;i < size;i++) {
		for (int q = 0;q < size;q++) {
			if (board[i][q] == 0) {
				return false;
			}
		}
	}
	for (int i = 0;i < size;i++) {
		for (int q = 0;q < size;q++) {
			if (q < size - 1 && board[i][q] == board[i][q + 1]) {
				return false;
			}
			if (i < size - 1 && board[i][q] == board[i + 1][q]) {
				return false;
			}
		}
	}
	return true;
}

bool isWin() {
	for (int i = 0;i < size;i++) {
		for (int q = 0;q < size;q++) {
			if (board[i][q] == 2048) {
				return true;
			}
		}
	}
	return false;
}

int main() {
	srand(time(0));
	sf::RenderWindow window(sf::VideoMode(750, 800), "2048");
	sf::Font font;
	if (!font.loadFromFile("ariali.ttf")) {
		std::cout << "Loading error" << std::endl;
		return -1;
	}
	initBoard();
	addRandomTile();
	addRandomTile();
	score = 0;
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {

			if (event.type == sf::Event::Closed) {
				window.close();
			}
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::W) {
					moveUp();
					addRandomTile();
				}
				if (event.key.code == sf::Keyboard::S) {
					moveDown();
					addRandomTile();
				}
				if (event.key.code == sf::Keyboard::A) {
					moveLeft();
					addRandomTile();
				}
				if (event.key.code == sf::Keyboard::D) {
					moveRight();
					addRandomTile();
				}
			}
		}
		window.clear(sf::Color(187, 173, 160));
		for (int i = 0;i < size;i++) {
			for (int q = 0;q < size;q++) {
				int value = board[i][q];
				float x = offset + q * (TILE_SIZE + PADDING);
				float y = offset + i * (TILE_SIZE + PADDING);
				sf::RectangleShape tile(sf::Vector2f(TILE_SIZE, TILE_SIZE));
				tile.setFillColor(getTileColor(value));
				tile.setPosition(x,y);
				window.draw(tile);
				
				if (value != 0) {
					sf::Text text;
					text.setFont(font);
					text.setString(std::to_string(value));
					text.setCharacterSize(value < 100 ? 64 : 48);
					text.setFillColor(getTextColor(value));
					text.setStyle(sf::Text::Bold);
				
					sf::FloatRect textRect = text.getLocalBounds();
					text.setOrigin(
						textRect.left + textRect.width / 2.0f,
						textRect.top + textRect.height / 2.0f
					);
					text.setPosition(
						x + TILE_SIZE / 2.0f,
						y + TILE_SIZE / 2.0f

					);
					window.draw(text);
				}
				
			}
		}
		sf::Text scoreText;
		scoreText.setFont(font);
		scoreText.setString("Score " + std::to_string(score));
		scoreText.setCharacterSize(30);
		scoreText.setFillColor(sf::Color::White);
		scoreText.setPosition(50, 10);
		window.draw(scoreText);
		window.display();
	}
	return 0;
}