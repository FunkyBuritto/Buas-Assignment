#include "Map.h"
#include "StaticPhysicsObject.h"
#include "PhysicsManager.h"
#include "MapTrigger.h"
#include "surface.h"
#include <fstream>
#include <string>

Map::Map(char* file, Tmpl8::Sprite* tileSprite, Tmpl8::Sprite* finishSprite, Tmpl8::vec2 offset, Tmpl8::Player* character, Tmpl8::StaticPhysicsObject* wallL, Tmpl8::StaticPhysicsObject* wallR)
{
	// Get Map File
	std::ifstream mapfile;
	mapfile.open(file);
	if (!mapfile.is_open()) {
		printf("Could not open map file");
		return;
	}

	int itteration = 0;
	std::string line;

	// temporary !!
	int lvlWidth = 10;

	// Loop over every line of the file
	while (std::getline(mapfile, line))
	{
		//printf(line.c_str());
		//printf("\n");

		// Loop over every tile in the 
		for (size_t i = 0; i < lvlWidth; i++) {
			size_t cpos = line.find(",");
			std::string tile = line.substr(0, cpos);

			// If we find a tile
			if (tile != "") {
				int numb = stoi(tile);
				Tmpl8::vec2 p = Tmpl8::vec2(i * 120 + offset.x, itteration * 120 + offset.y);
				switch (numb) {
				case 0:
					tiles.push_back(new Tmpl8::StaticPhysicsObject(p, tileSprite));
					break;
				case 1:
					character->SetVelocity(Tmpl8::vec2(0));
					character->pos = p;
					break;
				case 2:
					finish = new Tmpl8::MapTrigger(tileSprite, finishSprite, p, character, wallL, wallR);
					break;
				}
			}

			line = line.substr(cpos + 1, line.size());
		}
		
		itteration += 1;
	}
	mapfile.close();
}