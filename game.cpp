#include "game.h"
#include "surface.h"
#include "PhysicsManager.h"
#include "DynamicPhysicsObject.h"
#include <sstream>
#include <cstdio> //printf

namespace Tmpl8
{
	Sprite tile(new Surface("assets/tile.png"), 1);
	StaticPhysicsObject* cube1;
	StaticPhysicsObject* cube2;
	StaticPhysicsObject* cube3;

	Sprite characterSprite(new Surface("assets/CharacterBig.png"), 2);
	DynamicPhysicsObject* character = NULL;
	int frame = 0;

	float characterSpeed = .025;
	vec2 playerInput = vec2(0);
	
	void Game::Init()
	{
		PhysicsManager::SetGame(this);
		PhysicsManager::SetPhysicsInterval(5);

		cube1 = new StaticPhysicsObject(vec2(500, 800), &tile);
		cube2 = new StaticPhysicsObject(vec2(620, 900), &tile);
		cube3 = new StaticPhysicsObject(vec2(740, 900), &tile);

		character = new DynamicPhysicsObject(vec2(590, 0), &characterSprite);
		character->SetDrag(.075);
		character->SetGravity(-.15);
	}
	
	void Game::Shutdown()
	{
	}


	void Game::Tick(float deltaTime) {
		// clear the graphics window
		screen->Clear(0);
		// Call the physics update method
		PhysicsManager::PhysicsUpdate(deltaTime);
		// Show the fps on screen
		screen->Print((char*)std::to_string((int)(1000 / deltaTime)).c_str(), 0, 0, 0xffffff);

		// Debug Colliders
		PhysicsManager::DebugPhysicsObject(character);
		PhysicsManager::DebugPhysicsObject(cube1);
		PhysicsManager::DebugPhysicsObject(cube2);
		PhysicsManager::DebugPhysicsObject(cube3);


		character->AddVelocity(playerInput * characterSpeed * deltaTime);
		character->sprite->SetFrame(frame);
	}

	void Game::KeyUp(int key) {
		switch (key)
		{
		case 44:
			frame = 0;
			character->AddVelocity(vec2(0, -15));
			break;
		case 7:
			playerInput.x = 0;
			break;
		case 4:
			playerInput.x = 0;
			break;
		}
	}

	void Game::KeyDown(int key) {
		switch (key)
		{
		case 44:
			frame = 1;
			break;
		case 7:
			playerInput.x = 1;
			break;
		case 4:
			playerInput.x = -1;
			break;
		}
	}
};