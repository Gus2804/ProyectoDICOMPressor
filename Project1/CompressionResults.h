#pragma once
class CompressionResults
{
public:
	CompressionResults();
	~CompressionResults();
	char* getCompressedFilePath();
	void setCompressedFilePath(char* path);
	double getCompressionRate();
	void setCompressionRate(double cr);
	double getPeakSignalToNoiseToRatio();
	void setPeakSignalToNoiseRatio(double psnr);
	double getEntropy();
	void setEntropy(double entropyValue);

private:
	char* compressedFilePath;
	double compressionRate;
	double peakSignalToNoiseRatio;
	double entropy;
};

