#include "Button.h"
#include "j1App.h"
#include "j1Input.h"
#include "p2Log.h"
#include "j1Gui.h"
#include "Label.h"

Button::Button(iPoint position) : UIElement(position, BUTTON)
{
	label = new Label(position);
}

bool Button::Update(float dt)
{
	SDL_Point pos;
	App->input->GetMousePosition(pos.x, pos.y);

	if (!SDL_RectEmpty(&position_rect)) {
		if (SDL_PointInRect(&pos, &position_rect)) 
			state = BUTTON_HOVER;
		else 
			state = BUTTON_UP;
	}
	else {
		LOG("Error, button without position rect"); 
		return false;
	}

	ManageSection();

	Draw();
	label->Draw();
	return true;
}

bool Button::setPositionRect()
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
		break;
	default:
		break;
	}
}

Button::~Button()
{
	RELEASE(label);
}
