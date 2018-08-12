#pragma once

#include "image.h"
//these classes all inherit image class to access the imageinfo function
class zoomInfoX2  : public Image
{
public:
	//outputs information
	void imageInfo(const char* fileName, const Image &img)
	{
		cout << "Image Information:\n" << endl;
		cout << "Filename:" << fileName << endl;
		cout << "Image Pixel Size: " << img.w*img.h << endl;
		cout << "Image Dimesions:" << endl;
		cout << "Width:  " << img.w << endl;
		cout << "Height: " << img.h << endl;
		cout << "Colour Depth: 24 bit" << endl;
		avRGB(img);
		cout << "Zoom Image Information:" << endl;
		cout << "Zoom Scale: X2" << endl;
		//this crates a log file for the image information of this type
		ofstream logFile("Log Files/zoom_x2_logfile.txt", ios_base::out | ios_base::app);
		logFile << "Filename:" << fileName << endl;
		logFile << "Image Pixel Size: " << img.w*img.h << endl;
		logFile << "Image Dimesions:" << endl;
		logFile << "Width:  " << img.w << endl;
		logFile << "Height: " << img.h << endl;
	}
};

class zoomInfoX4 : public Image
{
public:
	void imageInfo(const char* fileName, const Image &img)
	{
		cout << "Image Information:\n" << endl;
		cout << "Filename:" << fileName << endl;
		cout << "Image Pixel Size: " << img.w*img.h << endl;
		cout << "Image Dimesions:" << endl;
		cout << "Width:  " << img.w << endl;
		cout << "Height: " << img.h << endl;
		cout << "Colour Depth: 24 bit" << endl;
		avRGB(img);
		cout << "Zoom Image Information:" << endl;
		cout << "Zoom Scale: X4" << endl;

		ofstream logFile("Log Files/zoom_x4_logfile.txt", ios_base::out | ios_base::app);
		logFile << "Filename:" << fileName << endl;
		logFile << "Image Pixel Size: " << img.w*img.h << endl;
		logFile << "Image Dimesions:" << endl;
		logFile << "Width:  " << img.w << endl;
		logFile << "Height: " << img.h << endl;
	}
};

class roiInfo : public Image
{
	void imageInfo(const char* fileName, const Image &img)
	{
		cout << "Image Information:\n" << endl;
		cout << "Filename:" << fileName << endl;
		cout << "Image Pixel Size: " << img.w*img.h << endl;
		cout << "Image Dimesions:" << endl;
		cout << "Width:  " << img.w << endl;
		cout << "Height: " << img.h << endl;
		cout << "Colour Depth: 24 bit" << endl;
		avRGB(img);
		cout << "Starting point of ROI: 11.09% (Of pixel size)" << endl;

		ofstream logFile("Log Files/ROI_logfile.txt", ios_base::out | ios_base::app);
		logFile << "Filename:" << fileName << endl;
		logFile << "Image Pixel Size: " << img.w*img.h << endl;
		logFile << "Image Dimesions:" << endl;
		logFile << "Width:  " << img.w << endl;
		logFile << "Height: " << img.h << endl;
	}

};