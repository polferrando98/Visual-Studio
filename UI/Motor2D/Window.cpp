#include "Window.h"


Window::Window(iPoint position) :InteractiveUIElement(position, WINDOW)
{

}

bool Window::Update(float dt)
{
	ManagePositionChanges();

	return CheckPositionRect();

	ManageEvents();

	Draw();

	

	element_last_event = element_event;
	return true;
}

Window::~Window()
{
}
