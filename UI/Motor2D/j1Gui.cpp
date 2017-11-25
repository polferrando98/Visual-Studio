#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Fonts.h"
#include "j1Input.h"
#include "j1Gui.h"
#include "Picture.h"
#include "Label.h"

j1Gui::j1Gui() : j1Module()
{
	name.create("gui");
}

// Destructor
j1Gui::~j1Gui()
{}

// Called before render is available
bool j1Gui::Awake(pugi::xml_node& conf)
{
	LOG("Loading GUI atlas");
	bool ret = true;

	atlas_file_name = conf.child("atlas").attribute("file").as_string("");

	return ret;
}

// Called before the first frame
bool j1Gui::Start()
{
	atlas = App->tex->Load(atlas_file_name.GetString());

	return true;
}

// Update all guis
bool j1Gui::PreUpdate()
{	

	return true;
}

// Called after all Updates
bool j1Gui::PostUpdate()
{
	for (p2List_item<UIElement*>* element_iterator = elements.start; element_iterator != nullptr; element_iterator = element_iterator->next) {
		element_iterator->data->Update(App->dt);
	}
	return true;
}

// Called before quitting
bool j1Gui::CleanUp()
{
	LOG("Freeing GUI");

	return true;
}

UIElement* j1Gui::AddUIElement(iPoint position, UIType type)
{
	UIElement* elem;
	switch (type)
	{
	case LABEL:
		elem = new Label(position);
		break;
	case PICTURE:
		elem = new Picture(position);
		elem->texture = atlas;
		break;
	default:
		return nullptr;
		break;
	}
	elements.add(elem);
	return elem;
}

UIElement * j1Gui::AddUIText(iPoint position, p2SString text, SDL_Color color)
{
	UIElement* elem;

	elem = new Label(position, text, color);
	elements.add(elem);

	return elem;
}

UIElement * j1Gui::AddUIPicture(iPoint position, p2SString name, SDL_Rect section)
{
	UIElement* elem;

	elem = new Picture(position);

	if (name != "") {
		SDL_Texture* newTexture = nullptr;
		newTexture = App->tex->Load(name.GetString());
		elem->texture = newTexture;
	}
	else {
		elem->texture = atlas;
		if (!SDL_RectEmpty(&section))
			elem->section = section;
	}

	elements.add(elem);

	return elem;
}

// const getter for atlas
SDL_Texture* j1Gui::GetAtlas() const
{
	return atlas;
}

// class Gui ---------------------------------------------------

