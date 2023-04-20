#include <fstream>
#include <sstream>
#include <vector>
#include <string>

#include "parser.hpp"

using namespace std;

// Loads an image file, reads its contents, and returns pixel values as a vector of integers
vector<int> parser::load_image(const char* path)
{
	ifstream myfile;
	string text, number;
	vector<int> result;

	// Open the file and read its contents into a string
	myfile.open(path);
	myfile >> text;

	// Use a stringstream to split the string by '|' delimiter and convert to integers
	stringstream stream(text);
	while (getline(stream, number, '|'))
		result.emplace_back(stoi(number));

	myfile.close();

	return result;
}

// Loads a configuration file, reads its contents, and returns them as a vector of strings
vector<string> parser::load_config(const char* path)
{
	ifstream myfile;
	string text, option;
	vector<string> result;

	// Open the file and read its contents into a string
	myfile.open(path);
	myfile >> text;

	// Use a stringstream to split the string by '|' delimiter
	stringstream stream(text);
	while (getline(stream, option, '|'))
		result.emplace_back(option);

	myfile.close();

	return result;
}

// Writes the result of an image transformation to a file
void parser::write_result(const char* path, const string& contents)
{
	ofstream myfile;
	myfile.open(path);
	myfile << contents;
	myfile.close();
}
