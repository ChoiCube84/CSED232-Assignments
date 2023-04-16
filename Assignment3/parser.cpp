#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

#include "parser.hpp"

using namespace std;

vector<int> parser::load_image(const char* path)
{
	ifstream myfile;
	string text, number;
	vector<int> result;

	myfile.open(path);
	myfile >> text;

	stringstream stream(text);
	
	while (getline(stream, number, '|'))
		result.emplace_back(stoi(number));

	myfile.close();

	return result;
}

vector<string> parser::load_config(const char* path)
{
	ifstream myfile;
	string text, option;
	vector<string> result;

	myfile.open(path);
	myfile >> text;

	stringstream stream(text);

	while (getline(stream, option, '|'))
		result.emplace_back(option);

	myfile.close();

	return result;
}

void parser::write_result(const char* path, const string& contents)
{
	ofstream myfile;
	myfile.open(path);
	myfile << contents;
	myfile.close();
}
