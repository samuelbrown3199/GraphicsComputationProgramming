#include "Application.h"

#undef main

int main()
{
	std::shared_ptr<Application> app = std::make_shared<Application>();
	int appType = 0;

	std::cout << "Types of shadows:" << std::endl;
	std::cout << "1. Directional Shadows" << std::endl;
	std::cout << "2. Point Light Shadows" << std::endl;

	std::cout << "Please enter what type of shadows you want: ";
	std::cin >> appType;

	while (appType > 2 || appType < 1)
	{
		std::cin.clear();

		std::cout << "Types of shadows:" << std::endl;
		std::cout << "1. Directional Shadows" << std::endl;
		std::cout << "2. Point Light Shadows" << std::endl;

		std::cout << "Please enter a valid type of shadows you want: ";
		std::cin >> appType;
	}

	app->Initialise(appType);
	app->MainLoop();

	return 0;
}