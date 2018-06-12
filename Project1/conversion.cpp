#include <stdio.h>
#include <iostream>
#include <fstream>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core/utility.hpp>

#include "Converter.h"
#include "Compresor.h"
#include "HuffmanTree.h"
#include "HuffmanCompressor.h"
#include "DicomExtractor.h"

using namespace cv; // all the new API is put into "cv" namespace. Export its content
using namespace std;

int main(int argc, char** argv)
{
	//Ruta de imagen a convertir
	string rutaImagen = "C:\\Users\\muset\\Desktop\\Retinal Images\\diaretdb1_v_1_1\\diaretdb1_v_1_1\\resources\\images\\ddb1_fundusimages\\image003.png";

	//Ruta de imagen convertida
	char imagenDestino[] = "C:\\Users\\muset\\Desktop\\Retinal Images\\diaretdb1_v_1_1\\diaretdb1_v_1_1\\resources\\images\\ddb1_fundusimages\\image003.dcm";


	Converter converter = Converter();

	//Datos del paciente (Opcionales), 
	Study study = Study();
	study.studyDate = "20180509";
	study.patientName = "Peralta^Gustavo^^^"; //Formato de nombres de persona
	study.patientBirthdate = "19930428"; //Formato para fechas
	study.studyDescription = "Retinografia de prueba";
	study.responsable = "";//Este tambien es nombre
	study.institutionName = "Instituto Politécnico Nacional";

	converter.convertImageToDicom(rutaImagen, imagenDestino, study);

	cout << "Archivo generado: " << imagenDestino << endl;
	
	DicomExtractor extractor;
 
	//Esto sirve para separar la cabecera de la imagen y obtener datos del archivo dicom
	//Es necesario usarlo, pero se puede usar con cualquier imagen .dcm aunque debe ser de ese formato
	DicomFileStructure structure = extractor.extractDICOM(imagenDestino);

	Compresor compresor;

	//Comprimir con parametros de entrada (dicom extraido, ancho bloque m, alto bloque n, umbral, bits de cuantización)
	CompressionResults results = compresor.compressByBilinearInterpolation(structure, 4, 4, 1.0f, 8);

	cout << "Tasa de compresion: " << results.getCompressionRate() << endl;
	cout << "Entropia: " << results.getEntropy() << endl;
	cout << "PSNR: " << results.getPeakSignalToNoiseToRatio() << endl;
	cout << "Ruta de archivo comprimido: " << results.getCompressedFilePath() << endl; //Esta es la ruta del archivo que se va a transferir

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