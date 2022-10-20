#pragma once

#include <list>
#include <mutex>

class MutexedList
{
public:
	MutexedList() = default;
	~MutexedList() = default;

	void AddToList(int element);
	bool ListContains(int element);

private:
	std::list<int> data_;
	std::mutex mutex_for_data_;
};

