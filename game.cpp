#include "game.h"
#include "surface.h"
#include "PhysicsManager.h"
#include "DynamicPhysicsObject.h"
#include "MapTrigger.h"
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

	Sprite map1(new Surface("assets/Map1.png"), 1);
	Sprite map2(new Surface("assets/Map2.png"), 1);
	Sprite map3(new Surface("assets/Map3.png"), 1);
	Sprite map4(new Surface("assets/Map4.png"), 1);
	Sprite finish(new Surface("assets/Finish.png"), 1);

	MapTrigger* mapTrigger1;
	MapTrigger* mapTrigger2;
	MapTrigger* mapTrigger3;
	MapTrigger* mapTrigger4;

	int frame = 0;
	float characterSpeed = .025;
	vec2 playerInput = vec2(0);
	vec2 cpos;
	
	void Game::Init()
	{
		//finish = Sprite( new Surface("assets/Map2.png"), 1);

		// Initialize the PhysicsManager
		PhysicsManager::SetGame(this);
		PhysicsManager::SetPhysicsInterval(8);

		// Initialize walls
		wallLeft = new StaticPhysicsObject(vec2(300, -1200), &leftWallSprite);
		wallRight = new StaticPhysicsObject(vec2(1560, -1200), &rightWallSprite);

		// Initialize the player character
		character = new Player(vec2(ScreenWidth / 2, 760), &characterSprite);
		character->SetDrag(.15);
		character->SetGravity(-.3);

		LoadMenu();

		// Set the camera position
		cpos = vec2(PhysicsManager::GetGame()->screen->GetWidth() / 2, character->pos.y);
	}
	
	void Game::Shutdown()
	{
	}

	void Game::Tick(float deltaTime) {
		// Clear the graphics window
		screen->Clear(0);
		// Call the physics update method
		PhysicsManager::PhysicsUpdate(deltaTime);
		
		// Show the fps on screen
		//screen->Print((char*)std::to_string((int)(1000 / deltaTime)).c_str(), 0, 0, 0xffffff);
		// Debug Colliders 
		//PhysicsManager::DebugPhysicsObject(character);

		character->sprite->SetFrame(frame);

		// Vertical camera movement
		cpos.y = character->pos.y - 100;
		PhysicsManager::SetCamPos(cpos);

		// UI
		// Right input
		screen->Bar(175, ScreenHeight - 125, 175 + 115 * playerInput.x, ScreenHeight - 100, 0xffffff);
		screen->Box(175, ScreenHeight - 125, 290, ScreenHeight - 100, 0xffffff);

		// Left input
		screen->Bar(150 + 125 * playerInput.x, ScreenHeight - 125, 150, ScreenHeight - 100, 0xffffff);
		screen->Box(25, ScreenHeight - 125, 150, ScreenHeight - 100, 0xffffff);

		// Vertical Input
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
		printf(std::to_string(key).c_str());
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

		case 21:
			LoadMenu();
			break;
		}

		// Clamp playerinput
		playerInput.y = playerInput.y < -1 ? -1 : (playerInput.y > -.2 ? -.2 : playerInput.y);
		playerInput.x = playerInput.x < -1 ? -1 : (playerInput.x > 1 ? 1 : playerInput.x);
	}

	void Game::LoadMenu() {
		PhysicsManager::LoadMap("assets/maps/MenuMap.csv", &tile, &finish, vec2(360, 0), character, wallLeft, wallRight);

		// Load map triggers
		mapTrigger1 = new MapTrigger("assets/maps/TestMap.csv", &tile, &map1, &finish, vec2(490, 624), character, wallLeft, wallRight);
		mapTrigger2 = new MapTrigger("assets/maps/TestMap.csv", &tile, &map2, &finish, vec2(1340, 624), character, wallLeft, wallRight);
		mapTrigger3 = new MapTrigger("assets/maps/TestMap.csv", &tile, &map3, &finish, vec2(490, 264), character, wallLeft, wallRight);
		mapTrigger4 = new MapTrigger("assets/maps/TestMap.csv", &tile, &map4, &finish, vec2(1340, 264), character, wallLeft, wallRight);
	}
};