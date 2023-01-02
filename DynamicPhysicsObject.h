#pragma once
#include "PhysicsObject.h"

namespace Tmpl8 {
class DynamicPhysicsObject : public PhysicsObject
{
public:
	DynamicPhysicsObject();
	DynamicPhysicsObject(vec2 p, Sprite* s);
	DynamicPhysicsObject(vec2 p, Sprite* s, float g);
	DynamicPhysicsObject(vec2 p, vec2 r, Sprite* s);
	DynamicPhysicsObject(vec2 p, vec2 r, Sprite* s, float g);

	virtual void Update();

	void SetGravity(float g) { gravity = g; };
	void SetVelocity(vec2 v) { velocity = v; };
	void AddVelocity(vec2 v) { addedVelocity += v; };
	void SetDrag(float d)	 { drag = d < 0 ? 0: vec2(d); };
	void SetDrag(vec2 d)	 { drag = d.length() < 0 ? vec2(0) : d;	};

	bool flipX = false;

protected:
	vec2 addedVelocity;
	vec2 velocity;
	vec2 drag;

	float gravity;
};
}
