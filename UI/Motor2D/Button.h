#ifndef __BUTTON_H__
#define __BUTTON_H__
#include "InteractiveUIElement.h"
//#include "UIElement.h"
class Picture; 
class Label;

enum j1KeyState;
class j1Module;

class Button :
	public InteractiveUIElement
{
public:
	Button(iPoint position);
	bool Update(float dt);
	void CenterLabel();
	void ManageSection();
	void ManageState();

	void saveMousePos(iPoint& mousePos);

	bool ManageDrag();

	~Button();

public:
	Label*		label = nullptr;
	iPoint		label_offset = { 0,0 };
	j1KeyState	button_click_type;
	SDL_Rect	up = { 0,0,0,0 };
	SDL_Rect	hover = { 0,0,0,0 };
	SDL_Rect	down = { 0,0,0,0 };

	iPoint begin_drag_point;

	bool		draggabel = true;

};

#endif