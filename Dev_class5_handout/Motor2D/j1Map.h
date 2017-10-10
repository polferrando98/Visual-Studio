#ifndef __j1MAP_H__
#define __j1MAP_H__

#include "PugiXml/src/pugixml.hpp"
#include "p2List.h"
#include "p2Point.h"
#include "j1Module.h"

// TODO 1: Create a struct for the map layer
struct Layer {
	p2SString name;
	uint width;
	uint height;
	uint* data = nullptr;
	~Layer() { RELEASE(data) };
};

// ----------------------------------------------------

	// TODO 6: Short function to get the value of x,y
inline void ToRowsAndCols(int *x, int *y)  {
	int row = *x / *y;
	int column = *x - row*(*y);

	*x = column;
	*y = row;
}





// ----------------------------------------------------
struct TileSet
{
	// TODO 7: Create a method that receives a tile id and returns it's Rectfind the Rect associated with a specific tile id
	SDL_Rect GetTileRect(int id) const;

	p2SString			name;
	int					firstgid;
	int					margin;
	int					spacing;
	int					tile_width;
	int					tile_height;
	SDL_Texture*		texture;
	int					tex_width;
	int					tex_height;
	int					num_tiles_width;
	int					num_tiles_height;
	int					offset_x;
	int					offset_y;
};

enum MapTypes
{
	MAPTYPE_UNKNOWN = 0,
	MAPTYPE_ORTHOGONAL,
	MAPTYPE_ISOMETRIC,
	MAPTYPE_STAGGERED
};
// ----------------------------------------------------
struct MapData
{
	int					width;
	int					height;
	int					tile_width;
	int					tile_height;
	SDL_Color			background_color;
	MapTypes			type;
	p2List<TileSet*>	tilesets;
	p2List<Layer*>		layers;
	// TODO 2: Add a list/array of layers to the map!
	
};

// ----------------------------------------------------
class j1Map : public j1Module
{
public:

	j1Map();

	// Destructor
	virtual ~j1Map();

	// Called before render is available
	bool Awake(pugi::xml_node& conf);

	// Called each loop iteration
	void Draw();

	bool Update();

	// Called before quitting
	bool CleanUp();

	// Load new map
	bool Load(const char* path);

	// TODO 8: Create a method that translates x,y coordinates from map positions to world positions
	iPoint MapToWorld(int x, int y) const;

private:

	bool LoadMap();
	bool LoadTilesetDetails(pugi::xml_node& tileset_node, TileSet* set);
	bool LoadLayer(pugi::xml_node& node, Layer* layer);
	bool LoadTilesetImage(pugi::xml_node& tileset_node, TileSet* set);

	void Get_pixels_from_tiles(int x, int y, int* dest_x, int* dest_y)
	{
		*dest_x = x * data.tilesets.At(0)->data->tile_height;

		*dest_y = y * data.tilesets.At(0)->data->tile_width;
	}

	// TODO 3: Create a method that loads a single laye
	// bool LoadLayer(pugi::xml_node& node, MapLayer* layer);

public:

	MapData data;

private:

	pugi::xml_document	map_file;
	p2SString			folder;
	bool				map_loaded;
};

#endif // __j1MAP_H__