#pragma once

#include <vector>

class DataGenerator
{
public:
	std::vector<std::vector<int>> generate_random_matrix(size_t row_count, size_t col_count);
	std::vector<int> generate_random_vector(size_t vector_size);
};

