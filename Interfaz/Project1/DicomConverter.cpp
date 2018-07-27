#include "DicomConverter.h"
#include "Study.h"

#include <iostream>
#include <fstream>
#include <ctime>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core/utility.hpp>

using namespace cv;
using namespace std;

DicomConverter::DicomConverter()
{
}


DicomConverter::~DicomConverter()
{
}

int DicomConverter::convertImageToDicom(string sourcePath, char* destinationPath, Study studyData)
{
	Mat image = readImage(sourcePath);

	cout << "Dimensiones de la imagen: " << image.cols << "," << image.rows << endl;

	writeDICOM(&image, destinationPath, studyData);
	return 0;
}

Mat DicomConverter::readImage(string path)
{
	return imread(path);
}

int DicomConverter::writeDICOM(Mat* image, char* path, Study studyData)
{
	//Creación de archivo de archivo
	ofstream fsalida(path,
		ios::out | ios::binary);

	//Creación de metainformation
	char* preamble = (char*)malloc(sizeof(char) * 128);
	for (int i = 127; i >= 0; i--) {
		preamble[i] = 0;
	}
	fsalida.write(preamble, sizeof(char) * 128);
	char* prefix = (char*)malloc(sizeof(char) * 4);
	prefix[0] = 'D';
	prefix[1] = 'I';
	prefix[2] = 'C';
	prefix[3] = 'M';
	fsalida.write(prefix, sizeof(char) * 4);

	//Longitud de metainformación
	char* metainfoLength = (char*)malloc(sizeof(char) * 12);
	metainfoLength[0] = 2;
	metainfoLength[1] = 0;
	metainfoLength[2] = 0;
	metainfoLength[3] = 0;
	metainfoLength[4] = 'U';
	metainfoLength[5] = 'L';
	metainfoLength[6] = 4;
	metainfoLength[7] = 0;
	metainfoLength[8] = 139;
	metainfoLength[9] = 0;
	metainfoLength[10] = 0;
	metainfoLength[11] = 0;
	fsalida.write(metainfoLength, sizeof(char) * 12);

	//Versión de metainformación
	char* metainfoVersion = (char*)malloc(sizeof(char) * 14);
	metainfoVersion[0] = 2;
	metainfoVersion[1] = 0;
	metainfoVersion[2] = 1;
	metainfoVersion[3] = 0;
	metainfoVersion[4] = 'O';
	metainfoVersion[5] = 'B';
	metainfoVersion[6] = 0;
	metainfoVersion[7] = 0;
	metainfoVersion[8] = 2;
	metainfoVersion[9] = 0;
	metainfoVersion[10] = 0;
	metainfoVersion[11] = 0;
	metainfoVersion[12] = 0;
	metainfoVersion[13] = 1;
	fsalida.write(metainfoVersion, sizeof(char) * 14);

	//SOP Class UID Ophthalmic photography 8 bit 
	char* sopUidDataSet = (char*)malloc(sizeof(char) * 8);
	char sopUid[33] = "1.2.840.10008.5.1.4.1.1.77.1.5.1";

	sopUidDataSet[0] = 2;
	sopUidDataSet[1] = 0;
	sopUidDataSet[2] = 2;
	sopUidDataSet[3] = 0;
	sopUidDataSet[4] = 'U';
	sopUidDataSet[5] = 'I';
	sopUidDataSet[6] = 33;
	sopUidDataSet[7] = 0;

	fsalida.write(sopUidDataSet, sizeof(char) * 8);
	fsalida.write(sopUid, sizeof(char) * 33);

	//SOP Instance UID
	char* sopInstanceUidDataSet = (char*)malloc(sizeof(char) * 8);
	string sopInstanceUidPrefix = "1.2.484.0.";

	time_t t = std::time(0);
	long int now = static_cast<long int> (t) % 100000000;
	string sopInstanceUid = sopInstanceUidPrefix + "1.1." + std::to_string(now);

	sopInstanceUidDataSet[0] = 2;
	sopInstanceUidDataSet[1] = 0;
	sopInstanceUidDataSet[2] = 3;
	sopInstanceUidDataSet[3] = 0;
	sopInstanceUidDataSet[4] = 'U';
	sopInstanceUidDataSet[5] = 'I';
	sopInstanceUidDataSet[6] = 22;
	sopInstanceUidDataSet[7] = 0;

	fsalida.write(sopInstanceUidDataSet, sizeof(char) * 8);
	fsalida.write(sopInstanceUid.c_str(), sizeof(char) * sopInstanceUid.size());

	//Transfer syntax default
	char* transferSyntaxDataSet = (char*)malloc(sizeof(char) * 8);
	char transferSyntax[20] = "1.2.840.10008.1.2.1";

	transferSyntaxDataSet[0] = 2;
	transferSyntaxDataSet[1] = 0;
	transferSyntaxDataSet[2] = 16;
	transferSyntaxDataSet[3] = 0;
	transferSyntaxDataSet[4] = 'U';
	transferSyntaxDataSet[5] = 'I';
	transferSyntaxDataSet[6] = 20;
	transferSyntaxDataSet[7] = 0;

	fsalida.write(transferSyntaxDataSet, sizeof(char) * 8);
	fsalida.write(transferSyntax, sizeof(char) * 18);

	//Implementation class UID
	char* implementationClassDataSet = (char*)malloc(sizeof(char) * 8);
	string impleClassUID = sopInstanceUidPrefix + std::to_string(now % 10)
		+ "." + std::to_string((now % 8) + 1) + "." + std::to_string(now % 10000);

	implementationClassDataSet[0] = 2;
	implementationClassDataSet[1] = 0;
	implementationClassDataSet[2] = 18;
	implementationClassDataSet[3] = 0;
	implementationClassDataSet[4] = 'U';
	implementationClassDataSet[5] = 'I';
	implementationClassDataSet[6] = (char)impleClassUID.size();
	implementationClassDataSet[7] = 0;

	fsalida.write(implementationClassDataSet, sizeof(char) * 8);
	fsalida.write(impleClassUID.c_str(), sizeof(char) * impleClassUID.size());

	//Grupo 08 de dicom
	char* studyDateDataSet = (char*)malloc(sizeof(char) * 8);
	char* institutionDataSet = (char*)malloc(sizeof(char) * 8);
	char* studyDescriptionDataSet = (char*)malloc(sizeof(char) * 8);
	char* institutionDepartamentDataSet = (char*)malloc(sizeof(char) * 8);
	char* studyDataLengthDataSet = (char*)malloc(sizeof(char) * 12);

	if (!studyData.studyDate.empty()) {
		if (isValidDate(studyData.studyDate)) {
			studyDateDataSet[0] = 0x08;
			studyDateDataSet[1] = 0x00;
			studyDateDataSet[2] = 0x20;
			studyDateDataSet[3] = 0x00;
			studyDateDataSet[4] = 'D';
			studyDateDataSet[5] = 'A';
			studyDateDataSet[6] = 8;
			studyDateDataSet[7] = 0x00;
		}
		else {
			for (int i = 0; i < 8; i++) {
				studyDateDataSet[i] = 0;
			}
		}
	}
	else {
		for (int i = 0; i < 8; i++) {
			studyDateDataSet[i] = 0;
		}
	}

	if (!studyData.institutionName.empty()) {
		institutionDataSet[0] = 0x08;
		institutionDataSet[1] = 0x00;
		institutionDataSet[2] = 0x80;
		institutionDataSet[3] = 0x00;
		institutionDataSet[4] = 'L';
		institutionDataSet[5] = 'O';
		institutionDataSet[6] = (char)studyData.institutionName.size();
		institutionDataSet[7] = 0x00;
	}
	else {
		for (int i = 0; i < 8; i++) {
			institutionDataSet[i] = 0;
		}
	}

	if (!studyData.studyDescription.empty()) {
		studyDescriptionDataSet[0] = 0x08;
		studyDescriptionDataSet[1] = 0x00;
		studyDescriptionDataSet[2] = 0x30;
		studyDescriptionDataSet[3] = 0x10;
		studyDescriptionDataSet[4] = 'L';
		studyDescriptionDataSet[5] = 'O';
		studyDescriptionDataSet[6] = (char)studyData.studyDescription.size();
		studyDescriptionDataSet[7] = 0x00;
	}
	else {
		for (int i = 0; i < 8; i++) {
			studyDescriptionDataSet[i] = 0;
		}
	}

	if (!studyData.institutionDepartament.empty()) {
		institutionDepartamentDataSet[0] = 0x08;
		institutionDepartamentDataSet[1] = 0x00;
		institutionDepartamentDataSet[2] = 0x40;
		institutionDepartamentDataSet[3] = 0x10;
		institutionDepartamentDataSet[4] = 'L';
		institutionDepartamentDataSet[5] = 'O';
		institutionDepartamentDataSet[6] = (char)studyData.institutionDepartament.size();
		institutionDepartamentDataSet[7] = 0x00;
	}
	else {
		for (int i = 0; i < 8; i++) {
			institutionDepartamentDataSet[i] = 0;
		}
	}

	int length = 0;
	if (studyDateDataSet[6] > 0) {
		length = length + studyDateDataSet[6] + 8;
	}
	if (institutionDataSet[6] > 0) {
		length = length + institutionDataSet[6] + 8;
	}
	if (studyDescriptionDataSet[6] > 0) {
		length = length + studyDescriptionDataSet[6] + 8;
	}
	if (institutionDepartamentDataSet[6] > 0) {
		length = length + institutionDepartamentDataSet[6] + 8;
	}

	if (length > 0) {
		studyDataLengthDataSet[0] = 0x08;
		studyDataLengthDataSet[1] = 0x00;
		studyDataLengthDataSet[2] = 0x00;
		studyDataLengthDataSet[3] = 0x00;
		studyDataLengthDataSet[4] = 'U';
		studyDataLengthDataSet[5] = 'L';
		studyDataLengthDataSet[6] = 0x04;
		studyDataLengthDataSet[7] = 0x00;
		studyDataLengthDataSet[8] = length & 0xff;
		studyDataLengthDataSet[9] = (length >> 8) & 0xff;
		studyDataLengthDataSet[10] = (length >> 16) & 0xff;
		studyDataLengthDataSet[11] = (length >> 24) & 0xff;

		fsalida.write(studyDataLengthDataSet, sizeof(char) * 8);

		if (studyDateDataSet[6] > 0) {
			fsalida.write(studyDateDataSet, sizeof(char) * 8);
			fsalida.write(studyData.studyDate.c_str(), sizeof(char) * 8);
		}
		if (institutionDataSet[6] > 0) {
			fsalida.write(institutionDataSet, sizeof(char) * 8);
			fsalida.write(studyData.institutionName.c_str(), sizeof(char) * studyData.institutionName.length());
		}
		if (studyDescriptionDataSet[6] > 0) {
			fsalida.write(studyDescriptionDataSet, sizeof(char) * 8);
			fsalida.write(studyData.studyDescription.c_str(), sizeof(char) * studyData.studyDescription.length());
		}
		if (institutionDepartamentDataSet[6] > 0) {
			fsalida.write(institutionDepartamentDataSet, sizeof(char) * 8);
			fsalida.write(studyData.institutionDepartament.c_str(), sizeof(char) * studyData.institutionDepartament.length());
		}

	}

	//Grupo 10 dicom
	char* patientNameDataSet = (char*)malloc(sizeof(char) * 8);
	char* patientBirthdayDataSet = (char*)malloc(sizeof(char) * 8);
	char* patientSexDataSet = (char*)malloc(sizeof(char) * 8);
	char* responsableNameDataSet = (char*)malloc(sizeof(char) * 8);
	char* responsableRolDataSet = (char*)malloc(sizeof(char) * 8);
	char* clinicalDataLengthDataSet = (char*)malloc(sizeof(char) * 8);

	if (studyData.patientName.empty()) {
		for (int i = 0; i < 8; i++) {
			patientNameDataSet[i] = 0;
		}
	}
	else {
		patientNameDataSet[0] = 0x10;
		patientNameDataSet[1] = 0x00;
		patientNameDataSet[2] = 0x10;
		patientNameDataSet[3] = 0x00;
		patientNameDataSet[4] = 'P';
		patientNameDataSet[5] = 'N';
		patientNameDataSet[6] = studyData.patientName.length();
		patientNameDataSet[7] = 0x00;
	}

	if (studyData.patientBirthdate.empty()) {
		for (int i = 0; i < 8; i++) {
			patientBirthdayDataSet[i] = 0;
		}
	}
	else {
		if (isValidDate(studyData.patientBirthdate)) {
			patientBirthdayDataSet[0] = 0x10;
			patientBirthdayDataSet[1] = 0x00;
			patientBirthdayDataSet[2] = 0x30;
			patientBirthdayDataSet[3] = 0x00;
			patientBirthdayDataSet[4] = 'D';
			patientBirthdayDataSet[5] = 'A';
			patientBirthdayDataSet[6] = 0x08;
			patientBirthdayDataSet[7] = 0x00;
		}
		else {
			for (int i = 0; i < 8; i++) {
				patientBirthdayDataSet[i] = 0;
			}
		}
	}

	if (studyData.patientSex.empty()) {
		for (int i = 0; i < 8; i++) {
			patientSexDataSet[i] = 0;
		}
	}
	else {
		patientSexDataSet[0] = 0x10;
		patientSexDataSet[1] = 0x00;
		patientSexDataSet[2] = 0x40;
		patientSexDataSet[3] = 0x00;
		patientSexDataSet[4] = 'C';
		patientSexDataSet[5] = 'S';
		patientSexDataSet[6] = studyData.patientSex.length();
		patientSexDataSet[7] = 0x00;
	}

	if (studyData.responsable.empty()) {
		for (int i = 0; i < 8; i++) {
			responsableNameDataSet[i] = 0;
		}
	}
	else {
		responsableNameDataSet[0] = 0x10;
		responsableNameDataSet[1] = 0x00;
		responsableNameDataSet[2] = 0x97;
		responsableNameDataSet[3] = 0x22;
		responsableNameDataSet[4] = 'P';
		responsableNameDataSet[5] = 'N';
		responsableNameDataSet[6] = studyData.responsable.length();
		responsableNameDataSet[7] = 0x00;
	}

	if (studyData.responsableRol.empty()) {
		for (int i = 0; i < 8; i++) {
			responsableRolDataSet[i] = 0;
		}
	}
	else {
		responsableRolDataSet[0] = 0x10;
		responsableRolDataSet[1] = 0x00;
		responsableRolDataSet[2] = 0x98;
		responsableRolDataSet[3] = 0x22;
		responsableRolDataSet[4] = 'C';
		responsableRolDataSet[5] = 'S';
		responsableRolDataSet[6] = studyData.responsableRol.length();
		responsableRolDataSet[7] = 0x00;
	}

	length = 0;
	if (patientNameDataSet[6] > 0) {
		length = length + patientNameDataSet[6] + 8;
	}
	if (patientBirthdayDataSet[6] > 0) {
		length = length + patientBirthdayDataSet[6] + 8;
	}
	if (patientSexDataSet[6] > 0) {
		length = length + patientSexDataSet[6] + 8;
	}
	if (responsableNameDataSet[6] > 0) {
		length = length + responsableNameDataSet[6] + 8;
	}
	if (responsableRolDataSet[6] > 0) {
		length = length + responsableRolDataSet[6] + 8;
	}

	if (length > 0) {
		studyDataLengthDataSet[0] = 0x10;
		studyDataLengthDataSet[1] = 0x00;
		studyDataLengthDataSet[2] = 0x00;
		studyDataLengthDataSet[3] = 0x00;
		studyDataLengthDataSet[4] = 'U';
		studyDataLengthDataSet[5] = 'L';
		studyDataLengthDataSet[6] = 0x04;
		studyDataLengthDataSet[7] = 0x00;
		studyDataLengthDataSet[8] = length & 0xff;
		studyDataLengthDataSet[9] = (length >> 8) & 0xff;
		studyDataLengthDataSet[10] = (length >> 16) & 0xff;
		studyDataLengthDataSet[11] = (length >> 24) & 0xff;

		fsalida.write(studyDataLengthDataSet, sizeof(char) * 8);

		if (patientNameDataSet[6] > 0) {
			fsalida.write(patientNameDataSet, sizeof(char) * 8);
			fsalida.write(studyData.patientName.c_str(), sizeof(char) * studyData.patientName.length());
		}
		if (patientBirthdayDataSet[6] > 0) {
			fsalida.write(patientBirthdayDataSet, sizeof(char) * 8);
			fsalida.write(studyData.patientBirthdate.c_str(), sizeof(char) * 8);
		}
		if (patientSexDataSet[6] > 0) {
			fsalida.write(patientSexDataSet, sizeof(char) * 8);
			fsalida.write(studyData.patientSex.c_str(), sizeof(char) * studyData.patientSex.length());
		}
		if (responsableNameDataSet[6] > 0) {
			fsalida.write(responsableNameDataSet, sizeof(char) * 8);
			fsalida.write(studyData.responsable.c_str(), sizeof(char) * studyData.responsable.length());
		}
		if (responsableRolDataSet[6] > 0) {
			fsalida.write(responsableRolDataSet, sizeof(char) * 8);
			fsalida.write(studyData.responsableRol.c_str(), sizeof(char) * studyData.responsableRol.length());
		}

	}

	//Escritura de la imagen (Caracteristicas)
	unsigned short cols = image->cols;
	unsigned short rows = image->rows;

	cout << rows << "x" << cols << endl;

	char* imageCharacteristicsLengthDataSet = (char*)malloc(sizeof(char) * 12);
	char* samplesPerPixelDataSet = (char*)malloc(sizeof(char) * 10);
	char* photometricInterpretationDataSet = (char*)malloc(sizeof(char) * 12);
	char* planarConfigurationDataSet = (char*)malloc(sizeof(char) * 10);
	char* numberOfFramesDataSet = (char*)malloc(sizeof(char) * 10);
	char* rowsDataSet = (char*)malloc(sizeof(char) * 10);
	char* columnsDataSet = (char*)malloc(sizeof(char) * 10);
	char* bitsAllocatedDataSet = (char*)malloc(sizeof(char) * 10);
	char* bitsStoredDataSet = (char*)malloc(sizeof(char) * 10);
	char* highBitDataSet = (char*)malloc(sizeof(char) * 10);

	imageCharacteristicsLengthDataSet[0] = 0x28;
	imageCharacteristicsLengthDataSet[1] = 0x00;
	imageCharacteristicsLengthDataSet[2] = 0x00;
	imageCharacteristicsLengthDataSet[3] = 0x00;
	imageCharacteristicsLengthDataSet[4] = 'U';
	imageCharacteristicsLengthDataSet[5] = 'L';
	imageCharacteristicsLengthDataSet[6] = 4;
	imageCharacteristicsLengthDataSet[7] = 0;
	imageCharacteristicsLengthDataSet[8] = 92;
	imageCharacteristicsLengthDataSet[9] = 0x00;
	imageCharacteristicsLengthDataSet[10] = 0x00;
	imageCharacteristicsLengthDataSet[11] = 0x00;

	fsalida.write(imageCharacteristicsLengthDataSet, sizeof(char) * 12);

	samplesPerPixelDataSet[0] = 0x28;
	samplesPerPixelDataSet[1] = 0x00;
	samplesPerPixelDataSet[2] = 0x02;
	samplesPerPixelDataSet[3] = 0x00;
	samplesPerPixelDataSet[4] = 'U';
	samplesPerPixelDataSet[5] = 'S';
	samplesPerPixelDataSet[6] = 2;
	samplesPerPixelDataSet[7] = 0;
	samplesPerPixelDataSet[8] = 3;
	samplesPerPixelDataSet[9] = 0;

	fsalida.write(samplesPerPixelDataSet, sizeof(char) * 10);

	photometricInterpretationDataSet[0] = 0x28;
	photometricInterpretationDataSet[1] = 0x00;
	photometricInterpretationDataSet[2] = 0x04;
	photometricInterpretationDataSet[3] = 0x00;
	photometricInterpretationDataSet[4] = 'C';
	photometricInterpretationDataSet[5] = 'S';
	photometricInterpretationDataSet[6] = 4;
	photometricInterpretationDataSet[7] = 0;
	photometricInterpretationDataSet[8] = 'R';
	photometricInterpretationDataSet[9] = 'G';
	photometricInterpretationDataSet[10] = 'B';
	photometricInterpretationDataSet[10] = '\0';

	fsalida.write(photometricInterpretationDataSet, sizeof(char) * 12);

	planarConfigurationDataSet[0] = 0x28;
	planarConfigurationDataSet[1] = 0x00;
	planarConfigurationDataSet[2] = 0x06;
	planarConfigurationDataSet[3] = 0x00;
	planarConfigurationDataSet[4] = 'U';
	planarConfigurationDataSet[5] = 'S';
	planarConfigurationDataSet[6] = 2;
	planarConfigurationDataSet[7] = 0;
	planarConfigurationDataSet[8] = 0;
	planarConfigurationDataSet[9] = 0;

	fsalida.write(planarConfigurationDataSet, sizeof(char) * 10);

	numberOfFramesDataSet[0] = 0x28;
	numberOfFramesDataSet[1] = 0x00;
	numberOfFramesDataSet[2] = 0x08;
	numberOfFramesDataSet[3] = 0x00;
	numberOfFramesDataSet[4] = 'I';
	numberOfFramesDataSet[5] = 'S';
	numberOfFramesDataSet[6] = 2;
	numberOfFramesDataSet[7] = 0;
	numberOfFramesDataSet[8] = '1';
	numberOfFramesDataSet[9] = '\0';

	fsalida.write(numberOfFramesDataSet, sizeof(char) * 10);

	rowsDataSet[0] = 0x28;
	rowsDataSet[1] = 0x00;
	rowsDataSet[2] = 0x10;
	rowsDataSet[3] = 0x00;
	rowsDataSet[4] = 'U';
	rowsDataSet[5] = 'S';
	rowsDataSet[6] = 2;
	rowsDataSet[7] = 0;
	rowsDataSet[8] = rows & 0x00ff;
	rowsDataSet[9] = (rows & 0xff00) >> 8;

	fsalida.write(rowsDataSet, sizeof(char) * 10);

	columnsDataSet[0] = 0x28;
	columnsDataSet[1] = 0x00;
	columnsDataSet[2] = 0x11;
	columnsDataSet[3] = 0x00;
	columnsDataSet[4] = 'U';
	columnsDataSet[5] = 'S';
	columnsDataSet[6] = 2;
	columnsDataSet[7] = 0;
	columnsDataSet[8] = cols & 0xff;
	columnsDataSet[9] = (cols >> 8) & 0xff;

	fsalida.write(columnsDataSet, sizeof(char) * 10);

	bitsAllocatedDataSet[0] = 0x28;
	bitsAllocatedDataSet[1] = 0x00;
	bitsAllocatedDataSet[2] = 0x00;
	bitsAllocatedDataSet[3] = 0x01;
	bitsAllocatedDataSet[4] = 'U';
	bitsAllocatedDataSet[5] = 'S';
	bitsAllocatedDataSet[6] = 2;
	bitsAllocatedDataSet[7] = 0;
	bitsAllocatedDataSet[8] = 8;
	bitsAllocatedDataSet[9] = 0;

	fsalida.write(bitsAllocatedDataSet, sizeof(char) * 10);

	bitsStoredDataSet[0] = 0x28;
	bitsStoredDataSet[1] = 0x00;
	bitsStoredDataSet[2] = 0x01;
	bitsStoredDataSet[3] = 0x01;
	bitsStoredDataSet[4] = 'U';
	bitsStoredDataSet[5] = 'S';
	bitsStoredDataSet[6] = 2;
	bitsStoredDataSet[7] = 0;
	bitsStoredDataSet[8] = 8;
	bitsStoredDataSet[9] = 0;

	fsalida.write(bitsStoredDataSet, sizeof(char) * 10);

	highBitDataSet[0] = 0x28;
	highBitDataSet[1] = 0x00;
	highBitDataSet[2] = 0x02;
	highBitDataSet[3] = 0x01;
	highBitDataSet[4] = 'U';
	highBitDataSet[5] = 'S';
	highBitDataSet[6] = 2;
	highBitDataSet[7] = 0;
	highBitDataSet[8] = 7;
	highBitDataSet[9] = 0;

	fsalida.write(highBitDataSet, sizeof(char) * 10);

	char* pixelLengthDataSet = (char*)malloc(sizeof(char) * 12);
	int pixelsSizeInBytes = cols * rows * 3;

	pixelLengthDataSet[0] = 0xffffffe0;
	pixelLengthDataSet[1] = 0x7f;
	pixelLengthDataSet[2] = 0x00;
	pixelLengthDataSet[3] = 0x00;
	pixelLengthDataSet[4] = 'U';
	pixelLengthDataSet[5] = 'L';
	pixelLengthDataSet[6] = 4;
	pixelLengthDataSet[7] = 0;
	pixelLengthDataSet[8] = (pixelsSizeInBytes + 12) & 0xff;
	pixelLengthDataSet[9] = ((pixelsSizeInBytes + 12) >> 8) & 0xff;
	pixelLengthDataSet[10] = ((pixelsSizeInBytes + 12) >> 16) & 0xff;
	pixelLengthDataSet[11] = ((pixelsSizeInBytes + 12) >> 24) & 0xff;

	fsalida.write(pixelLengthDataSet, sizeof(char) * 12);

	char* pixelDataSet = (char*)malloc(sizeof(char) * 12);

	pixelDataSet[0] = 0xffffffe0;
	pixelDataSet[1] = 0x7f;
	pixelDataSet[2] = 0x10;
	pixelDataSet[3] = 0x00;
	pixelDataSet[4] = 'O';
	pixelDataSet[5] = 'W';
	pixelDataSet[6] = 0;
	pixelDataSet[7] = 0;
	pixelDataSet[8] = (char)pixelsSizeInBytes & 0xff;
	pixelDataSet[9] = (char)(pixelsSizeInBytes >> 8) & 0xff;
	pixelDataSet[10] = (char)(pixelsSizeInBytes >> 16) & 0xff;
	pixelDataSet[11] = (char)(pixelsSizeInBytes >> 24) & 0xff;

	fsalida.write(pixelDataSet, sizeof(char) * 12);

	for (int i = 0; i < image->rows; i++)
	{
		for (int j = 0; j < image->cols; j++)
		{
			Vec3b pixel = image->at<Vec3b>(i, j);

			char* rgb = (char*)malloc(sizeof(char) * 3);

			rgb[0] = pixel[2];
			rgb[1] = pixel[1];
			rgb[2] = pixel[0];

			fsalida.write(rgb, sizeof(char) * 3);
		}
	}

	fsalida.close();
	return 0;
}

