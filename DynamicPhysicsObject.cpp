#include "DynamicPhysicsObject.h"
#include "PhysicsManager.h"
#include "game.h"
#include "surface.h"
#include "template.h"
#include <vector>
#include <sstream>

Tmpl8::DynamicPhysicsObject::DynamicPhysicsObject()
{
	addedVelocity = vec2(0);
	PhysicsManager::AddToDynamicQue(this);
}

Tmpl8::DynamicPhysicsObject::DynamicPhysicsObject(vec2 p, Sprite* s)
{
	pos = p; sprite = s; gravity = 0; velocity = vec2(0, 0);
	size = vec2(sprite->GetWidth(), sprite->GetHeight());
	addedVelocity = vec2(0);

	PhysicsManager::AddToDynamicQue(this);
}

Tmpl8::DynamicPhysicsObject::DynamicPhysicsObject(vec2 p, Sprite* s, float g)
{
	pos = p; sprite = s; gravity = g / 100; velocity = vec2(0, 0);
	size = vec2(sprite->GetWidth(), sprite->GetHeight());
	addedVelocity = vec2(0);

	PhysicsManager::AddToDynamicQue(this);
}

Tmpl8::DynamicPhysicsObject::DynamicPhysicsObject(vec2 p, vec2 r, Sprite* s)
{
	pos = p; size = r; sprite = s; gravity = 0; velocity = vec2(0, 0);
	addedVelocity = vec2(0);
	PhysicsManager::AddToDynamicQue(this);
}

Tmpl8::DynamicPhysicsObject::DynamicPhysicsObject(vec2 p, vec2 r, Sprite* s, float g)
{
	pos = p; size = r; sprite = s; gravity = g / 100; velocity = vec2(0, 0);
	addedVelocity = vec2(0);
	PhysicsManager::AddToDynamicQue(this);
}

void Tmpl8::DynamicPhysicsObject::Update()
{
	// Apply gravity to velocity
	velocity.y -= gravity;

	// Add the add velocity velocities
	velocity += addedVelocity;
	addedVelocity = 0;

	// Apply drag if needed
	if (abs(velocity.x) > drag.x)
		velocity.x += (velocity.x < 0 ? drag.x : -drag.x);
	else
		velocity.x = 0;
		
	if (abs(velocity.y) > drag.y)
		velocity.y += (velocity.y < 0 ? drag.y : -drag.y);
	else
		velocity.y = 0;
		
	// Check if we are going to collide with a PhysicsObject
	std::vector<PhysicsObject*> objs = PhysicsManager::CheckCollision(this, &velocity);

	// If we are going to collide with a PhysicsObject, make sure we can still move in other directions
	for (size_t i = 0; i < objs.size(); i++)
	{
		PhysicsObject* obj = objs[i];
		
		// Frictionless collision
		// Check if we can't move down and dont allow the velocity to be higher than 0 if true
		if (pos.y + size.y + velocity.y >= obj->pos.y &&
			pos.x + size.x >= obj->pos.x && pos.x <= obj->pos.x + obj->size.x) {
			velocity.y = velocity.y >= 0 ? 0 : velocity.y;
		}
		// Check if we can't move up and dont allow the velocity to be lower than 0 if true
		if (pos.y + velocity.y <= obj->pos.y + obj->size.y &&
			pos.x + size.x >= obj->pos.x && pos.x <= obj->pos.x + obj->size.x) {
			velocity.y = velocity.y <= 0 ? 0 : velocity.y;
		}
		
		// Check if we can't move Right and dont allow the velocity to be higher than 0 if true
		if (pos.x + size.x + velocity.x >= obj->pos.x && 
			pos.y + size.y >= obj->pos.y && pos.y <= obj->pos.y + obj->size.y) {
			velocity.x = velocity.x >= 0 ? 0 : velocity.x;
		}
		// Check if we can't move left and dont allow the velocity to be lower than 0 if true
		if (pos.x + velocity.x <= obj->pos.x + obj->size.x && 
			pos.y + size.y >= obj->pos.y && pos.y <= obj->pos.y + obj->size.y) {
			velocity.x = velocity.x <= 0 ? 0 : velocity.x;
		}

	}

	// Apply velocity to position
	pos += velocity;
}
