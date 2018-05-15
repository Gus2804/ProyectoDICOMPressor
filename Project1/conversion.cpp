#include <stdio.h>
#include <iostream>
#include <fstream>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core/utility.hpp>

#include "Converter.h"

using namespace cv; // all the new API is put into "cv" namespace. Export its content
using namespace std;

int main(int argc, char** argv) 
{
	string rutaImagen = "C:\\Users\\muset\\Desktop\\Retinal Images\\diaretdb1_v_1_1\\diaretdb1_v_1_1\\resources\\images\\ddb1_fundusimages\\image002.png";

	char imagenDestino[] = "C:\\Users\\muset\\Desktop\\Retinal Images\\diaretdb1_v_1_1\\diaretdb1_v_1_1\\resources\\images\\ddb1_fundusimages\\image002.dcm";

	char ejemplo[] = "C:\\Users\\muset\\Dropbox\\TT\\Simulaciones\\01test.dcm";

	Converter converter = Converter();

	Study study = Study();
	/*study.studyDate = "20180509";
	study.patientName = "Peralta^Gustavo^^^";
	study.patientBirthdate = "19930428";*/

	converter.convertImageToDicom(rutaImagen, imagenDestino, study);
	
	ifstream fentrada(imagenDestino,
		ios::in | ios::binary);

	char* file = (char*)malloc(sizeof(char) * 1000);

	fentrada.read(file, sizeof(char) * 1000);

	for (int i = 132; i < 408; i++) {
		cout << std::hex << (unsigned int)file[i] << " " << file[i] << endl;
	}

	fentrada.close();

	//pixeles

	
	cin.get();
	
	return 0;
}

//Nombre del paciente
//Fecha de nacimiento
//Nombre del studio
//Fecha del estudio
//Institución
//Departamento
//Médico
//Buscar otras 3