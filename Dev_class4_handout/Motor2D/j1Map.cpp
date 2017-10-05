#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Map.h"
#include <math.h>

j1Map::j1Map() : j1Module(), map_loaded(false)
{
	name.create("map");
}

// Destructor
j1Map::~j1Map()
{}

// Called before render is available
bool j1Map::Awake(pugi::xml_node& config)
{
	LOG("Loading Map Parser");
	bool ret = true;

	folder.create(config.child("folder").child_value());

	return ret;
}

void j1Map::Draw()
{
	if(map_loaded == false)
		return;

	// TODO 6: Iterate all tilesets and draw all their 
	// images in 0,0 (you should have only one tileset for now)
	for (pugi::xml_node tileset_node = map_file.child("map").child("tileset"); tileset_node; tileset_node = tileset_node.next_sibling("tileset")) {

		SDL_Texture *tileset_texture;
		tileset_texture = App->tex->Load(tileset_node.child("image").attribute("source").as_string());
		App->render->Blit(tileset_texture, 0, 0);
		//App->render->Blit();
	}
}

// Called before quitting
bool j1Map::CleanUp()
{
	LOG("Unloading map");

	// TODO 2: Make sure you clean up any memory allocated
	// from tilesets / map
	tilesets.clear();

	map_file.reset();

	return true;
}

// Load new map
bool j1Map::Load(const char* file_name)
{
	bool ret = true;
	p2SString tmp("%s%s", folder.GetString(), file_name);

	pugi::xml_parse_result result = map_file.load_file(tmp.GetString());

	if(result == NULL)
	{
		LOG("Could not load map xml file %s. pugi error: %s", file_name, result.description());
		ret = false;
	}

	if(ret == true)
	{
		// TODO 3: Create and call a private function to load and fill
		// all your map data
		loadAndFillMap();
		loadAndFillTilesets();
		loadAndFillLayers();
	}

	// TODO 4: Create and call a private function to load a tileset
	// remember to support more any number of tilesets!
	LogEverything();

	if(ret == true)
	{
		// TODO 5: LOG all the data loaded
		// iterate all tilesets and LOG everything
	}

	map_loaded = ret;

	return ret;
}


bool j1Map::loadAndFillMap()
{
	pugi::xml_node map_node = map_file.child("map");

	map1.version = (map_node.attribute("version").as_float());

	//if (strlen(map_node.attribute("orientation").as_string()) == strlen("orthogonal")) { //WTF no va
	//	map1.orientation = orthogonal;
	//}

	if (map_node.attribute("orientation").as_string() == "orthogonal") { //faltan casos
		map1.orientation = orthogonal;
	}

	if (strlen(map_node.attribute("renderorder").as_string()) == strlen("right-down")) { 
		map1.renderorder = rightDown;
	}
	map1.width = map_node.attribute("width").as_int();
	map1.height = map_node.attribute("height").as_int();
	map1.tilewidth = map_node.attribute("tilewidth").as_int();
	map1.tileheight = map_node.attribute("tileheight").as_int();
	map1.nextobjectid = map_node.attribute("nextobjectid").as_int();
	
	return true;
}

bool j1Map::loadAndFillTilesets()
{


	tileset tilset_temp;

	for (pugi::xml_node tileset_node = map_file.child("map").child("tileset"); tileset_node; tileset_node = tileset_node.next_sibling("tileset")) {
		tilset_temp.firstgid = tileset_node.attribute("firstgid").as_int();
		tilset_temp.name = (char*)(tileset_node.attribute("name").as_string());
		tilset_temp.tilewidth = tileset_node.attribute("tilewidth").as_int();
		tilset_temp.tileheight = tileset_node.attribute("tileheight").as_int();
		tilset_temp.spacing = tileset_node.attribute("spacing").as_int();
		tilset_temp.margin = tileset_node.attribute("margin").as_int();
		tilesets_count++;
	}

	tilesets.add(tilset_temp);
	return false;
}

bool j1Map::loadAndFillLayers()
{
	layer layer_temp;

	for (pugi::xml_node layer_node = map_file.child("map").child("layer"); layer_node; layer_node = layer_node.next_sibling("tileset")) {
		layer_temp.name = (char*)(layer_node.attribute("name").as_string());
		layer_temp.width = layer_node.attribute("width").as_int();
		layer_temp.height = layer_node.attribute("height").as_int();
		tilesets_count++;
	}
	layers.add(layer_temp);
	return false;
}

void j1Map::LogEverything()
{
	LOG("Map version: %f", map1.version);
	LOG("Map orientation: %i", map1.orientation);//logs an int equivalent to the enum
	LOG("Map renderorder: %i", map1.renderorder);
	LOG("Map width %d", map1.width);
	LOG("Map height %d", map1.height);
	LOG("Map tilewidth %d", map1.tilewidth);
	LOG("Map tileheight %d", map1.tileheight);
	LOG("Map nextobjectid %d", map1.nextobjectid);

	for (int i = 0; tilesets.At(i); i++) {
		tileset tileset_iterator = tilesets.At(i)->data;
		LOG("Tileset #%d firstgid: %d", i + 1,tileset_iterator.firstgid);
		LOG("Tileset #%d name: %s", i + 1, tileset_iterator.name);
		LOG("Tileset #%d tilewidth: %d", i + 1, tileset_iterator.tilewidth);
		LOG("Tileset #%d tileheight: %d", i + 1, tileset_iterator.tileheight);
		LOG("Tileset #%d spacing: %d", i + 1, tileset_iterator.spacing);
		LOG("Tileset #%d margin: %d", i + 1, tileset_iterator.margin);
	}

	for (int i = 0; layers.At(i); i++) {
		layer layer_iterator = layers.At(i)->data;
		LOG("Layer #%d name: %s", i + 1, layer_iterator.name);
		LOG("Layer #%d width: %d", i + 1, layer_iterator.width);
		LOG("Layer #%d height: %d", i + 1, layer_iterator.height);
	}
}


