//main.cpp
#include <iostream>
#include <cstring>
#include <string>
#include <stdlib.h>
#include "Image.h"
#include "ImageBlending.h"
#include "rwFiles.h"
#include "Scaling.h"


using namespace std;

int main()
{
	//Creating Image Objects of different sizes
	Image *zoomSource = new Image(750, 750);
	Image *roiX2 = new Image(750, 750);
	Image *img =  new Image(3264, 2448);
	Image *img2 = new Image(3264, 2448);
	Image *roi = new Image(375, 375);
	Image *zoomX2 = new Image(1500, 1500);
	Image *zoomX4 = new Image(3000, 3000);
	//creating objects to call functions
	readWrite *file = new readWrite;
	Blending blend;
	scale scale;

	//initializing input
	char input;

	cout << "****************************" << endl;
	cout << "Image Stacker / Image Scaler" << endl;
	cout << "Initial Reading Of Images ..."<< endl;
	cout << "****************************\n" << endl;
	//passing 2 image objects to the vector converter, 
	//once the images are read into the vector the image object is then deleted
	blend.imgToVector(*img, *zoomSource);
	delete img;

	system("cls");

	//while loop to loop the program
	do {

		cout << "****************************" << endl;
		cout << "Image Stacker / Image Scaler" << endl;
		cout << "****************************" << endl;
		cout << "        MAIN MENU           " << endl;
		cout << "****************************" << endl;
		cout << "\nPlease Choose an Option\n" << endl;
		cout << "1. Blend Images " << endl;
		cout << "2. Scale " << endl;
		cout << "Press 0 to QUIT" << endl;
		cout << "\nOption: ";
		cin >> input;
			
		system("cls");

		if (input == '1')
		{
			cout << "************************************" << endl;
			cout << "            Image Stacker           " << endl;
			cout << "************************************" << endl;
			cout << "\nPlease Choose an Option\n" << endl;
			cout << "1. Mean Blending " << endl;
			cout << "2. Median Blending" << endl;
			cout << "3. Sigma Clipping" << endl;
			cout << "4. Back to Main Menu" << endl;
			cout << "Press 0 to QUIT" << endl;
			cout << "\nOption: ";
			cin >> input;
			system("cls");

			switch (input)
			{
				case '1':
					//calling the mean blending function and passing 1 image to it
					blend.meanBlending(*img2);
					cout << "Writing Image: MeanBlendedImage.ppm  . . ." << endl;
					//calling the write function, and defining the id of what im writing so that it can output the right information
					file->writePPM(*img2, "Image Results/meanBlendedImage.ppm", "img");
					system("cls");
					system("pause");
				break;
				case '2':
					blend.medianBlending(*img2);
					cout << "\nWriting Image: MedianBlendedImage.ppm  . . ." << endl;
					file->writePPM(*img2, "Image Results/medianBlendedImage.ppm","img");
					system("cls");
					system("pause");
					break;
				case '3':
					blend.sigmaClip(*img2);
					cout << "\nWriting Image: SigmaClipped.ppm  . . ." << endl;
					file->writePPM(*img2, "Image Results/SigmaClipped.ppm","img");
					system("cls");
					system("pause");
					break;
				case '4':
					//back to main menu
					break;
				default:
					cout << "Error Returning Back To Main Menu" << endl;
					cin >> input;
					system("pause");
					system("cls");
					break;
			}
			if (cin.fail())
			{
				cout << "Please Enter a Valid Option" << endl;
				cin.clear();
				cin.ignore();
			}
		}

		if (input == '2')
		{
			cout << "************************************" << endl;
			cout << "            Image Scaler           " << endl;
			cout << "************************************" << endl;
			cout << "Please Choose an Option:" << endl;
			cout << "1. Nearest Neigbour Image x2" << endl;
			cout << "2. Nearest Neigbour Image x4" << endl;
			cout << "3. Bilinear Interpolation Image x2" << endl;
			cout << "4. Bilinear Interpolation Image x4" << endl;
			cout << "5. Region Of Interest x2 - Nearest Neighbour" << endl;
			cout << "6. Region Of Interest x4 - Nearest Neighbour" << endl;
			cout << "7. Region Of Interest x2 - Bilinear" << endl;
			cout << "8. Region Of Interest x4 - Bilinear" << endl;
			cout << "9. Back to Main Menu" << endl;
			cout << "Press 0 to QUIT" << endl;
			cout << "\nOption: ";
			cin >> input;
			switch (input)
			{
			case '1':
				scale.zoomX2(*zoomSource, *zoomX2);
				cout << "\nWriting Image zoomX2.ppm" << endl;
				file->writePPM(*zoomX2, "Image Results/ZoomX2.ppm", "zoom2");
				system("pause");
				system("cls");
				input = '0';
				break;
			case '2':
				scale.zoomX4(*zoomSource, *zoomX4);
				cout << "\nWriting Image zoomX4.ppm" << endl;
				file->writePPM(*zoomX4, "Image Results/ZoomX4.ppm", "zoom4");
				system("pause");
				system("cls");
				input = '0';
				break;
			case '3':
				scale.bilinear(*zoomSource, *zoomX2);
				cout << "\nWriting Image bilinearX2.ppm" << endl;
				file->writePPM(*zoomX2, "Image Results/BilinearX2.ppm", "zoom2");
				delete zoomX2;
				system("pause");
				system("cls");
				input = '0';
				break;
			case '4':
				scale.bilinear(*zoomSource, *zoomX4);
				cout << "\nWriting Image bilinearX4.ppm" << endl;
				file->writePPM(*zoomX4, "Image Results/BilinearX4.ppm", "zoom4");
				system("pause");
				system("cls");
				input = '0';
				break;
			case '5':
				cout << "Creating Region Of Interest" << endl;
				scale.ROI(*zoomSource, *roi);
				cout << "Nearest Neighbour Scaling x2: Region Of Interest" << endl;
				scale.zoomX2(*roi, *roiX2);
				cout << "\nWriting Image: ROI_NearestNeighbour_x2.ppm" << endl;
				file->writePPM(*roiX2, "Image Results/ROI_NearestNeighbour_x2.ppm", "roi");
				system("pause");
				system("cls");
				input = '0';
				break;
			case '6':
				cout << "Creating Region Of Interest" << endl;
				scale.ROI(*zoomSource, *roi);
				cout << "Nearest Neighbour Scaling x4: Region Of Interest" << endl;
				scale.zoomX4(*roi, *zoomX2);
				cout << "\nWriting Image: ROI_NearestNeighbour_x4.ppm" << endl;
				file->writePPM(*zoomX2, "Image Results/ROI_NearestNeighbour_x4.ppm", "roi");
				system("pause");
				system("cls");
				input = '0';
				break;

			case '7':
				cout << "Creating Region Of Interest" << endl;
				scale.ROI(*zoomSource, *roi);
				cout << "Bilinear Scaling x2: Region Of Interest" << endl;
				scale.bilinear(*roi, *roiX2);
				file->writePPM(*roiX2, "Image Results/ROI_Bilinear_x2.ppm", "roi");
				cout << "\nWriting Image: RegionOfInterestImgX2.ppm" << endl;
				system("pause");
				system("cls");
				input = '0';
				break;
			case '8':
				cout << "Creating Region Of Interest" << endl;
				scale.ROI(*zoomSource, *roi);
				cout << "Nearest Neighbour Scaling x4: Region Of Interest" << endl;
				scale.bilinear(*roi, *zoomX2);
				file->writePPM(*zoomX2, "Image Results/ROI_Bilinear_x4.ppm", "roi");
				cout << "\nWriting Image: RegionOfInterestImgX4.ppm" << endl;
				system("pause");
				system("cls");
				input = '0';
				break;
			case '9':
				break;
			default:
				cout << "Error Returning Back To Main Menu" << endl;
				system("pause");
				system("cls");
				break;
			}
		}
		if (cin.fail())
		{
			cout << "Please Enter a Valid Option" << endl;
			cin.clear();
			cin.ignore();
		}

	} while (input!='0');

	return 0;
}
