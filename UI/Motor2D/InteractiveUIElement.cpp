#include "InteractiveUIElement.h"
#include "j1App.h"
#include "j1Input.h"
#include "p2Log.h"

#include "j1Render.h"
#include "j1Window.h"
#include "j1Module.h"

InteractiveUIElement::~InteractiveUIElement()
{
}

bool InteractiveUIElement::SetPositionRect()
{
	return false;
}

void InteractiveUIElement::DragElement()
{
}

void InteractiveUIElement::ManageEvents()
{
	SDL_Point pos;
	App->input->GetMousePosition(pos.x, pos.y);

	switch (state)
	{
	case ELEMENT_UP:
		if (SDL_PointInRect(&pos, &position_rect))
		{
			button_event = MOUSE_ENTER;

			LOG("MOUSE HAS ENTERED");
		}
		break;
	case ELEMENT_HOVER:
		if (!SDL_PointInRect(&pos, &position_rect))
		{
			button_event = MOUSE_LEAVE;
			LOG("MOUSE HAS LEFT");
		}
		else if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN) {
			button_event = CLICK_DOWN;
		}
		break;
	case ELEMENT_DOWN:
		if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_UP)
		{
			button_event = CLICK_UP;
			if (listener)
				listener->OnButtonClick(this, button_event);
			break;
		}
	}
}
