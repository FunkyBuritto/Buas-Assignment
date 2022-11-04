#include "Map.h"
#include "StaticPhysicsObject.h"
#include "PhysicsManager.h"
#include <fstream>
#include <string>

Map::Map(char* file, Tmpl8::Sprite* tileSprite)
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
			if (tile != "" && stoi(tile) == 0) {
				Tmpl8::StaticPhysicsObject* obj = new Tmpl8::StaticPhysicsObject(Tmpl8::vec2(i * 120, itteration* 120), tileSprite);
				tiles.push_back(obj);
			}

			line = line.substr(cpos + 1, line.size());
		}
		
		itteration += 1;
	}
	mapfile.close();
}