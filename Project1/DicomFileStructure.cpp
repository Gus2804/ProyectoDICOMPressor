#include "DicomFileStructure.h"

DicomFileStructure::DicomFileStructure()
{
}


DicomFileStructure::~DicomFileStructure()
{
}

char * DicomFileStructure::getHeader()
{
	return header;
}

void DicomFileStructure::setHeader(char * head)
{
	header = head;
}

int DicomFileStructure::getHeaderSize()
{
	return headerSize;
}

void DicomFileStructure::setHeaderSize(int headSize)
{
	headerSize = headSize;
}

Mat DicomFileStructure::getPixelData()
{
	return pixelData;
}

void DicomFileStructure::setPixelData(Mat pixels)
{
	pixelData = pixels;
}

char * DicomFileStructure::getPath()
{
	return path;
}

void DicomFileStructure::setPath(char * filePath)
{
	path = filePath;
}

long DicomFileStructure::getSize()
{
	return size;
}

void DicomFileStructure::setSize(long fileSize)
{
	size = fileSize;
}
