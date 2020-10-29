#include "Application.h"

void Application::Render()
{
	for (int i = 0; i < 100000; i++)
	{

	}

	std::cout << "Render finished" << std::endl;
}
void Application::Update()
{
	for (int i = 0; i < 100000; i++)
	{
		int a = rand() % 100000;
		int b = rand() % 500000;

		int c = a + b;
	}

	std::cout << "Update finished" << std::endl;
}

void Application::MainLoop()
{
	std::thread renderThread;
	std::thread updateThread;

	while (loop)
	{
		renderThread = std::thread(&Application::Render, this);
		updateThread = std::thread(&Application::Update, this);

		updateThread.join();
		renderThread.join();
	}
}