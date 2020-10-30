#include "Application.h"

#undef main

int main()
{
	std::shared_ptr<Application> app = std::make_shared<Application>();
	app->Initialise();
	app->MainLoop();

	return 0;
}