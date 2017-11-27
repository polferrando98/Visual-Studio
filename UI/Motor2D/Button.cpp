#include "Button.h"
#include "j1App.h"
#include "j1Input.h"
#include "p2Log.h"
#include "j1Gui.h"
#include "Label.h"
#include "j1Render.h"
#include "p2Log.h"


Button::Button(iPoint position) : UIElement(position, BUTTON)
{
	label = new Label(position);
	button_click_type = KEY_DOWN;
}

bool Button::Update(float dt)
{
	CenterLabel();

	SDL_Point pos;
	App->input->GetMousePosition(pos.x, pos.y);

	if (!SDL_RectEmpty(&position_rect)) {
		if (SDL_PointInRect(&pos, &position_rect)) 
			state = BUTTON_HOVER;
		else 
			state = BUTTON_UP;

		if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == button_click_type)
		{
			if (state = BUTTON_HOVER) 
			{
				state = BUTTON_DOWN;
				LOG("Click! :)");
			}
		}
		
	}
	else {
		LOG("Error, button without position rect"); 
		return false;
	}

	ManageSection();

	Draw();

	label->Update(dt);
	return true;
}

bool Button::SetPositionRect()
{
	if (!SDL_RectEmpty(&section)) {

		position_rect = {
		this->position.x,
		this->position.y,
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

Button::~Button()
{
	RELEASE(label);
}
