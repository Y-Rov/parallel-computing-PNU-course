#pragma once

#include <list>

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
};

