#include <iostream>
#include <mutex>
#include <string>
#include <sstream>
#include <queue>

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

int main()
{
	std::thread data_preparation(DataPreparation);
	std::thread data_processing(DataProcessing);

	data_preparation.detach();
	data_processing.join();

	system("pause");
	return 0;
}