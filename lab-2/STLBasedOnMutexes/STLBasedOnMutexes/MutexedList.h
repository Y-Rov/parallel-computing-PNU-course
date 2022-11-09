#pragma once

#include <list>
#include <mutex>

class MutexedList
{
public:
	MutexedList() = default;
	~MutexedList() = default;

	void AddToList(int element_to_insert);
	bool ListContains(int element_to_find);

private:
	std::list<int> data_;
	std::mutex mutex_for_data_;
};
