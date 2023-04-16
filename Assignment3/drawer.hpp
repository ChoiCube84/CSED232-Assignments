#ifndef __DRAWER_HPP__
#define __DRAWER_HPP__

#include <string>
#include "artist.hpp"

class drawer
{
public:
	artist* style;

	drawer(artist*);
	virtual string draw();
};

class downsample : public drawer
{
public:
	downsample(artist*);
	string draw() override;
};

class upsample : public drawer
{
public:
	upsample(artist*);
	string draw() override;
};

class scale : public drawer
{
public:
	int x, y;

	scale(artist*, int, int);
	string draw() override;
};

#endif // !__DRAWER_HPP__
