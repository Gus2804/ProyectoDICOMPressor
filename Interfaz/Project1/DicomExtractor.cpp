#include "DicomExtractor.h"

#include <fstream>

using namespace std;
using namespace cv;

DicomExtractor::DicomExtractor()
{
}


DicomExtractor::~DicomExtractor()
{
}

DicomFileStructure DicomExtractor::extractDICOM(char * path)
{
	DicomFileStructure dicomStructure;

	ifstream file(path, ios::in | ios::binary);

	file.seekg(0, ios::end);
	streampos size = file.tellg();
	file.seekg(128, ios::beg);
	char * bytes = new char[(int)size - 128];
	file.read(bytes, (int)size - 128);
	file.close();

	int i = 4;

	//busqueda por inicio de pixeles
	while (bytes[i] != 0x28 || bytes[i + 1] != 0x00 || bytes[i + 2] != 0x10 || bytes[i + 3] != 0x00) {
		i++;
	}
	short rows = 0;
	for (int j = 9; j > 7; j--) {
		rows = (rows << 8) + (bytes[i + j] & 0x000000ff);
	}
	i += 10;
	short cols = 0;
	for (int j = 9; j > 7; j--) {
		cols = (cols << 8) + (bytes[i + j] & 0x000000ff);
	}

	while (bytes[i] != 0xffffffe0 || bytes[i + 1] != 0x7f || bytes[i + 2] != 0x10 || bytes[i + 3] != 0x00) {
		i++;
	}

	char* header = new char[i+4];
	cout << i << endl;
	for (int a = 0; a < i+4; a++) {
		header[a] = bytes[a];
	}
	cout << (int)header[0] << endl;
	cout << (int)header[i] << endl;
	cout << (int)header[i + 1] << endl;
	cout << (int)header[i + 2] << endl;
	cout << (int)header[i + 3] << endl;
	int headerSize = i+4;

	i += 12;
	Mat image = Mat(rows, cols, CV_8UC3);
	int a, b;
	for (a = 0; a < rows; a++) {
		Vec3b* imageRow = image.ptr<Vec3b>(a);
		for (b = 0; b < cols; b++) {
			imageRow[b][2] = (uchar)bytes[i];
			imageRow[b][1] = (uchar)bytes[i + 1];
			imageRow[b][0] = (uchar)bytes[i + 2];
			i += 3;
		}
	}

	dicomStructure.setStudy(getStudyFromHeader(header, headerSize));
	dicomStructure.setHeader(header);
	dicomStructure.setHeaderSize(headerSize);
	dicomStructure.setPixelData(image);
	dicomStructure.setPath(path);
	dicomStructure.setSize(size);

	return dicomStructure;
}

Study DicomExtractor::getStudyFromHeader(char * header, int length)
{
	Study study;
	//Fecha del estudio (0008,0020) DA * 
	int i = 4;
	while ((header[i] != 0x08 || header[i + 1] != 0x00 || header[i + 2] != 0x20 || header[i + 3] != 0x00) && i+3<length) {
		i++;
	}
	if (i < length - 3) {
		string date = "";
		for (int j = i + 8; j < i + 16; j++) {
			date += header[j];
		}
		study.studyDate = date;
	}
	else {
		i = 4;
	}
	//Institución (0008,0080) LO
	while ((header[i] != 0x08 || header[i + 1] != 0x00 || header[i + 2] != 0x80 || header[i + 3] != 0x00) && i + 3<length) {
		i++;
	}
	if (i < length - 3) {
		int stringLength = header[i + 6];
		string institutionName = "";
		i += 8;
		for (int j = i; j < i + stringLength; j++) {
			institutionName += header[j];
		}
		study.institutionName = institutionName;
	}
	else {
		i = 4;
	}
	//Nombre del estudio (0008,1030) LO
	while ((header[i] != 0x08 || header[i + 1] != 0x00 || header[i + 2] != 0x30 || header[i + 3] != 0x10) && i + 3<length) {
		i++;
	}
	if (i < length - 3) {
		int stringLength = header[i + 6];
		string studyName = "";
		i += 8;
		for (int j = i; j < i + stringLength; j++) {
			studyName += header[j];
		}
		study.studyDescription = studyName;
	}
	else {
		i = 4;
	}
	//Departamento (0008,1040) LO
	while ((header[i] != 0x08 || header[i + 1] != 0x00 || header[i + 2] != 0x40 || header[i + 3] != 0x10) && i + 3<length) {
		i++;
	}
	if (i < length - 3) {
		int stringLength = header[i + 6];
		string institutionDepartament = "";
		i += 8;
		for (int j = i; j < i + stringLength; j++) {
			institutionDepartament += header[j];
		}
		study.institutionDepartament = institutionDepartament;
	}
	else {
		i = 4;
	}
	//Nombre del paciente (0010,0010) PN
	while ((header[i] != 0x10 || header[i + 1] != 0x00 || header[i + 2] != 0x10 || header[i + 3] != 0x00) && i + 3<length) {
		i++;
	}
	if (i < length - 3) {
		int stringLength = header[i + 6];
		string patientName = "";
		i += 8;
		for (int j = i; j < i + stringLength; j++) {
			patientName += header[j];
		}
		study.patientName = patientName;
	}
	else {
		i = 4;
	}
	//Fecha de nacimiento (0010,0030)​ DA
	while ((header[i] != 0x10 || header[i + 1] != 0x00 || header[i + 2] != 0x30 || header[i + 3] != 0x00) && i + 3<length) {
		i++;
	}
	if (i < length - 3) {
		int stringLength = header[i + 6];
		string patientBirthdate = "";
		i += 8;
		for (int j = i; j < i + stringLength; j++) {
			patientBirthdate += header[j];
		}
		study.patientBirthdate = patientBirthdate;
	}
	else {
		i = 4;
	}
	//Sexo del paciente (0010,0040)​ CS
	while ((header[i] != 0x10 || header[i + 1] != 0x00 || header[i + 2] != 0x40 || header[i + 3] != 0x00) && i + 3<length) {
		i++;
	}
	if (i < length - 3) {
		int stringLength = header[i + 6];
		string patientSex = "";
		i += 8;
		for (int j = i; j < i + stringLength; j++) {
			patientSex += header[j];
		}
		study.patientSex = patientSex;
	}
	else {
		i = 4;
	}
	//Persona responsable (0010,2297) PN
	while ((header[i] != 0x10 || header[i + 1] != 0x00 || header[i + 2] != 0x97 || header[i + 3] != 0x22) && i + 3<length) {
		i++;
	}
	if (i < length - 3) {
		int stringLength = header[i + 6];
		string responsableName = "";
		i += 8;
		for (int j = i; j < i + stringLength; j++) {
			responsableName += header[j];
		}
		study.responsable = responsableName;
	}
	else {
		i = 4;
	}
	//Rol de la persona responsable (0010,2298) CS
	while ((header[i] != 0x10 || header[i + 1] != 0x00 || header[i + 2] != 0x98 || header[i + 3] != 0x22) && i + 3<length) {
		i++;
	}
	if (i < length - 3) {
		int stringLength = header[i + 6];
		string responsableRol = "";
		i += 8;
		for (int j = i; j < i + stringLength; j++) {
			responsableRol += header[j];
		}
		study.responsableRol = responsableRol;
	}
	return study;
}
