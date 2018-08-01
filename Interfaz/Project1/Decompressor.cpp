#include "Decompressor.h"
#include "Compresor.h"
#include "HuffmanCompressor.h"
#include "RandomizationList.h"
#include "DicomExtractor.h"

#include <fstream>

using namespace std;
using namespace cv;

Decompressor::Decompressor()
{
}


Decompressor::~Decompressor()
{
}

DicomFileStructure Decompressor::decompress(string path)
{
	DicomFileStructure structure;
	string outPath = path.substr(0, path.size() - 5);
	outPath.append(".dcm");

	ofstream fileOutput(outPath, ios::out | ios::binary);
	char* preamble = (char*)malloc(sizeof(char) * 128);
	for (int i = 127; i >= 0; i--) {
		preamble[i] = 0;
	}
	fileOutput.write(preamble, sizeof(char) * 128);
	ifstream file(path, ios::in | ios::binary);
	char prefix[3];
	file.read(prefix, 3);
	double PSNR, entropy, compressionRatio;
	int imageWidth, imageHeigth, quantizationLevels;
	if (prefix[0] == 'I') {
		int headerLength, m, n;
		char *PSNRBytes, *CRBytes, *entropyBytes, *headerLengthBytes, *headerBytes;

		PSNRBytes = new char[sizeof(double)];
		file.read(PSNRBytes, sizeof(double));
		PSNR = *((double*)(PSNRBytes));

		CRBytes = new char[sizeof(double)];
		file.read(CRBytes, sizeof(double));
		compressionRatio = *((double*)(CRBytes));

		entropyBytes = new char[sizeof(double)];
		file.read(entropyBytes, sizeof(double));
		entropy = *((double*)(entropyBytes));

		headerLengthBytes = new char[sizeof(int)];
		file.read(headerLengthBytes, sizeof(int));
		m = *((int*)(headerLengthBytes));

		headerLengthBytes = new char[sizeof(int)];
		file.read(headerLengthBytes, sizeof(int));
		n = *((int*)(headerLengthBytes));

		cout << m << "x" << n << endl;

		headerLengthBytes = new char[sizeof(int)];
		file.read(headerLengthBytes, sizeof(int));
		imageWidth = *((int*)(headerLengthBytes));

		headerLengthBytes = new char[sizeof(int)];
		file.read(headerLengthBytes, sizeof(int));
		imageHeigth = *((int*)(headerLengthBytes));

		headerLengthBytes = new char[sizeof(int)];
		file.read(headerLengthBytes, sizeof(int));
		quantizationLevels = *((int*)(headerLengthBytes));

		headerLengthBytes = new char[sizeof(int)];
		file.read(headerLengthBytes, sizeof(int));
		headerLength = *((int*)(headerLengthBytes));

		cout << imageWidth << "x" << imageHeigth << endl;

		headerBytes = new char[headerLength];
		file.read(headerBytes, headerLength);
		fileOutput.write(headerBytes, headerLength);
		DicomExtractor extractor;
		structure.setStudy(extractor.getStudyFromHeader(headerBytes, headerLength));

		char* doubleBytes = new char[sizeof(double)];
		char* intBytes = new char[sizeof(int)];
		double maxCorners[3], minCorners[3], maxDifferences[3], minDifferences[3];
		int freqCornersLength[3], freqDifferenceLength[3];
		uchar* freqCorners, *freqDifferences;
		HuffmanCompressor compressor;
		HuffmanTree tree, diffTree;
		string differenceDictionaries[3][256], cornerDictionaries[3][256];
		Mat cornersMat[3], differencesMat[3];
		uchar** corners = new uchar*[3];
		uchar** differencies = new uchar*[3];
		string code;
		
		cout << "extracción de esquinas" << endl;
		for (int i = 0; i < 3; i++) {
			file.read(doubleBytes, sizeof(double));
			minCorners[i] = *((double*)(doubleBytes));

			file.read(doubleBytes, sizeof(double));
			maxCorners[i] = *((double*)(doubleBytes));

			file.read(intBytes, sizeof(int));
			freqCornersLength[i] = *((int*)(intBytes));
			
			freqCorners = new uchar[freqCornersLength[i]];
			file.read((char*)freqCorners, freqCornersLength[i]);
			uchar element;
			long frequency = 0;
			long totalElements = 0;
			if (tree.getLength() == 1) {
				tree.pop();
			}
			for (int j = freqCornersLength[i] - 1; j >= 0; j--) {
				if (j % 5 == 0) {
					element = freqCorners[j];
					tree.insert(element, frequency);
					totalElements += frequency;
					frequency = 0;
				}
				else {
					frequency = (frequency << 8) + freqCorners[j];
				}
			}
			compressor.creatDictionary(&tree, cornerDictionaries[i]);
			//cout << "Diccionario creado " << totalElements << endl;

			corners[i] = new uchar[totalElements];
			char nextByte;
			long symbolCounter = 0;
			int byteCounter = 0;
			while (symbolCounter < totalElements) {
				file.get(nextByte);
				/*if (byteCounter < 50) {
					cout << (int)(uchar)nextByte << endl;
					byteCounter++;
				}*/
				for (int k = 0; k < 8; k++) {
					if ((nextByte >> k) & 0x01)
						code += '1';
					else
						code += '0';
					for (int a = 0; a < 256; a++) {
						if (cornerDictionaries[i][a].length()) {
							if (cornerDictionaries[i][a] == code) {
								corners[i][symbolCounter] = (uchar)a;
								code.clear();
								symbolCounter++;
								break;
							}
						}
					}
					if (symbolCounter == totalElements) {
						break;
					}
				}
			}
		}
		cout << "Iniciando extracción de diferencias" << endl;
		for (int i = 0; i < 3; i++) {
			file.read(doubleBytes, sizeof(double));
			minDifferences[i] = *((double*)(doubleBytes));
			file.read(doubleBytes, sizeof(double));
			maxDifferences[i] = *((double*)(doubleBytes));
			file.read(intBytes, sizeof(int));
			freqDifferenceLength[i] = *((int*)(intBytes));
			freqDifferences = new uchar[freqDifferenceLength[i]];
			file.read((char*)freqDifferences, freqDifferenceLength[i]);
			uchar element;
			long frequency = 0;
			long totalElements = 0;
			if (diffTree.getLength() == 1) {
				diffTree.pop();
			}
			for (int j = freqDifferenceLength[i] - 1; j >= 0; j--) {
				if (j % 5 == 0) {
					element = freqDifferences[j];
					diffTree.insert(element, frequency);
					totalElements += frequency;
					frequency = 0;
				}
				else {
					frequency = (frequency << 8) + freqDifferences[j];
				}
			}
			compressor.creatDictionary(&diffTree, differenceDictionaries[i]);
			differencies[i] = new uchar[totalElements];
			char nextByte;
			long symbolCounter = 0;
			while (symbolCounter < totalElements) {
				file.get(nextByte);
				for (int k = 0; k < 8; k++) {
					if ((nextByte >> k) & 0x01)
						code += '1';
					else
						code += '0';
					for (int a = 0; a < 256; a++) {
						if (differenceDictionaries[i][a] == code) {
							differencies[i][symbolCounter] = (uchar)a;
							code.clear();
							symbolCounter++;
							break;
						}
					}
					if (symbolCounter == totalElements) {
						break;
					}
				}
			}
		}
		cout << "Termina Huffman" << endl;
		Mat cornersDequantized[3], differencesDequantized[3];
		int index = 0;
		for (int i = 0; i < 3; i++) {
			index = 0;
			cornersMat[i] = Mat((imageHeigth / n) * 2, (imageWidth / m) * 2, CV_8UC1);
			for (int j = 0; j < (imageHeigth / n) * 2; j++) {
				uchar* cornersRow = cornersMat[i].ptr<uchar>(j);
				for (int k = 0; k < (imageWidth / m) * 2; k++) {
					//cout << index << " ";
					cornersRow[k] = corners[i][index];
					index++;
				}
			}
			cornersDequantized[i] = dequantizeMat(cornersMat[i], 8, minCorners[i], maxCorners[i]);
			index = 0;
			differencesMat[i] = Mat(imageHeigth, imageWidth, CV_8UC1);
			for (int j = 0; j < imageHeigth; j++) {
				uchar* differencesRow = differencesMat[i].ptr<uchar>(j);
				for (int k = 0; k < imageWidth; k++) {
					differencesRow[k] = differencies[i][index];
					index++;
				}
			}
			differencesDequantized[i] = dequantizeMat(differencesMat[i], quantizationLevels, minDifferences[i], maxDifferences[i]);
		}
		cout << "Termina Decuantización" << endl;
		Mat cornersDequantizedUchar[3];
		for (int i = 0; i < 3; i++) {
			cornersDequantized[i].convertTo(cornersDequantizedUchar[i], CV_8U);
		}
		cout << "Inicia intepolacion" << endl;
		Mat interpolatedImage = Mat(imageHeigth, imageWidth, CV_32FC3);
		for (int j = 0; j < imageHeigth/n; j++) {
			for (int i = 0; i < imageWidth/m; i++) {
				Mat interpolatedImageBlock = interpolatedImage(Rect(i*m, j*n, m, n));
				for (int k = 0; k < 3; k++) {
					uchar blockCorners[2][2];
					blockCorners[0][0] = cornersDequantizedUchar[k].at<uchar>(2 * j, 2 * i);
					blockCorners[0][1] = cornersDequantizedUchar[k].at<uchar>(2 * j, 2 * i + 1);
					blockCorners[1][0] = cornersDequantizedUchar[k].at<uchar>(2 * j + 1, 2 * i);
					blockCorners[1][1] = cornersDequantizedUchar[k].at<uchar>(2 * j + 1, 2 * i + 1);
					Mat interpolation = computeInterpolation(blockCorners, n, m);
					for (int a = 0; a < n; a++) {
						Vec3f* interpolatedBlockRow = interpolatedImageBlock.ptr<Vec3f>(a);
						float* interpolationRow = interpolation.ptr<float>(a);
						for (int b = 0; b < m; b++) {
							interpolatedBlockRow[b][k] = interpolationRow[b];
						}
					}
				}
			}
		}

		Mat differencesMerged;
		merge(differencesDequantized, 3, differencesMerged);

		Mat imageReconstructed = interpolatedImage + differencesMerged;

		Mat imageFinal;
		imageReconstructed.convertTo(imageFinal, CV_8U);

		structure.setPixelData(imageFinal);

		for (int i = 0; i < imageFinal.rows; i++)
		{
			for (int j = 0; j < imageFinal.cols; j++)
			{
				Vec3b pixel = imageFinal.at<Vec3b>(i, j);

				char* rgb = (char*)malloc(sizeof(char) * 3);

				rgb[0] = pixel[1];
				rgb[1] = pixel[0];
				rgb[2] = pixel[2];

				fileOutput.write(rgb, sizeof(char) * 3);
			}
		}

	}
	else {
		RandomizationList list[3];
		char *PSNRBytes, *CRBytes, *entropyBytes, *readBytes, *doubleBytes, *headerBytes;
		uchar *frequencies;
		int headerLength, frequencyLengths[3];
		double minDCT[3], maxDCT[3];
		HuffmanCompressor compressor;
		HuffmanTree tree;
		string dictionaries[3][512];
		short** DCTValues = new short*[3];
		PSNRBytes = new char[sizeof(double)];
		file.read(PSNRBytes, sizeof(double));
		PSNR = *((double*)(PSNRBytes));
		CRBytes = new char[sizeof(double)];
		file.read(CRBytes, sizeof(double));
		compressionRatio = *((double*)(CRBytes));
		entropyBytes = new char[sizeof(double)];
		file.read(entropyBytes, sizeof(double));
		entropy = *((double*)(entropyBytes));
		readBytes = new char[sizeof(int)];
		file.read(readBytes, sizeof(int));
		imageWidth = *((int*)(readBytes));
		readBytes = new char[sizeof(int)];
		file.read(readBytes, sizeof(int));
		imageHeigth = *((int*)(readBytes));
		for (int i = 0; i < 3; i++) {
			readBytes = new char[sizeof(int)];
			file.read(readBytes, sizeof(int));
			int length = *((int*)(readBytes));
			for (int j = 0; j < length; j++) {
				int pos[2];
				readBytes = new char[sizeof(int)];
				file.read(readBytes, sizeof(int));
				pos[0] = *((int*)(readBytes));
				readBytes = new char[sizeof(int)];
				file.read(readBytes, sizeof(int));
				pos[1] = *((int*)(readBytes));
				unsigned char data = file.get();
				list[i].insert(pos, data);
			}
		}
		readBytes = new char[sizeof(int)];
		file.read(readBytes, sizeof(int));
		headerLength = *((int*)(readBytes));
		if (headerLength > 0) {
			headerBytes = new char[headerLength];
			file.read(headerBytes, headerLength);
		}
		string code = "";
		for (int i = 0; i < 3; i++) {
			doubleBytes = new char[sizeof(double)];
			file.read(doubleBytes, sizeof(double));
			minDCT[i] = *((double*)(doubleBytes));

			doubleBytes = new char[sizeof(double)];
			file.read(doubleBytes, sizeof(double));
			maxDCT[i] = *((double*)(doubleBytes));

			readBytes = new char[sizeof(int)];
			file.read(readBytes, sizeof(int));
			frequencyLengths[i] = *((int*)(readBytes));

			frequencies = new uchar[frequencyLengths[i]];
			file.read((char*)frequencies, frequencyLengths[i]);
			short element = 0;
			long frequency = 0;
			long totalElements = 0;
			
			if (tree.getLength() == 1) {
				tree.pop();
			}
			for (int j = frequencyLengths[i] - 1; j >= 0; j--) {
				
				if (j % 6 <= 1) {
					element = (element<<8)+ frequencies[j];
					if (j % 6 == 0) {
						cout << element << ": " << frequency << endl;
						tree.insert(element, frequency);
						totalElements += frequency;
						frequency = 0;
						element = 0;
					}
				}
				else {
					frequency = (frequency << 8) + frequencies[j];
				}
			}
			compressor.creatDictionary(&tree, dictionaries[i]);

			DCTValues[i] = new short[totalElements];
			char nextByte;
			long symbolCounter = 0;
			int byteCounter = 0;
			while (symbolCounter < totalElements) {
				file.get(nextByte);
				for (int k = 0; k < 8; k++) {
					if ((nextByte >> k) & 0x01)
						code += '1';
					else
						code += '0';
					for (int a = 0; a < 512; a++) {
						if (dictionaries[i][a].length()) {
							if (dictionaries[i][a] == code) {
								DCTValues[i][symbolCounter] = a;
								code.clear();
								symbolCounter++;
								break;
							}
						}
					}
					if (symbolCounter == totalElements) {
						break;
					}
				}
			}
		}

		Mat dctQuantized[3];

		Mat dctDequantized[3];

		char header[2048];
		int index = 0, count=0;
		char aux;
		for (int i = 0; i < 3; i++) {
			index = 0;
			dctQuantized[i] = Mat(imageHeigth, imageWidth, CV_16SC1);
			for (int j = 0; j < imageHeigth; j++) {
				short* dctQuantizedRow = dctQuantized[i].ptr<short>(j);
				for (int k = 0; k < imageWidth; k++) {
					dctQuantizedRow[k] = DCTValues[i][index];
					index++;
				}
			}

			list[i].restartCursor();
			if (list[i].getLength()) {
				while (list[i].hasNext()) {
					int* pos = list[i].getActualPos();
					if (count < 4 ||
						((header[count - 4] != 0xffffffe0) ||
						(header[count - 3] != 0x7f) ||
						(header[count - 2] != 0x10) ||
						(header[count - 1] != 0x00))) {
						aux = (char)dctQuantized[i].at<short>(pos[0], pos[1]);
						header[count] = aux;
						count++;
					}
					dctQuantized[i].at<short>(pos[0], pos[1]) = list[i].getActualData();;
					list[i].next();
				}
				int* pos = list[i].getActualPos();
				if (index < 4 ||
					((header[index - 4] != 0xffffffe0) ||
					(header[index - 3] != 0x7f) ||
					(header[index - 2] != 0x10) ||
					(header[index - 1] != 0x00))) {
					aux = (char)dctQuantized[i].at<short>(pos[0], pos[1]);
					header[index] = aux;
					index++;
				}
				dctQuantized[i].at<short>(pos[0], pos[1]) = list[i].getActualData();;
			}
			dctDequantized[i] = dequantizeMat(dctQuantized[i], 9, minDCT[i], maxDCT[i]);
		}

		if (headerLength > 0) {
			for (int i = 0; i < headerLength; i++) {
				header[count+1+i] = headerBytes[i];
			}
		}

		Mat imageChannelsReconstructed[3];
		Mat imageReconstructedRounded(imageHeigth, imageWidth, CV_8UC3);
		for (int i = 0; i < 3; i++) {
			idct(dctDequantized[i], imageChannelsReconstructed[i]);
			for (int j = 0; j < imageChannelsReconstructed[i].rows; j++) {
				float* imageChannelsReconstructedRow = imageChannelsReconstructed[i].ptr<float>(j);
				for (int k = 0; k < imageChannelsReconstructed[i].cols; k++) {
					imageReconstructedRounded.at<Vec3b>(j, k)[i] = (uchar)((int)round(imageChannelsReconstructedRow[k]));
				}
			}
		}
		structure.setPixelData(imageReconstructedRounded);
		fileOutput.write(header, headerLength+count+1);

		for (int i = 0; i < imageReconstructedRounded.rows; i++)
		{
			for (int j = 0; j < imageReconstructedRounded.cols; j++)
			{
				Vec3b pixel = imageReconstructedRounded.at<Vec3b>(i, j);

				char* rgb = (char*)malloc(sizeof(char) * 3);

				rgb[0] = pixel[0];
				rgb[1] = pixel[1];
				rgb[2] = pixel[2];

				fileOutput.write(rgb, sizeof(char) * 3);
			}
		}
	}
	file.close();
	fileOutput.close();
	return structure;
}

