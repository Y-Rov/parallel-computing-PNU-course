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

std::vector<int> CalculateMultiplication(std::vector<std::vector<int>>& matrix, std::vector<int> column_vector)
{
	const size_t kQuantityOfThreads = 6;
	const size_t kQuantityOfRowStripes = matrix.size() / kQuantityOfThreads;
	std::vector<std::future<std::vector<int>>> future_results(kQuantityOfThreads);
	for (size_t i = 0, counter = 0; i < kQuantityOfThreads; i++, counter += kQuantityOfRowStripes)
	{
		auto begin_iterator = matrix.begin() + counter;
		auto end_iterator = counter < kQuantityOfThreads - 1
			? begin_iterator + kQuantityOfRowStripes
			: matrix.end();

		future_results[i] = std::async(std::launch::async, RowMultiplication, begin_iterator, end_iterator, column_vector);
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
	

int main()
{
	DataReader data_reader;
	std::vector<std::vector<int>> matrix_from_file = data_reader.read_matrix_from_file("M1_V2.txt");
	std::vector<int> vector_from_file = data_reader.read_vector_from_file("V1_V2.txt");

	std::vector<int> result_vector = CalculateMultiplication(matrix_from_file, vector_from_file);

	DataWriter data_writer;
	if (result_vector.size() <= DataGenerator::ROW_MAX)
	{
		data_writer.write_vector_to_screen(result_vector);
	}
	else
	{
		data_writer.write_vector_to_file("Result.txt", result_vector);
	}

	/*std::cout << "Enter the matrix size:\n" << "Count of rows: ";
	size_t row_count, col_count;
	std::cin >> row_count;
	std::cout << "Count of columns: ";
	std::cin >> col_count;*/

	//std::vector<std::vector<int>> matrix_from_keyboard = data_reader.read_matrix_from_keyboard(row_count, col_count);
	//std::vector<int> vector_from_keyboard = data_reader.read_vector_from_keyboard(col_count);

	/*DataGenerator data_generator;
	
	std::vector<std::vector<int>> random_matrix = data_generator.generate_random_matrix(row_count, col_count);
	std::vector<int> random_column_vector = data_generator.generate_random_vector(col_count);*/
	system("pause");
	return 0;
}