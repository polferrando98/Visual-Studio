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
	if (old_position != position) {
		AdjustToPivot();
		SetPositionRect();
	}

	if (SDL_RectEmpty(&position_rect))
	{
		LOG("Error, button without position rect");
		return false;
	}
	CenterLabel();

	ManageEvents();

	if (button_event != button_last_event) {
		ManageState();
		ManageSection();
	}

	ManageDrag();

	Draw();


	button_last_event = button_event;
	label->Update(dt);
	return true;
}

void Button::CenterLabel()
{
	label->position.x = position.x + (section.w / 2) - (label->size.x / 2);     //Not entirely centered don't know why
	label->position.y = position.y + (section.h / 2) - (label->size.y / 2);
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
			listener->OnButtonHover(this, button_event);
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
	switch (button_event)
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

void Button::saveMousePos(iPoint& mousePos)
{
	App->input->GetMousePosition(mousePos.x, mousePos.y);
}

bool Button::ManageDrag()
{
	if (!draggabel)
		return false;

	if (button_event != button_last_event) {
		if (button_event == CLICK_DOWN)
			saveMousePos(begin_drag_point);
	}

	if (state == ELEMENT_DOWN) {
		iPoint curr_mouse_pos;
		App->input->GetMousePosition(curr_mouse_pos.x, curr_mouse_pos.y);

		iPoint differential = curr_mouse_pos - begin_drag_point;

		position += differential;
		
		SetPositionRect();
		saveMousePos(begin_drag_point);
	}
	

	return true;
}



Button::~Button()
{
	RELEASE(label);
}
