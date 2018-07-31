#include "HuffmanTree.h"
#include <iostream>

FrequencyNode::FrequencyNode(short elementValue, FrequencyNode* nextNode) {
	element = elementValue;
	frequency = 1;
	next = nextNode;
	right = NULL;
	left = NULL;
}

FrequencyNode::FrequencyNode(short elementValue, long frequencyValue, FrequencyNode * nextNode)
{
	element = elementValue;
	frequency = frequencyValue;
	next = nextNode;
	right = NULL;
	left = NULL;
}

FrequencyNode::FrequencyNode(FrequencyNode * leftNode, FrequencyNode * rightNode, FrequencyNode * nextNode)
{
	element = NULL;
	frequency = leftNode->frequency + rightNode->frequency;
	left = leftNode;
	right = rightNode;
	next = nextNode;
}

void FrequencyNode::incrementFrequency()
{
	frequency++;
}

bool FrequencyNode::hasToShift()
{
	return next && next->frequency<frequency;
}

void FrequencyNode::fillDictionary(string dict[], string & code)
{
	if (!left&&!right) {
		/*cout << *pos << endl;
		dict[*pos].element = element;
		cout << dict[*pos].element << endl;
		dict[*pos].code = code;
		cout << dict[*pos].code << endl;
		*pos = *pos + 1;*/
		//cout << (int) element << ": " << code << endl;
		dict[element] = code;
		return;
	}
	if (left) {
		code += '0';
		left->fillDictionary(dict, code);
		code.erase(code.end() - 1);
	}
	if (right) {
		code += '1';
		right->fillDictionary(dict, code);
		code.erase(code.end() - 1);
	}

}

HuffmanTree::HuffmanTree()
{
	first = NULL;
	length = 0;
}


HuffmanTree::~HuffmanTree()
{
}

bool HuffmanTree::isEmpty()
{
	return first == NULL;
}

void HuffmanTree::insert(short element)
{
	if (isEmpty()) {
		first = new FrequencyNode(element);
	}
	else {
		FrequencyNode* newNode = new FrequencyNode(element, first);
		first = newNode;
	}
	length++;
}

void HuffmanTree::insert(FrequencyNode* left, FrequencyNode* right)
{
	if (isEmpty()) {
		first = new FrequencyNode(left, right);
	}
	else {
		FrequencyNode* newNode = new FrequencyNode(left, right, first);
		first = newNode;
	}
	length++;
}

void HuffmanTree::insert(short element, long frequency)
{
	if (isEmpty()) {
		first = new FrequencyNode(element, frequency);
	}
	else {
		FrequencyNode* newNode = new FrequencyNode(element, frequency, first);
		first = newNode;
	}
	length++;
}

FrequencyNode * HuffmanTree::search(short element)
{
	if (isEmpty()) {
		return NULL;
	}
	else {
		FrequencyNode *cursor = first;
		while (cursor&&cursor->element != element) {
			cursor = cursor->next;
		}
		return cursor;
	}
}

void HuffmanTree::shiftElement(uchar element)
{
	FrequencyNode* cursor = first;
	if (first->element == element) {
		cursor = first->next;
		first->next = cursor->next;
		cursor->next = first;
		first = cursor;
		if (first->next->hasToShift()) {
			shiftElement(first->next->element);
		}
	}
	else {
		while (cursor->next->element != element) {
			cursor = cursor->next;
		}
		FrequencyNode* aux = cursor->next;
		cursor->next = aux->next;
		aux->next = aux->next->next;
		cursor->next->next = aux;
		if (aux->hasToShift()) {
			shiftElement(aux->element);
		}
	}

}

void HuffmanTree::shiftElement(FrequencyNode * node)
{
	FrequencyNode* before = NULL;
	FrequencyNode* cursor = first;
	while (cursor != node) {
		before = cursor;
		cursor = cursor->next;
	}
	if (before != NULL) {
		before->next = cursor->next;
	}
	else {
		first = cursor->next;
	}
	cursor->next = cursor->next->next;
	if (before != NULL) {
		before->next->next = cursor;
	}
	else {
		first->next = cursor;
	}
	if (cursor->hasToShift()) {
		shiftElement(cursor);
	}
}



void HuffmanTree::print()
{
	FrequencyNode *cursor = first;
	do {
		cout << (int)cursor->element << ": " << cursor->frequency << endl;
		cursor = cursor->next;
	} while (cursor);
}

FrequencyNode * HuffmanTree::pop()
{
	FrequencyNode* firstNode = first;
	first = firstNode->next;
	firstNode->next = NULL;
	length--;
	return firstNode;
}

long HuffmanTree::getLength()
{
	return length;
}

FrequencyNode * HuffmanTree::getFirst()
{
	return first;
}

double HuffmanTree::getEntropy(long numberOfElements)
{
	double entropy = 0.0;
	FrequencyNode* cursor = first;
	while (cursor)
	{
		entropy += (cursor->frequency * log2((double)(numberOfElements / cursor->frequency)));
		cursor = cursor->next;
	}
	entropy /= numberOfElements;
	return entropy;
}

void HuffmanTree::fillFrequencyArray(uchar * array, int bitsForElement)
{
	FrequencyNode* cursor = first;
	int index = 0;
	while (cursor) {
		if (bitsForElement <= 8) {
			array[index] = cursor->element;
			array[index + 1] = (uchar)(0x000000ff & cursor->frequency);
			array[index + 2] = (uchar)((0x0000ff00 & cursor->frequency) >> 8);
			array[index + 3] = (uchar)((0x00ff0000 & cursor->frequency) >> 16);
			array[index + 4] = (uchar)((0xff000000 & cursor->frequency) >> 24);
			index += 5;
		}
		else
		{
			array[index] = (uchar)(0x000000ff & cursor->element);
			array[index + 1] = (uchar)((0x0000ff00 & cursor->element) >> 8); ;
			array[index + 2] = (uchar)(0x000000ff & cursor->frequency);
			array[index + 3] = (uchar)((0x0000ff00 & cursor->frequency) >> 8);
			array[index + 4] = (uchar)((0x00ff0000 & cursor->frequency) >> 16);
			array[index + 5] = (uchar)((0xff000000 & cursor->frequency) >> 24);
			index += 6;
		}

		cursor = cursor->next;
		
	}
}
