#include "MutexedList.h"

#include <thread>

void RunFirstTask(MutexedList& list)
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
	MutexedList list;
	RunFirstTask(list);

	system("pause");
	return 0;
}