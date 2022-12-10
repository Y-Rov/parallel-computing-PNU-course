#include "DataReader.h"

#include <fstream>
#include <iostream>
#include <sstream>

std::vector<std::vector<int>> DataReader::read_matrix_from_file(const std::string path)
{
	std::ifstream matrix_file(path);
	std::vector<std::vector<int>> matrix;
	if (matrix_file.is_open())
	{
		std::string line;
		std::istringstream stream_for_line;
		while (std::getline(matrix_file, line))
		{
			stream_for_line.clear();
			stream_for_line.str(line);
			stream_for_line.seekg(0);
			std::vector<int> matrix_row;
			int number;
			while (stream_for_line >> number)
			{
				matrix_row.push_back(number);
			}
			matrix.push_back(matrix_row);
		}
		matrix_file.close();
	}
	
	return matrix;
}

std::vector<int> DataReader::read_vector_from_file(const std::string path)
{
	std::ifstream vector_file(path);
	std::vector<int> column_vector;
	if (vector_file.is_open())
	{
		int number;
		while (vector_file >> number)
		{
			column_vector.push_back(number);
		}
		vector_file.close();
	}
	
	return column_vector;
}

std::vector<std::vector<int>> DataReader::read_matrix_from_keyboard(size_t row_count, size_t col_count)
{
	std::vector<std::vector<int>> matrix(row_count);
	std::cout << "Enter your matrix:\n";
	for (size_t i = 0; i < row_count; i++)
	{
		std::vector<int> matrix_row(col_count);
		int number;
		for (size_t j = 0; j < col_count; j++)
		{
			std::cin >> number;
			matrix_row[j] = number;
		}
		matrix[i] = matrix_row;
	}

	return matrix;
}

std::vector<int> DataReader::read_vector_from_keyboard(size_t vector_size)
{
	std::vector<int> column_vector(vector_size);
	int number;
	std::cout << "Enter your column vector:\n";
	for (size_t i = 0; i < vector_size; i++)
	{
		std::cin >> number;
		column_vector[i] = number;
	}

	return column_vector;
}
