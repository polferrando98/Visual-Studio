#include "Button.h"
#include "j1App.h"
#include "j1Input.h"
#include "p2Log.h"
#include "j1Gui.h"
#include "Label.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1Module.h"
#include "InteractiveUIElement.h"

Button::Button(iPoint position) : InteractiveUIElement(position, BUTTON)
{
	label = new Label(position);
	button_click_type = KEY_DOWN;
}

bool Button::Update(float dt)
{
	bool ret;
	ret = CheckPositionRect(type);


	if (PositionChanged()) {
		AdjustToPivot();
		SetPositionRect();
	}


	
	ManageEvents();

	if (element_event != element_last_event) {
		ManageState();
		ManageSection();
	}

	ManageDrag();

	Draw();
	CenterLabel();

	element_last_event = element_event;
	label->Update(dt);
	return ret;
}

void Button::CenterLabel()
{
	label->position.x = draw_positon.x + (section.w / 2) - (label->size.x / 2);     //Not entirely centered don't know why
	label->position.y = draw_positon.y + (section.h / 2) - (label->size.y / 2);
}

void Button::ManageSection()
{
	switch (state)
	{
	case ELEMENT_UP:
		section = up;
		break;
	case ELEMENT_HOVER:
		if (!SDL_RectEmpty(&hover))
			section = hover;
		if (listener)
			listener->OnButtonHover(this, element_event);
		break;
	case ELEMENT_DOWN:
		if (!SDL_RectEmpty(&down))
			section = down;
		break;
	default:
		break;
	}
}

void Button::ManageState()
{
	switch (element_event)
	{
	case MOUSE_ENTER:
		state = ELEMENT_HOVER;
		break;
	case MOUSE_LEAVE:
		state = ELEMENT_UP;
		break;
	case CLICK_DOWN:
		state = ELEMENT_DOWN;
		break;
	case CLICK_UP:
		state = ELEMENT_HOVER;
		break;
	}
}

Button::~Button()
{
	RELEASE(label);
}
