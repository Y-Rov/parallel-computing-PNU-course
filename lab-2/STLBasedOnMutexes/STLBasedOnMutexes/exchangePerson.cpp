#include "exchangePerson.h"

#include <iostream>

void exchangePerson::JohnDoe(exchangePerson & person)
{
	std::lock_guard<std::mutex> lock(mutex_for_data_);
	person.data_.SetAllFields("John", "Doe", "Unknown", 120);
}

void exchangePerson::JacobSmith(exchangePerson & person)
{
	person.data_.SetAllFields("Jacob", "Smith", "Known", 1);
}

void exchangePerson::Swap(exchangePerson & lhs, exchangePerson & rhs)
{
	if (&lhs == &rhs)
	{
		return;
	}

	std::lock(lhs.mutex_for_data_, rhs.mutex_for_data_);
	std::lock_guard<std::mutex> lock_a(lhs.mutex_for_data_, std::adopt_lock);
	std::lock_guard<std::mutex> lock_b(rhs.mutex_for_data_, std::adopt_lock);
	std::cout << "Before Swap:\n" << lhs.data_ << '\n' << rhs.data_ << '\n';
	std::swap(lhs.data_, rhs.data_);
	std::cout << "After Swap:\n" << lhs.data_ << '\n' << rhs.data_ << '\n';
}
