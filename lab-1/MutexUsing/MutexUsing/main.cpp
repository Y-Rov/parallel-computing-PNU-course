#include <iostream>
#include <thread>

// Task 1
void Thread1()
{
	std::cout << 1 << '\n';
}

// Task 1
void Thread2()
{
	std::cout << 2 << '\n';
}

int main()
{
	// Task 1
	std::thread first_thread(Thread1);
	std::thread second_thread(Thread2);

	// Task 2
	first_thread.detach();
	second_thread.detach();

	system("pause");
	return 0;
}