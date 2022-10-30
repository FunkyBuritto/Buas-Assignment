#include "StaticPhysicsObject.h"
#include "PhysicsManager.h"

Tmpl8::StaticPhysicsObject::StaticPhysicsObject()
{
	PhysicsManager::AddToStaticQue(this);
}

Tmpl8::StaticPhysicsObject::StaticPhysicsObject(vec2 p, Sprite* s)
{
	pos = p; size = vec2(s->GetWidth(), s->GetHeight()); sprite = s;
	PhysicsManager::AddToStaticQue(this);
}

Tmpl8::StaticPhysicsObject::StaticPhysicsObject(vec2 p, vec2 r, Sprite* s)
{
	pos = p; size = r; sprite = s;
	PhysicsManager::AddToStaticQue(this);
}
