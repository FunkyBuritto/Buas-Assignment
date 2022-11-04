#pragma once
#include <vector>
#include "DynamicPhysicsObject.h"
#include "StaticPhysicsObject.h"
#include "PhysicsObject.h"
#include "game.h"

class PhysicsManager
{
public:
	static void AddToDynamicQue(Tmpl8::DynamicPhysicsObject* obj);
	static void AddToStaticQue(Tmpl8::StaticPhysicsObject* obj);
	static std::vector <Tmpl8::PhysicsObject*> CheckCollision(Tmpl8::DynamicPhysicsObject* obj, Tmpl8::vec2* velocity);
	static void PhysicsUpdate(float deltaTime);
	static void SetPhysicsInterval(float i);
	static void SetGame(Tmpl8::Game* Game);
	static void DebugPhysicsObject(Tmpl8::PhysicsObject* obj);
	static Tmpl8::Game* GetGame() { return game; };
	static void SetCamPos(Tmpl8::vec2 pos) { camPos = pos - Tmpl8::vec2(ScreenWidth / 2, ScreenHeight / 2); };
	static Tmpl8::vec2 GetCamPos() { return camPos; };

private:
	static Tmpl8::Game* game;
	static Tmpl8::vec2 camPos;
	static float addedDelta;
	static float interval;
	static std::vector <Tmpl8::DynamicPhysicsObject*> dynamicObjects;
	static std::vector <Tmpl8::StaticPhysicsObject*> staticObjects;
};


