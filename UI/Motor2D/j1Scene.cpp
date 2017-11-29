#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1Map.h"
#include "j1PathFinding.h"
#include "j1Gui.h"
#include "j1Scene.h"
#include "j1Fonts.h"
#include "Button.h"
#include "Label.h"

j1Scene::j1Scene() : j1Module()
{
	name.create("scene");
}

// Destructor
j1Scene::~j1Scene()
{}

// Called before render is available
bool j1Scene::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool j1Scene::Start()
{
	if(App->map->Load("iso_walk.tmx") == true)
	{
		int w, h;
		uchar* data = NULL;
		if(App->map->CreateWalkabilityMap(w, h, &data))
			App->pathfinding->SetMap(w, h, data);

		RELEASE_ARRAY(data);
	}

	SDL_Rect rect = { 0,0,100,100 };

	//App->gui->AddUIElement({ 0,0 }, PICTURE);

	debug_tex = App->tex->Load("maps/path2.png");

	// TODO 3: Create the banner (rect {485, 829, 328, 103}) and the text "Hello World"

	_TTF_Font* morfeus = App->font->Load("fonts/open_sans/OpenSans-ExtraBoldItalic.ttf", 18);

	//App->gui->AddUIPicture({ 0,0 }, "gui/login_background.png"); //Background

	App->gui->AddUIPicture({ 0,0 }, "gui/Glues-Logo.png"); //Logo

	App->gui->AddUIText({ 800,500 }, "Account name:",morfeus); //Input
	App->gui->AddUIText({ 800,700 }, "Account Password:",morfeus); //Input
	//App->gui->AddUIButton({ 800,750 }, "Login", "gui/button-atlas.png", { 0,0,127,23 }, { 0,50,127,23 }, { 169,0,127,23 }); //LoginButton

	//App->gui->AddUIButton({ 100,850 }, "Manage account", "gui/button-atlas.png", { 0,0,127,23 }, { 0,50,127,23 }, { 169,0,127,23 }); //LoginButton
	//App->gui->AddUIButton({ 100,900 }, "Community site", "gui/button-atlas.png", { 0,0,127,23 }, { 0,50,127,23 }, { 169,0,127,23 }); //LoginButton

	//App->gui->AddUIButton({ 1500,800 }, "Cinematics", "gui/button-atlas.png", { 0,0,127,23 }, { 0,50,127,23 }, { 169,0,127,23 }); //LoginButton
	//App->gui->AddUIButton({ 1500,850 }, "Credits", "gui/button-atlas.png", { 0,0,127,23 }, { 0,50,127,23 }, { 169,0,127,23 }); //LoginButton

	Button* terms_of_use_but = App->gui->AddUIButton({ 1500,900 }, "Terms of use", "gui/button-atlas.png", { 0,0,127,23 }, { 0,50,127,23 }, { 169,0,127,23 }); //LoginButton

	terms_of_use_but->MoveInPercentage({ 50,50 });

	

	return true;
}

// Called each loop iteration
bool j1Scene::PreUpdate()
{

	// debug pathfing ------------------
	static iPoint origin;
	static bool origin_selected = false;

	int x, y;
	App->input->GetMousePosition(x, y);
	iPoint p = App->render->ScreenToWorld(x, y);
	p = App->map->WorldToMap(p.x, p.y);

	if(App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN)
	{
		if(origin_selected == true)
		{
			App->pathfinding->CreatePath(origin, p);
			origin_selected = false;
		}
		else
		{
			origin = p;
			origin_selected = true;
		}
	}

	return true;
}

// Called each loop iteration
bool j1Scene::Update(float dt)
{
	// Gui ---
	
	// -------
	if(App->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN)
		App->LoadGame("save_game.xml");

	if(App->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN)
		App->SaveGame("save_game.xml");

	if(App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
		App->render->camera.y += floor(200.0f * dt);

	if(App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
		App->render->camera.y -= floor(200.0f * dt);

	if(App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		App->render->camera.x += floor(200.0f * dt);

	if(App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		App->render->camera.x -= floor(200.0f * dt);

	App->map->Draw();

	int x, y;
	App->input->GetMousePosition(x, y);
	iPoint map_coordinates = App->map->WorldToMap(x - App->render->camera.x, y - App->render->camera.y);

	// Debug pathfinding ------------------------------
	//int x, y;
	App->input->GetMousePosition(x, y);
	iPoint p = App->render->ScreenToWorld(x, y);
	p = App->map->WorldToMap(p.x, p.y);
	p = App->map->MapToWorld(p.x, p.y);

	const p2DynArray<iPoint>* path = App->pathfinding->GetLastPath();

	for(uint i = 0; i < path->Count(); ++i)
	{
		iPoint pos = App->map->MapToWorld(path->At(i)->x, path->At(i)->y);
		
	}

	p2SString title("%d,%d", p.x, p.y);

	App->win->SetTitle(title.GetString());

	return true;
}

// Called each loop iteration
bool j1Scene::PostUpdate()
{
	bool ret = true;

	if(App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	return ret;
}

// Called before quitting
bool j1Scene::CleanUp()
{
	LOG("Freeing scene");

	return true;
}
