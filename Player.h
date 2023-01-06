#pragma once
#include "DynamicPhysicsObject.h"

namespace Tmpl8 {
class Player : public DynamicPhysicsObject
{
public:
	Player(vec2 p, Sprite* s);
	void Update() override;

	bool grounded;
}; 
}

