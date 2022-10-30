#pragma once
#include "PhysicsObject.h"

namespace Tmpl8 {
class StaticPhysicsObject : public PhysicsObject
{
public:
	StaticPhysicsObject();
	StaticPhysicsObject(vec2 p, Sprite* s);
	StaticPhysicsObject(vec2 p, vec2 r, Sprite* s);
};
}


