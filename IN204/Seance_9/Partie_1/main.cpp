#include<iostream>
#include<thread>
#include <chrono>
 
using namespace std::chrono_literals;
 
void worker_process(int numberOfIterations)
{
	for (int i = 1; i < numberOfIterations; i++)
	{
		std::cout << "Worker Thread: " << i << "\n";
		std::this_thread::sleep_for(10ns);
	}
}
 
void main_process()
{
	for (int i = 1; i < 1000; i++)
	{
		using namespace std;
		std::cout << "Primary Thread: " << i << "\n";
		std::this_thread::sleep_for(1ns);
	}
}
 
int main()
{
	std::thread worker_proc(&worker_process, 10000);
	std::thread main_proc(&main_process);
	worker_proc.join();
	main_proc.join();
}