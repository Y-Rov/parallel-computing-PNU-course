#include "DataReader.h"
#include "DataGenerator.h"

#include <iostream>

int main()
{
	DataReader data_reader;
	std::vector<std::vector<int>> matrix_from_file = data_reader.read_matrix_from_file("M1_V2.txt");
	std::vector<int> vector_from_file = data_reader.read_vector_from_file("V1_V2.txt");

	std::cout << "Enter the matrix size:\n" << "Count of rows: ";
	size_t row_count, col_count;
	std::cin >> row_count;
	std::cout << "Count of columns: ";
	std::cin >> col_count;

	//std::vector<std::vector<int>> matrix_from_keyboard = data_reader.read_matrix_from_keyboard(row_count, col_count);
	//std::vector<int> vector_from_keyboard = data_reader.read_vector_from_keyboard(col_count);

	DataGenerator data_generator;
	
	std::vector<std::vector<int>> random_matrix = data_generator.generate_random_matrix(row_count, col_count);
	std::vector<int> random_column_vector = data_generator.generate_random_vector(col_count);

	return 0;
}