#include "game.h"
#include "surface.h"
#include "PhysicsManager.h"
#include "DynamicPhysicsObject.h"
#include "Player.h"
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
	Player* character = NULL;

	int frame = 0;
	float characterSpeed = .025;
	vec2 playerInput = vec2(0);
	
	void Game::Init()
	{
		PhysicsManager::SetGame(this);
		PhysicsManager::SetPhysicsInterval(16);

		wallLeft = new StaticPhysicsObject(vec2(300, -10000), &leftWallSprite);
		wallRight = new StaticPhysicsObject(vec2(1560, -10000), &rightWallSprite);

		character = new Player(vec2(ScreenWidth / 2, 760), &characterSprite);
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
		//PhysicsManager::DebugPhysicsObject(character);

		character->sprite->SetFrame(frame);

		vec2 cpos = vec2(PhysicsManager::GetGame()->screen->GetWidth() / 2, character->pos.y);
		PhysicsManager::SetCamPos(cpos);

		// Temporary Input UI
		//Right input
		screen->Bar(175, ScreenHeight - 125, 175 + 115 * playerInput.x, ScreenHeight - 100, 0xffffff);
		screen->Box(175, ScreenHeight - 125, 290, ScreenHeight - 100, 0xffffff);

		//Left input
		screen->Bar(150 + 125 * playerInput.x, ScreenHeight - 125, 150, ScreenHeight - 100, 0xffffff);
		screen->Box(25, ScreenHeight - 125, 150, ScreenHeight - 100, 0xffffff);

		//Vertical Input
		screen->Bar(150, ScreenHeight - 150 + 125 * (playerInput.y + .2), 175, ScreenHeight - 150, 0xffffff);
		screen->Box(150, ScreenHeight - 250, 175, ScreenHeight - 150, 0xffffff);
	}

	void Game::KeyUp(int key) {
		switch (key)
		{
		case 44:
			frame = 0;
			// Apply velocity to player if grounded and reset player input
			if (character->grounded) {
				character->SetVelocity(vec2(playerInput.x * 13, playerInput.y * 20));
				playerInput = vec2(0, -.2);
			}
			break;
		}
	}

	void Game::KeyDown(int key) {
		switch (key)
		{
		case 44:
			if (character->grounded) frame = 1;
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

		// Clamp playerinput
		playerInput.y = playerInput.y < -1 ? -1 : (playerInput.y > -.2 ? -.2 : playerInput.y);
		playerInput.x = playerInput.x < -1 ? -1 : (playerInput.x > 1 ? 1 : playerInput.x);
	}
};