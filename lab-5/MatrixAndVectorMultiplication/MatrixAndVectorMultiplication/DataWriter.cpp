#include "DataWriter.h"

#include <fstream>
#include <iostream>

size_t DataWriter::ROW_MAX_VALUE = 12;

void DataWriter::write_matrix_to_file(const std::string path, const std::vector<std::vector<int>>& matrix)
{
	std::ofstream input_data_file(path);
	if (input_data_file.is_open())
	{
		for (size_t i = 0; i < matrix.size(); i++)
		{
			std::vector<int> matrix_row = matrix[i];
			for (size_t j = 0; j < matrix_row.size(); j++)
			{
				if (j == matrix_row.size() - 1)
				{
					input_data_file << matrix_row[j] << '\n';
				}
				else
				{
					input_data_file << matrix_row[j] << ' ';
				}
			}
		}
		input_data_file.close();
	}
}

void DataWriter::write_vector_to_file(const std::string path, const std::vector<int>& column_vector)
{
	std::ofstream input_data_file(path, std::ios_base::app);
	if (input_data_file.is_open())
	{
		input_data_file << '\n';
		for (size_t i = 0; i < column_vector.size(); i++)
		{
			input_data_file << column_vector[i] << '\n';
		}

		input_data_file.close();
	}
}

void DataWriter::write_matrix_to_screen(const std::vector<std::vector<int>>& matrix)
{
	for (size_t i = 0; i < matrix.size(); i++)
	{
		std::vector<int> matrix_row = matrix[i];
		for (size_t j = 0; j < matrix_row.size(); j++)
		{
			if (j == matrix_row.size() - 1)
			{
				std::cout << matrix_row[j] << '\n';
			}
			else
			{
				std::cout << matrix_row[j] << ' ';
			}
		}
	}
}

void DataWriter::write_vector_to_screen(const std::vector<int>& column_vector)
{
	for (size_t i = 0; i < column_vector.size(); i++)
	{
		std::cout << column_vector[i] << '\n';
	}
}
