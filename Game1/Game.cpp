#include "Game.h"

void initObjects(Game *game);

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {

	int flag = 0;
	if (fullscreen)
		flag = SDL_WINDOW_FULLSCREEN;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0){

		std::cout << "SDL initialized correctly!" << std::endl;

		//Create a window or print a message if an error ocurrs
		window = SDL_CreateWindow(title, xpos, ypos, width, height, flag);
		if (window) {
			std::cout << "Window created!" << std::endl;
			this->width = width;
			this->height = height;
		}
		//Create a renderer or print a message if an error ocurrs
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) {
			std::cout << "Renderer created!" << std::endl;
			SDL_SetRenderDrawColor(renderer, 95, 141, 216, 255);
		}
		isRunning = true;

		//pointer to keystates
		keystates = SDL_GetKeyboardState(NULL);

		//game objects are instanciated
		initObjects(this);
	}
	else {
		isRunning = false;
		std::cout << "error while initializing" << std::endl;
	}
}

void Game::setGravity(Vector2D g) { gravity = g; }

void Game::loadLevel(int level) {
	/*

	std::ifstream myReadFile;

	switch (level) {
	case 1:
		myReadFile.open("level1.txt");
		break;
	}

	char c;

	double xpos = 0;
	double ypos = 0;
	int i = 0;
	int j = 0;
	int GRID_SIZE = 11;
	double blockwidth = this->height/ GRID_SIZE;
	double blockheight = this->height/ GRID_SIZE;

	

	if (myReadFile.is_open()) {

		std::vector<Set*>* s = new std::vector<Set*>();
		int count = 0;

		while (myReadFile.get(c)) {
			
			switch (c) {
			case '1':
				s->push_back(new Set(new Vector2D(xpos, ypos), blockwidth, blockheight, renderer, "brick.png"));
				break;
			case '2':
				s->push_back(new Set(new Vector2D(xpos, ypos), blockwidth, blockheight, renderer, "floor.png"));
				break;
			}

			xpos = j * blockwidth;
			ypos = i * blockheight;
			std::cout << i << ", " << j << std::endl << xpos << " " << ypos << std::endl;

			if (++i >= GRID_SIZE) {
				i = 0;
				j++;
			}


			if (count++ >= 11) {
				count = 0;
				set.push_back(s);
				s = new std::vector<Set*>();
			}
		}
		if (count < 11) {
			set.push_back(s);
		}
	}
	myReadFile.close();
	*/
	player->setPos(new Vector2D(100, 200));
	scene->loadLevel(level);
}

void Game::update(const double &dt) {
	for (Mushroom* m : mushrooms) {
		m->setQuadrant(scene->checkQuadrant(m->getPos()));
		m->applyForce(gravity, dt);
		m->update(dt);
	}

	for (Goomba* g : goombas) {
		g->setQuadrant(scene->checkQuadrant(g->getPos()));
		g->applyForce(gravity, dt);
		g->update(dt);
	}

	player->setQuadrant(scene->checkQuadrant(player->getPos()));
	player->applyForce(gravity, dt);
	player->update(dt);

	checkCoinsCollision();
	checkMushroomCollision();
	checkGoombaCollision();
	checkGoombaKill();

	camera->update(dt);
}

void Game::render() {
	SDL_RenderClear(renderer);
	
	camera->render(player, background, scene->getSet(), coins, mushrooms, goombas);

	SDL_RenderPresent(renderer);
}

