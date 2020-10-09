#include "Application.h"

void Application::Render()
{
	for (int i = 0; i < 10000; i++)
	{

	}

	ioMtx.lock();
	std::cout << "Render finished" << std::endl;
	ioMtx.unlock();
}
void Application::Update()
{
	for (int i = 0; i < 10000; i++)
	{

	}

	ioMtx.lock();
	std::cout << "Update finished" << std::endl;
	ioMtx.unlock();
}

void Application::MainLoop()
{
	std::thread renderThread;
	std::thread updateThread;

	while (loop)
	{
		renderThread = std::thread(&Application::Render, this);
		updateThread = std::thread(&Application::Update, this);

		renderThread.join();
		updateThread.join();
	}
}