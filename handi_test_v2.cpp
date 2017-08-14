#include "opencv\cv.h"
#include "opencv\highgui.h"
#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <ctype.h>
#include <direct.h>

using namespace cv;
using namespace std;

IplImage* img;
IplImage* img1;
IplImage* img4;
IplImage* hand;

char handiname[200];
char handipath[200];
char orginalname[200];
char filename[200];
char fullname[200];
char dirname[200];
const char ext[4] = {'.','p', 'n', 'g', };

int a1_all[2] = { 2976,192 };
int a1_left[2] = { 1536,192 };

int a4_all[2] = { 2336,192 };
int a4_right[2] = { 1184,192 };
int a4_left[2] = { 1152,192 };

int extra[2] = { 192,192 };

int width, height;

void A1Divider(IplImage*img) {

	char outname[200];
	cvSetImageROI(img, cvRect(0, 0, a1_left[0], a1_left[1]));
	cvSetImageROI(img1, cvRect(0, 0, a1_left[0], a1_left[1]));

	cvCopy(img, img1, NULL);

	cvResetImageROI(img1);
	cvResetImageROI(img);


	cvSetImageROI(img, cvRect(a1_left[0], 0, a1_all[0] - a1_left[0] - extra[0], a1_all[1]));
	cvSetImageROI(img1, cvRect(0, 192, a1_all[0] - a1_left[0] - extra[0], a1_all[1]));

	cvCopy(img, img1, NULL);

	cvResetImageROI(img1);
	cvResetImageROI(img);

	cvSetImageROI(hand, cvRect(0, 0, 192, 192));
	cvSetImageROI(img1, cvRect((a1_all[0] - a1_left[0] - extra[0]), 192, 192, 192));

	cvCopy(hand, img1, NULL);

	cvResetImageROI(img1);
	cvResetImageROI(img);

	sprintf(outname, "%s//%s", dirname, "a1");
	sprintf(outname, "%s//%s", outname, filename);
	sprintf(outname, "%s%s", outname, ".png");


	cvSaveImage(outname, img1);
	cout << "IMAGE IS CREATED SUCCESSFULLY" << "\n" << "\n";

}


void A4Divider(IplImage*img) {

	char outname[200];

	cvSetImageROI(img, cvRect(0, 0, a4_left[0], a4_left[1]));
	cvSetImageROI(img4, cvRect(0, 0, a4_left[0], a4_left[1]));

	cvCopy(img, img4, NULL);

	cvResetImageROI(img4);
	cvResetImageROI(img);

	cvSetImageROI(img, cvRect(a4_left[0], 0, a4_all[0] - a4_left[0] - extra[0], a4_all[1]));
	cvSetImageROI(img4, cvRect(0, 192, a4_all[0] - a4_left[0] - extra[0], a4_all[1]));

	cvCopy(img, img4, NULL);

	cvResetImageROI(img4);
	cvResetImageROI(img);

	cvSetImageROI(hand, cvRect(0, 0, 192, 192));
	cvSetImageROI(img4, cvRect((a4_all[0] - a4_left[0] - extra[0]), 192, 192, 192));

	cvCopy(hand, img4, NULL);

	cvResetImageROI(img4);
	cvResetImageROI(img);

	sprintf(outname, "%s//%s", dirname, "a4");
	sprintf(outname, "%s//%s", outname, filename);
	sprintf(outname, "%s%s", outname, ".png");


	cvSaveImage(outname, img4);
	cout << "IMAGE IS CREATED SUCCESSFULLY" << "\n" << "\n";

}

void createFolder() {

	char foldername[200];
	sprintf(foldername, "%s//%s", dirname, "a1");
	mkdir(foldername);
	sprintf(foldername, "%s//%s", dirname, "a4");
	mkdir(foldername);
	sprintf(foldername, "%s//%s", dirname, "nord");
	mkdir(foldername);

}


String changePath(string address) {

//		=(char *) malloc (sizeof(char)*200);

	for (int i = 0; dir[i] != '\0'; i++) {
		if (dir[i] != '\\') {
			sprintf(address, "%c%c", &address, dir[i]);
		}
		else {
			strcat(address, "//");
		}
	}

	return address;
}


void distributer(IplImage *image) {

	width = img->width;
	height = img->height;

	if (width == 2784 && height == 192) {		// If the resolation is 2976 x 192 handle it as A1
		A1Divider(image);
	}
	if (width == 2144 && height == 192) {		// If the resolation is 2336 x 192 handle it as A4

		A4Divider(image);
	}

	// NORD WILL BE ADDED

}


int main(int argc, char** argv)
{

	
	cout << "Provide the path of the handyimage: ";
	cin.getline(handipath, 200);
	handipath =changePath(handipath);

	cout << "Name of the handyimage: ";
	cin.getline(handiname, 200);
	sprintf(handipath, "%s//%s", handipath, handiname);
	strcat(handipath, ext);

	

	hand = cvLoadImage(handipath);
	cout << handipath;

	cout << "Provide the path of the images: ";
	cin.getline(orginalname, 200);
	originalname=changePath(orginalname);



	createFolder();

	while (1) {

		cout << "Image name: ";
		cin.getline(filename, 200);


		sprintf(fullname, "%s//%s", dirname, filename);
		strcat(fullname, ext);

		img = cvLoadImage(fullname);

	//	if (!img) break;

		img1 = cvCreateImage(cvSize(1920, 1080), img->depth, 3);
		img4 = cvCreateImage(cvSize(1920, 1080), img->depth, 3);

		distributer(img);

		//  cvShowImage("wind", img);
		//	cvShowImage("wind1", img1);
		//	cvShowImage("wind4", img4);
		//	cvWaitKey(0);

		cvReleaseImage(&img);
		cvReleaseImage(&img1);
		cvReleaseImage(&img4);

	}

	

	return 0;
}
