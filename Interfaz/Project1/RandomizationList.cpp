#include "RandomizationList.h"



RandomizationList::RandomizationList()
{
	first = NULL;
	actual = first;
	length = 0;
}


RandomizationList::~RandomizationList()
{
}

void RandomizationList::insert(int pos[2], unsigned char element)
{
	if (isEmpty()) {
		first = new RandomizationNode(pos, element);
		actual = first;
		last = first;
	}
	else {
		last->next = new RandomizationNode(pos, element);
		last = last->next;
	}
	length++;
}

void RandomizationList::next()
{
	actual = actual->next;
}

bool RandomizationList::hasNext()
{
	return actual->next;
}

void RandomizationList::restartCursor()
{
	actual = first;
}

int * RandomizationList::getActualPos()
{
	return actual->position;
}

uchar RandomizationList::getActualData()
{
	return actual->data;
}

int RandomizationList::getLength()
{
	return length;
}

bool RandomizationList::isEmpty()
{
	return first == NULL;
}

RandomizationNode::RandomizationNode(int pos[2], uchar dat, RandomizationNode * nextNode)
{
	position[0] = pos[0];
	position[1] = pos[1];
	data = dat;
	next = nextNode;
}
