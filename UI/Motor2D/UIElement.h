#pragma once
#include "p2SString.h"
#include "PugiXml\src\pugixml.hpp"
#include "p2Point.h"
#include "SDL\include\SDL_rect.h"

struct SDL_Texture;
enum UIType { LABEL, PICTURE, BUTTON };

class UIElement
{
public:
	UIElement(iPoint position, UIType type) {
		this->position = position;
		this->texture = texture;
		this->type = type;
	};
	~UIElement() {};


	// Called before the first frame
	virtual bool Start()
	{
		return true;
	}

	// Called each loop iteration
	virtual bool PreUpdate()
	{
		return true;
	}

	// Called each loop iteration
	virtual bool Update(float dt)
	{
		return true;
	}

	// Called each loop iteration
	virtual bool PostUpdate()
	{
		return true;
	}

	// Called before quitting
	virtual bool CleanUp()
	{
		return true;
	}

	void Draw() const;

	void DebugDraw() const;


public:
	iPoint position = { 0, 0 };
	SDL_Texture* texture = nullptr;
	UIType type;
	SDL_Rect section = { 0,0,0,0 };
	bool move_with_camera = true; 
};

