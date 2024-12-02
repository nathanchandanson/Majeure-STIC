#include <iostream>
#include <string>
#include <sstream>
#include <future>

std::string computeE(int numberOfDigits)
{
	int sizeOfTable = numberOfDigits + 9;
	int* table = (int*)alloca(sizeOfTable * sizeof(numberOfDigits));   // _alloca fait la meme chose que malloc mais dans la pile
	table[0] = 0;
	table[1] = 2;
	for (int i = sizeOfTable - 1; i > 0; i--) {
		table[i] = 1;
	}
 
	std::ostringstream output;
	int x = 0;
	table[1] = 2;
	for (; sizeOfTable > 9; sizeOfTable -- ) 
	{
		for (int i = sizeOfTable - 1; i > 0; i--) 
		{
			table[i] = x % i;
			x = 10 * table[i - 1] + x / i;
		}
		output << x;
	}
	return output.str();
}

void display(std::future<std::string>& aFutureValue, int theDecimals)
{
	aFutureValue.wait();
	std::cout << "e with " << theDecimals << " decimals\n" << aFutureValue.get() << std::endl;
}
 
int main()
{
	std::future<std::string> eWidth20000 = std::async(std::launch::async, &computeE, 20000);
	std::future<std::string> eWidth100000 = std::async(std::launch::async, &computeE, 100000);
	display(eWidth20000, 20000);
	display(eWidth100000, 100000);
}