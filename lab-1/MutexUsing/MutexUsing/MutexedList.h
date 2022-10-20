#pragma once

#include <list>
#include <mutex>

class MutexedList
{
public:
	MutexedList() = default;
	~MutexedList() = default;

	// Task 3
	void AddToList(int element);	
	bool ListContains(int element);

private:
	std::list<int> data_;
	const int kCounterValue = 10;
	// Task 4
	std::mutex mutex_for_data_;
};

