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
	//Número de bloques de la imagen
	int M = dicomFile.getPixelData().cols / m;
	if (dicomFile.getPixelData().cols % m > 0) {
		M++;
	}
	int N = dicomFile.getPixelData().rows / n;
	if (dicomFile.getPixelData().rows % n > 0) {
		N++;
	}

	//Declaración de matriz de esquinas y matriz de diferencias
	Mat corners = Mat(N*2,M*2, CV_8UC3);
	Mat differences = Mat::zeros(dicomFile.getPixelData().rows, dicomFile.getPixelData().cols, CV_64FC3);

	for (int j = 0; j < N; j++) {
		for (int i = 0; i < M; i++) {
			corners.at<Vec3b>(j, i) = dicomFile.getPixelData().at<Vec3b>(j*n, i*m);
			corners.at<Vec3b>(j, i+1) = dicomFile.getPixelData().at<Vec3b>(j*n, ((i+1)*m)-1);
			corners.at<Vec3b>(j+1, i) = dicomFile.getPixelData().at<Vec3b>(((j+1)*n)-1, i*m);
			corners.at<Vec3b>(j+1, i+1) = dicomFile.getPixelData().at<Vec3b>(((j + 1)*n) - 1, ((i + 1)*m) - 1);
			Mat block = (dicomFile.getPixelData())(Rect(j*n, i*m, n, m));
			Mat differencesBlock = differences(Rect(j*n, i*m, n, m));
			//clasificación			
			Vec3f variances = computeVariance(block);
			for (int k = 0; k < 3; k++) {
				if (variances[k] > threshold) {
					uchar blockCorners[2][2];
					blockCorners[0][0] = corners.at<Vec3b>(j, i)[k];
					blockCorners[0][1] = corners.at<Vec3b>(j, i + 1)[k];
					blockCorners[1][0] = corners.at<Vec3b>(j + 1, i)[k];
					blockCorners[1][1] = corners.at<Vec3b>(j + 1, i + 1)[k];
					Mat interpolation = computeInterpolation(blockCorners,n,m);
					for (int a = 0; a < n; a++) {
						Vec3f* differencesRow = differencesBlock.ptr<Vec3f>(a);
						float* interpolationRow = interpolation.ptr<float>(a);
						Vec3b* imageRow = block.ptr<Vec3b>(a);
						for (int b = 0; b < m; b++) {
							differencesRow[b][k] = imageRow[b][k] - interpolationRow[b];
						}
					}
				}
			}
		}
	}
	return CompressionResults();
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
	Vec3f median = Vec3f(sum[0] / numOfPixels, sum[1] / numOfPixels, sum[2] / numOfPixels);
	sum = Vec3f(0, 0, 0);
	for (int i = 0; i < block.rows; i++) {
		Vec3b* blockRow = block.ptr<Vec3b>(i);
		for (int j = 0; j < block.cols; j++) {
			for (int k = 0; k < 3; k++) {
				sum[k] += (blockRow[j][k] - median[k]) * (blockRow[j][k] - median[k]);
				variances[k] = sqrtf(sum[k]/numOfPixels);
			}
		}
	}
	return variances;
}

Mat Compresor::computeInterpolation(uchar corners[2][2], int n, int m)
{
	Mat interpolation = Mat(n,m,CV_64FC1);
	for (int i = 0; i < n; i++) {
		float* interpolationRow = interpolation.ptr<float>(i);
		for (int j = 0; j < m; j++) {
			interpolationRow[i] = (corners[0][0] / (n*m))*(m - j - 1)*(n - i - 1) +
				(corners[0][1] / (n*m))*(j - 1)*(n - i - 1) +
				(corners[1][0] / (n*m))*(m - j - 1)*(i - 1) +
				(corners[1][1] / (n*m))*(j - 1)*(i - 1);
		}
	}
	return interpolation;
}
