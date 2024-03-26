#include "RGB/png.h"
#include "RGB/rgbapixel.h"

#include <string>
#include <cmath>

void rotate(std::string inputFile, std::string outputFile)
{
	PNG pic(inputFile);
	PNG originalPic(inputFile);
	for (size_t y = 0; y < pic.height(); y++)
	{
		for (size_t x = 0; x < pic.width(); x++)
		{
			RGBAPixel *originalPixel = pic(x, y);
			RGBAPixel *newPixel = originalPic(originalPic.width() - x - 1, originalPic.height() - y - 1);
			*originalPixel = *newPixel;
		}
	}

	pic.writeToFile(outputFile);
}

PNG myArt(unsigned int width, unsigned int height)
{
	PNG png(width, height);
	for (size_t y = 0; y < height; y++)
	{
		for (size_t x = 0; x < width; x++)
		{
			u_int8_t color = (x + y) + (rand() % 40) % 255;

			RGBAPixel *pixel = png(x, y);
			pixel->red = color;
			pixel->green = color / (x % 10 + 1);
			pixel->blue = color / (y % 5 + 1);
			pixel = png(x  , y);
		}
	}

	return png;
}
