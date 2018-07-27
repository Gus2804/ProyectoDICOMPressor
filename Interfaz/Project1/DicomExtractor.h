#include "DicomFileStructure.h"

#pragma once
class DicomExtractor
{
public:
	DicomExtractor();
	~DicomExtractor();
	DicomFileStructure extractDICOM(char* path);
	Study getStudyFromHeader(char* header, int length);
};

