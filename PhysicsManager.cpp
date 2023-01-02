#include "PhysicsManager.h"
#include "game.h"
#include <sstream>

// Initialize variables
Tmpl8::Game* PhysicsManager::game;
Tmpl8::vec2 PhysicsManager::camPos;
float PhysicsManager::addedDelta;
float PhysicsManager::interval;

// Initializes physics objects lists
std::vector<Tmpl8::DynamicPhysicsObject*> PhysicsManager::dynamicObjects;
std::vector<Tmpl8::StaticPhysicsObject*> PhysicsManager::staticObjects;

void PhysicsManager::AddToDynamicQue(Tmpl8::DynamicPhysicsObject* obj)
{
	dynamicObjects.push_back(obj);
}

void PhysicsManager::AddToStaticQue(Tmpl8::StaticPhysicsObject* obj)
{
	staticObjects.push_back(obj);
}

std::vector <Tmpl8::PhysicsObject*> PhysicsManager::CheckCollision(Tmpl8::DynamicPhysicsObject* obj, Tmpl8::vec2* velocity)
{
	std::vector <Tmpl8::PhysicsObject*> objs;

	Tmpl8::vec2 tl = obj->pos + *velocity;
	Tmpl8::vec2 br = obj->pos + *velocity + obj->size;

	Tmpl8::vec2 tr = obj->pos + Tmpl8::vec2(obj->size.x, 0) + *velocity;
	Tmpl8::vec2 bl = obj->pos + Tmpl8::vec2(0, obj->size.y) + *velocity;

	// Collision Check for DynamicObjects
	for (uint32_t i = 0; i < dynamicObjects.size(); i++) {
		// Avoid collision check with self
		if (dynamicObjects[i] == obj)
			continue;

		// Other top left and top right
		Tmpl8::vec2 otl = dynamicObjects[i]->pos;
		Tmpl8::vec2 obr = dynamicObjects[i]->pos + dynamicObjects[i]->size;

		// Other top right and bottom right
		Tmpl8::vec2 otr = dynamicObjects[i]->pos + Tmpl8::vec2(dynamicObjects[i]->size.x, 0);
		Tmpl8::vec2 obl = dynamicObjects[i]->pos + Tmpl8::vec2(0, dynamicObjects[i]->size.y);

		// Check Topleft
		if (tl > otl && tl < obr) objs.push_back(dynamicObjects[i]);

		// Check BottomRight
		else if (br < obr && br > otl)
			objs.push_back(dynamicObjects[i]);

		// Check TopRight
		else if((tr.x < otr.x && tr.y > otr.y) && (tr.x > obl.x && tr.y < obl.y))
			objs.push_back(dynamicObjects[i]);

		// Check BottomLeft
		else if ((bl.x > obl.x && bl.y < obl.y) && (bl.x < otr.x && bl.y > otr.y))
			objs.push_back(dynamicObjects[i]);
	}

	// Collision Check for staticObjects
	for (uint32_t i = 0; i < staticObjects.size(); i++) {
		// Other top left and top right
		Tmpl8::vec2 otl = staticObjects[i]->pos;
		Tmpl8::vec2 obr = staticObjects[i]->pos + staticObjects[i]->size;

		// Other top right and bottom right
		Tmpl8::vec2 otr = staticObjects[i]->pos + Tmpl8::vec2(staticObjects[i]->size.x, 0);
		Tmpl8::vec2 obl = staticObjects[i]->pos + Tmpl8::vec2(0, staticObjects[i]->size.y);

		// Check Topleft
		if (tl > otl && tl < obr)
			objs.push_back(staticObjects[i]);

		// Check BottomRight
		else if (br < obr && br > otl)
			objs.push_back(staticObjects[i]);

		// Check TopRight
		else if ((tr.x < otr.x && tr.y > otr.y) && (tr.x > obl.x && tr.y < obl.y))
			objs.push_back(staticObjects[i]);

		// Check BottomLeft
		else if ((bl.x > obl.x && bl.y < obl.y) && (bl.x < otr.x && bl.y > otr.y))
			objs.push_back(staticObjects[i]);
	}

	return objs;
}

void PhysicsManager::PhysicsUpdate(float deltaTime)
{
	// Draw all DynamicPhysicsObject
	for (uint32_t i = 0; i < dynamicObjects.size(); i++) {
		dynamicObjects[i]->sprite->Draw(game->screen, dynamicObjects[i]->pos.x - camPos.x, dynamicObjects[i]->pos.y - camPos.y, dynamicObjects[i]->flipX);
	}

	// Draw all StaticPhysicsObject
	for (uint32_t i = 0; i < staticObjects.size(); i++) {
		staticObjects[i]->sprite->Draw(game->screen, staticObjects[i]->pos.x - camPos.x, staticObjects[i]->pos.y - camPos.y);
	}

	// If we haven't reached our wanted time interval, return
	if (deltaTime + addedDelta < interval) {
		addedDelta += deltaTime;
		return;
	} 

	// Do a physics update on all DynamicPhysicsObject	
	for (uint32_t i = 0; i < dynamicObjects.size(); i++) {
		dynamicObjects[i]->Update();
	}

	addedDelta = 0;
}

void PhysicsManager::SetPhysicsInterval(float i)
{
	interval = i;
}

void PhysicsManager::SetGame(Tmpl8::Game* Game)
{
	game = Game;
}

void PhysicsManager::DebugPhysicsObject(Tmpl8::PhysicsObject* obj)
{
	game->screen->Box(obj->pos.x - camPos.x, obj->pos.y - camPos.y, obj->pos.x + obj->size.x - camPos.x, obj->pos.y + obj->size.y - camPos.y, 0x00ff00);
}
