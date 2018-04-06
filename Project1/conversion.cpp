#include <stdio.h>
#include <iostream>
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

	Converter converter = Converter();

	converter.convertImageToDicom(rutaImagen, imagenDestino);

	return 0;
}