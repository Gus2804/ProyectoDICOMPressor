#include "Compresor.h"
#include <cmath>
#include <ctime>
#include <iostream>
#include <fstream>
#include "HuffmanCompressor.h"
#include "RandomizationList.h"

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
	//cout << compressedPath << endl;
	compressedPath = compressedPath.substr(0, compressedPath.size() - 4);
	compressedPath.append("_compressed_ibl.comp");
	//cout << compressedPath << endl;

	compressionResults.setCompressedFilePath(compressedPath);

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
	Mat corners = Mat(N * 2, M * 2, CV_8UC3);
	Mat differences = Mat::zeros(N*n, M*m, CV_32FC3);
	Mat imageAjusted = Mat::zeros(N*n, M*m, CV_8UC3);
	imageAjusted(Rect(0, 0, dicomFile.getPixelData().cols, dicomFile.getPixelData().rows)) += dicomFile.getPixelData();

	//namedWindow("Imagen ajustada", WINDOW_FREERATIO);
	//imshow("Imagen ajustada", imageAjusted);
	//waitKey(0);

	for (int j = 0; j < N; j++) {
		for (int i = 0; i < M; i++) {
			corners.at<Vec3b>(2 * j, 2 * i) = imageAjusted.at<Vec3b>(j*n, i*m);
			corners.at<Vec3b>(2 * j, 2 * i + 1) = imageAjusted.at<Vec3b>(j*n, ((i + 1)*m) - 1);
			corners.at<Vec3b>(2 * j + 1, 2 * i) = imageAjusted.at<Vec3b>(((j + 1)*n) - 1, i*m);
			corners.at<Vec3b>(2 * j + 1, 2 * i + 1) = imageAjusted.at<Vec3b>(((j + 1)*n) - 1, ((i + 1)*m) - 1);
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
					blockCorners[0][0] = corners.at<Vec3b>(2 * j, 2 * i)[k];
					blockCorners[0][1] = corners.at<Vec3b>(2 * j, 2 * i + 1)[k];
					blockCorners[1][0] = corners.at<Vec3b>(2 * j + 1, 2 * i)[k];
					blockCorners[1][1] = corners.at<Vec3b>(2 * j + 1, 2 * i + 1)[k];
					Mat interpolation = computeInterpolation(blockCorners, n, m);
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

	Mat cornersFloat;
	corners.convertTo(cornersFloat, CV_32F);

	Mat cornersSplitted[3];
	cv::split(cornersFloat, cornersSplitted);

	Mat differencesSplitted[3];
	cv::split(differences, differencesSplitted);

	for (int i = 0; i < 3; i++) {
		differencesQuantized[i] = quantizeMat(differencesSplitted[i], quantizationLevels, &minDifference[i], &maxDifference[i]);
		cornersQuantized[i] = quantizeMat(cornersSplitted[i], quantizationLevels, &minCorner[i], &maxCorner[i]);
	}

	Mat differencesDequantized[3];
	Mat cornersDequantized[3];

	for (int i = 0; i < 3; i++) {
		differencesDequantized[i] = dequantizeMat(differencesQuantized[i], quantizationLevels, minDifference[i], maxDifference[i]);
		cornersDequantized[i] = dequantizeMat(cornersQuantized[i], quantizationLevels, minCorner[i], maxCorner[i]);
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
		frequenciesArray[2 * i] = (uchar*)malloc(sizeof(uchar)*lengths[2 * i]);
		differencesFrequencies[i].fillFrequencyArray(frequenciesArray[2 * i], quantizationLevels);
		huffmanCompressor.creatDictionary(&differencesFrequencies[i], differenceDictionaries[i]);

		//cout << "Min: " << minCorner[i] << ", Max: " << maxCorner[i] << endl;
		huffmanCompressor.countElements(cornersQuantized[i], &cornersFrequencies[i]);
		//cornersFrequencies[i].print();		
		cornersEntropies[i] = cornersFrequencies[i].getEntropy(cornersQuantized[i].rows*cornersQuantized[i].cols);
		lengths[2 * i + 1] = cornersFrequencies[i].getLength() * 5;
		frequenciesArray[2 * i + 1] = (uchar*)malloc(sizeof(uchar)*lengths[2 * i + 1]);
		cornersFrequencies[i].fillFrequencyArray(frequenciesArray[2 * i + 1], quantizationLevels);
		huffmanCompressor.creatDictionary(&cornersFrequencies[i], cornerDictionaries[i]);
		//cornersFrequencies[i].print();
	}

	//Escritura del archivo temporal con bytes de huffman
	ofstream ftemp("Temp", ios::out | ios::binary | ios::app);
	char nextByte;
	//char buffer[10];
	int bitCount = 0;
	int z = 0, bufferIndex;
	long lastPos, pos;
	for (int i = 0; i < 3; i++) {
		ftemp.write(reinterpret_cast<char*>(&minCorner[i]), sizeof(double));
		ftemp.write(reinterpret_cast<char*>(&maxCorner[i]), sizeof(double));
		ftemp.write(reinterpret_cast<char*>(&lengths[2 * i + 1]), sizeof(int));
		ftemp.write((char*)frequenciesArray[2 * i + 1], lengths[2 * i + 1]);
		nextByte = 0;
		bitCount = 0;
		bufferIndex = 0;
		for (int a = 0; a < cornersQuantized[i].rows; a++) {
			uchar* cornersQuantizedRow = cornersQuantized[i].ptr<uchar>(a);
			for (int b = 0; b < cornersQuantized[i].cols; b++) {
				uchar symbol = cornersQuantizedRow[b];
				for (int k = 0; k < cornerDictionaries[i][symbol].size(); k++, bitCount++) {
					if (bitCount == 8) {
						lastPos = ftemp.tellp();
						ftemp.put(nextByte);
						pos = ftemp.tellp();
						if ((pos - lastPos) > 1) {
							ftemp.seekp(lastPos + 1);
						}
						nextByte = 0;
						bitCount = 0;
					}
					if (cornerDictionaries[i][symbol][k] == '1') {
						nextByte = nextByte | (0x01 << bitCount);
					}
				}
			}
		}
		if (bitCount) {
			ftemp.put(nextByte);
		}
	}
	for (int i = 0; i < 3; i++) {
		ftemp.write(reinterpret_cast<char*>(&minDifference[i]), sizeof(double));
		ftemp.write(reinterpret_cast<char*>(&maxDifference[i]), sizeof(double));
		ftemp.write(reinterpret_cast<char*>(&lengths[2 * i]), sizeof(int));
		ftemp.write((char*)frequenciesArray[2 * i], lengths[2 * i]);
		nextByte = 0;
		bitCount = 0;
		for (int a = 0; a < differencesQuantized[i].rows; a++) {
			uchar* differencesQuantizedRow = differencesQuantized[i].ptr<uchar>(a);
			for (int b = 0; b < differencesQuantized[i].cols; b++) {
				uchar symbol = differencesQuantizedRow[b];
				//cout << (int)symbol << " ";
				for (int k = 0; k < differenceDictionaries[i][symbol].size(); k++, bitCount++) {
					if (bitCount == 8) {
						//buffer[bufferIndex] = nextByte;
						//ftemp.write(nextByte, 1);
						ftemp.put(nextByte);
						//cout << ftemp.tellp() << ": " << (int)(uchar)nextByte << endl;
						nextByte = 0;
						bitCount = 0;
						//bufferIndex++;
						/*if (bufferIndex == 10) {
							bufferIndex = 0;
							ftemp.write(buffer, 10);
						}*/
					}
					if (differenceDictionaries[i][symbol][k] == '1') {
						nextByte = nextByte | (0x01 << bitCount);
					}
				}
			}
		}
		if (bitCount) {
			ftemp.put(nextByte);
			//cout << ftemp.tellp() << ": " << (int)(uchar)nextByte << endl;
			//buffer[bufferIndex] = nextByte;
			//bufferIndex++;
		}
		//cout << endl;
		/*if (bufferIndex) {
			char* lastBuffer = new char[bufferIndex];
			for (int a = 0; a < bufferIndex; a++) {
				lastBuffer[a] = buffer[a];
			}
			ftemp.write(lastBuffer, bufferIndex);
		}*/
	}
	ftemp.close();

	//Calculo de entropia
	double totalEntropyDifferences = 0;
	double totalEntropyCorners = 0;
	for (int i = 0; i < 3; i++) {
		std::cout << "Entropia de esquinas: " << cornersEntropies[i] << endl;
		totalEntropyCorners += cornersEntropies[i];
		std::cout << "Entropia de diferencias: " << differencesEntropies[i] << endl;
		totalEntropyDifferences += differencesEntropies[i];
	}
	std::cout << "Entropia total de esquinas: " << totalEntropyCorners << endl;
	std::cout << "Entropia total de diferencias: " << totalEntropyDifferences << endl;
	double totalEntropy = (totalEntropyCorners / (m*n)) + totalEntropyDifferences;
	compressionResults.setEntropy(totalEntropy);

	//Cálculo de PSNR
	double meanSquareError;
	double PSNR;

	//Interpolación a toda la imagen
	Mat interpolatedImage = Mat(N*n, M*m, CV_32FC3);
	for (int j = 0; j < N; j++) {
		for (int i = 0; i < M; i++) {
			Mat interpolatedImageBlock = interpolatedImage(Rect(i*m, j*n, m, n));
			for (int k = 0; k < 3; k++) {
				uchar blockCorners[2][2];
				blockCorners[0][0] = corners.at<Vec3b>(2 * j, 2 * i)[k];
				blockCorners[0][1] = corners.at<Vec3b>(2 * j, 2 * i + 1)[k];
				blockCorners[1][0] = corners.at<Vec3b>(2 * j + 1, 2 * i)[k];
				blockCorners[1][1] = corners.at<Vec3b>(2 * j + 1, 2 * i + 1)[k];
				/*blockCorners[0][0] = (uchar)((int)round(cornersSplitted[k].at<float>(2 * j, 2 * i)));
				blockCorners[0][1] = (uchar)((int)round(cornersSplitted[k].at<float>(2 * j, 2 * i + 1)));
				blockCorners[1][0] = (uchar)((int)round(cornersSplitted[k].at<float>(2 * j + 1, 2 * i)));
				blockCorners[1][1] = (uchar)((int)round(cornersSplitted[k].at<float>(2 * j + 1, 2 * i + 1)));*/
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

	int numOfPixels = N * n * M * m;
	Mat ajustedImageFloat;
	imageAjusted.convertTo(ajustedImageFloat, CV_32F);
	Mat error = ajustedImageFloat - reconstructedImage;
	Scalar sumError = sum(error);
	meanSquareError = ((std::pow(sumError[0], 2) + std::pow(sumError[1], 2) + std::pow(sumError[2], 2)) / numOfPixels) / 3;

	PSNR = 10 * log(std::pow(255, 2) / meanSquareError);

	compressionResults.setPeakSignalToNoiseRatio(PSNR);

	//namedWindow("Image", WINDOW_FREERATIO);
	//imshow("Image", reconstructedImage);

	//waitKey(0);

	//Escritura archivo de salida
	ifstream tempFile("Temp", ios::in | ios::binary | ios::ate);
	streampos tempSize = tempFile.tellg();
	long compressedSize = (long)tempFile.tellg() + (long)sizeof(dicomFile.getHeader());
	double compressionRatio = (double)dicomFile.getSize() / (double)compressedSize;
	int headerSize = dicomFile.getHeaderSize();
	int imageWidth = m * M, imageHeight = n * N;
	//cout << headerSize << endl;
	//cout << *((int*)(reinterpret_cast<char*>(&headerSize))) << endl;
	compressionResults.setCompressionRate(compressionRatio);
	tempFile.seekg(0, ios::beg);
	ofstream compressedFile(compressedPath.c_str(), ios::binary | ios::out);
	char prefix[] = "IBL";
	compressedFile.write(prefix, 3);
	compressedFile.write(reinterpret_cast<char*>(&PSNR), sizeof(double));
	compressedFile.write(reinterpret_cast<char*>(&compressionRatio), sizeof(double));
	compressedFile.write(reinterpret_cast<char*>(&totalEntropy), sizeof(double));
	compressedFile.write(reinterpret_cast<char*>(&m), sizeof(int));
	compressedFile.write(reinterpret_cast<char*>(&n), sizeof(int));
	compressedFile.write(reinterpret_cast<char*>(&imageWidth), sizeof(int));
	compressedFile.write(reinterpret_cast<char*>(&imageHeight), sizeof(int));
	compressedFile.write(reinterpret_cast<char*>(&headerSize), sizeof(int));
	compressedFile.write(dicomFile.getHeader(), dicomFile.getHeaderSize());
	//cout << tempSize << endl;
	char* tempBytes = new char[tempSize];
	tempFile.read(tempBytes, tempSize);
	/*for (int i = (lengths[1] + 20); i < (lengths[1] + 120); i++) {
		cout << (int)(uchar)tempBytes[i] << endl;
	}*/
	compressedFile.write(tempBytes, tempSize);
	tempFile.close();
	compressedFile.close();
	remove("Temp");

	return compressionResults;

	
}

CompressionResults Compresor::compressByRandomization(DicomFileStructure dicomFile, float threshold)
{
	CompressionResults results;
	string compressedPath = string(dicomFile.getPath());
	compressedPath = compressedPath.substr(0, compressedPath.size() - 4);
	compressedPath.append("_compressed_csa.comp");
	results.setCompressedFilePath(compressedPath);

	Mat imageChannels[3];
	split(dicomFile.getPixelData(), imageChannels);

	Mat imageChannelsFloat[3];

	Mat dctImage[3];

	double maxDct[3];
	double minDct[3];

	for (int i = 0; i < 3; i++) {
		imageChannels[i].convertTo(imageChannelsFloat[i], CV_32F);
		dct(imageChannelsFloat[i], dctImage[i]);
	}

	Mat dctQuantized[3];
	for (int i = 0; i < 3; i++) {
		dctQuantized[i] = quantizeMat(dctImage[i], 9, &minDct[i], &maxDct[i]);
		cout << "minDCT " << i << ": " << minDct[i] << endl;
		cout << "maxDCT " << i << ": " << maxDct[i] << endl;
	}

	srand(time(NULL));

	int start = rand() % 256;

	bool clasificating = true;

	cout << dctQuantized[0].rows << "x" << dctQuantized[0].cols << endl;
	cout << "Start: " << start << endl;

	//Tecnica de selección aleatoria
	RandomizationList list[3];
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < dctQuantized[i].rows; j++) {
			short* dctRow = dctQuantized[i].ptr<short>(j);
			for (int k = 0; k < dctQuantized[i].cols; k++) {
				/*if ((int)dctRow[k] == start) {
				clasificating = true;
				}*/
				if (clasificating) {
					if ((dctRow[k] % 2) == (start % 2) && dctRow[k] < threshold) {
						int pos[2] = { j,k };
						list[i].insert(pos, dctRow[k]);
						//dctRow[k] = 0;
					}
				}
			}
		}
	}

	cout << "Longitud de la lista 0: " << list[0].getLength() << endl;
	cout << "Longitud de la lista 1: " << list[1].getLength() << endl;
	cout << "Longitud de la lista 2: " << list[2].getLength() << endl;
	//Recorrer header para insertar datos
	int count = 0, i = 0;
	list[count].restartCursor();
	cout << "Longitud de la cabecera: " << dicomFile.getHeaderSize() << endl;
	for (i = 0; i < dicomFile.getHeaderSize(); i++) {
		if (list[count].getLength()) {
			int* pos = list[count].getActualPos();
			dctQuantized[count].at<short>(pos[0], pos[1]) = dicomFile.getHeader()[i];
			if (list[count].hasNext()) {
				list[count].next();
			}
			else {
				count++;
				if (count == 3) {
					break;
				}
			}
		}
	}
	i++;
	char* headerBytes;
	short newLength = 0;
	if (i < dicomFile.getHeaderSize()) {
		newLength = dicomFile.getHeaderSize() - i;
		headerBytes = new char[newLength];
		for (int j = i; j < dicomFile.getHeaderSize(); j++) {
			headerBytes[j - i] = dicomFile.getHeader()[j];
		}
	}

	//Escritura archivo comprimido
	HuffmanTree dctFrequencies[3];
	double dctEntropies[3];
	string dctDictionaries[3][512];
	uchar** frequenciesArray = new uchar*[3];
	int lengths[3];
	HuffmanCompressor huffmanCompressor;
	for (int i = 0; i < 3; i++) {
		huffmanCompressor.countElements(dctQuantized[i], &dctFrequencies[i]);
		dctEntropies[i] = dctFrequencies[i].getEntropy(dctQuantized[i].rows*dctQuantized[i].cols);
		lengths[i] = dctFrequencies[i].getLength() * 6;
		frequenciesArray[i] = (uchar*)malloc(sizeof(uchar)*lengths[i]);
		dctFrequencies[i].fillFrequencyArray(frequenciesArray[i],9);
		huffmanCompressor.creatDictionary(&dctFrequencies[i], dctDictionaries[i]);
	}

	//Escritura del archivo temporal con bytes de huffman
	ofstream ftemp("Temp.tmp", ios::out | ios::binary);
	char nextByte;
	int bitCount = 0;
	for (int i = 0; i < 3; i++) {
		ftemp.write(reinterpret_cast<char*>(&maxDct[i]), sizeof(double));
		ftemp.write(reinterpret_cast<char*>(&minDct[i]), sizeof(double));
		ftemp.write(reinterpret_cast<char*>(&lengths[i]), sizeof(int));
		ftemp.write((char*)frequenciesArray[i], lengths[i]);
		nextByte = 0;
		bitCount = 0;
		for (int a = 0; a < dctQuantized[i].rows; a++) {
			short* dctQuantizedRow = dctQuantized[i].ptr<short>(a);
			for (int b = 0; b < dctQuantized[i].cols; b++) {
				uchar symbol = dctQuantizedRow[b];
				for (int k = 0; k < dctDictionaries[i][symbol].size(); k++, bitCount++) {
					if (bitCount == 8) {
						ftemp.put(nextByte);
						nextByte = 0;
						bitCount = 0;
					}
					if (dctDictionaries[i][symbol][k] == '1') {
						nextByte = nextByte | (0x01 << bitCount);
					}
				}
			}
		}
		if (bitCount) {
			ftemp.put(nextByte);
		}
	}
	ftemp.close();

	//Calculo de entropia
	double totalEntropy = 0;
	for (int i = 0; i < 3; i++) {
		totalEntropy += dctEntropies[i];
	}

	//Calculo de PSNR
	Mat dctDequantized[3];
	for (int i = 0; i < 3; i++) {
		list[i].restartCursor();
		if (list[i].getLength()) {
			while (list[i].hasNext()) {
				int* pos = list[i].getActualPos();
				dctQuantized[i].at<short>(pos[0], pos[1]) = list[i].getActualData();;
				list[i].next();
			}
			int* pos = list[i].getActualPos();
			dctQuantized[i].at<short>(pos[0], pos[1]) = list[i].getActualData();;
		}
		dctDequantized[i] = dequantizeMat(dctQuantized[i], 9, minDct[i], maxDct[i]);
	}

	Mat imageChannelsReconstructed[3];
	Mat imageReconstructedRounded(dicomFile.getPixelData().rows, dicomFile.getPixelData().cols, CV_8UC3);
	for (int i = 0; i < 3; i++) {
		idct(dctDequantized[i], imageChannelsReconstructed[i]);
		for (int j = 0; j < imageChannelsReconstructed[i].rows; j++) {
			float* imageChannelsReconstructedRow = imageChannelsReconstructed[i].ptr<float>(j);
			for (int k = 0; k < imageChannelsReconstructed[i].cols; k++) {
				imageReconstructedRounded.at<Vec3b>(j, k)[i] = (uchar)((int)round(imageChannelsReconstructedRow[k]));
			}
		}
	}

	int imageWidth = dicomFile.getPixelData().cols;
	int imageHeight = dicomFile.getPixelData().rows;
	int numOfPixels = imageWidth * imageHeight;
	Mat error = dicomFile.getPixelData() - imageReconstructedRounded;
	Scalar sumError = sum(error);
	double meanSquareError = ((std::pow(sumError[0], 2) + std::pow(sumError[1], 2) + std::pow(sumError[2], 2)) / numOfPixels) / 3;

	double PSNR = 10 * log(std::pow(255, 2) / meanSquareError);

	//Escritura archivo de salida
	ifstream tempFile("Temp.tmp", ios::in | ios::binary | ios::ate);
	streampos tempSize = tempFile.tellg();
	long compressedSize = (long)tempFile.tellg() + (long)sizeof(dicomFile.getHeader());
	double compressionRatio = (double)dicomFile.getSize() / (double)compressedSize;
	results.setCompressionRate(compressionRatio);
	tempFile.seekg(0);
	ofstream compressedFile(compressedPath.c_str(), ios::binary | ios::out);
	char prefix[] = "CSA";
	compressedFile.write(prefix, 3);
	compressedFile.write(reinterpret_cast<char*>(&PSNR), sizeof(double));
	cout << "PSNR: " << PSNR << endl;
	compressedFile.write(reinterpret_cast<char*>(&compressionRatio), sizeof(double));
	cout << "CR: " << compressionRatio << endl;
	compressedFile.write(reinterpret_cast<char*>(&totalEntropy), sizeof(double));
	cout << "Entropy: " << totalEntropy << endl;
	compressedFile.write(reinterpret_cast<char*>(&imageWidth), sizeof(int));
	cout << "Width: " << imageWidth << endl;
	compressedFile.write(reinterpret_cast<char*>(&imageHeight), sizeof(int));
	cout << "Height: " << imageHeight << endl;
	for (int i = 0; i < 3; i++) {
		int length = list[i].getLength();
		list[i].restartCursor();
		compressedFile.write(reinterpret_cast<char*>(&length), sizeof(int));
		cout << "Length " << i << ": " << length << endl;
		for (int j = 0; j < length; j++) {
			int* pos = list[i].getActualPos();
			char data = list[i].getActualData();
			compressedFile.write(reinterpret_cast<char*>(&pos[0]), sizeof(int));
			compressedFile.write(reinterpret_cast<char*>(&pos[1]), sizeof(int));
			compressedFile.write(&data, sizeof(char));
			if (list[i].hasNext()) {
				list[i].next();
			}	
		}
	}
	compressedFile.write(reinterpret_cast<char*>(&newLength), sizeof(int));
	cout << "Header Length: " << newLength << endl;
	if (newLength > 0) {
		compressedFile.write(headerBytes, newLength);
	}
	char* tempBytes = new char[tempSize];
	tempFile.read(tempBytes, tempSize);
	compressedFile.write(tempBytes, tempSize);
	tempFile.close();
	compressedFile.close();
	remove("Temp.tmp");

	results.setPeakSignalToNoiseRatio(PSNR);
	results.setEntropy(totalEntropy);

	return results;
}

Vec3f Compresor::computeVariance(Mat block)
{
	int numOfPixels = block.rows*block.cols;
	Vec3f variances;
	Vec3f sum = Vec3f(0, 0, 0);
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
				variances[k] = sqrtf(sum[k] / numOfPixels);
			}
		}
	}
	return variances;
}

