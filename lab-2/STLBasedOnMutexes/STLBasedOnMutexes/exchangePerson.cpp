#include "exchangePerson.h"

#include <iostream>

void exchangePerson::JohnDoe(exchangePerson & person)
{
	std::lock_guard<std::mutex> lock(person.mutex_for_data_);
	person.data_.SetAllFields("John", "Doe", "Unknown", 120);
}

void exchangePerson::JacobSmith(exchangePerson & person)
{
	std::lock_guard<std::mutex> lock(person.mutex_for_data_);
	person.data_.SetAllFields("Jacob", "Smith", "Known", 1);
}

void exchangePerson::Swap(exchangePerson & lhs, exchangePerson & rhs)
{
	if (&lhs == &rhs)
	{
		return;
	}
	/*
	// Task 1.2.2
	std::lock(lhs.mutex_for_data_, rhs.mutex_for_data_);
	std::lock_guard<std::mutex> lock_a(lhs.mutex_for_data_, std::adopt_lock);
	std::lock_guard<std::mutex> lock_b(rhs.mutex_for_data_, std::adopt_lock);
	*/
	// Task 1.2.3
	std::unique_lock<std::mutex> lock_a(lhs.mutex_for_data_, std::defer_lock);
	std::unique_lock<std::mutex> lock_b(rhs.mutex_for_data_, std::defer_lock);
	std::lock(lock_a, lock_b);
	std::cout << "Before Swap:\n" << lhs.data_ << '\n' << rhs.data_ << '\n';
	std::swap(lhs.data_, rhs.data_);
	std::cout << "After Swap:\n" << lhs.data_ << '\n' << rhs.data_ << '\n';
}
