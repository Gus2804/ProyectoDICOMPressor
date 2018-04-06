#include "Converter.h"

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core/utility.hpp>

using namespace cv;
using namespace std;

struct dataset {
	unsigned short *tag;
	char *vr;
	unsigned int length;
	void *value;
};

Converter::Converter()
{
}


Converter::~Converter()
{
}

int Converter::convertImageToDicom(string sourcePath, char* destinationPath)
{
	Mat image = readImage(sourcePath);
	writeDICOM(&image, destinationPath);
	return 0;
}

Mat Converter::readImage(string path)
{
	return imread(path);
}

int Converter::writeDICOM(Mat* image, char* path)
{
	//Creación de archivo de archivo
	ofstream fsalida(path,
		ios::out | ios::binary);

	//Creacion de metainformation
	char* preamble = (char*) malloc(sizeof(char)*128);
	for (int i = 127; i >= 0; i--) {
		preamble[i] = 0;
	}
	fsalida.write(preamble,sizeof(preamble));
	char* prefix = (char*)malloc(sizeof(char) * 4);
	prefix[0] = 'd';
	prefix[1] = 'i';
	prefix[2] = 'c';
	prefix[3] = 'm';
	fsalida.write(prefix, sizeof(prefix));

	fsalida.close();
	return 0;
}
