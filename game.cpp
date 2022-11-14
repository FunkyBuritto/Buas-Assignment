#include "game.h"
#include "surface.h"
#include "PhysicsManager.h"
#include "DynamicPhysicsObject.h"
#include "Map.h"
#include <sstream>
#include <cstdio> //printf

namespace Tmpl8
{
	Sprite tile(new Surface("assets/tile.png"), 1);

	Sprite leftWallSprite(new Surface("assets/WallLeft.png"), 1);
	StaticPhysicsObject* wallLeft;

	Sprite rightWallSprite(new Surface("assets/WallRight.png"), 1);
	StaticPhysicsObject* wallRight;

	Sprite characterSprite(new Surface("assets/CharacterBig.png"), 2);
	DynamicPhysicsObject* character = NULL;

	int frame = 0;
	float characterSpeed = .025;
	vec2 playerInput = vec2(0);
	
	void Game::Init()
	{
		PhysicsManager::SetGame(this);
		PhysicsManager::SetPhysicsInterval(10);


		wallLeft = new StaticPhysicsObject(vec2(300, -10000), &leftWallSprite);
		wallRight = new StaticPhysicsObject(vec2(1560, -10000), &rightWallSprite);

		character = new DynamicPhysicsObject(vec2(590, 0), &characterSprite);
		character->SetDrag(.15);
		character->SetGravity(-.3);

		Map map = Map("assets/maps/TestMap.csv", &tile, vec2(360, -11000));
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
		/*
		PhysicsManager::DebugPhysicsObject(character);
		PhysicsManager::DebugPhysicsObject(cube1);
		PhysicsManager::DebugPhysicsObject(cube2);
		PhysicsManager::DebugPhysicsObject(cube3);
		*/

		character->AddVelocity(playerInput * characterSpeed * deltaTime);
		character->sprite->SetFrame(frame);

		PhysicsManager::SetCamPos(vec2(PhysicsManager::GetGame()->screen->GetWidth() / 2, character->pos.y));
	}

	void Game::KeyUp(int key) {
		switch (key)
		{
		case 44:
			frame = 0;
			//character->AddVelocity(vec2(0, -150));
			character->SetVelocity(vec2(0, -20));
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