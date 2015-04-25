
#include "collisionhandler.h"
#include "game.h"
#include "water.h"

#include <iostream>


void CollisionHandler::onCollision(Entity* e, Entity* f) {
	std::cout << "Entity collision\n";
}

void CollisionHandler::onCollision(Water* w, Entity* e) {
	std::cout << "Something entered water!\n";
	game->kill(e);
	w->contained = e;
}


void CollisionHandler::onCollision(Player* p, Monster* m) {
	std::cout << "Player and Monster collided!\n";
}
