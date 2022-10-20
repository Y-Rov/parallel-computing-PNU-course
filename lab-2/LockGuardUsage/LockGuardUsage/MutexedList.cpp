#include "MutexedList.h"

#include <algorithm>
#include <iostream>
#include <string>

void MutexedList::AddToList(int element)
{
	mutex_for_data_.lock();

	data_.push_back(element);
	std::cout << "Element " << element << " was added to list\n";

	mutex_for_data_.unlock();
}

bool MutexedList::ListContains(int element)
{
	mutex_for_data_.lock();

	bool found = std::find(data_.begin(), data_.end(), element) != data_.end();
	std::string message = found ? "Element " + std::to_string(element) + " was found in list"
		: "Element " + std::to_string(element) + " wasn't found in list";
	std::cout << message << '\n';

	mutex_for_data_.unlock();
	return found;
}