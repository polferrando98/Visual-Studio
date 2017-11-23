#include "Picture.h"
#include "j1App.h"
#include "j1Render.h"

Picture::Picture(iPoint position, SDL_Texture* texture) : UIElement(position, texture, PICTURE)
{
	section = { 0,0,200,200 };
}


Picture::~Picture()
{
}

bool Picture::Update(float dt)
{
	App->render->Blit(texture, position.x, position.y, &section);
	return true;
}
