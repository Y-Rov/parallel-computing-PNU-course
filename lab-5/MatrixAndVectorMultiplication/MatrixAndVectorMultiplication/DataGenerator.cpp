#include "DataGenerator.h"
#include "DataWriter.h"

#include <cstdlib>
#include <ctime>
#include <iostream>

std::vector<std::vector<int>> DataGenerator::generate_random_matrix(size_t row_count, size_t col_count)
{
	std::vector<std::vector<int>> matrix(row_count);
	std::srand(std::time(NULL));
	for (size_t i = 0; i < row_count; i++)
	{
		std::vector<int> matrix_row(col_count);
		for (size_t j = 0; j < col_count; j++)
		{
			matrix_row[j] = std::rand() % 100;
		}
		matrix[i] = matrix_row;
	}

	DataWriter data_writer;
	if (row_count <= DataWriter::ROW_MAX_VALUE && col_count <= DataWriter::ROW_MAX_VALUE)
	{
		std::cout << "Random generated matrix:\n";
		data_writer.write_matrix_to_screen(matrix);
	}
	else
	{
		data_writer.write_matrix_to_file("Input_Data.txt", matrix);
	}

	return matrix;
}

std::vector<int> DataGenerator::generate_random_vector(size_t vector_size)
{
	std::vector<int> column_vector(vector_size);
	for (size_t i = 0; i < vector_size; i++)
	{
		column_vector[i] = std::rand() % 100;
	}

	DataWriter data_writer;
	if (vector_size <= DataWriter::ROW_MAX_VALUE)
	{
		std::cout << "Random generated vector:\n";
		data_writer.write_vector_to_screen(column_vector);
	}
	else
	{
		data_writer.write_vector_to_file("Input_Data.txt", column_vector);
	}

	return column_vector;
}
