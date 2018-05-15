#include "CompressionResults.h"



CompressionResults::CompressionResults()
{
}


CompressionResults::~CompressionResults()
{
}

char * CompressionResults::getCompressedFilePath()
{
	return compressedFilePath;
}

void CompressionResults::setCompressedFilePath(char * path)
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
