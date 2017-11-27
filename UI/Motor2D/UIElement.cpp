#include "UIElement.h"
#include "j1App.h"
#include "j1Render.h"

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
			App->render->DrawQuad({ position.x - App->render->camera.x,position.y - App->render->camera.y, section.w, section.h }, 0, 0, 100, 100);
		else { //if section is empty we will draw the full texture
			iPoint size;
			SDL_QueryTexture(texture, 0, 0, &size.x, &size.y);
			App->render->DrawQuad({ position.x - App->render->camera.x,position.y - App->render->camera.y, size.x, size.y }, 0, 0, 100, 100);
		}
	}
	else
		if (!SDL_RectEmpty(&section))
			App->render->DrawQuad({ position.x,position.y,section.w,section.h }, 0, 0, 100, 100);
		else {
			iPoint size;
			SDL_QueryTexture(texture, 0, 0, &size.x, &size.y);
			App->render->DrawQuad({ position.x - App->render->camera.x,position.y - App->render->camera.y, size.x, size.y }, 0, 0, 100, 100);
		}
}
