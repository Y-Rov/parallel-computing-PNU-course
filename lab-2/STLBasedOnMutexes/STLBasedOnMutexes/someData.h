#pragma once
#include <string>

class someData
{
public:
	someData() = default;
	~someData() = default;

	void SetAllFields(std::string name, std::string surname, std::string address, int age);
	friend std::ostream& operator<<(std::ostream& os, const someData& data);

private:
	std::string name_;
	std::string surname_;
	std::string address_;
	int age_;
};

