#include "MapTrigger.h"
#include <vector>
#include "PhysicsManager.h"

Tmpl8::MapTrigger::MapTrigger(char* file, Tmpl8::Sprite* tile, Tmpl8::Sprite* s, Tmpl8::Sprite* finishSprite, Tmpl8::vec2 p, Tmpl8::Player* character, Tmpl8::StaticPhysicsObject* wallL, Tmpl8::StaticPhysicsObject* wallR)
{
	addedVelocity = vec2(0); velocity = vec2(0); drag = vec2(0); gravity = 0;
	dir = file; mapTile = tile; pos = p; sprite = s; finish = finishSprite; Character = character; wallLeft = wallL; wallRight = wallR;
	size = vec2(sprite->GetWidth(), sprite->GetHeight());
}

Tmpl8::MapTrigger::MapTrigger(Tmpl8::Sprite* tile, Tmpl8::Sprite* s, Tmpl8::vec2 p, Tmpl8::Player* character, Tmpl8::StaticPhysicsObject* wallL, Tmpl8::StaticPhysicsObject* wallR)
{
	addedVelocity = vec2(0); velocity = vec2(0); drag = vec2(0); gravity = 0;
	dir = ""; mapTile = tile; pos = p; sprite = s; Character = character; wallLeft = wallL; wallRight = wallR;
	size = vec2(sprite->GetWidth(), sprite->GetHeight());
	finish = nullptr;
}

void Tmpl8::MapTrigger::Update()
{
	vec2 v = -Character->GetVelocity();

	// Check if we are going to collide with a PhysicsObject
	std::vector<PhysicsObject*> objs = PhysicsManager::CheckCollision(this, &v);

	// If we collided with something
	if (objs.size() > 0) {
		// if there is no finish load the menu
		if(finish != nullptr)
			PhysicsManager::LoadMap(dir, mapTile, finish, vec2(360, 0), Character, wallLeft, wallRight);
		else
			PhysicsManager::GetGame()->LoadMenu();
	}
}
