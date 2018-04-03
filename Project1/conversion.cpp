#include <stdio.h>
#include <iostream>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core/utility.hpp>

using namespace cv; // all the new API is put into "cv" namespace. Export its content
using namespace std;

int main(int argc, char** argv) 
{
	string rutaImagen = "C:\\Users\\muset\\Desktop\\Retinal Images\\diaretdb1_v_1_1\\diaretdb1_v_1_1\\resources\\images\\ddb1_fundusimages\\image002.png";

	Mat imagen = imread(rutaImagen);

	if (imagen.empty()) {
		cout << "Could not open or find the image" << std::endl;
		return -1;
	}

	namedWindow("Display window", WINDOW_AUTOSIZE); // Create a window for display.
	imshow("Display window", imagen);                // Show our image inside it.
	waitKey(0); // Wait for a keystroke in the window

	return 0;
}