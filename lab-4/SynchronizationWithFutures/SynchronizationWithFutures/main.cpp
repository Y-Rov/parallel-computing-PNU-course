#include <deque>
#include <future>
#include <mutex>
#include <iostream>
#include <utility>
#include <vector>

// ---------------------- TASK 1 BEGIN -------------------------------
//const int kMaxPrimeNumber = 15'485'917;
const int kMaxPrimeNumber = 305'597;

int GetPrimeNumberByIndex(int index)
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
	return prime_numbers[index - 1];
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
	std::cout << "OK, we are still waiting for the result...\n";
}

void Task1DefferedAsync()
{
	int prime_number_index;
	std::cout << "Enter the index of a prime number (1 <= n <= 1000000): ";
	std::cin >> prime_number_index;
	std::future<int> deferred_result = std::async(std::launch::deferred, GetPrimeNumberByIndex, prime_number_index);
	GameWithUser(prime_number_index);
	std::cout << "The result is " << deferred_result.get() << '\n';
}

void Task1RealAsync()
{
	int prime_number_index;
	std::cout << "Enter the index of a prime number (1 <= n <= 1000000): ";
	std::cin >> prime_number_index;
	std::future<int> async_result = std::async(std::launch::async, GetPrimeNumberByIndex, prime_number_index);
	GameWithUser(prime_number_index);
	std::cout << "The result is " << async_result.get() << '\n';
}

// ---------------------- TASK 1 END ----------------------------------

// ---------------------- TASK 2 BEGIN --------------------------------

std::deque<std::packaged_task<int(int)>> tasks;
std::deque<int> prime_number_indexes;
std::mutex defensive_mutex;

void Calculation()
{
	do
	{
		std::packaged_task<int(int)> prime_number_task;

		std::unique_lock<std::mutex> thread_lock(defensive_mutex);
		prime_number_task = std::move(tasks.front());
		tasks.pop_front();
		int prime_number_index = prime_number_indexes.front();
		prime_number_indexes.pop_front();
		thread_lock.unlock();

		prime_number_task(prime_number_index);
	} while (!tasks.empty() && !prime_number_indexes.empty());
}

void Task2()
{
	std::thread independent_thread;
	int prime_number_index;
	std::vector<std::future<int>> results;
	bool start_flag = true;
	std::cout << "Enter the index of a prime number (1 <= n <= 1000000, -1 - to stop): ";
	std::cin >> prime_number_index;
	while (prime_number_index != -1)
	{
		std::packaged_task<int(int)> prime_number_task(GetPrimeNumberByIndex);
		results.push_back(std::move(prime_number_task.get_future()));

		std::unique_lock<std::mutex> main_lock(defensive_mutex);
		tasks.push_back(std::move(prime_number_task));
		prime_number_indexes.push_back(prime_number_index);
		main_lock.unlock();

		if (start_flag)
		{
			independent_thread = std::thread(Calculation);
			start_flag = false;
		}
		std::cout << "Enter the index of a prime number (1 <= n <= 1000000, -1 - to stop): ";
		std::cin >> prime_number_index;
	}

	std::cout << "Your results: ";

	for (size_t i = 0; i < results.size(); i++)
	{
		if (i == results.size() - 1)
		{
			std::cout << results[i].get();
		}
		else 
		{
			std::cout << results[i].get() << ' ';
		}
	}
	std::cout << '\n';
	independent_thread.join();
}

// ---------------------- TASK 2 END ----------------------------------

// ---------------------- TASK 3 BEGIN --------------------------------

void Thread1FromTask3(int prime_num_index, std::promise<int> prime_num_promise, std::promise<int> mult_prime_num_promise,
	std::promise<bool> promise_for_second_thread)
{
	prime_num_promise.set_value(GetPrimeNumberByIndex(prime_num_index));
	promise_for_second_thread.set_value(true);
	mult_prime_num_promise.set_value(GetPrimeNumberByIndex(prime_num_index * 10));
}

void Thread2FromTask3(int prime_num_index, std::future<bool> first_thread_ready_flag)
{
	if (first_thread_ready_flag.get())
	{
		std::this_thread::sleep_for(std::chrono::seconds(2));
		std::cout << "SQRT(" << prime_num_index << ") = " << std::sqrt(prime_num_index) << '\n';
	}
}

void Task3()
{
	int prime_number_index;
	std::cout << "Enter the index of a prime number (1 <= n <= 1000000): ";
	std::cin >> prime_number_index;
	
	std::promise<int> prime_number_promise;
	std::future<int> prime_num_result = prime_number_promise.get_future();
	std::promise<bool> promise_for_second_thread;
	std::future<bool> second_promise_result = promise_for_second_thread.get_future();
	std::promise<int> mult_prime_number_promise;
	std::future<int> mult_prime_num_result = mult_prime_number_promise.get_future();
	
	std::thread first_thread(Thread1FromTask3, prime_number_index, std::move(prime_number_promise),
		std::move(mult_prime_number_promise), std::move(promise_for_second_thread));
	std::thread second_thread(Thread2FromTask3, prime_number_index, std::move(second_promise_result));

	std::cout << prime_number_index << "-th prime number is " << prime_num_result.get() << '\n';
	std::cout << prime_number_index * 10 << "-th prime number is " << mult_prime_num_result.get() << '\n';
	
	first_thread.join();
	second_thread.join();
}

// ---------------------- TASK 3 END ----------------------------------

int main()
{
	//Task1DefferedAsync();
	//Task1RealAsync();
	//Task2();
	Task3();
	system("pause");
	return 0;
}