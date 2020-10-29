#pragma once

#include <iostream>
#include <thread>
#include <mutex>
#include <vector>

class Application
{
private:
	bool loop = true;
	std::mutex ioMtx;

	std::vector<std::thread> threads;

public:
	void Render();
	void Update();

	void MainLoop();
};

