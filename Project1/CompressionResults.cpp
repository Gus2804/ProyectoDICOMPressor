#include<stdio.h>
#include "CompressionResults.h"

using namespace std;

CompressionResults::CompressionResults()
{
}


CompressionResults::~CompressionResults()
{
}

string CompressionResults::getCompressedFilePath()
{
	return compressedFilePath;
}

void CompressionResults::setCompressedFilePath(string path)
{
	compressedFilePath = path;
}

double CompressionResults::getCompressionRate()
{
	return compressionRate;
}

void CompressionResults::setCompressionRate(double cr)
{
	compressionRate = cr;
}

double CompressionResults::getPeakSignalToNoiseToRatio()
{
	return peakSignalToNoiseRatio;
}

void CompressionResults::setPeakSignalToNoiseRatio(double psnr)
{
	peakSignalToNoiseRatio = psnr;
}

double CompressionResults::getEntropy()
{
	return entropy;
}

void CompressionResults::setEntropy(double entropyValue)
{
	entropy = entropyValue;
}
