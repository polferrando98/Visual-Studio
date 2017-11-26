#pragma once
#include "UIElement.h"
class Picture; 
class Label;

enum ButtonState {BUTTON_UP, BUTTON_HOVER, BUTTON_DOWN};
class Button :
	public UIElement
{
public:
	Button(iPoint position);
	bool Update(float dt);
	bool setPositionRect();
	void ManageSection();
	~Button();

public:
	Label* label = nullptr;
	SDL_Rect position_rect = { 0,0,0,0 };
	SDL_Rect up = { 0,0,0,0 };
	SDL_Rect hover = { 0,0,0,0 };
	ButtonState state = BUTTON_UP;
};

