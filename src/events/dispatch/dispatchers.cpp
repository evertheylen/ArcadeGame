#include "./events/dispatch/dispatchers.h"

// This file is autogenerated, based on dispatchers.toml
// Do not edit!


// Lesson learned: do not #define _Container!
#include <iostream>

#include <dispatch_base.h>
#include <water.h>
#include <entity.h>
#include <button.h>
#include <goal.h>
#include <boobytrap.h>

#include <../collisionhandler.h>
#include <../ia_enterhandler.h>
#include <../ia_leavehandler.h>
#include <../killhandler.h>

// no specific cpp header.


// IA_LeaveDispatch

#include <limits>

int IA_LeaveDispatch::getRule(Entity* __Entity0, Entity* __Entity1) {
    // Rule 0
    Entity* __r0_Entity0 = dynamic_cast<Entity*>(__Entity0);
    Button* __r0_Button1 = dynamic_cast<Button*>(__Entity1);
    if (__r0_Entity0 != nullptr && __r0_Button1 != nullptr) {
        return 0;
    }


    return std::numeric_limits<int>::max();
}
    
void IA_LeaveDispatch::doRule(int rulenum, Entity* __Entity0, Entity* __Entity1) {
    switch(rulenum) {

        case 0:
            return onLeave(dynamic_cast<Entity*>(__Entity0), dynamic_cast<Button*>(__Entity1));

        default:
            return onLeave(dynamic_cast<Entity*>(__Entity0), dynamic_cast<Entity*>(__Entity1));
    }
}




// KillDispatch

#include <limits>

int KillDispatch::getRule(Entity* __Entity0) {
    // Rule 0
    Player* __r0_Player0 = dynamic_cast<Player*>(__Entity0);
    if (__r0_Player0 != nullptr) {
        return 0;
    }

    // Rule 1
    Alive* __r1_Alive0 = dynamic_cast<Alive*>(__Entity0);
    if (__r1_Alive0 != nullptr) {
        return 1;
    }


    return std::numeric_limits<int>::max();
}
    
void KillDispatch::doRule(int rulenum, Entity* __Entity0) {
    switch(rulenum) {

        case 0:
            return onKill(dynamic_cast<Player*>(__Entity0));

        case 1:
            return onKill(dynamic_cast<Alive*>(__Entity0));

        default:
            return onKill(dynamic_cast<Entity*>(__Entity0));
    }
}




// CollisionDispatch

#include <limits>

int CollisionDispatch::getRule(Entity* __Entity0, Entity* __Entity1) {
    // Rule 0
    Player* __r0_Player0 = dynamic_cast<Player*>(__Entity0);
    Monster* __r0_Monster1 = dynamic_cast<Monster*>(__Entity1);
    if (__r0_Player0 != nullptr && __r0_Monster1 != nullptr) {
        return 0;
    }

    // Rule 1
    Water* __r1_Water0 = dynamic_cast<Water*>(__Entity0);
    Entity* __r1_Entity1 = dynamic_cast<Entity*>(__Entity1);
    if (__r1_Water0 != nullptr && __r1_Entity1 != nullptr) {
        return 1;
    }


    return std::numeric_limits<int>::max();
}
    
void CollisionDispatch::doRule(int rulenum, Entity* __Entity0, Entity* __Entity1) {
    switch(rulenum) {

        case 0:
            return onCollision(dynamic_cast<Player*>(__Entity0), dynamic_cast<Monster*>(__Entity1));

        case 1:
            return onCollision(dynamic_cast<Water*>(__Entity0), dynamic_cast<Entity*>(__Entity1));

        default:
            return onCollision(dynamic_cast<Entity*>(__Entity0), dynamic_cast<Entity*>(__Entity1));
    }
}




// IA_EnterDispatch

#include <limits>

int IA_EnterDispatch::getRule(Entity* __Entity0, Entity* __Entity1) {
    // Rule 0
    Player* __r0_Player0 = dynamic_cast<Player*>(__Entity0);
    Goal* __r0_Goal1 = dynamic_cast<Goal*>(__Entity1);
    if (__r0_Player0 != nullptr && __r0_Goal1 != nullptr) {
        return 0;
    }

    // Rule 1
    Actor* __r1_Actor0 = dynamic_cast<Actor*>(__Entity0);
    Boobytrap* __r1_Boobytrap1 = dynamic_cast<Boobytrap*>(__Entity1);
    if (__r1_Actor0 != nullptr && __r1_Boobytrap1 != nullptr) {
        return 1;
    }

    // Rule 2
    Entity* __r2_Entity0 = dynamic_cast<Entity*>(__Entity0);
    Button* __r2_Button1 = dynamic_cast<Button*>(__Entity1);
    if (__r2_Entity0 != nullptr && __r2_Button1 != nullptr) {
        return 2;
    }


    return std::numeric_limits<int>::max();
}
    
void IA_EnterDispatch::doRule(int rulenum, Entity* __Entity0, Entity* __Entity1) {
    switch(rulenum) {

        case 0:
            return onEnter(dynamic_cast<Player*>(__Entity0), dynamic_cast<Goal*>(__Entity1));

        case 1:
            return onEnter(dynamic_cast<Actor*>(__Entity0), dynamic_cast<Boobytrap*>(__Entity1));

        case 2:
            return onEnter(dynamic_cast<Entity*>(__Entity0), dynamic_cast<Button*>(__Entity1));

        default:
            return onEnter(dynamic_cast<Entity*>(__Entity0), dynamic_cast<Entity*>(__Entity1));
    }
}



