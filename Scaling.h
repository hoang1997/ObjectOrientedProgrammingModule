#pragma once

#include <iostream>
#include <vector>
#include "Image.h"
#include "rwFiles.h"

using namespace std;

class scale
{
	//privatising variables
private:
	float w1, w2, h1 ,h2 = 0.f;
	float x_ratio, y_ratio = 0.f;
	float x_diff, y_diff;
	int x2, y2;
	int offset = 0;
	int index, x, y;
	int count = 0;
	int count2 = 0;
public:
	//makes the image scaled to x2
	void zoomX2(Image &zoomSource, Image &zoomImg)
	{
		w1 = zoomSource.w;
		h1 = zoomSource.h;
		//setting the ratio  to x2
		w2 = w1 * 2;
		h2 = h1 * 2;

		//calculates the ratio 
		x_ratio = w1 / (double)w2;
		y_ratio = h1 / (double)h2;

		for (unsigned int i = 0; i<zoomImg.h; i++)
		{
			for (unsigned int j = 0; j<zoomImg.w; j++)
			{
				//calculating the rounded down position of width * the width ratio and height * the height ratio
				x2 = floor(j*x_ratio);
				y2 = floor(i*y_ratio);
				//setting pixels
				zoomImg.pixels[(int)(i*w2) + j].r = zoomSource.pixels[(y2*zoomSource.w) + x2].r;
				zoomImg.pixels[(int)(i*w2) + j].g = zoomSource.pixels[(y2*zoomSource.w) + x2].g;
				zoomImg.pixels[(int)(i*w2) + j].b = zoomSource.pixels[(y2*zoomSource.w) + x2].b;
			}
		}
	}

	void zoomX4(Image &zoomSource, Image &zoomImg)
	{
		w1 = zoomSource.w;
		h1 = zoomSource.h;
		w2 = w1 * 4;
		h2 = h1 * 4;

		float x_ratio = w1 / (double)w2;
		float y_ratio = h1 / (double)h2;

		for (unsigned int i = 0; i<zoomImg.h; i++)
		{
			for (unsigned int j = 0; j<zoomImg.w; j++)
			{
				x2 = floor(j*x_ratio);
				y2 = floor(i*y_ratio);
				zoomImg.pixels[(int)(i*w2) + j].r = zoomSource.pixels[(y2*zoomSource.w) + x2].r;
				zoomImg.pixels[(int)(i*w2) + j].g = zoomSource.pixels[(y2*zoomSource.w) + x2].g;
				zoomImg.pixels[(int)(i*w2) + j].b = zoomSource.pixels[(y2*zoomSource.w) + x2].b;
			}
		}
	}

	//calculates bilinear 
	void bilinear(Image &zoomSource, Image &zoomImg)
	{
		//getting setting different rgb stucts
		Image::Rgb a, b, c, d;
		//calculating ratio
		x_ratio = ((float)(zoomSource.w - 1)) / zoomImg.w;
		y_ratio = ((float)(zoomSource.h - 1)) / zoomImg.h;
		
		for (int i = 0; i<zoomImg.h; i++) {
			for (int j = 0; j<zoomImg.w; j++) {
				//calculating ratio for the height and width
				x = (int)(x_ratio * j);
				y = (int)(y_ratio * i);
				//calculating the height and width difference
				x_diff = (x_ratio * j) - x;
				y_diff = (y_ratio * i) - y;
				//calculating index
				index = (y*zoomSource.w + x);
				//setting structs 
				a = zoomSource.pixels[index];
				b = zoomSource.pixels[index + 1];
				c = zoomSource.pixels[index + zoomSource.w];
				d = zoomSource.pixels[index + zoomSource.w + 1];
				//setting pixels
				zoomImg.pixels[offset].b = (a.b)*(1 - x_diff)*(1 - y_diff) + (b.b)*(x_diff)*(1 - y_diff) + (c.b)*(y_diff)*(1 - x_diff) + (d.b)*(x_diff*y_diff);
				zoomImg.pixels[offset].g = (a.g)*(1 - x_diff)*(1 - y_diff) + (b.g)*(x_diff)*(1 - y_diff) + (c.g)*(y_diff)*(1 - x_diff) + (d.g)*(x_diff*y_diff);
				zoomImg.pixels[offset].r = (a.r)*(1 - x_diff)*(1 - y_diff) + (b.r)*(x_diff)*(1 - y_diff) + (c.r)*(y_diff)*(1 - x_diff) + (d.r)*(x_diff*y_diff);
				//incrementing offset
				offset++;
			}
		}
	}

	//calculates the region of interest
	void ROI(Image &img, Image &roiImg) 
	{
		//loops through all the images starting at a specific pixel point
		for (unsigned int i = 66938; i < img.h*img.w; i++)
		{
			//setting the new images pixel 
			roiImg.pixels[count2].r = img.pixels[i].r;
			roiImg.pixels[count2].g = img.pixels[i].g;
			roiImg.pixels[count2].b = img.pixels[i].b;

			//incrementing the counts
			count2++;
			count++;

			//if the count is = to the width of the new img then add the width to the i to get to the next line of pixels
			if (count == roiImg.w)
			{
				count = 0;
				i = i + roiImg.w;
			}
			//if the new image pixels gets to the limit then break
			if (count2 == (roiImg.w*roiImg.h))
			{
				break;
			}
		}
	}
};