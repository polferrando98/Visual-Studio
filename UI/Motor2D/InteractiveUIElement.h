#pragma once

#include "UIElement.h"

enum ElementState { ELEMENT_UP, ELEMENT_HOVER, ELEMENT_DOWN };
enum Mouse_UI_Event { MOUSE_ENTER, MOUSE_LEAVE, CLICK_DOWN, CLICK_UP };

enum j1KeyState;

class InteractiveUIElement :
	public UIElement
{
public:
	InteractiveUIElement(iPoint position, UIType type) : UIElement(position, type)
	{
		this->position = position;
		this->texture = texture;
		this->type = type;
	};
	~InteractiveUIElement();
	bool SetPositionRect();
	void ManageEvents();
	void ManagePositionChanges();
	bool CheckPositionRect();
	void saveMousePos(iPoint& mousePos);
	bool ManageDrag();
	

protected:
	Mouse_UI_Event element_event = MOUSE_LEAVE;
	Mouse_UI_Event element_last_event = MOUSE_LEAVE;
	j1KeyState button_click_type;
	SDL_Rect position_rect = { 0,0,0,0 };
	bool draggabel = true;

	iPoint begin_drag_point;

	ElementState	state = ELEMENT_UP;
};

