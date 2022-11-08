#include "MutexedList.h"

#include <thread>

int main()
{
	MutexedList list;

	const int kQuantityOfIterations = 10;
	int element_to_insert = 10;
	int element_to_find = 5;

	for (int i = 0; i < kQuantityOfIterations; i++)
	{
		std::thread first_thread_with_list(&MutexedList::AddToList, std::ref(list), element_to_insert++);
		std::thread second_thread_with_list(&MutexedList::ListContains, std::ref(list), element_to_find);
		first_thread_with_list.detach();
		second_thread_with_list.detach();
	}

	system("pause");
	return 0;
}