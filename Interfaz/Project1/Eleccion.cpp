#include "Eleccion.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]
int main() {
//int main(int argc, char** argv) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Interfaz::Eleccion form;
	Application::Run(%form);

	return 0;
}
