
#ifndef _H_Handler
#define _H_Handler

class Game;

class Handler {
public:
	Handler(Game* _g);
	Handler();
	void setGame(Game* _g);

protected:
	Game* game;
};

#endif
