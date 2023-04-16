#ifndef __ARTIST_HPP__
#define __ARTIST_HPP__

#include <vector>

using namespace std;

class artist
{
public:
	int width;
	int height;
	vector<int> vals;

	artist(int, int, const vector<int>&);
	virtual char mapper(int, int);
};

class classic : public artist
{
public:
	classic(int, int, const vector<int>&);
	char mapper(int, int) override;
};

class iclassic : public artist
{
public:
	iclassic(int, int, const vector<int>&);
	char mapper(int, int) override;
};

class sobelx : public artist
{
public:
	sobelx(int, int, const vector<int>&);
	char mapper(int, int) override;
};

class sobely : public artist
{
public:
	sobely(int, int, const vector<int>&);
	char mapper(int, int) override;
};

class gradient : public artist
{
public:
	gradient(int, int, const vector<int>&);
	char mapper(int, int) override;
};

#endif // !__ARTIST_HPP__
