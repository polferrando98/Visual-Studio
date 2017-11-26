#include "UIElement.h"
#include "j1App.h"
#include "j1Render.h"

void UIElement::Draw()
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
