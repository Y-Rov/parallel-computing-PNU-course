#include "MutexedList.h"

#include <algorithm>
#include <iostream>
#include <string>

void MutexedList::AddToList(int element_to_insert)
{
	std::lock_guard<std::mutex> lock(mutex_for_data_);

	data_.push_back(element_to_insert);
	std::cout << "Element " << element_to_insert << " was added to list\n";
}

bool MutexedList::ListContains(int element_to_find)
{
	std::lock_guard<std::mutex> lock(mutex_for_data_);

	bool found = std::find(data_.begin(), data_.end(), element_to_find) != data_.end();
	std::string message = found ? "Element " + std::to_string(element_to_find) + " was found in list"
								: "Element " + std::to_string(element_to_find) + " wasn't found in list";
	std::cout << message << '\n';
	return found;
}
