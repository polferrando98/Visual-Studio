#pragma once
#include "UIElement.h"
class Label :
	public UIElement
{
public:
	Label(iPoint position, p2SString text = "Empty Text", SDL_Color color = { 255,255,255,255 });
	bool Update(float dt);
	void SetText(p2SString text);
	~Label();

public:


private:
	p2SString text;
	SDL_Color color;
};

