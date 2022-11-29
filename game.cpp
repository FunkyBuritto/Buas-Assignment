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
		PhysicsManager::DebugPhysicsObject(character);

		character->sprite->SetFrame(frame);

		vec2 cpos = vec2(PhysicsManager::GetGame()->screen->GetWidth() / 2, character->pos.y);
		PhysicsManager::SetCamPos(cpos);
		screen->Bar(25, ScreenHeight - 150, 150, ScreenHeight - 100, 0xffffff);
		screen->Box(25, ScreenHeight - 150, 290, ScreenHeight - 100, 0xffffff);
	}

	void Game::KeyUp(int key) {
		switch (key)
		{
		case 44:
			frame = 0;
			character->SetVelocity(vec2(playerInput.x * 15, playerInput.y * 20));
			playerInput = vec2(0);
			break;
		}
	}

	void Game::KeyDown(int key) {
		switch (key)
		{
		case 44:
			frame = 1;
			break;
		case 26:
			playerInput.y -= .2;
			break;
		case 22:
			playerInput.y += .2;
			break;
		case 7:
			playerInput.x += .2;
			break;
		case 4:
			playerInput.x -= .2;
			break;
		}

		// Clamp playerinput between -1 and 1
		playerInput.y = playerInput.y < -1 ? -1 : (playerInput.y > 1 ? 1 : playerInput.y);
		playerInput.x = playerInput.x < -1 ? -1 : (playerInput.x > 1 ? 1 : playerInput.x);
	}
};