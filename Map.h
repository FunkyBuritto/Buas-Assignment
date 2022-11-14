#pragma once
#include <vector>
#include "StaticPhysicsObject.h"

class Map
{
public:
	Map(char* file, Tmpl8::Sprite* tileSprite, Tmpl8::vec2 offset);
	std::vector<Tmpl8::StaticPhysicsObject*> tiles;
};

