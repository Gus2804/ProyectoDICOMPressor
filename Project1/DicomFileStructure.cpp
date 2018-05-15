#include "DicomFileStructure.h"

DicomFileStructure::DicomFileStructure()
{
}


DicomFileStructure::~DicomFileStructure()
{
}

char * DicomFileStructure::getMetainformation()
{
	return metainformation;
}

void DicomFileStructure::setMetainformation(char * metainfo)
{
	metainformation = metainfo;
}

Study DicomFileStructure::getStudyData()
{
	return studyData;
}

void DicomFileStructure::setStudyData(Study study)
{
	studyData = study;
}

Mat DicomFileStructure::getPixelData()
{
	return pixelData;
}

void DicomFileStructure::setPixelData(Mat pixels)
{
	pixelData = pixels;
}
