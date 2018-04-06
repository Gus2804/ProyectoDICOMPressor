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
	int convertImageToDicom(string sourcePath, char* destinationPath);

private:
	Mat readImage(string path);
	int writeDICOM(Mat* image, char* path);
};

