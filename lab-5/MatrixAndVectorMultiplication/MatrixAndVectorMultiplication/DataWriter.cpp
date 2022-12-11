#include "DataWriter.h"

#include <fstream>
#include <iostream>

size_t DataWriter::ROW_MAX_VALUE = 12;

void DataWriter::write_matrix_to_file(const std::string& path, const std::vector<std::vector<int>>& matrix)
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
		std::cout << "The matrix has been written to the file successfully!\n";
	}
}

void DataWriter::write_vector_to_file(const std::string& path, const std::vector<int>& column_vector)
{
	auto open_mode = std::ios_base::app;
	int difference = path.compare("Result.txt");
	if (difference == 0)
	{
		open_mode = std::ios_base::out;
	}

	std::ofstream file_to_write(path, open_mode);
	if (file_to_write.is_open())
	{
		if (difference != 0)
		{
			file_to_write << '\n';
		}
		
		for (size_t i = 0; i < column_vector.size(); i++)
		{
			file_to_write << column_vector[i] << '\n';
		}

		file_to_write.close();
		std::cout << "The vector has been written to the file successfully!\n";
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
