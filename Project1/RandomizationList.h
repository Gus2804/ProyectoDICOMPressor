#include <opencv2/core/utility.hpp>

using namespace cv; 
using namespace std;

#pragma once
class RandomizationNode 
{
public:
	RandomizationNode(int pos[2],uchar dat, RandomizationNode *nextNode = NULL);
private:
	int position[2];
	uchar data;
	RandomizationNode* next;

	friend class RandomizationList;
};

class RandomizationList
{
public:
	RandomizationList();
	~RandomizationList();
	void insert(int pos[2], unsigned char element);
	void next();
	bool hasNext();
	void restartCursor();
	int* getActualPos();
	uchar getActualData();
	int getLength();
	bool isEmpty();

private:
	RandomizationNode * first;
	RandomizationNode * actual;
	RandomizationNode * last;
	int length;
};

