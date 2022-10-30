#pragma once
#include "template.h"
#include "surface.h"
#include "Rect2D.h"

namespace Tmpl8 {

class PhysicsObject
{

public:
	PhysicsObject() {};

	vec2 pos;
	vec2 size;
	Sprite* sprite;
};

}


