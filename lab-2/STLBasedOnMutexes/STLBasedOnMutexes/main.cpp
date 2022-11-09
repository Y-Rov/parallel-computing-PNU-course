#include "MutexedList.h"
#include "exchangePerson.h"

#include <thread>

void Task1()
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
}

void Tasks2And3()
{
	exchangePerson person1, person2;

	std::thread first_thread_with_person(&exchangePerson::JohnDoe, std::ref(person1));
	first_thread_with_person.detach();

	std::thread second_thread_with_person(&exchangePerson::JacobSmith, std::ref(person2));
	second_thread_with_person.detach();

	std::thread third_thread_with_person(&exchangePerson::JohnDoe, std::ref(person1));
	third_thread_with_person.detach();

	std::thread fourth_thread_with_person(&exchangePerson::JacobSmith, std::ref(person2));
	fourth_thread_with_person.detach();

	std::thread person_swap_thread(&exchangePerson::Swap, std::ref(person1), std::ref(person2));
	person_swap_thread.join();
}

int main()
{
	//Task1();
	Tasks2And3();

	return 0;
}
