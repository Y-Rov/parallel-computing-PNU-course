#include "MutexedList.h"

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

void RunThirdTask(MutexedList& list)
{
	int element_to_insert = 10;
	int element_to_find = 5;
	std::thread first_thread_with_list(&MutexedList::AddToList, std::ref(list), element_to_insert);
	std::thread second_thread_with_list(&MutexedList::ListContains, std::ref(list), element_to_find);

	first_thread_with_list.detach();
	second_thread_with_list.detach();
}

int main()
{
	// Task 1
	std::thread first_thread(Thread1);
	std::thread second_thread(Thread2);

	// Task 2
	first_thread.detach();
	second_thread.detach();

	// Task 3
	MutexedList list;
	RunThirdTask(list);

	system("pause");
	return 0;
}