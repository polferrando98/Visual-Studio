#ifndef __UIELEMENT_H__
#define __UIELEMENT_H__
#include "p2SString.h"
#include "PugiXml\src\pugixml.hpp"
#include "p2Point.h"
#include "SDL\include\SDL_rect.h"

struct SDL_Texture;
enum UIType { LABEL, PICTURE, BUTTON };

class j1Module;

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

	void MoveInPercentage(fPoint position_in_percentage);

	void AdjustToPivot();

	void UpdateOldPos();

	void Focus();

public:
	iPoint			position = { 0, 0 };
	iPoint			old_position = position;

	SDL_Texture*	texture = nullptr;
	UIType			type;
	SDL_Rect		section = { 0,0,0,0 };
	bool			move_with_camera = true;
	fPoint			pivot = { 0.5,0.5 };
	uint			id =0;
	j1Module* listener = nullptr;

	bool focus = true;

};

#endif