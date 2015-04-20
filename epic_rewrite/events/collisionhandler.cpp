
#include "collisionhandler.h"
#include "game.h"
#include <iostream>


int CollisionHandler::onCollision(Entity* e, Entity* f) {
	std::cout << "Entity collision\n";
	return 5;
}

int CollisionHandler::onCollision(Player* p, Monster* m) {
	std::cout << "Player and Monster collided!\n";
	return 5;
}