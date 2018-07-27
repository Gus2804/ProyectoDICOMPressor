#include <stdio.h>
#include <iostream>
#include <fstream>

#include "DicomConverter.h"
#include "Compresor.h"
#include "DicomExtractor.h"
#include "Decompressor.h"

using namespace std;
/*
int main()
{
	DicomExtractor extractor;
	CompressionResults results;
	Compresor compresor;

	string imagenDestino = "C:\\Users\\muset\\Desktop\\Retinal Images\\diaretdb1_v_1_1\\diaretdb1_v_1_1\\resources\\images\\ddb1_fundusimages\\image003.dcm";
	string path = "C:\\Users\\muset\\Desktop\\Retinal Images\\diaretdb1_v_1_1\\diaretdb1_v_1_1\\resources\\images\\ddb1_fundusimages\\image003_compressed_ibl.comp";
	
	DicomFileStructure structure = extractor.extractDICOM((char*)imagenDestino.c_str());

	//results = compresor.compressByBilinearInterpolation(structure, 4, 4, 1.0f, 8);
	
	Decompressor decompressor;
	decompressor.decompress(path);
	
	cin.get();
	
	return 0;
}
*/
//Nombre del paciente
//Fecha de nacimiento
//Nombre del studio
//Fecha del estudio
//Institución
//Departamento
//Médico
//Buscar otras 3