#ifndef __j1GUI_H__
#define __j1GUI_H__

#include "j1Module.h"
#include "UIElement.h"

#define CURSOR_WIDTH 2

// TODO 1: Create your structure of classes


// ---------------------------------------------------
class j1Gui : public j1Module
{
public:

	j1Gui();

	// Destructor
	virtual ~j1Gui();

	// Called when before render is available
	bool Awake(pugi::xml_node&);

	// Call before first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called after all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	// TODO 2: Create the factory methods
	// Gui creation functions
	UIElement* AddUIElement(iPoint position, UIType type);

	UIElement* AddUIText(iPoint position, p2SString text, SDL_Color color = { 255,255,255,255 });

	UIElement* AddUIPicture(iPoint position, p2SString name = "", SDL_Rect section = { 0,0,0,0 });

	SDL_Texture* GetAtlas() const;

private:

	SDL_Texture* atlas;
	p2SString atlas_file_name;

	p2List<UIElement*> elements;

	
};

#endif // __j1GUI_H__