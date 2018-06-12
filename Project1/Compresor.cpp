#include "Compresor.h"
#include <cmath>
#include <iostream>
#include <fstream>
#include "HuffmanCompressor.h"

using namespace cv;
using namespace std;

Compresor::Compresor()
{
}


Compresor::~Compresor()
{
}

CompressionResults Compresor::compressByBilinearInterpolation(DicomFileStructure dicomFile, int m, int n, float threshold, int quantizationLevels)
{
	CompressionResults compressionResults;
	string compressedPath = string(dicomFile.getPath());
	cout << compressedPath << endl;
	compressedPath = compressedPath.substr(0, compressedPath.size() - 4);
	compressedPath.append("_compressed.comp");
	cout << compressedPath << endl;

	compressionResults.setCompressedFilePath((char*)compressedPath.c_str());

	int sigBlocks = 0;
	//Número de bloques de la imagen
	int M = dicomFile.getPixelData().cols / m;
	if (dicomFile.getPixelData().cols % m > 0) {
		M++;
	}
	int N = dicomFile.getPixelData().rows / n;
	if (dicomFile.getPixelData().rows % n > 0) {
		N++;
	}
	cout << M << "x" << N << endl;

	//Declaración de matriz de esquinas y matriz de diferencias
	Mat corners = Mat(N*2,M*2, CV_8UC3);
	Mat differences = Mat::zeros(N*n, M*m, CV_32FC3);
	Mat imageAjusted = Mat::zeros(N*n, M*m, CV_8UC3);
	imageAjusted(Rect(0, 0, dicomFile.getPixelData().cols, dicomFile.getPixelData().rows)) += dicomFile.getPixelData();

	for (int j = 0; j < N; j++) {
		for (int i = 0; i < M; i++) {
			corners.at<Vec3b>(2*j, 2*i) = imageAjusted.at<Vec3b>(j*n, i*m);
			corners.at<Vec3b>(2*j, 2*i+1) = imageAjusted.at<Vec3b>(j*n, ((i+1)*m)-1);
			corners.at<Vec3b>(2*j+1, 2*i) = imageAjusted.at<Vec3b>(((j+1)*n)-1, i*m);
			corners.at<Vec3b>(2*j+1, 2*i+1) = imageAjusted.at<Vec3b>(((j + 1)*n) - 1, ((i + 1)*m) - 1);
			Mat block;
			block = imageAjusted(Rect(i*m, j*n, m, n));
			
			Mat differencesBlock = differences(Rect(i*m, j*n, m, n));

			//clasificación			
			Vec3f variances = computeVariance(block);
			Mat blockFloat;
			block.convertTo(blockFloat, CV_32F);
			for (int k = 0; k < 3; k++) {
				if (variances[k] > threshold) {
					uchar blockCorners[2][2];
					blockCorners[0][0] = corners.at<Vec3b>(2*j, 2*i)[k];
					blockCorners[0][1] = corners.at<Vec3b>(2*j, 2*i + 1)[k];
					blockCorners[1][0] = corners.at<Vec3b>(2*j + 1, 2*i)[k];
					blockCorners[1][1] = corners.at<Vec3b>(2*j + 1, 2*i + 1)[k];
					Mat interpolation = computeInterpolation(blockCorners,n,m);
					//differencesBlock[k] = blockSplitted[k] - interpolation;
					for (int a = 0; a < n; a++) {
						Vec3f* differencesBlockRow = differencesBlock.ptr<Vec3f>(a);
						Vec3f* blockFloatRow = blockFloat.ptr<Vec3f>(a);
						float* interpolationRow = interpolation.ptr<float>(a);
						for (int b = 0; b < m; b++) {
							differencesBlockRow[b][k] = blockFloatRow[b][k] - interpolationRow[b];
						}
					}
					sigBlocks++;
				}
			}
		}
	}

	//Fase de cuantización
	Mat differencesQuantized[3];
	Mat cornersQuantized[3];

	//Calculo de máximos y mínimos
	double maxCorner[3];
	double minCorner[3];
	double maxDifference[3];
	double minDifference[3];

	Mat cornersSplitted[3];
	cv::split(corners, cornersSplitted);

	Mat differencesSplitted[3];
	cv::split(differences, differencesSplitted);

	for (int i = 0; i < 3; i++) {
		differencesQuantized[i] = quantizeMat(differencesSplitted[i], quantizationLevels, &minDifference[i], &maxDifference[i]);
		cornersQuantized[i] = quantizeMat(cornersSplitted[i], quantizationLevels, &minCorner[i], &maxCorner[i]);
	}

	//Compresión Huffman
	HuffmanTree differencesFrequencies[3], cornersFrequencies[3];
	double differencesEntropies[3], cornersEntropies[3];
	string differenceDictionaries[3][256], cornerDictionaries[3][256];
	uchar** frequenciesArray = new uchar*[6];
	int lengths[6];
	HuffmanCompressor huffmanCompressor;
	for (int i = 0; i < 3; i++) {
		huffmanCompressor.countElements(differencesQuantized[i], &differencesFrequencies[i]);
		differencesEntropies[i] = differencesFrequencies[i].getEntropy(differencesQuantized[i].rows*differencesQuantized[i].cols);
		lengths[2 * i] = differencesFrequencies[i].getLength() * 5;
		frequenciesArray[2*i] = (uchar*)malloc(sizeof(uchar)*lengths[2 * i]);		
		differencesFrequencies[i].fillFrequencyArray(frequenciesArray[2 * i]);
		huffmanCompressor.creatDictionary(&differencesFrequencies[i], differenceDictionaries[i]);

		huffmanCompressor.countElements(cornersQuantized[i], &cornersFrequencies[i]);
		cornersEntropies[i] = cornersFrequencies[i].getEntropy(cornersQuantized[i].rows*cornersQuantized[i].cols);
		lengths[2 * i + 1] = cornersFrequencies[i].getLength() * 5;
		frequenciesArray[2 * i + 1] = (uchar*)malloc(sizeof(uchar)*lengths[2 * i + 1]);
		cornersFrequencies[i].fillFrequencyArray(frequenciesArray[2 * i + 1]);
		huffmanCompressor.creatDictionary(&cornersFrequencies[i], cornerDictionaries[i]);
	}

	//Escritura del archivo temporal con bytes de huffman
	ofstream ftemp("Temp.tmp",ios::out | ios::binary);
	char nextByte[1];
	int bitCount = 0;
	for (int i = 0; i < 3; i++) {
		ftemp.write(reinterpret_cast<char*>(&minCorner[i]), sizeof(double));
		ftemp.write(reinterpret_cast<char*>(&maxCorner[i]), sizeof(double));
		ftemp.write((char*)frequenciesArray[2*i+1],lengths[2*i+1]);
		nextByte[0] = 0;
		bitCount = 0;
		for (int a = 0; a < cornersQuantized[i].rows; a++) {
			uchar* cornersQuantizedRow = cornersQuantized[i].ptr<uchar>(a);
			for (int b = 0; b < cornersQuantized[i].cols; b++) {
				uchar symbol = cornersQuantizedRow[b];
				for (int k = 0; k < cornerDictionaries[i][symbol].size(); k++, bitCount++) {
					if (bitCount == 8) {
						ftemp.write(nextByte, 1);
						nextByte[0] = 0;
						bitCount = 0;
					}
					if (cornerDictionaries[i][symbol][k] == '1') {
						nextByte[0] = nextByte[0] | (0x01 << bitCount);
					}
				}
			}
		}
		if (bitCount) {
			ftemp.write(nextByte, 1);
		}
	}
	for (int i = 0; i < 3; i++) {
		ftemp.write(reinterpret_cast<char*>(&minDifference[i]), sizeof(double));
		ftemp.write(reinterpret_cast<char*>(&maxDifference[i]), sizeof(double));
		ftemp.write((char*)frequenciesArray[2 * i], lengths[2 * i]);
		nextByte[0] = 0;
		bitCount = 0;
		for (int a = 0; a < differencesQuantized[i].rows; a++) {
			uchar* differencesQuantizedRow = differencesQuantized[i].ptr<uchar>(a);
			for (int b = 0; b < differencesQuantized[i].cols; b++) {
				uchar symbol = differencesQuantizedRow[b];
				for (int k = 0; k < differenceDictionaries[i][symbol].size(); k++, bitCount++) {
					if (bitCount == 8) {
						ftemp.write(nextByte, 1);
						nextByte[0] = 0;
						bitCount = 0;
					}
					if (differenceDictionaries[i][symbol][k] == '1') {
						nextByte[0] = nextByte[0] | (0x01 << bitCount);
					}
				}
			}
		}
		if (bitCount) {
			ftemp.write(nextByte, 1);
		}
	}
	ftemp.close();

	//Calculo de entropia
	double totalEntropyDifferences = 0;
	double totalEntropyCorners = 0;
	for (int i = 0; i < 3; i++) {
		cout << "Entropia de esquinas: " << cornersEntropies[i] << endl;
		totalEntropyCorners += cornersEntropies[i];
		cout << "Entropia de diferencias: " << differencesEntropies[i] << endl;
		totalEntropyDifferences += differencesEntropies[i];
	}
	cout << "Entropia total de esquinas: " << totalEntropyCorners << endl;
	cout << "Entropia total de diferencias: " << totalEntropyDifferences << endl;
	double totalEntropy = (totalEntropyCorners / (m*n)) + totalEntropyDifferences;
	compressionResults.setEntropy(totalEntropy);

	//Cálculo de PSNR
	double meanSquareError;
	double PSNR;

	//Interpolación a toda la imagen
	Mat interpolatedImage = Mat(N*n, M*m, CV_32FC3);
	for (int j = 0; j < N; j++) {
		for (int i = 0; i < M; i++) {
			Mat interpolatedImageBlock = interpolatedImage(Rect(i*m,j*n,m,n));
			for (int k = 0; k < 3; k++) {
				uchar blockCorners[2][2];
				blockCorners[0][0] = corners.at<Vec3b>(2*j, 2*i)[k];
				blockCorners[0][1] = corners.at<Vec3b>(2*j, 2*i + 1)[k];
				blockCorners[1][0] = corners.at<Vec3b>(2*j + 1, 2*i)[k];
				blockCorners[1][1] = corners.at<Vec3b>(2*j + 1, 2*i + 1)[k];
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

	Mat reconstructedImage = interpolatedImage + differences;
	
	int  numOfPixels = N * n * M * m;
	Mat ajustedImageFloat;
	imageAjusted.convertTo(ajustedImageFloat, CV_32F);
	Mat error = ajustedImageFloat - reconstructedImage;
	Scalar sumError = sum(error);
	meanSquareError = ((std::pow(sumError[0],2) + std::pow(sumError[1], 2) + std::pow(sumError[2], 2)) / numOfPixels) / 3;

	PSNR = 10 * log(std::pow(255, 2) / meanSquareError);
	
	compressionResults.setPeakSignalToNoiseRatio(PSNR);

	//Escritura archivo de salida
	ifstream tempFile("Temp.tmp", ios::in | ios::binary | ios::ate);
	streampos tempSize = tempFile.tellg();
	long compressedSize = (long)tempFile.tellg() + (long)sizeof(dicomFile.getHeader());
	double compressionRatio = (double)dicomFile.getSize() / (double)compressedSize;
	compressionResults.setCompressionRate(compressionRatio);
	tempFile.seekg(0);
	ofstream compressedFile(compressedPath.c_str(),ios::binary | ios::out);
	char prefix[] = "IBL";
	compressedFile.write(prefix,3);
	compressedFile.write(reinterpret_cast<char*>(&PSNR), sizeof(double));
	compressedFile.write(reinterpret_cast<char*>(&compressionRatio), sizeof(double));
	compressedFile.write(reinterpret_cast<char*>(&totalEntropy), sizeof(double));
	compressedFile.write(dicomFile.getHeader(),sizeof(dicomFile.getHeader()));
	char* tempBytes = new char[tempSize];
	tempFile.read(tempBytes, tempSize);
	compressedFile.write(tempBytes,tempSize);
	tempFile.close();
	compressedFile.close();
	remove("Temp.tmp");
	return compressionResults;
}

Vec3f Compresor::computeVariance(Mat block)
{
	int numOfPixels = block.rows*block.cols;
	Vec3f variances;
	Vec3f sum = Vec3f(0,0,0);
	for (int i = 0; i < block.rows; i++) {
		Vec3b* blockRow = block.ptr<Vec3b>(i);
		for (int j = 0; j < block.cols; j++) {
			sum[0] += blockRow[j][0];
			sum[1] += blockRow[j][1];
			sum[2] += blockRow[j][2];
		}
	}
	Vec3f mean = Vec3f(sum[0] / numOfPixels, sum[1] / numOfPixels, sum[2] / numOfPixels);
	sum = Vec3f(0, 0, 0);
	for (int i = 0; i < block.rows; i++) {
		Vec3b* blockRow = block.ptr<Vec3b>(i);
		for (int j = 0; j < block.cols; j++) {
			for (int k = 0; k < 3; k++) {
				sum[k] += (blockRow[j][k] - mean[k]) * (blockRow[j][k] - mean[k]);
				variances[k] = sqrtf(sum[k]/numOfPixels);
			}
		}
	}
	return variances;
}

Mat Compresor::computeInterpolation(uchar corners[2][2], int n, int m)
{
	Mat interpolation = Mat(n,m,CV_32FC1);
	for (int i = 0; i < n; i++) {
		float* interpolationRow = interpolation.ptr<float>(i);
		for (int j = 0; j < m; j++) {
			interpolationRow[j] = (float)(corners[0][0]*(m-1-j)*(n-1-i)+corners[0][1]*j*(n-1-i)+corners[1][0]*(m-1-j)*i+corners[1][1]*i*j) / (float)((m - 1)*(n - 1));
		}
	}
	return interpolation;
}

Mat Compresor::quantizeMat(Mat input, int quantizationLevels, double* min, double* max)
{
	minMaxLoc(input, min, max);
	Mat quantizedMat = Mat::zeros(input.rows, input.cols, CV_8UC1);
	for (int i = 0; i < input.rows; i++) {
		uchar* quantizedMatRow = quantizedMat.ptr<uchar>(i);
		float* inputRow = input.ptr<float>(i);
		for (int j = 0; j < input.cols; j++) {
			float valueQuantized = ((pow(2, quantizationLevels) - 1) * (inputRow[j] - *min)) / (*max - *min);
			quantizedMatRow[j] = (uchar)((int)round(valueQuantized));
		}
	}
	return quantizedMat;
}

//Código que puede servir

/*for (int i = 0; i < 3; i++) {
minMaxLoc(cornersSplitted[i], &minCorner[i], &maxCorner[i]);
minMaxLoc(differencesSplitted[i], &minDifference[i], &maxDifference[i]);
differencesQuantized[i] = Mat::zeros(differences.rows, differences.cols,CV_8UC1);
cornersQuantized[i] = Mat::zeros(corners.rows, corners.cols, CV_8UC1);

//cout << "Max diferencias: " << maxDifference[i] << " Min diferencias: " << minDifference[i] << endl;
for (int j = 0; j < differences.rows; j++) {
uchar* differencesQuantizedRow = differencesQuantized[i].ptr<uchar>(j);
float* differencesSplittedRow = differencesSplitted[i].ptr<float>(j);
for (int k = 0; k < differences.cols; k++) {
float difference = ((pow(2,quantizationLevels)-1) * (differencesSplittedRow[k] - minDifference[i])) / (maxDifference[i] - minDifference[i]);
differencesQuantizedRow[k] = (uchar)((int)round(difference));
}
}

huffmanCompressor.countElements(differencesQuantized[i],&differencesFrequencies[i]);

if (i == 0) {
differencesFrequencies[i].print();
}

lengths[2 * i] = differencesFrequencies[i].getLength() * 5;

dictionaries[2 * i] = (uchar*)malloc(sizeof(uchar)*lengths[2*i]);

differencesFrequencies[i].fillFrequencyArray(dictionaries[2 * i]);

differencesEntropies[i] = differencesFrequencies[i].getEntropy(differencesQuantized[i].cols * differencesQuantized[i].rows);

huffmanCompressor.creatDictionary(&differencesFrequencies[i], differenceDictionaries[i]);

//cout << "Max esquinas: " << maxCorner[i] << " Min esquinas: " << minCorner[i] << endl;
for (int j = 0; j < corners.rows; j++) {
uchar* cornersQuantizedRow = cornersQuantized[i].ptr<uchar>(j);
uchar* cornersSplittedRow = cornersSplitted[i].ptr<uchar>(j);
for (int k = 0; k < corners.cols; k++) {
cornersQuantizedRow[k] = (uchar)(255 * (cornersSplittedRow[k] - minCorner[i]) / (maxCorner[i] - minCorner[i]));
}
}

huffmanCompressor.countElements(cornersQuantized[i], &cornersFrequencies[i]);

cornersEntropies[i] = cornersFrequencies[i].getEntropy(cornersQuantized[i].cols * cornersQuantized[i].rows);

huffmanCompressor.creatDictionary(&cornersFrequencies[i],cornerDictionaries[i]);

}*/

//Escritura del archivo
/*cout << "Diccionario en char[]" << endl;
for (int i = 0; i < lengths[0]; i+=5) {
uchar element = dictionaries[0][i];
long freq = 0;
for (int j = i+4; j >= i + 1; j--) {
freq = (freq << 8) + dictionaries[0][j];
}
cout << (int)element << ": " << freq << endl;
}*/

