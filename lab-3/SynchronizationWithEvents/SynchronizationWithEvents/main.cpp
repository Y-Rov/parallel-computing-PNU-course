#include <condition_variable>
#include <iostream>
#include <mutex>
#include <string>
#include <sstream>
#include <queue>

// Task 1
bool global_flag = false;
std::mutex mutex_for_flag;

std::queue<int> global_queue;

void DataPreparation()
{
	std::cout << "Enter some integer numbers: ";
	std::string str;
	std::getline(std::cin, str);
	std::istringstream sstr(str);
	int number;
	while (sstr >> number)
	{
		global_queue.push(number);
	}
	global_flag = true;
}

void DataProcessing()
{
	std::unique_lock<std::mutex> lock_for_global_flag(mutex_for_flag);
	while (!global_flag)
	{
		lock_for_global_flag.unlock();
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		lock_for_global_flag.lock();
	}

	while (!global_queue.empty())
	{
		int number = global_queue.front();
		global_queue.pop();

		bool is_prime = true;
		for (int i = 2; i <= number / 2; i++)
		{
			if (number % i == 0)
			{
				is_prime = false;
				break;
			}
		}

		if (is_prime)
		{
			std::cout << number << " is a prime number\n";
		}
		else
		{
			std::cout << number << " is not a prime number\n";
		}
	}
}

// Task 2
int global_variable = 0;
std::condition_variable global_variable_cond;
std::mutex mutex_for_global_variable;
bool check_global_variable() { return global_variable == 1; }

void Awake()
{
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	std::cout << "'Awake' function begins to inform the waiting threads\n";
	global_variable_cond.notify_all();
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	global_variable = 1;
	std::cout << "'Awake' function again informs the waiting threads\n";
	global_variable_cond.notify_all();
}

void Waits()
{
	std::cout << "'Waits' function enters the standby state\n";
	std::unique_lock<std::mutex> lock_for_global_variable(mutex_for_global_variable);
	global_variable_cond.wait(lock_for_global_variable, check_global_variable);
	std::cout << "'Waits' function leaves the standby state\n";
}

void Task1()
{
	std::thread data_preparation(DataPreparation);
	std::thread data_processing(DataProcessing);

	data_preparation.detach();
	data_processing.join();
}

void Task2()
{
	const int kThreadCount = 3;
	for (size_t i = 0; i < kThreadCount; i++)
	{
		std::thread wait_thread(Waits);
		wait_thread.detach();
	}

	std::thread awake_thread(Awake);
	awake_thread.join();
}

int main()
{
	Task1();
	//Task2();

	system("pause");
	return 0;
}