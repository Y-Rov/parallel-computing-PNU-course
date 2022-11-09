#pragma once

#include <string>

class someData
{
public:
	someData() = default;
	~someData() = default;

	someData(someData && other);

	void SetAllFields(std::string name, std::string surname, std::string address, int age);

	friend std::ostream & operator<<(std::ostream & os, const someData & data);
	someData & operator=(someData && other);

private:
	std::string name_;
	std::string surname_;
	std::string address_;
	int age_;
};
