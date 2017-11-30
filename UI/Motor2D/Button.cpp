#include "Button.h"
#include "j1App.h"
#include "j1Input.h"
#include "p2Log.h"
#include "j1Gui.h"
#include "Label.h"
#include "j1Render.h"
#include "p2Log.h"
#include "j1Window.h"
#include "j1Module.h"


Button::Button(iPoint position) : UIElement(position, BUTTON)
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

bool Button::SetPositionRect()
{
	if (!SDL_RectEmpty(&section)) {

		position_rect = {
		position.x,
		position.y,
		section.w,
		section.h
		};

		return true;
	}
	else
		return false;
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
	case BUTTON_UP:
		section = up;
		break;
	case BUTTON_HOVER:
		if (!SDL_RectEmpty(&hover))
			section = hover;
		if (listener)
			listener->OnButtonHover(this, button_event);
		break;
	case BUTTON_DOWN:
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
		state = BUTTON_HOVER;
		break;
	case MOUSE_LEAVE:
		state = BUTTON_UP;
		break;
	case CLICK_DOWN:
		state = BUTTON_DOWN;
		break;
	case CLICK_UP:
		state = BUTTON_HOVER;
		break;
	}
}

void Button::ManageEvents()
{
	SDL_Point pos;
	App->input->GetMousePosition(pos.x, pos.y);

	switch (state)
	{
	case BUTTON_UP:
		if (SDL_PointInRect(&pos, &position_rect))
		{
			button_event = MOUSE_ENTER;

			LOG("MOUSE HAS ENTERED");
		}
		break;
	case BUTTON_HOVER:
		if (!SDL_PointInRect(&pos, &position_rect))
		{
			button_event = MOUSE_LEAVE;
			LOG("MOUSE HAS LEFT");
		}
		else if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN) {
			button_event = CLICK_DOWN;
		}
		break;
	case BUTTON_DOWN:
		if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_UP)
		{
			button_event = CLICK_UP;
			if(listener)
				listener->OnButtonClick(this, button_event);
			break;
		}
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

	if (state == BUTTON_DOWN) {
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
