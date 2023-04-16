#include <iostream>
#include <vector>
#include <string>

#include "drawer.hpp"

drawer::drawer(artist* style) : style(style) {}

string drawer::draw() 
{ 
	string result = "";

	for (int j = 0; j < style->height; j++)
	{
		for (int i = 0; i < style->width; i++)
			result += style->mapper(i, j);

		result += '\n';
	}

	return result;
}

downsample::downsample(artist* style) : drawer(style) {}

string downsample::draw()
{
	string result = "";

	for (int j = 0; j < style->height / 2; j++)
	{
		for (int i = 0; i < style->width / 2; i++)
			result += style->mapper(i * 2, j * 2);
		
		result += '\n';
	}

	return result;
}

upsample::upsample(artist* style) : drawer(style) {}

string upsample::draw()
{
	string result = "";

	for (int j = 0; j < style->height * 2; j++)
	{
		for (int i = 0; i < style->width * 2; i++)
			result += style->mapper(i / 2, j / 2);

		result += '\n';
	}

	return result;
}

scale::scale(artist* style, int x, int y) : drawer(style), x(x), y(y) {}

string scale::draw()
{
	string result = "";

	int scaled_width = style->width;
	int scaled_height = style->height;
	
	if (x >= 0)
		scaled_width *= x;
	else
		scaled_width /= -x;

	if (y >= 0)
		scaled_height *= y;
	else
		scaled_height /= -y;

	for (int j = 0; j < scaled_height; j++)
	{
		for (int i = 0; i < scaled_width; i++)
		{
			int scaled_i = i;
			int scaled_j = j;

			if (x > 0)
				scaled_i /= x;
			else
				scaled_i *= -x;

			if (y > 0)
				scaled_j /= y;
			else
				scaled_j *= -y;

			result += style->mapper(scaled_i, scaled_j);
		}
		result += '\n';
	}

	return result;
}