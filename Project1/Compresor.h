#include "CompressionResults.h"
#include "DicomFileStructure.h"

#pragma once
class Compresor
{
public:
	Compresor();
	~Compresor();
	CompressionResults compressByBilinearInterpolation(DicomFileStructure dicomFile);
};

