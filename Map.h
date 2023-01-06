#pragma once
#include <vector>
#include "StaticPhysicsObject.h"
#include "Player.h"
#include "MapTrigger.h"

class Map
{
public:
	Map() {};
	Map(char* file, Tmpl8::Sprite* tileSprite, Tmpl8::Sprite* finishSprite, Tmpl8::vec2 offset, Tmpl8::Player* character, Tmpl8::StaticPhysicsObject* wallL, Tmpl8::StaticPhysicsObject* wallR);
	std::vector<Tmpl8::StaticPhysicsObject*> tiles;
	Tmpl8::MapTrigger* finish;
};

