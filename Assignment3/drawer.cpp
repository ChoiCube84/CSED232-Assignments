#include <string>

#include "drawer.hpp"

// Constructor initializes the drawer object with a specific artist style
drawer::drawer(artist* style) : style(style) {}

// Protected method for derived classes to access the style
artist* drawer::get_style() const
{
	return style;
}

// Generates the output string by applying the artist's mapping to each pixel
string drawer::draw()
{
	artist* style = get_style();
	int width = style->get_width();
	int height = style->get_height();

	string result = "";

	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
			result += style->mapper(i, j);

		result += '\n';
	}

	return result;
}

// Constructor initializes the downsample object with a specific artist style
downsample::downsample(artist* style) : drawer(style) {}

// Generates the downsampled output string by applying the artist's mapping to every other pixel
string downsample::draw()
{
	artist* style = get_style();
	int width = style->get_width();
	int height = style->get_height();

	string result = "";

	for (int j = 0; j < height / 2; j++)
	{
		for (int i = 0; i < width / 2; i++)
			result += style->mapper(i * 2, j * 2);

		result += '\n';
	}

	return result;
}

// Constructor initializes the upsample object with a specific artist style
upsample::upsample(artist* style) : drawer(style) {}

// Generates the upsampled output string by applying the artist's mapping with double resolution
string upsample::draw()
{
	artist* style = get_style();
	int width = style->get_width();
	int height = style->get_height();

	string result = "";

	for (int j = 0; j < height * 2; j++)
	{
		for (int i = 0; i < width * 2; i++)
			result += style->mapper(i / 2, j / 2);

		result += '\n';
	}

	return result;
}

// Constructor initializes the scale object with a specific artist style and scaling factors
scale::scale(artist* style, int x, int y) : drawer(style), x(x), y(y) {}

// Generates the scaled output string by applying the artist's mapping with custom scaling factors
string scale::draw()
{
	artist* style = get_style();
	int scaled_width = style->get_width();
	int scaled_height = style->get_height();

	string result = "";

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
