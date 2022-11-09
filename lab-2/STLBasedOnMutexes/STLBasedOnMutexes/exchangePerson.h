#pragma once

#include "someData.h"

#include <mutex>

class exchangePerson
{
public:
	static void JohnDoe(exchangePerson & person);
	static void JacobSmith(exchangePerson & person);
	static void Swap(exchangePerson & lhs, exchangePerson & rhs);

private:
	someData data_;
	std::mutex mutex_for_data_;
};