void Game::handleEvents(const double &dt) {
	
	SDL_PollEvent(&event);

	switch (event.type) {
	case SDL_KEYUP:
		if (event.key.keysym.sym == SDLK_a) {
			key = 1;
		}
		else if (event.key.keysym.sym == SDLK_d) {
			key = 2;
		}
		break;

	case SDL_KEYDOWN:
		if (event.key.keysym.sym == SDLK_a) {
			key = 3;
		}
		else if (event.key.keysym.sym == SDLK_d) {
			key = 4;
		}
		else if (event.key.keysym.sym == SDLK_w) {
			key = 5;
		}
		break; 
		
	case SDL_QUIT:
		isRunning = false;
		break;
	default:
		key = 0;
	}

	switch (key) {
	case 1:
		if (player->isGrounded()) {
			player->setVelX(std::min(player->getVelX() + 0.1, 0.0));
		}
		else {
			player->setVelX(std::min(player->getVelX() + 0.01, 0.0));
		}
		break;
	case 2:
		if (player->isGrounded()) {
			player->setVelX(std::max(player->getVelX() - 0.1, 0.0));
		}
		else {
			player->setVelX(std::max(player->getVelX() - 0.01, 0.0));
		}
		break;
	case 3:
		if (player->isGrounded()) {
			player->setVelX(std::max(player->getVelX() - 1, -player->getMAX_VELOCITY()));
		}
		else {
			player->setVelX(std::max(player->getVelX() - 0.5, -player->getMAX_VELOCITY()));
		}
		player->faceLeft();
		break;
	case 4:
		if (player->isGrounded()) {
			player->setVelX(std::min(player->getVelX() + 1, player->getMAX_VELOCITY()));
		}
		else {
			player->setVelX(std::min(player->getVelX() + 0.5, player->getMAX_VELOCITY()));
		}
		player->faceRight();
		break;
	case 5:
		if (player->isGrounded()) {
			player->setVelY(-6.0f);
		}
		break;

	}
	
}

void Game::clear() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "game cleared!" << std::endl;
}

void Game::checkCoinsCollision() {
	for (int i = 0; i < coins.size(); i++) {
		if (player->collide(coins[i])) {
			coins[i]->pickup();
			Coin* c = coins[i];
			coins.erase(coins.begin() + i);
			delete c;
		}
	}
}

void Game::checkMushroomCollision() {
	for (int i = 0; i < mushrooms.size(); i++) {
		if (player->collide(mushrooms[i])) {
			mushrooms[i]->pickup();
			Mushroom* m = mushrooms[i];
			mushrooms.erase(mushrooms.begin() + i);
			delete m;
			if (player->getState() == SMALL) {
				player->setState(LARGE);
				player->setY(player->getY() - 50);
			}
			else {
				loadLevel(2);//sumar puntos (????)
			}
		}
	}
}

void Game::checkGoombaCollision() {
	for (int i = 0; i < goombas.size(); i++) {
		if (player->getVelY() > 0 && player->collideY(goombas[i], player->getVelY())) {
			Goomba* g = goombas[i];
			goombas.erase(goombas.begin() + i);
			g->kill();
			player->setVelY(-6.0f);
		}
		
		else if(player->collide(goombas[i]) || goombas[i]->collideX(player, 0)) {

			if (player->getState() == LARGE) {
				player->setState(SMALL);
				Goomba* g = goombas[i];
				goombas.erase(goombas.begin() + i);
				g->kill();
			}
			else 
				isRunning = false;
		}
	}
}

void Game::checkGoombaKill() {

}


//Funciones Auxiliares
void initObjects(Game *game) {
	game->coins.push_back(new Coin(new Vector2D(700, 300), game->renderer));
	game->coins.push_back(new Coin(new Vector2D(500, 300), game->renderer));
	game->coins.push_back(new Coin(new Vector2D(600, 300), game->renderer));
	game->player = new Player(new Vector2D(100, 200), 50, 50, game->renderer, "spriteSheet2.png", game);
	game->player->addAnimation(4, 80, 16, 16, WALK_RIGHT);
	game->player->addAnimation(4, 80, 16, 16, WALK_LEFT);
	game->player->addAnimation(1, 100, 16, 16, IDLE_RIGHT);
	game->player->addAnimation(1, 100, 16, 16, IDLE_LEFT);
	game->player->addAnimation(1, 100, 16, 16, JUMP_LEFT);
	game->player->addAnimation(1, 100, 16, 16, JUMP_RIGHT);
	for (int i = 0; i < 10; i++) {
		double size = rand() % 10 + 1;
		game->background.push_back(new Set(new Vector2D(200*i + rand() % 500, -100 + rand() % 500), 20 * size, 10 * size, game->renderer, "cloud.png", size / 15));
	}
	std::sort(game->background.begin(), game->background.end(), []( Set* lhs, Set* rhs)
	{
		return lhs->getDepth() < rhs->getDepth();
	});
	game->camera = new Camera(game->player);
	game->scene = new Scene(game->renderer, game);
}