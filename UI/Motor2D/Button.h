#pragma once
#include "UIElement.h"
class Picture; 
class Label;

enum ButtonState {BUTTON_UP, BUTTON_HOVER, BUTTON_DOWN};


enum j1KeyState;

class j1Module;

class Button :
	public UIElement
{
public:
	Button(iPoint position);
	bool Update(float dt);
	bool SetPositionRect();
	void CenterLabel();

	void ManageSection();
	void ManageState();
	void ManageEvents();

	void saveMousePos(iPoint& mousePos);

	bool ManageDrag();

	~Button();

public:
	Label*		label = nullptr;
	iPoint		label_offset = { 0,0 };

	j1KeyState	button_click_type;

	SDL_Rect	position_rect = { 0,0,0,0 };
	SDL_Rect	up = { 0,0,0,0 };
	SDL_Rect	hover = { 0,0,0,0 };
	SDL_Rect	down = { 0,0,0,0 };

	ButtonState	state = BUTTON_UP;

	iPoint begin_drag_point;

	bool		draggabel = true;

};

