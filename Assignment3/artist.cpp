#include <iostream>
#include <vector>
#include <string>

#include "artist.hpp"

using namespace std;

artist::artist(int width, int height, const vector<int>& vals) : width(width), height(height), vals(vals) {}

char artist::mapper(int x, int y) 
{
	return 0;
}

classic::classic(int width, int height, const vector<int>& vals) : artist(width, height, vals) {}

char classic::mapper(int x, int y)
{
	int pixel = vals[x + width * y];

	pixel /= 17;

	switch (pixel)
	{
	case 0:
		return '@';
		break;
	case 1:
		return '&';
		break;
	case 2:
		return '%';
		break;
	case 3:
		return 'W';
		break;
	case 4:
		return 'X';
		break;
	case 5:
		return 'A';
		break;
	case 6:
		return 'H';
		break;
	case 7:
		return 'O';
		break;
	case 8:
		return 'T';
		break;
	case 9:
		return '*';
		break;
	case 10:
		return '^';
		break;
	case 11:
		return '+';
		break;
	case 12:
		return '-';
		break;
	case 13:
		return '.';
		break;
	default:
		return ' ';
		break;
	}
}

iclassic::iclassic(int width, int height, const vector<int>& vals) : artist(width, height, vals) {}

char iclassic::mapper(int x, int y)
{
	int pixel = vals[x + width * y];

	pixel /= 17;

	switch (pixel)
	{
	case 0:
		return ' ';
		break;
	case 1:
		return '.';
		break;
	case 2:
		return '-';
		break;
	case 3:
		return '+';
		break;
	case 4:
		return '^';
		break;
	case 5:
		return '*';
		break;
	case 6:
		return 'T';
		break;
	case 7:
		return 'O';
		break;
	case 8:
		return 'H';
		break;
	case 9:
		return 'A';
		break;
	case 10:
		return 'X';
		break;
	case 11:
		return 'W';
		break;
	case 12:
		return '%';
		break;
	case 13:
		return '&';
		break;
	default:
		return '@';
		break;
	}
}

sobelx::sobelx(int width, int height, const vector<int>& vals) : artist(width, height, vals) {}

char sobelx::mapper(int x, int y)
{
	int origin = vals[x + width * y];

	if (x < width - 1)
	{
		int right = vals[(x + 1) + width * y];
		int offset = right - origin;

		if (offset < 50 && offset > -50) return ' ';
		else return '|';
	}
	else return ' ';
}

sobely::sobely(int width, int height, const vector<int>& vals) : artist(width, height, vals) {}

char sobely::mapper(int x, int y)
{
	int origin = vals[x + width * y];

	if (y < height - 1)
	{
		int down = vals[x + width * (y + 1)];
		int offset = down - origin;

		if (offset < 50 && offset > -50) return ' ';
		else return '-';
	}
	else return ' ';
}

gradient::gradient(int width, int height, const vector<int>& vals) : artist(width, height, vals) {}

char gradient::mapper(int x, int y)
{
	int origin = vals[x + width * y];

	bool x_check = false;
	bool y_check = false;

	if (x < width - 1)
	{
		int right = vals[(x + 1) + width * y];
		int offset = right - origin;

		if (offset < 50 && offset > -50) x_check = false;
		else x_check = true;
	}
	else x_check = false;

	if (y < height - 1)
	{
		int down = vals[x + width * (y + 1)];
		int offset = down - origin;

		if (offset < 50 && offset > -50) y_check = false;
		else y_check = true;
	}
	else y_check = false;

	if (x_check)
	{
		if (y_check) return '+';
		else return '|';
	}

	else
	{
		if (y_check) return '-';
		else return ' ';
	}
}