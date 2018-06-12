#include "HuffmanCompressor.h"
#include "HuffmanTree.h"

HuffmanCompressor::HuffmanCompressor()
{
}


HuffmanCompressor::~HuffmanCompressor()
{
}

void HuffmanCompressor::countElements(Mat coeficient, HuffmanTree* destinyList)
{
	for (int i = 0; i < coeficient.rows; i++) {
		uchar* coeficientRow = coeficient.ptr<uchar>(i);
		for (int j = 0; j < coeficient.cols; j++) {
			FrequencyNode *node = destinyList->search(coeficientRow[j]);
			if (node) {
				node->incrementFrequency();
				if (node->hasToShift()) {
					destinyList->shiftElement(coeficientRow[j]);
				}
			}
			else {
				destinyList->insert(coeficientRow[j]);
			}
		}
	}
}

void HuffmanCompressor::creatDictionary(HuffmanTree * frequencies, string dictionary[])
{
	while (frequencies->getLength() > 1) {
		FrequencyNode *leftNode = frequencies->pop();
		FrequencyNode *rightNode = frequencies->pop();
		frequencies->insert(leftNode, rightNode);
		if (frequencies->getFirst()->hasToShift()) {
			frequencies->shiftElement(frequencies->getFirst());
		}
	}
	string code = "";
	frequencies->getFirst()->fillDictionary(dictionary, code);
	//frequencies->printCodes(frequencies->getFirst(), dictionary, 0);
}
