#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core/utility.hpp>

#include "HuffmanTree.h"

using namespace cv;

#pragma once
class HuffmanCompressor
{
public:
	HuffmanCompressor();
	~HuffmanCompressor();
	void countElements(Mat coeficient, HuffmanTree* destinyList);
	void creatDictionary(HuffmanTree* frequencies, string dictionary[]);
};
