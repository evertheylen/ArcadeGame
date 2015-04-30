
#include "dispatch/dispatchers.h"

#ifndef _H_Handlers
#define _H_Handlers

class Game;

// simple trick so I don't need to write a thousand constructors
template <typename DispatcherT>
class Manager: public DispatcherT {
public:
	Manager(Game* _g) {
		this->setGame(_g);
	}
};

typedef Manager<CollisionDispatch> CollisionManager;

typedef Manager<IA_EnterDispatch> IA_EnterManager;

typedef Manager<IA_LeaveDispatch> IA_LeaveManager;

typedef Manager<KillDispatch> KillManager;

#endif
