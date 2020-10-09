#pragma once

#include <iostream>
#include <thread>
#include <mutex>

class Application
{
private:
	bool loop = true;
	std::mutex ioMtx;

public:
	void Render();
	void Update();

	void MainLoop();
};

