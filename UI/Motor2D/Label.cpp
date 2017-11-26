#include "Label.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Fonts.h"

Label::Label(iPoint position, p2SString text, SDL_Color color) : UIElement(position, LABEL)
{
	this->texture = App->font->Print(text.GetString(), color);
	this->text = text;
	this->color = color;
}

bool Label::Update(float dt)
{
	Draw();
	return true;
}

void Label::SetText(p2SString text)
{
	this->text = text;
	texture = App->font->Print(text.GetString(), color, font);
}

void Label::SetFont(_TTF_Font* font)
{
	this->font = font;
	texture = App->font->Print(text.GetString(), color, font);
}

Label::~Label()
{
}
