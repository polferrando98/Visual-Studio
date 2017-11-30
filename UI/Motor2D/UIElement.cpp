#include "UIElement.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Window.h"

void UIElement::Draw() const 
{
	if (move_with_camera) {
		if (SDL_RectEmpty(&section)) 
			App->render->Blit(texture, position.x - App->render->camera.x, position.y - App->render->camera.y);
		else
			App->render->Blit(texture, position.x - App->render->camera.x, position.y - App->render->camera.y, &section);
	}

	else
		if (SDL_RectEmpty(&section))
			App->render->Blit(texture, position.x, position.y);
		else
			App->render->Blit(texture, position.x, position.y, &section);
}

void UIElement::DebugDraw() const
{	
	if (move_with_camera) {
		if (!SDL_RectEmpty(&section)) 
				App->render->DrawQuad({ position.x - App->render->camera.x,position.y - App->render->camera.y, section.w, section.h }, 255, 0, 0, 255, false);

		else { //if section is empty we will draw the full texture
			iPoint size;
			SDL_QueryTexture(texture, 0, 0, &size.x, &size.y);
			App->render->DrawQuad({ position.x - App->render->camera.x,position.y - App->render->camera.y, size.x, size.y }, 255, 0, 0, 255, false);
		}
	}
	else
		if (!SDL_RectEmpty(&section))
			App->render->DrawQuad({ position.x,position.y,section.w,section.h }, 255, 0, 0, 255, false);
		else {
			iPoint size;
			SDL_QueryTexture(texture, 0, 0, &size.x, &size.y);
			App->render->DrawQuad({ position.x - App->render->camera.x,position.y - App->render->camera.y, size.x, size.y }, 255, 0, 0, 255, false);
		}
}

void UIElement::MoveInPercentage(fPoint position_in_percentage)
{
	position_in_percentage.x /= float(100);
	position_in_percentage.y /= float(100);
	fPoint new_position;
	iPoint window_size;
	SDL_GetWindowSize(App->win->window, &window_size.x, &window_size.y);
	position.x = (window_size.x * position_in_percentage.x);
	position.y = (window_size.y * position_in_percentage.y);
}

void UIElement::AdjustToPivot()
{
	if (!SDL_RectEmpty(&section)) {
		position.x -= (section.w / 2);
		position.y -= (section.h / 2);
	}
	else { //if section is empty we will draw the full texture
		iPoint size;
		SDL_QueryTexture(texture, 0, 0, &size.x, &size.y);
		position.x -= size.x / 2;
		position.y -= size.y / 2;
	}

}

void UIElement::UpdateOldPos()
{
	old_position = position;
}

void UIElement::Focus()
{
	
}

