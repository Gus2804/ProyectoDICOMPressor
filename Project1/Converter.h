#include <stdio.h>
#include <iostream>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core/utility.hpp>

using namespace cv;
using namespace std;

#pragma once
class Converter
{
public:
	Converter();
	~Converter();
	int convertPNGToDicom(string sourcePath, string destinationPath);
	int convertTIFFToDicom(string sourcePath, string destinationPath);
	int convertPPMToDicom(string sourcePath, string destinationPath);
	int convertDicomToPNG(string sourcePath, string destinationPath);
	int convertDicomToTIFF(string sourcePath, string destinationPath);
	int convertDicomToPPM(string sourcePath, string destinationPath);

private:
	Mat readImage(string path);
	int writePNG(Mat image, string path);
	int writePPM(Mat image, string path);
	int writeTIFF(Mat image, string path);
	int writeDICOM(Mat image, string path);
};

