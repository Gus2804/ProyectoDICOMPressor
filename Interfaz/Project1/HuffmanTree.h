#include <opencv2/core/utility.hpp>

using namespace cv;
using namespace std;

#pragma once
typedef struct dictionaryPair {
	uchar element;
	string code;
} dictionaryPair_t;

class FrequencyNode
{
public:
	FrequencyNode(short elementValue, FrequencyNode* nextNode = NULL);
	FrequencyNode(short elementValue, long frequencyValue, FrequencyNode* nextNode = NULL);
	FrequencyNode(FrequencyNode* leftNode, FrequencyNode* rightNode, FrequencyNode* nextNode = NULL);
	void incrementFrequency();
	bool hasToShift();
	void fillDictionary(string dict[], string &code);


private:
	short element;
	long frequency;
	FrequencyNode *next;
	FrequencyNode *left;
	FrequencyNode *right;

	friend class HuffmanTree;
};

class HuffmanTree
{
public:
	HuffmanTree();
	~HuffmanTree();
	bool isEmpty();
	/*
	Metodo que inserta un nodo de elemento
	*/
	void insert(short element);
	/*
	Metodo que inserta un nodo de frecuencia
	*/
	void insert(FrequencyNode* left, FrequencyNode* right);
	/*
	Metodo que inserta un nodo de elemento y frecuencia
	*/
	void insert(short element, long frequency);
	FrequencyNode* search(short element);
	/*
	Metodo para recorrer un elemento a la siguiente posición
	*/
	void shiftElement(uchar element);
	void shiftElement(FrequencyNode* node);
	void print();
	/*
	Metodo para obtener y eliminar el primer elemento
	*/
	FrequencyNode* pop();
	long getLength();
	FrequencyNode* getFirst();
	double getEntropy(long numberOfElements);
	void fillFrequencyArray(uchar* array, int bitsForElement);

protected:
	FrequencyNode * first;
	long length;
};
