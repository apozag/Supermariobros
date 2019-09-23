#include "Scene.h"

bool Scene::loadLevel(int level) {

	for (std::vector<Set*>* v : quadrants) {
		for (Set* s : *v) {
			delete s;
		}
		v->clear();
	}
	quadrants.clear();

	set.clear();

	positions.clear();


	std::ifstream myReadFile;

	switch (level) {
	case 1:
		myReadFile.open("levels/level1.txt");
		break;
	case 2:
		myReadFile.open("levels/level2.txt");
	}

	char c;

	double xpos = 0;
	double ypos = 0;
	int i = 0;
	int j = 0;
	int GRID_SIZE = 11;
	int QUADRANT_SIZE = 4;
	double blockwidth = this->width / GRID_SIZE;
	double blockheight = this->height / GRID_SIZE;



	if (myReadFile.is_open()) {

		std::vector<Set*>* s = new std::vector<Set*>();
		int column = 0;
		Set* block = new Set();
		bool first = true;

		while (myReadFile.get(c)) {
			
			switch (c) {
			case '1':
				block = new Set(new Vector2D(xpos, ypos), blockwidth, blockheight, renderer, "assets/floor.png", 1.0);
				block->setType(FLOOR);
				s->push_back(block);
				set.push_back(block);
				if (first) {
					positions.push_back(&block->getPos()->getX());
					first = false;
				}
				break;
			case '2':
				block = new Set(new Vector2D(xpos, ypos), blockwidth, blockheight, renderer, "assets/brick.png", 1.0);
				block->setType(BRICK);
				s->push_back(block);
				set.push_back(block);
				if (first) {
					positions.push_back(&block->getPos()->getX());
					first = false;
				}
				break;

			case '3':
				block = new Set(new Vector2D(xpos, ypos), blockwidth, blockheight, renderer, "assets/question.png", 1.0);
				block->setType(QUESTION);
				s->push_back(block);
				set.push_back(block);
				if (first) {
					positions.push_back(&block->getPos()->getX());
					first = false;
				}
				break;
			case '4':
				game->addGoomba(new Goomba(new Vector2D(xpos, ypos), renderer));
				break;
				
			}
			

			xpos = j * blockwidth;
			ypos = i * blockheight;

			if (++i >= GRID_SIZE) {
				i = 0;
				j++;
				column++;
			}

			if (column >= QUADRANT_SIZE) {
				quadrants.push_back(s);
				positions.push_back(&block->getPos()->getX());
				s = new std::vector<Set*>();
				//s->push_back(block);
				column = 0;
			}

			if (myReadFile.peek() == EOF && column >= QUADRANT_SIZE) {
				positions.push_back(&block->getPos()->getX());
				quadrants.push_back(s);
			}
			
		}
		

	}
	else
		return false;
	myReadFile.close();
	return true;
}

std::vector<Set*>* Scene::checkQuadrant(Vector2D pos) {
	for (int i = 0; i < quadrants.size(); i++) {
		if (*positions.at(i) <= pos.getX() && *positions.at(i + 1) + width / 11 >= pos.getX()) {
			return quadrants.at(i);
		}
	}
	return nullptr;

}