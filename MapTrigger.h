#pragma once
#include "PhysicsObject.h"
#include "StaticPhysicsObject.h"
#include "Player.h"

namespace Tmpl8 {
class MapTrigger : public DynamicPhysicsObject
{
public:
	MapTrigger(char* file, Tmpl8::Sprite* tile, Tmpl8::Sprite* s, Tmpl8::Sprite* finishSprite, Tmpl8::vec2 p, Tmpl8::Player* character, Tmpl8::StaticPhysicsObject* wallL, Tmpl8::StaticPhysicsObject* wallR);
	MapTrigger(Tmpl8::Sprite* tile, Tmpl8::Sprite* s, Tmpl8::vec2 p, Tmpl8::Player* character, Tmpl8::StaticPhysicsObject* wallL, Tmpl8::StaticPhysicsObject* wallR);
	void Update() override;

private:
	char* dir;
	Tmpl8::Player* Character;
	Tmpl8::Sprite* mapTile;
	Tmpl8::Sprite* finish;
	Tmpl8::StaticPhysicsObject* wallLeft;
	Tmpl8::StaticPhysicsObject* wallRight;
};
}

