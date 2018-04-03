#include "Converter.h"



Converter::Converter()
{
}


Converter::~Converter()
{
}

int Converter::convertPNGToDicom(string sourcePath, string destinationPath)
{
	return 0;
}

int Converter::convertTIFFToDicom(string sourcePath, string destinationPath)
{
	return 0;
}

int Converter::convertPPMToDicom(string sourcePath, string destinationPath)
{
	return 0;
}

int Converter::convertDicomToPNG(string sourcePath, string destinationPath)
{
	return 0;
}

int Converter::convertDicomToTIFF(string sourcePath, string destinationPath)
{
	return 0;
}

int Converter::convertDicomToPPM(string sourcePath, string destinationPath)
{
	return 0;
}

Mat Converter::readImage(string path)
{
	return Mat();
}

int Converter::writePNG(Mat image, string path)
{
	return 0;
}

int Converter::writePPM(Mat image, string path)
{
	return 0;
}

int Converter::writeTIFF(Mat image, string path)
{
	return 0;
}

int Converter::writeDICOM(Mat image, string path)
{
	return 0;
}
