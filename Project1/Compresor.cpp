#include "Compresor.h"
#include <cmath>

Compresor::Compresor()
{
}


Compresor::~Compresor()
{
}

CompressionResults Compresor::compressByBilinearInterpolation(DicomFileStructure dicomFile, int m, int n, float threshold)
{
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
		cv::minMaxLoc(cornersSplitted[i], &minCorner[i], &maxCorner[i]);
		cv::minMaxLoc(differencesSplitted[i], &minDifference[i], &maxDifference[i]);
		differencesQuantized[i] = Mat::zeros(differences.rows, differences.cols,CV_8UC1);
		cornersQuantized[i] = Mat::zeros(corners.rows, corners.cols, CV_8UC1);

		for (int j = 0; j < differences.rows; j++) {
			uchar* differencesQuantizedRow = differencesQuantized[i].ptr<uchar>(j);
			float* differencesSplittedRow = differencesSplitted[i].ptr<float>(j);
			for (int k = 0; k < differences.cols; k++) {
				differencesQuantizedRow[k] = (uchar) (255 * (differencesSplittedRow[k] - minDifference[i])/(maxDifference[i] - minDifference[i]));
			}
		}

		for (int j = 0; j < corners.rows; j++) {
			uchar* cornersQuantizedRow = cornersQuantized[i].ptr<uchar>(j);
			uchar* cornersSplittedRow = cornersSplitted[i].ptr<uchar>(j);
			for (int k = 0; k < corners.cols; k++) {
				cornersQuantizedRow[k] = (uchar)(255 * (cornersSplittedRow[k] - minCorner[i]) / (maxCorner[i] - minCorner[i]));
			}
		}
	}

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

	cout << "Bloques significativos: " << sigBlocks << endl;

	cout << "PSNR: " << PSNR << endl;

	CompressionResults compressionResults = CompressionResults();
	compressionResults.setPeakSignalToNoiseRatio(PSNR);
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