Mat Compresor::computeInterpolation(uchar corners[2][2], int n, int m)
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

Mat Compresor::quantizeMat(Mat input, int quantizationLevels, double* min, double* max)
{
	minMaxLoc(input, min, max);
	Mat quantizedMat;
	if (quantizationLevels <= 8) {
		quantizedMat = Mat::zeros(input.rows, input.cols, CV_8UC1);
		for (int i = 0; i < input.rows; i++) {
			uchar* quantizedMatRow = quantizedMat.ptr<uchar>(i);
			float* inputRow = input.ptr<float>(i);
			for (int j = 0; j < input.cols; j++) {
				float valueQuantized = ((pow(2, quantizationLevels) - 1) * (inputRow[j] - *min)) / (*max - *min);
				quantizedMatRow[j] = (uchar)((int)round(valueQuantized));
			}
		}
	}
	else {
		quantizedMat = Mat::zeros(input.rows, input.cols, CV_16UC1);
		for (int i = 0; i < input.rows; i++) {
			ushort* quantizedMatRow = quantizedMat.ptr<ushort>(i);
			float* inputRow = input.ptr<float>(i);
			for (int j = 0; j < input.cols; j++) {
				float valueQuantized = ((pow(2, quantizationLevels) - 1) * (inputRow[j] - *min)) / (*max - *min);
				quantizedMatRow[j] = (ushort)((int)valueQuantized);
			}
		}
	}
	return quantizedMat;
}

Mat Compresor::dequantizeMat(Mat input, int quantizationLevels, double min, double max)
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

