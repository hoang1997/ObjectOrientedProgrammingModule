#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cstring>
#include <string>
#include "scaleInfo.h"

#ifndef readWriteFiles

#define readWriteFiles
using namespace std;

//Read ppm files into the code
//They need to be in 'binary' format (P6) with no comments in the header
//The first line is the 'P'number - P6 indicates it is a binary file, then the image dimensions and finally the colour range
//This header is then followed by the pixel colour data
//eg:	P6
//		3264 2448
//		255
//Open a .ppm file in notepad++ to see this header (caution: they are large files!)
class readWrite
{
	public: 
	
	//function to read the image data
	Image readPPM(const char *filename)
	{
		//Remove this cout to prevent multiple outputs
		cout << "Reading image ..." << endl;
		ifstream ifs;
		ifs.open(filename, std::ios::binary);
		Image src;
		try {
			if (ifs.fail()) {
				throw("Can't open the input file - is it named correctly/is it in the right directory?");
			}
			string header;
			int w, h, b;
			ifs >> header;
			if (strcmp(header.c_str(), "P6") != 0) throw("Can't read the input file - is it in binary format (Has P6 in the header)?");
			ifs >> w >> h >> b;
			src.w = w;
			src.h = h;
			//std::cout << w << " " << h << std::endl;
			src.pixels = new Image::Rgb[w * h]; // this is throw an exception if bad_alloc 
			ifs.ignore(256, '\n'); // skip empty lines in necessary until we get to the binary data 
			unsigned char pix[3]; // read each pixel one by one and convert bytes to floats 
			for (int i = 0; i < w * h; ++i) {
				ifs.read(reinterpret_cast<char *>(pix), 3);
				src.pixels[i].r = pix[0] / 255.f;
				src.pixels[i].g = pix[1] / 255.f;
				src.pixels[i].b = pix[2] / 255.f;
			}
			ifs.close();
		}
		catch (const char *err) {
			fprintf(stderr, "%s\n", err);
			ifs.close();
		}

		//Confirm image read
		//Delete this to prevent multiple lines output
		cout << "Image read" <<endl;
		return src;
	}
	//function to write the image
	void writePPM(const Image &img, const char *filename, string id)
	{
		//std::cout << filename << std::endl;
		cout << "Writing image ..." << endl;
		if (img.w == 0 || img.h == 0) { fprintf(stderr, "Can't save an empty image\n"); return; }
		std::ofstream ofs;
		try 
		{
			ofs.open(filename, std::ios::binary); // need to spec. binary mode for Windows users 
			if (ofs.fail()) throw("Can't open output file");
			ofs << "P6\n" << img.w << " " << img.h << "\n255\n";
			//std::cout << "P6\n" << img.w << " " << img.h << "\n255\n";
			unsigned char r, g, b;
			// loop over each pixel in the image, clamp and convert to byte format
			for (unsigned int i = 0; i < img.w * img.h; ++i) {
				r = static_cast<unsigned char>(std::min(1.f, img.pixels[i].r) * 255);
				g = static_cast<unsigned char>(std::min(1.f, img.pixels[i].g) * 255);
				b = static_cast<unsigned char>(std::min(1.f, img.pixels[i].b) * 255);
				ofs << r << g << b;
			}
			ofs.close();
			//Confirm image write
			cout << "Image written" << endl;
			
			//if the image id is zoom x2 then it outputs zoom x2 info
			if (id == "zoom2")
			{
				//creating an image object pointer
				Image *imgObj;
				//creating a zoom x2 info object 
				zoomInfoX2 zoomObj;
				//pointing the image object to zoom info x2 location
				imgObj = &zoomObj;
				//image object calls the function
				imgObj->imageInfo(filename, img);
			}
			if (id == "zoom4") {
				Image *imgObj;
				zoomInfoX4 zoomObj;
				imgObj = &zoomObj;
				imgObj->imageInfo(filename, img);
			}
			if (id == "roi")
			{
				Image *imgObj;
				roiInfo roiObj;
				imgObj = &roiObj;
				imgObj->imageInfo(filename, img);
			}
			if(id=="img"){
				Image *imgObj = new Image;
				imgObj->imageInfo(filename, img);
				//creates logfile for the blended images
				ofstream logFile("Log Files/Blended_logfile.txt", ios_base::out | ios_base::app);
				logFile << "Filename:" << filename << endl;
				logFile << "Image Pixel Size: " << img.w*img.h << endl;
				logFile << "Image Dimesions:" << endl;
				logFile << "Width:  " << img.w << endl;
				logFile << "Height: " << img.h << endl;
			}
		}
		catch (const char *err) {
			fprintf(stderr, "%s\n", err);
			ofs.close();
		}
	}
};

#endif
