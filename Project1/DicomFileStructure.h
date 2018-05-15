#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core/utility.hpp>
#include "Study.h"

using namespace cv;
using namespace std;

#pragma once
class DicomFileStructure
{
public:
	DicomFileStructure();
	~DicomFileStructure();
	char *getMetainformation();
	void setMetainformation(char* metainformation);
	Study getStudyData();
	void setStudyData(Study study);
	Mat getPixelData();
	void setPixelData(Mat pixels);

private:
	char* metainformation;
	Study studyData;
	Mat pixelData;
};

