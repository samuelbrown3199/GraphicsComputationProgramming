#include <iostream>
#include <thread>
#include <mutex>

#include <chrono>

#include "Application.h"

//bad global variables
std::mutex mtx;
int* massiveArray;

void SecondThreadFunction(int id)
{
	int a = 0;
	for (int i = 0; i < 100000; i++)
	{
		a = i;
	}

	mtx.lock();
	std::cout << "Thread # " << id << " has finished its second count!" << std::endl;
	mtx.unlock();
}

void ThreadPrint(int id)
{
	int a = 0;
	for (int i = 0; i < 10000; i++)
	{
		a = i;
	}

	mtx.lock();
	std::cout << "Thread # " << id << " has finished counting!" << std::endl;
	mtx.unlock();

	SecondThreadFunction(id);
}

void GenerateRandomNumberInArray(int array[], int offset, int count)
{
	for (int i = 0; i < count; i++)
	{
		array[i + offset] = rand() % 100000;
	}
}

int main()
{
	auto start = std::chrono::high_resolution_clock::now();
	srand(time(NULL));

	/*massiveArray = new int[10000];

	std::thread threads[2];
	for (int i = 0; i < 2; i++)
	{
		threads[i] = std::thread(GenerateRandomNumberInArray, massiveArray, i*5000, 5000);
	}

	for (auto& th : threads) th.join();

	//GenerateRandomNumberInArray(massiveArray, 0, 10000);

	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

	for (int i = 0; i < 10000; i++)
	{
		std::cout << "Massive Array " << i << " = " << massiveArray[i] << std::endl;
	}*/

	Application* app = new Application();
	app->MainLoop();

	//std::cout << "Process took " << duration.count() << " ms to create the array values." << std::endl;

	return 0;
}