#include <array>
#include <future>
#include <iostream>
#include <vector>

const int kAmountOfPrimeNumber = 1'025'000;

std::vector<int> GetPrimeNumbersVector()
{
	std::vector<bool> is_prime(kAmountOfPrimeNumber, true);

	for (int p = 2; p * p < kAmountOfPrimeNumber; p++)
	{
		if (is_prime[p] == true)
		{
			for (int i = p * p; i < kAmountOfPrimeNumber; i += p)
			{
				is_prime[i] = false;
			}
		}
	}

	std::vector<int> prime_numbers;
	for (int p = 2; p < kAmountOfPrimeNumber; p++)
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
	std::cout << "While the prime number is calculating, please, we can calculate the one of available mathematical operations: \n";
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
}

int main()
{
	int primeNumberIndex = 0;
	std::cout << "Enter the index of a prime number that you want to know (n): ";
	std::cin >> primeNumberIndex;
	std::vector<int> result = GetPrimeNumbersVector();
	//GameWithUser(primeNumberIndex);
	std::cout << result[primeNumberIndex] << '\n';
	system("pause");
	return 0;
}