Mat Decompressor::computeInterpolation(uchar corners[2][2], int n, int m)
{
	Mat interpolation = Mat(n, m, CV_32FC1);
	for (int i = 0; i < n; i++) {
		float* interpolationRow = interpolation.ptr<float>(i);
		for (int j = 0; j < m; j++) {
			interpolationRow[j] = (float)(corners[0][0] * (m - 1 - j)*(n - 1 - i) + corners[0][1] * j*(n - 1 - i) + corners[1][0] * (m - 1 - j)*i + corners[1][1] * i*j) / (float)((m - 1)*(n - 1));
		}
	}
	return interpolation;
}

Mat Decompressor::dequantizeMat(Mat input, int quantizationLevels, double min, double max)
{
	Mat dequantizedMat = Mat::zeros(input.rows, input.cols, CV_32FC1);

	for (int i = 0; i < input.rows; i++) {
		float* dequantizedMatRow = dequantizedMat.ptr<float>(i);
		if (quantizationLevels <= 8) {
			uchar* inputRow = input.ptr<uchar>(i);
			for (int j = 0; j < input.cols; j++) {
				float valueDequantized = ((inputRow[j] * (max - min)) / (pow(2, quantizationLevels) - 1)) + min;
				dequantizedMatRow[j] = valueDequantized;
			}
		}
		else {
			ushort* inputRow = input.ptr<ushort>(i);
			for (int j = 0; j < input.cols; j++) {
				float valueDequantized = ((inputRow[j] * (max - min)) / (pow(2, quantizationLevels) - 1)) + min;
				dequantizedMatRow[j] = valueDequantized;
			}
		}
	}
	return dequantizedMat;
}
