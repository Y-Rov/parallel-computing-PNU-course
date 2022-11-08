#include "someData.h"

void someData::SetAllFields(std::string name, std::string surname, std::string address, int age)
{
	name_ = name;
	surname_ = surname;
	address_ = address;
	age_ = age;
}

std::ostream & operator<<(std::ostream & os, const someData & data)
{
	os << "Name: " << data.name_ << ", Surname: " << data.surname_ << ", Age: " << data.age_
		<< ", Address: " << data.address_;
	return os;
}
