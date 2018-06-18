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
	char *getHeader(); 
	void setHeader(char* head);
	int getHeaderSize();
	void setHeaderSize(int headSize);
	Mat getPixelData();
	void setPixelData(Mat pixels);
	char *getPath();
	void setPath(char* filePath);
	long getSize();
	void setSize(long fileSize);

private:
	char* header;
	int headerSize;
	Mat pixelData;
	char* path;
	long size;
};

