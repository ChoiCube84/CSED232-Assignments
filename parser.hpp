#ifndef __PARSER_HPP__
#define __PARSER_HPP__

#include <vector>
#include <string>
using namespace std;

// The parser class is responsible for handling file input and output operations
class parser
{
public:
    // Loads an image file and returns its pixel values as a vector of integers
    vector<int> load_image(const char*);

    // Loads a configuration file and returns its contents as a vector of strings
    vector<string> load_config(const char*);

    // Writes the result of an image transformation to a file
    void write_result(const char*, const string&);
};

#endif // !__PARSER_HPP__