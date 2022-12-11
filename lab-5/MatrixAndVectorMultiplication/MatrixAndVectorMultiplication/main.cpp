#include "DataReader.h"
#include "DataGenerator.h"
#include "DataWriter.h"

#include <future>
#include <iostream>

std::vector<int> RowMultiplication(std::vector<std::vector<int>>::iterator begin_stripe,
	std::vector<std::vector<int>>::iterator end_stripe, std::vector<int> column_vector)
{
	std::vector<int> result(end_stripe - begin_stripe);
	int i = 0;
	for (auto iter = begin_stripe; iter != end_stripe; iter++, i++)
	{
		std::vector<int> stripe = *iter;
		result[i] = 0;
		for (size_t j = 0; j < column_vector.size(); j++)
		{
			result[i] += stripe[j] * column_vector[j];
		}
	}

	return result;
}

std::vector<int> CalculateRowMultiplication(std::vector<std::vector<int>>& matrix, std::vector<int> column_vector)
{
	const size_t kQuantityOfThreads = 6;
	const size_t kQuantityOfRowStripes = matrix.size() / kQuantityOfThreads;
	std::vector<std::future<std::vector<int>>> future_results(kQuantityOfThreads);
	for (size_t i = 0, counter = 0; i < kQuantityOfThreads; i++, counter += kQuantityOfRowStripes)
	{
		auto begin_iterator = matrix.begin() + counter;
		auto end_iterator = i < kQuantityOfThreads - 1 ? begin_iterator + kQuantityOfRowStripes
							: matrix.end();

		future_results[i] = std::async(std::launch::async, RowMultiplication, begin_iterator, end_iterator,
			column_vector);
	}

	std::vector<int> result_vector(matrix.size());
	for (size_t i = 0, k = 0; i < future_results.size(); i++)
	{
		std::vector<int> result = future_results[i].get();
		for (size_t j = 0; j < result.size(); j++)
		{
			result_vector[k++] = result[j];
		}
	}

	return result_vector;
}
	
std::vector<std::vector<int>> ColumnMultiplication(const std::vector<std::vector<int>>& matrix,
	std::vector<int> column_vector, size_t start_column_index, size_t end_column_index)
{
	std::vector<std::vector<int>> temp_vectors(matrix.size());
	for (size_t j = start_column_index; j < end_column_index; j++)
	{
		for (size_t i = 0; i < matrix.size(); i++)
		{
			int temp_value = matrix[i][j] * column_vector[j];
			temp_vectors[i].push_back(temp_value);
		}
	}

	return temp_vectors;
}

std::vector<int> CalculateColumnMultiplication(const std::vector<std::vector<int>>& matrix, std::vector<int> column_vector)
{
	const size_t kQuantityOfThreads = 10;
	const size_t kQuantityOfColumnStripes = matrix[0].size() / kQuantityOfThreads;
	std::vector<std::future<std::vector<std::vector<int>>>> future_results(kQuantityOfThreads);
	for (size_t i = 0, counter = 0; i < kQuantityOfThreads; i++, counter += kQuantityOfColumnStripes)
	{
		size_t start_index = counter;
		size_t end_index = i < kQuantityOfThreads - 1 ? counter + kQuantityOfColumnStripes
							: matrix[0].size();

		future_results[i] = std::async(std::launch::async, ColumnMultiplication, std::cref(matrix),
			column_vector, start_index, end_index);
	}

	std::vector<int> result_vector(matrix.size(), 0);
	for (size_t i = 0; i < future_results.size(); i++)
	{
		std::vector<std::vector<int>> temp_result = future_results[i].get();
		for (size_t j = 0, l = 0; j < temp_result.size(); j++, l++)
		{
			for (size_t k = 0; k < temp_result[j].size(); k++)
			{
				result_vector[l] += temp_result[j][k];
			}
		}
	}

	return result_vector;
}

void GetMatrixSizeFromUser(size_t& row_count, size_t& col_count)
{
	std::cout << "Enter the matrix size:\n" << "Count of rows: ";
	std::cin >> row_count;
	std::cout << "Count of columns: ";
	std::cin >> col_count;
}

void DataPreparation(const std::string &path_to_matrix, const std::string &path_to_column_vector,
	std::vector<std::vector<int>>& matrix, std::vector<int>& column_vector)
{
	int operation_value;
	std::cout << "Choose the type of getting data:\nFrom file (1)\nFrom keyboard (2)\nRandom generator (3)\nYour choice: ";
	std::cin >> operation_value;

	DataReader data_reader;
	size_t row_count, col_count;
	switch (operation_value)
	{
	case 1:
		matrix = data_reader.read_matrix_from_file(path_to_matrix);
		column_vector = data_reader.read_vector_from_file(path_to_column_vector);
		break;
	case 2:
		GetMatrixSizeFromUser(row_count, col_count);
		matrix = data_reader.read_matrix_from_keyboard(row_count, col_count);
		column_vector = data_reader.read_vector_from_keyboard(col_count);
		break;
	case 3:
		GetMatrixSizeFromUser(row_count, col_count);
		DataGenerator data_generator;
		matrix = data_generator.generate_random_matrix(row_count, col_count);
		column_vector = data_generator.generate_random_vector(col_count);
	default:
		break;
	}
}

void DataProcessing(std::vector<std::vector<int>>& matrix, const std::vector<int>& column_vector,
	int type_of_multiplication)
{
	std::vector<int> result_vector;

	switch (type_of_multiplication)
	{
	case 1:
		result_vector = CalculateRowMultiplication(matrix, column_vector);
		break;
	case 2:
		result_vector = CalculateColumnMultiplication(matrix, column_vector);
		break;
	default:
		break;
	}

	DataWriter data_writer;
	if (result_vector.size() <= DataWriter::ROW_MAX_VALUE)
	{
		std::cout << "Result vector:\n";
		data_writer.write_vector_to_screen(result_vector);
	}
	else
	{
		data_writer.write_vector_to_file("Result.txt", result_vector);
	}
}

int main()
{
	std::vector<std::vector<int>> matrix;
	std::vector<int> column_vector;
	int type_of_multiplication;

	std::cout << "Choose the type of matrix and column vector multiplication\nBy rows (1)\nBy columns (2)\nYour choice: ";
	std::cin >> type_of_multiplication;
	switch (type_of_multiplication)
	{
	case 1:
		DataPreparation("M1_V2.txt", "V1_V2.txt", matrix, column_vector);
		break;
	case 2:
		DataPreparation("M2_V2.txt", "V2_V2.txt", matrix, column_vector);
		break;
	default:
		break;
	}

	DataProcessing(matrix, column_vector, type_of_multiplication);

	system("pause");
	return 0;
}