bool DicomConverter::isValidDate(string date)
{
	time_t now = time(0);
	tm* ltm = (tm*)malloc(sizeof(tm));
	localtime_s(ltm, &now);

	if (!is_number(date)) {
		return false;
	}

	int year = std::stoi(date.substr(0, 4));
	int month = std::stoi(date.substr(4, 2));
	int day = std::stoi(date.substr(6, 2));
	if (year <= 1970 + ltm->tm_year) {
		if (year == 1970 + ltm->tm_year && month > (ltm->tm_mon + 1)) {
			return false;
		}
		if (month == (ltm->tm_mon + 1) && day > ltm->tm_mday) {
			return false;
		}
		if (day < 0 || day > 31) {
			return false;
		}
		if ((month == 4) || (month == 6) || (month == 9) || (month == 11)) {
			if (day > 0 && day <= 30) {
				return true;
			}
		}
		else if (month == 2) {
			if (ltm->tm_year % 4 == 2) {
				if (day > 0 && day <= 29) {
					return true;
				}
			}
			else {
				if (day > 0 && day <= 28) {
					return true;
				}
			}

		}
		else {
			if (day > 0 && day <= 31) {
				return true;
			}
		}
	}
	return false;
}

bool DicomConverter::is_number(string str)
{
	size_t found = str.find_first_not_of("0123456789");
	return found == std::string::npos;
}
//Fecha del estudio (0008,0020) DA
//Institución (0008,0080) LO
//Nombre del estudio (0008,1030) LO
//Departamento (0008,1040) LO
//Nombre del paciente (0010,0010) PN
//Fecha de nacimiento (0010,0030)​ DA
//Sexo del paciente (0010,0040)​ CS
//Persona responsable (0010,2297) PN
//Rol de la persona responsable (0010,2298) CS