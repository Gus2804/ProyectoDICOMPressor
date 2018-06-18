#include "CompressionResults.h"
#include "DicomFileStructure.h"

#pragma once
class Compresor
{
public:
	Compresor();
	~Compresor();
	CompressionResults compressByBilinearInterpolation(DicomFileStructure dicomFile, int m, int n, float threshold, int quantizationLevels);
	CompressionResults compressByRandomization(DicomFileStructure dicomFile, float threshold);
private:
	Vec3f computeVariance(Mat block);
	Mat computeInterpolation(uchar corners[2][2],int n, int m);
	Mat quantizeMat(Mat input, int quantizationLevels, double* min, double* max);

	Mat dequantizeMat(Mat input, int quantizationLevels, double min, double max);
	
};

