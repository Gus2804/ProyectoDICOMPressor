#include "Converter.h"
#include "Study.h"

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <ctime>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core/utility.hpp>

using namespace cv;
using namespace std;

Converter::Converter()
{
}


Converter::~Converter()
{
}

int Converter::convertImageToDicom(string sourcePath, char* destinationPath, Study studyData)
{
	Mat image = readImage(sourcePath);
	writeDICOM(&image, destinationPath, studyData);
	return 0;
}

Mat Converter::readImage(string path)
{
	return imread(path);
}

int Converter::writeDICOM(Mat* image, char* path, Study studyData)
{
	//Creación de archivo de archivo
	ofstream fsalida(path,
		ios::out | ios::binary);

	//Creacion de metainformation
	char* preamble = (char*) malloc(sizeof(char)*128);
	for (int i = 127; i >= 0; i--) {
		preamble[i] = 0;
	}
	fsalida.write(preamble,sizeof(char)*128);
	char* prefix = (char*)malloc(sizeof(char) * 4);
	prefix[0] = 'D';
	prefix[1] = 'I';
	prefix[2] = 'C';
	prefix[3] = 'M';
	fsalida.write(prefix, sizeof(char)*4);

	//Longitud de metainformación
	char* metainfoLength = (char*)malloc(sizeof(char)*12);
	metainfoLength[0] = 2;
	metainfoLength[1] = 0;
	metainfoLength[2] = 0;
	metainfoLength[3] = 0;
	metainfoLength[4] = 'U';
	metainfoLength[5] = 'L';
	metainfoLength[6] = 4;
	metainfoLength[7] = 0;
	metainfoLength[8] = 105;
	metainfoLength[9] = 0;
	metainfoLength[10] = 0;
	metainfoLength[11] = 0;
	fsalida.write(metainfoLength,sizeof(char)*12);

	//Versión de metainformación
	char* metainfoVersion = (char*)malloc(sizeof(char)*14);
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
	char* sopUidDataSet = (char*)malloc(sizeof(char)*8);
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
	char transferSyntax[18] = "1.2.840.10008.1.2";

	transferSyntaxDataSet[0] = 2;
	transferSyntaxDataSet[1] = 0;
	transferSyntaxDataSet[2] = 16;
	transferSyntaxDataSet[3] = 0;
	transferSyntaxDataSet[4] = 'U';
	transferSyntaxDataSet[5] = 'I';
	transferSyntaxDataSet[6] = 18;
	transferSyntaxDataSet[7] = 0;

	fsalida.write(transferSyntaxDataSet, sizeof(char) * 8);
	fsalida.write(transferSyntax, sizeof(char) * 18);

	//Implementation class UID
	char* implementationClassDataSet = (char*)malloc(sizeof(char)*8);
	string impleClassUID = sopInstanceUidPrefix + std::to_string(now%10) 
		+ "." + std::to_string((now%8)+1) + "." + std::to_string(now%10000); 

	implementationClassDataSet[0] = 2;
	implementationClassDataSet[1] = 0;
	implementationClassDataSet[2] = 18;
	implementationClassDataSet[3] = 0;
	implementationClassDataSet[4] = 'U';
	implementationClassDataSet[5] = 'I';
	implementationClassDataSet[6] = impleClassUID.size();
	implementationClassDataSet[7] = 0;

	fsalida.write(implementationClassDataSet, sizeof(char) * 8);
	fsalida.write(impleClassUID.c_str(), sizeof(char) * impleClassUID.size());

	//Institution


	fsalida.close();
	return 0;
}

//Nombre del paciente (0010,0010) PN
//Fecha de nacimiento (0010,0030)​ DA
//Sexo del paciente (0010,0040)​ CS
//Nombre del estudio (0008,1030) LO
//Fecha del estudio (0008,0020) DA
//Institución (0008,0080) LO
//Departamento (0008,1040) LO
//Persona responsable (0010,2297) PN
//Rol de la persona responsable (0010,2298) CS