#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include<stdio.h>
#include<vector>
#include<numeric>
#include<list>
#include "rwFiles.h"
#include "image.h"

using namespace std;

class Blending {
private:
	//creating object to read the files
	readWrite *file;
	//creating the array of the directory so that a function
	//can loop through the directories
	string imageArray[13] = { "Images/ImageStacker_set1/IMG_1.ppm","Images/ImageStacker_set1/IMG_2.ppm", "Images/ImageStacker_set1/IMG_3.ppm", "Images/ImageStacker_set1/IMG_4.ppm", "Images/ImageStacker_set1/IMG_5.ppm" ,"Images/ImageStacker_set1/IMG_6.ppm", "Images/ImageStacker_set1/IMG_7.ppm", "Images/ImageStacker_set1/IMG_8.ppm", "Images/ImageStacker_set1/IMG_9.ppm", "Images/ImageStacker_set1/IMG_10.ppm", "Images/ImageStacker_set1/IMG_11.ppm", "Images/ImageStacker_set1/IMG_12.ppm", "Images/ImageStacker_set1/IMG_13.ppm" };
	int imgSize = 3264 * 2448;

	vector<Image>imgVector;
	vector<float> rVal;
	vector<float> gVal;
	vector<float> bVal;
	float rResult, gResult, bResult;

	float rMean,gMean,bMean;

	float rMedian,gMedian,bMedian;

	float rStd,gStd,bStd;
public:
	//function to sort the rgb values all at once
	void rgbSort()
	{
		sort(rVal.begin(), rVal.end());
		sort(gVal.begin(), gVal.end());
		sort(bVal.begin(), bVal.end());
	}
	//function to clear the rgb values all at once
	void rgbClear()
	{
		rVal.clear();
		gVal.clear();
		bVal.clear();
	}
	//function to transfer the image data in a vector and to read the zoom image
	void imgToVector(Image &img, Image &zoomSource)
	{
		for (unsigned int j = 0; j < 13; j++)
		{
			char *fileSource = (char*)imageArray[j].c_str();

			img = file->readPPM(fileSource);

			imgVector.push_back(img);
		}

		zoomSource = file->readPPM("Images/Zoom/zIMG_1.ppm");
	}
	//function to calculate the mean of the image set
	void meanBlending(Image &img)
	{
		cout << "Starting Mean Blending" << endl;
		for (unsigned int i = 0; i < 13; i++)
		{
			for (unsigned int j = 0; j < imgSize; j++)
			{
				img.pixels[j].r += imgVector[i].pixels[j].r;
				img.pixels[j].g += imgVector[i].pixels[j].g;
				img.pixels[j].b += imgVector[i].pixels[j].b;
			}
		}

		for (unsigned int i = 0; i  < imgSize; i++)
		{
			img.pixels[i].r = img.pixels[i].r / 13;
			img.pixels[i].g = img.pixels[i].g / 13;
			img.pixels[i].b = img.pixels[i].b / 13;
		}

		cout << "Mean Blending Found" << endl;
	}

	//function to calculate the median of the image set
	void medianBlending(Image &img2)
	{
		cout << "\nSorting median values and blending . . ." << endl;
		for (unsigned int i = 0; i < imgSize; i++)
		{
			for (unsigned int j = 0; j < 13; j++)
			{
				rVal.push_back(imgVector[j].pixels[i].r);
				gVal.push_back(imgVector[j].pixels[i].g);
				bVal.push_back(imgVector[j].pixels[i].b);
			}

			rgbSort();

			img2.pixels[i].r += rVal[7];
			img2.pixels[i].g += gVal[7];
			img2.pixels[i].b += bVal[7];

			rgbClear();
		}

		cout << "Median Blending Found" << endl;
	}

	//function to calculate the sigma clipped of the image set
	void sigmaClip(Image &img)
	{
		cout << "Sigma Clipping . . ." << endl;
	
		for (unsigned int i = 0; i < imgSize; i++)
		{	
			for (unsigned int j = 0; j < 13; j++)
			{
				rVal.push_back(imgVector[j].pixels[i].r);
				gVal.push_back(imgVector[j].pixels[i].g);
				bVal.push_back(imgVector[j].pixels[i].b);
			}

			img.pixels[i].r = eraseData(rVal, rMedian, rStd, rResult);
			img.pixels[i].g = eraseData(gVal, gMedian, gStd, gResult);
			img.pixels[i].b = eraseData(bVal, bMedian, bStd, bResult);

			//cout << i << endl;
			rVal.clear();
			gVal.clear();
			bVal.clear();
		}
	}

	//function to erase the data of the r, g or b outliers in the pixels of the 13 images
	float eraseData(vector<float> rgbVal, float rgbMedian, float rgbStd, float rgbResult)
	{
		float oldStdDev = 0.0f;

		//iterating function 5 times
		for (unsigned int i = 0; i < 5; i++)
		{
			for (unsigned int j = 0; j < rgbVal.size(); j++)
			{
				//tolerance check to see if the standdard deviation is in the range and if so break out of the loop
				if (oldStdDev != 0)
				{
					//recalculating the standard deviation
					rgbStd = stdDev(rgbVal, rgbStd);
					//tolerance check
					if (rgbStd < oldStdDev + ((oldStdDev - rgbStd) / rgbStd) && rgbStd > oldStdDev - ((oldStdDev - rgbStd) / rgbStd))
					{
						break;
					}
				}

				//initializing the standard deviation and median by calling the functions and returning the values
				rgbStd = stdDev(rgbVal, rgbStd);
				rgbMedian = median2(rgbVal);

				//seeing if the r, g or b value is outside the range, and if it is erase the value
				if (rgbVal[j] > rgbMedian + (0.4 * rgbStd) || rgbVal[j] < rgbMedian - (0.4 * rgbStd))
				{
					rgbVal.erase(remove(rgbVal.begin(), rgbVal.end(), rgbVal[j]), rgbVal.end());
				}

				//setting the old standard deviation for the tolerance check
				oldStdDev = rgbStd;
			}
		}

		//setting the r g or b value by calculating the average of the remaining values in the vectors
		rgbResult = mean2(rgbVal);

		return rgbResult;
	}

	//calculates the mean for the erase standard deviation
	float mean2(vector<float> rgbVal)
	{
		float rgbMean = 0.0f;
		for (unsigned int i = 0; i < rgbVal.size(); i++)
		{
			rgbMean += rgbVal[i];
		}

		rgbMean = rgbMean / rgbVal.size();

		return rgbMean;
	}

	//calculates the standard deviation for the erase data function
	float stdDev(vector<float> rgbVal, float rgbMean)
	{
		float rgbStd = 0.0f;
		rgbMean = mean2(rgbVal);
		for (unsigned int i = 0; i < rgbVal.size(); i++)
		{
			rgbStd += pow(rgbVal[i] - rgbMean, 2);
		}
		rgbStd = sqrt(rgbStd / rgbVal.size());
		return rgbStd;
	}

	//calculates the median for the erase data function
	float median2(vector<float> rgbVal)
	{
		float median = 0.0f;

		sort(rgbVal.begin(), rgbVal.end());

		if (rgbVal.size() % 2 == 0)
		{
			median = (rgbVal[(rgbVal.size() / 2) - 1] + rgbVal[rgbVal.size() / 2]) / 2;
		}
		else {
			median = rgbVal[rgbVal.size() / 2];
		}
		return median;
	}

};  

