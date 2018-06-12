#include <stdio.h>
#include <iostream>

using namespace std;

#pragma once
class CompressionResults
{
public:
	CompressionResults();
	~CompressionResults();
	string getCompressedFilePath();
	void setCompressedFilePath(string path);
	double getCompressionRate();
	void setCompressionRate(double cr);
	double getPeakSignalToNoiseToRatio();
	void setPeakSignalToNoiseRatio(double psnr);
	double getEntropy();
	void setEntropy(double entropyValue);

private:
	string compressedFilePath;
	double compressionRate;
	double peakSignalToNoiseRatio;
	double entropy;
};

