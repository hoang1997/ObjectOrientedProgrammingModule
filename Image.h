#pragma once
//*********************************************
//Image class to hold and allow manipulation of images once read into the code
//from https://www.scratchapixel.com/
//*********************************************
#include <cstdlib> 
#include <cstdio> 
#include <iostream>
#include <cstring>
#include <string>
#include <stdlib.h>

using namespace std;

class Image
{
public:
	// Rgb structure, i.e. a pixel 
	struct Rgb
	{
		Rgb() : r(0), g(0), b(0) {}
		Rgb(float c) : r(c), g(c), b(c) {}
		Rgb(float _r, float _g, float _b) : r(_r), g(_g), b(_b) {}
		bool operator != (const Rgb &c) const
		{
			return c.r != r || c.g != g || c.b != b;
		}
		Rgb& operator *= (const Rgb &rgb)
		{
			r *= rgb.r, g *= rgb.g, b *= rgb.b; return *this;
		}
		Rgb& operator += (const Rgb &rgb)
		{
			r += rgb.r, g += rgb.g, b += rgb.b; return *this;
		}
		friend float& operator += (float &f, const Rgb rgb)
		{
			f += (rgb.r + rgb.g + rgb.b) / 3.f; return f;
		}
		float r, g, b;
	};

	Image() : w(0), h(0), pixels(nullptr) { /* empty image */ }
	Image(const unsigned int &_w, const unsigned int &_h, const Rgb &c = kBlack) :
		w(_w), h(_h), pixels(NULL)
	{
		pixels = new Rgb[w * h];
			for (unsigned int i = 0; i < w * h; ++i)
				pixels[i] = c;
	}
	const Rgb& operator [] (const unsigned int &i) const
	{
		return pixels[i];
	}
	Rgb& operator [] (const unsigned int &i)
	{
		return pixels[i];
	}
	~Image()
	{
		//if (pixels != NULL) delete[] pixels;
		//delete[] pixels;
	}
	unsigned int w, h; // Image resolution 
	Rgb *pixels; // 1D array of pixels 
	static const Rgb kBlack, kWhite, kRed, kGreen, kBlue; // Preset colors 
	
	//calculates the average pixels of r g and b, then outputs it - used by all imageinfo functions
	void avRGB(const Image &img)
	{
		float rVal = 0.f;
		float gVal = 0.f;
		float bVal = 0.f;

		for (unsigned int i = 0; i < img.h*img.w; i++)
		{
			rVal += img.pixels[i].r;
			gVal += img.pixels[i].g;
			bVal += img.pixels[i].b;
		}

		rVal /= (img.h*img.w)*255;
		gVal /= (img.h*img.w)*255;
		bVal /= (img.h*img.w)*255;

		cout << "Average RGB Values: " << rVal << " " << gVal << " " << bVal << endl;
	}

	//virtual function as Image is the parent class for the other classes to inherit and override the function
	virtual void imageInfo(const char* fileName, const Image &img)
	{
		cout << "Image Information:\n" << endl;
		cout << "Filename:" << fileName << endl;
		cout << "Image Dimesions:" << endl;
		cout << "Width: " << img.w << " Height: " << img.h << endl;
		cout << "Colour Depth: 24 bit" << endl;
		avRGB(img);
	}
};
     
const Image::Rgb Image::kBlack = Image::Rgb(0);
const Image::Rgb Image::kWhite = Image::Rgb(1);
const Image::Rgb Image::kRed = Image::Rgb(1, 0, 0);
const Image::Rgb Image::kGreen = Image::Rgb(0, 1, 0);
const Image::Rgb Image::kBlue = Image::Rgb(0, 0, 1);
