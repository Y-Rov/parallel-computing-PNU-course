#pragma once

#include <string>
#include <vector>

class DataReader
{
public:
	std::vector<std::vector<int>> read_matrix_from_file(const std::string path);
	std::vector<int> read_vector_from_file(const std::string path);
	std::vector<std::vector<int>> read_matrix_from_keyboard(size_t row_count, size_t col_count);
	std::vector<int> read_vector_from_keyboard(size_t vector_size);
};

