#include "Button.h"
#include "j1App.h"
#include "j1Input.h"
#include "p2Log.h"
#include "j1Gui.h"
#include "Label.h"
#include "j1Render.h"
#include "p2Log.h"
#include "j1Window.h"


Button::Button(iPoint position) : UIElement(position, BUTTON)
{
	label = new Label(position);
	button_click_type = KEY_DOWN;
	//AdjustToPivot();
}

bool Button::Update(float dt)
{
	if (old_position != position) {
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
	button_last_event = button_event;

	Draw();

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
			button_event = MOUSE_ENTER;
		break;
	case BUTTON_HOVER:
		if (!SDL_PointInRect(&pos, &position_rect))
			button_event = MOUSE_LEAVE;
		else if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN)
			button_event = CLICK_DOWN;
		break;
	case BUTTON_DOWN:
		if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_UP)
			button_event = CLICK_UP;
		break;
	}
}



Button::~Button()
{
	RELEASE(label);
}
