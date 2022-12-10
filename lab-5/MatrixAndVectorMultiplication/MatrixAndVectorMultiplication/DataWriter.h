#pragma once

#include <string>
#include <vector>

class DataWriter
{
public:
	void write_matrix_to_file(const std::string path, const std::vector<std::vector<int>>& matrix);
	void write_vector_to_file(const std::string path, const std::vector<int>& column_vector);
	void write_matrix_to_screen(const std::vector<std::vector<int>>& matrix);
	void write_vector_to_screen(const std::vector<int>& column_vector);
};

