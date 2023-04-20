#include <vector>

#include "artist.hpp"

using namespace std;

// artist constructor initializes the artist object with dimensions and pixel values
artist::artist(int width, int height, const vector<int>& vals) : width(width), height(height), vals(vals) {}

// Getter methods for artist class
int artist::get_width() const { return width; }
int artist::get_height() const { return height; }
int artist::get_pixel(int index) const { return vals[index]; }

// classic constructor initializes the classic artist object with dimensions and pixel values
classic::classic(int width, int height, const vector<int>& vals) : artist(width, height, vals) {}

// classic mapper function generates the character representation for a pixel
char classic::mapper(int x, int y)
{
	int width = get_width();
	int pixel = get_pixel(x + width * y);

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

// iclassic constructor initializes the iclassic artist object with dimensions and pixel values
iclassic::iclassic(int width, int height, const vector<int>& vals) : artist(width, height, vals) {}

// iclassic mapper function generates the inverted character representation for a pixel
char iclassic::mapper(int x, int y)
{
	int width = get_width();
	int pixel = get_pixel(x + width * y);

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

// sobelx constructor initializes the sobelx artist object with dimensions and pixel values
sobelx::sobelx(int width, int height, const vector<int>& vals) : artist(width, height, vals) {}

// sobelx mapper function generates the character representation for a pixel based on Sobel X edge detection
char sobelx::mapper(int x, int y)
{
	int width = get_width();
	int index = x + width * y;

	int origin = get_pixel(index);

	if (x < width - 1)
	{
		int right = get_pixel(index + 1);
		int offset = right - origin;

		if (offset < 50 && offset > -50) return ' ';
		else return '|';
	}
	else return ' ';
}

// sobely constructor initializes the sobely artist object with dimensions and pixel values
sobely::sobely(int width, int height, const vector<int>& vals) : artist(width, height, vals) {}

// sobely mapper function generates the character representation for a pixel based on Sobel Y edge detection
char sobely::mapper(int x, int y)
{
	int width = get_width();
	int height = get_height();
	int index = x + width * y;

	int origin = get_pixel(index);

	if (y < height - 1)
	{
		int down = get_pixel(index + width);
		int offset = down - origin;

		if (offset < 50 && offset > -50) return ' ';
		else return '-';
	}
	else return ' ';
}

// gradient constructor initializes the gradient artist object with dimensions and pixel values
gradient::gradient(int width, int height, const vector<int>& vals) : artist(width, height, vals) {}

// gradient mapper function generates the character representation for a pixel based on gradient edge detection
char gradient::mapper(int x, int y)
{
	int width = get_width();
	int height = get_height();
	int index = x + width * y;

	int origin = get_pixel(index);

	bool x_check = false;
	bool y_check = false;

	if (x < width - 1)
	{
		int right = get_pixel(index + 1);
		int offset = right - origin;

		if (offset < 50 && offset > -50) x_check = false;
		else x_check = true;
	}
	else x_check = false;

	if (y < height - 1)
	{
		int down = get_pixel(index + width);
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