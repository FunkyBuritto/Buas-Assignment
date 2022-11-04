#pragma once
#include <vector>
#include "StaticPhysicsObject.h"

class Map
{
public:
	Map(char* file, Tmpl8::Sprite* tileSprite);
	std::vector<Tmpl8::StaticPhysicsObject*> tiles;
};

