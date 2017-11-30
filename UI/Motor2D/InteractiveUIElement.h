#ifndef __INTERACTIVEUIELEMENT_H__
#define __INTERACTIVEUIELEMENT_H__

#include "UIElement.h"
#include "j1Input.h"
enum ElementState { ELEMENT_UP, ELEMENT_HOVER, ELEMENT_DOWN };
enum Mouse_UI_Event { MOUSE_ENTER, MOUSE_LEAVE, CLICK_DOWN, CLICK_UP };

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
	void DragElement();
	void ManageEvents();
	

protected:
	Mouse_UI_Event button_event = MOUSE_LEAVE;
	Mouse_UI_Event button_last_event = MOUSE_LEAVE;
	j1KeyState button_click_type;
	SDL_Rect position_rect = { 0,0,0,0 };
	bool draggable;
};

#endif