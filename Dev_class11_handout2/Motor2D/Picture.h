#pragma once
#include "UIElement.h"
class Picture :
	public UIElement
{
public:
	Picture(iPoint position, SDL_Texture* texture);
	~Picture();
	bool Update(float dt);

public:

};

