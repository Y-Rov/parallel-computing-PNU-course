#include "someData.h"

#include <utility>

someData::someData(someData && other)
{
	*this = std::move(other);
}

void someData::SetAllFields(std::string name, std::string surname, std::string address, int age)
{
	name_ = name;
	surname_ = surname;
	address_ = address;
	age_ = age;
}

someData & someData::operator=(someData && other)
{
	if (this != &other) 
	{
		name_ = std::move(other.name_);
		surname_ = std::move(other.surname_);
		address_ = std::move(other.address_);
		age_ = std::move(other.age_);
	}
	return *this;
}

std::ostream & operator<<(std::ostream & os, const someData & data)
{
	os << "Name: " << data.name_ << ", Surname: " << data.surname_ << ", Age: " << data.age_
		<< ", Address: " << data.address_;
	return os;
}
