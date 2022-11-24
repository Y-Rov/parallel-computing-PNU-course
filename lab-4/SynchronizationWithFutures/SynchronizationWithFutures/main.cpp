#include <array>
#include <future>
#include <iostream>
#include <vector>

const int kMaxPrimeNumber = 15'485'917;

std::vector<int> GetPrimeNumbersVector()
{
	std::vector<bool> is_prime(kMaxPrimeNumber, true);

	for (int p = 2; p * p < kMaxPrimeNumber; p++)
	{
		if (is_prime[p] == true)
		{
			for (int i = p * p; i < kMaxPrimeNumber; i += p)
			{
				is_prime[i] = false;
			}
		}
	}

	std::vector<int> prime_numbers;
	for (int p = 2; p < kMaxPrimeNumber; p++)
	{
		if (is_prime[p]) 
		{
			prime_numbers.push_back(p);
		}	
	}
	return prime_numbers;
}

void GameWithUser(int enteredIndex)
{
	std::cout << "While the searching of the prime number is in progress, you can choose and calculate the one of available mathematical operations:\n";
	std::cout << "SQRT(n) - press '1'\nSIN(n) - press '2'\nLN(n) - press '3'\n";
	std::cout << "Choose the operation: ";
	int operation;
	std::cin >> operation;
	switch (operation)
	{
		case 1:
			std::cout << "SQRT(n) = " << std::sqrt(enteredIndex) << '\n';
			break;
		case 2:
			std::cout << "SIN(n) = " << std::sin(enteredIndex) << '\n';
			break;
		case 3:
			std::cout << "LN(n) = " << std::log(enteredIndex) << '\n';
			break;
		default:
			break;
	}
	std::cout << "OK, we still waiting for the result...\n";
}

void Task1DefferedAsync(int enteredPrimeIndex)
{
	std::future<std::vector<int>> deferred_result = std::async(std::launch::deferred, GetPrimeNumbersVector);
	GameWithUser(enteredPrimeIndex);
	std::cout << "The result is " << deferred_result.get()[enteredPrimeIndex - 1] << '\n';
}

void Task1RealAsync(int enteredPrimeIndex)
{
	std::future<std::vector<int>> async_result = std::async(std::launch::async, GetPrimeNumbersVector);
	GameWithUser(enteredPrimeIndex);
	std::cout << "The result is " << async_result.get()[enteredPrimeIndex - 1] << '\n';
}

int main()
{
	int primeNumberIndex = 1;
	std::cout << "Enter the index of a prime number that you want to know (n <= 1000000): ";
	std::cin >> primeNumberIndex;
	//Task1DefferedAsync(primeNumberIndex);
	Task1RealAsync(primeNumberIndex);
	system("pause");
	return 0;
}