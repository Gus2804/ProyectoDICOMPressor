#include"DicomFileStructure.h"

#pragma once
class Decompressor
{
public:
	Decompressor();
	~Decompressor();
	DicomFileStructure decompress(string path);
private:
	Mat computeInterpolation(uchar corners[2][2], int n, int m);
	Mat dequantizeMat(Mat input, int quantizationLevels, double min, double max);
};

