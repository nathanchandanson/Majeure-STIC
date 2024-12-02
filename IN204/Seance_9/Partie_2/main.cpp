#include<vector>
#include<random>
#include<algorithm>
#include<thread>
#include<iostream>
#include <mutex>          
 
std::mutex vector_mutex;
 
void array_find_max(
	std::vector<int>::const_iterator begin, 
	std::vector<int>::const_iterator end, int* theMaxValue)
{
	std::unique_lock<std::mutex> lock(vector_mutex);
	if (begin != end)
	{
		int result = *begin;
		begin++;
		for (; begin != end; begin++)
			if (*begin > result)
				result = *begin;
		*theMaxValue = result;
	}
}
 
void array_multiply_by(
	std::vector<int>::iterator begin,
	std::vector<int>::iterator end, 
	int theValue)
{
	std::unique_lock<std::mutex> lock(vector_mutex);
	for (; begin != end; begin++)
		*begin *= theValue;
}
 
void initialize_array(std::vector<int>& theArray, int theSize,
	int theMaxValue)
{
	theArray.clear();
	theArray.resize(theSize);
	int step = theMaxValue / 3;
	theArray[0] = 0;
	for (int i = 1; i < theSize; i++)
		theArray[i] = (theArray[i - 1] + step) % (theMaxValue + 1);
}
 
void initialize_random_array(std::vector<int>& theArray, int theSize,
	int theMaxValue)
{
	static std::mt19937 gen(1729);
	std::uniform_int_distribution<> distrib(0, theMaxValue);
	theArray.clear();
	for (int i = 0; i < theSize; i++)
		theArray[i] = distrib(gen);
}
 
void test_valid_execution(std::vector<int>& theArray)
{
	std::mutex mutex;
	// Get the max value of the array
	int referenceMaxValue = *(std::max_element(theArray.begin(), theArray.end()));
 
	// Execute both threads in parallel
	int maxValue;
	std::thread max_proc(&array_find_max, theArray.begin(), theArray.end(), &maxValue);
	array_multiply_by(theArray.begin(), theArray.end(), 2);
	max_proc.join();
 
	int modifiedMaxValue = *(std::max_element(theArray.begin(), theArray.end()));
	if (referenceMaxValue != maxValue)
		std::cout << "Error when computing the max value: " << maxValue << " found, " << referenceMaxValue << " expected";
}
 
int main()
{
	std::vector<int> array;
	initialize_array(array, 10000, 100);
	test_valid_execution(array);
}