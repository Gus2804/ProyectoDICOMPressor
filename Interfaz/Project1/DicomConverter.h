#include "Study.h"
#include <stdio.h>
#include <iostream>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core/utility.hpp>

using namespace cv;
using namespace std;

#pragma once
class DicomConverter
{
public:
	DicomConverter();
	~DicomConverter();
	/*Error codes:
	-1: Study Date error
	-2: Study description error
	-3:
	*/
	int convertImageToDicom(string sourcePath, char *destinationPath, Study studyData);

private:
	Mat readImage(string path);
	int writeDICOM(Mat *image, char *path, Study studyData);
	bool isValidDate(string date);
	bool is_number(string str);
};

typedef struct dataset {
	unsigned short int tag[2];
	char *vr;
	char *length;
	char *value;
} dataset_t;
