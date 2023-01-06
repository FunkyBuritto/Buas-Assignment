#include "PhysicsManager.h"
#include "Player.h"
#include <vector>

Tmpl8::Player::Player(vec2 p, Sprite* s)
{
	pos = p; sprite = s; gravity = 0; velocity = vec2(0, 0);
	size = vec2(sprite->GetWidth(), sprite->GetHeight());
	addedVelocity = vec2(0);
	grounded = false;

	//PhysicsManager::AddToDynamicQue(this);
}

void Tmpl8::Player::Update()
{
	bool hbounce = false;
	bool vbounce = false;

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

		// Check if we collide verticly
		if ((pos.y + velocity.y <= obj->pos.y + obj->size.y && pos.x + size.x >= obj->pos.x && pos.x <= obj->pos.x + obj->size.x) ||
			(pos.y + size.y + velocity.y >= obj->pos.y && pos.x + size.x >= obj->pos.x && pos.x <= obj->pos.x + obj->size.x)) {
			// Eliminate micro bounces
			if (abs(velocity.y) < 2.5f) {
				velocity.y = 0;
			} // Check if we can bounce
			else if (velocity.y != 0 && !vbounce) {
				velocity.y = -velocity.y;
				vbounce = true;
			} 
		}

		// Check if we collide horizontally
		if ((pos.x + size.x + velocity.x >= obj->pos.x && pos.y + size.y >= obj->pos.y && pos.y <= obj->pos.y + obj->size.y) ||
			(pos.x + velocity.x <= obj->pos.x + obj->size.x && pos.y + size.y >= obj->pos.y && pos.y <= obj->pos.y + obj->size.y)) {
			// Eliminate micro bounces
			if (abs(velocity.x) < 2.5f) {
				velocity.x = 0;
			} // Check if we can bounce
			else if (velocity.x != 0 && !hbounce) {
				velocity.x = -velocity.x;
				hbounce = true;
			}
		}
	}

	// Flip the sprite based on the velocity
	if (velocity.x < 0)
		flipX = true;
	else if (velocity.x > 0)
		flipX = false;

	// Grounded Check
	if (objs.size() > 0 && abs(velocity.x) < 0.5f)
		grounded = true;
	else
		grounded = false;

	// Apply velocity to position
	pos += velocity;
}
