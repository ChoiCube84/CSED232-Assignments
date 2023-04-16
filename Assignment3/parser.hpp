#ifndef __PARSER_HPP__
#define __PARSER_HPP__

#include <vector>
#include <string>

using namespace std;

class parser
{
public:
	vector<int> load_image(const char*);
	vector<string> load_config(const char*);
	void write_result(const char*, const string&);
};

#endif // !__PARSER_HPP__
