#pragma once

#include <stdio.h>
#include <iostream>
#include <ostream>
#include <vcclr.h>
#include <atlstr.h>
#include <msclr\marshal_cppstd.h>

#include "DicomConverter.h"

#include "Info.h"
#include "ValoresEntrada.h"

#using <mscorlib.dll>

using namespace std;

namespace Interfaz {

	using namespace System;
	using namespace System::Runtime::InteropServices;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace std;
#include <stdio.h>
#include <iostream>
	/// <summary>
	/// Resumen de MyForm
	/// </summary>
	public ref class TransmisorF : public System::Windows::Forms::Form
	{
	public:
		TransmisorF(void)
		{
			InitializeComponent();
			//
			//TODO: agregar c�digo de constructor aqu�
			//
		}

	protected:
		/// <summary>
		/// Limpiar los recursos que se est�n usando.
		/// </summary>
		~TransmisorF()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  abrirbtn;
	protected:
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog1;
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::TextBox^  nombre;





	private: System::Windows::Forms::TextBox^  responsable;
	private: System::Windows::Forms::TextBox^  responsableRol;
	private: System::Windows::Forms::TextBox^  studyDescription;

	private: System::Windows::Forms::TextBox^  institutionName;
	private: System::Windows::Forms::TextBox^  institutionDepartament;
	private: System::Windows::Forms::TextBox^  ruta;
	private: System::Windows::Forms::Button^  convbtn;
	private: System::Windows::Forms::Button^  compbtn;
	private: System::Windows::Forms::Button^  enviarbtn;
	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  ayudaToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  salirToolStripMenuItem;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::Label^  label8;
	private: System::Windows::Forms::Label^  label9;
	private: System::Windows::Forms::Label^  label10;
	private: System::Windows::Forms::SaveFileDialog^  saveFileDialog1;
	private: System::Windows::Forms::Label^  label11;
	private: System::Windows::Forms::TextBox^  apellido;
	private: System::Windows::Forms::DateTimePicker^  patientBirthdate;
	private: System::Windows::Forms::ComboBox^  patientSex;
	private: System::Windows::Forms::DateTimePicker^  studyDate;







	protected:

	private:
		/// <summary>
		/// Variable del dise�ador necesaria.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// M�todo necesario para admitir el Dise�ador. No se puede modificar
		/// el contenido de este m�todo con el editor de c�digo.
		/// </summary>
		void InitializeComponent(void)
		{
			this->abrirbtn = (gcnew System::Windows::Forms::Button());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->nombre = (gcnew System::Windows::Forms::TextBox());
			this->responsable = (gcnew System::Windows::Forms::TextBox());
			this->responsableRol = (gcnew System::Windows::Forms::TextBox());
			this->studyDescription = (gcnew System::Windows::Forms::TextBox());
			this->institutionName = (gcnew System::Windows::Forms::TextBox());
			this->institutionDepartament = (gcnew System::Windows::Forms::TextBox());
			this->ruta = (gcnew System::Windows::Forms::TextBox());
			this->convbtn = (gcnew System::Windows::Forms::Button());
			this->compbtn = (gcnew System::Windows::Forms::Button());
			this->enviarbtn = (gcnew System::Windows::Forms::Button());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->ayudaToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->salirToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->saveFileDialog1 = (gcnew System::Windows::Forms::SaveFileDialog());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->apellido = (gcnew System::Windows::Forms::TextBox());
			this->patientBirthdate = (gcnew System::Windows::Forms::DateTimePicker());
			this->patientSex = (gcnew System::Windows::Forms::ComboBox());
			this->studyDate = (gcnew System::Windows::Forms::DateTimePicker());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->menuStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// abrirbtn
			// 
			this->abrirbtn->Location = System::Drawing::Point(8, 511);
			this->abrirbtn->Name = L"abrirbtn";
			this->abrirbtn->Size = System::Drawing::Size(75, 23);
			this->abrirbtn->TabIndex = 0;
			this->abrirbtn->Text = L"Abrir";
			this->abrirbtn->UseVisualStyleBackColor = true;
			this->abrirbtn->Click += gcnew System::EventHandler(this, &TransmisorF::abrirbtn_Click);
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			// 
			// pictureBox1
			// 
			this->pictureBox1->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->pictureBox1->Cursor = System::Windows::Forms::Cursors::No;
			this->pictureBox1->Location = System::Drawing::Point(352, 27);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(490, 507);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox1->TabIndex = 1;
			this->pictureBox1->TabStop = false;
			// 
			// nombre
			// 
			this->nombre->Location = System::Drawing::Point(141, 65);
			this->nombre->Name = L"nombre";
			this->nombre->Size = System::Drawing::Size(205, 27);
			this->nombre->TabIndex = 2;
			// 
			// responsable
			// 
			this->responsable->Location = System::Drawing::Point(125, 245);
			this->responsable->Name = L"responsable";
			this->responsable->Size = System::Drawing::Size(205, 27);
			this->responsable->TabIndex = 5;
			// 
			// responsableRol
			// 
			this->responsableRol->Location = System::Drawing::Point(125, 288);
			this->responsableRol->Name = L"responsableRol";
			this->responsableRol->Size = System::Drawing::Size(205, 27);
			this->responsableRol->TabIndex = 6;
			// 
			// studyDescription
			// 
			this->studyDescription->Location = System::Drawing::Point(121, 330);
			this->studyDescription->Name = L"studyDescription";
			this->studyDescription->Size = System::Drawing::Size(205, 27);
			this->studyDescription->TabIndex = 7;
			// 
			// institutionName
			// 
			this->institutionName->Location = System::Drawing::Point(121, 405);
			this->institutionName->Name = L"institutionName";
			this->institutionName->Size = System::Drawing::Size(205, 27);
			this->institutionName->TabIndex = 9;
			// 
			// institutionDepartament
			// 
			this->institutionDepartament->Location = System::Drawing::Point(121, 438);
			this->institutionDepartament->Name = L"institutionDepartament";
			this->institutionDepartament->Size = System::Drawing::Size(205, 27);
			this->institutionDepartament->TabIndex = 10;
			// 
			// ruta
			// 
			this->ruta->Location = System::Drawing::Point(121, 471);
			this->ruta->Name = L"ruta";
			this->ruta->Size = System::Drawing::Size(205, 27);
			this->ruta->TabIndex = 11;
			this->ruta->Visible = false;
			// 
			// convbtn
			// 
			this->convbtn->Location = System::Drawing::Point(89, 511);
			this->convbtn->Name = L"convbtn";
			this->convbtn->Size = System::Drawing::Size(75, 23);
			this->convbtn->TabIndex = 12;
			this->convbtn->Text = L"Convertir";
			this->convbtn->UseVisualStyleBackColor = true;
			this->convbtn->Click += gcnew System::EventHandler(this, &TransmisorF::convbtn_Click_1);
			// 
			// compbtn
			// 
			this->compbtn->Location = System::Drawing::Point(170, 511);
			this->compbtn->Name = L"compbtn";
			this->compbtn->Size = System::Drawing::Size(75, 23);
			this->compbtn->TabIndex = 13;
			this->compbtn->Text = L"Comprimir";
			this->compbtn->UseVisualStyleBackColor = true;
			this->compbtn->Click += gcnew System::EventHandler(this, &TransmisorF::compbtn_Click);
			// 
			// enviarbtn
			// 
			this->enviarbtn->Location = System::Drawing::Point(251, 511);
			this->enviarbtn->Name = L"enviarbtn";
			this->enviarbtn->Size = System::Drawing::Size(75, 23);
			this->enviarbtn->TabIndex = 14;
			this->enviarbtn->Text = L"Enviar";
			this->enviarbtn->UseVisualStyleBackColor = true;
			this->enviarbtn->Click += gcnew System::EventHandler(this, &TransmisorF::Enviar_Click);
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->ayudaToolStripMenuItem,
					this->salirToolStripMenuItem
			});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(854, 24);
			this->menuStrip1->TabIndex = 15;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// ayudaToolStripMenuItem
			// 
			this->ayudaToolStripMenuItem->Name = L"ayudaToolStripMenuItem";
			this->ayudaToolStripMenuItem->Size = System::Drawing::Size(80, 20);
			this->ayudaToolStripMenuItem->Text = L"Acerca de...";
			this->ayudaToolStripMenuItem->Click += gcnew System::EventHandler(this, &TransmisorF::ayudaToolStripMenuItem_Click);
			// 
			// salirToolStripMenuItem
			// 
			this->salirToolStripMenuItem->Name = L"salirToolStripMenuItem";
			this->salirToolStripMenuItem->Size = System::Drawing::Size(41, 20);
			this->salirToolStripMenuItem->Text = L"Salir";
			this->salirToolStripMenuItem->Click += gcnew System::EventHandler(this, &TransmisorF::salirToolStripMenuItem_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(12, 73);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(124, 19);
			this->label1->TabIndex = 16;
			this->label1->Text = L"Nombre del Paciente";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(11, 165);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(124, 19);
			this->label2->TabIndex = 17;
			this->label2->Text = L"Fecha de Nacimiento";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(44, 209);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(34, 19);
			this->label3->TabIndex = 18;
			this->label3->Text = L"Sexo";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(3, 248);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(116, 19);
			this->label4->TabIndex = 19;
			this->label4->Text = L"Medico Responsable";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(11, 296);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(95, 19);
			this->label5->TabIndex = 20;
			this->label5->Text = L"Rol Responsable";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(17, 338);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(73, 19);
			this->label6->TabIndex = 21;
			this->label6->Text = L"Descripci�n";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(17, 372);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(86, 19);
			this->label7->TabIndex = 22;
			this->label7->Text = L"Fecha Estudio";
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(20, 405);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(66, 19);
			this->label8->TabIndex = 23;
			this->label8->Text = L"Instituci�n";
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Location = System::Drawing::Point(11, 441);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(89, 19);
			this->label9->TabIndex = 24;
			this->label9->Text = L"Departamento";
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Location = System::Drawing::Point(12, 479);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(78, 19);
			this->label10->TabIndex = 25;
			this->label10->Text = L"Ruta Imagen";
			this->label10->Visible = false;
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Location = System::Drawing::Point(20, 118);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(104, 19);
			this->label11->TabIndex = 27;
			this->label11->Text = L"Apellido Paciente";
			// 
			// apellido
			// 
			this->apellido->Location = System::Drawing::Point(141, 115);
			this->apellido->Name = L"apellido";
			this->apellido->Size = System::Drawing::Size(205, 27);
			this->apellido->TabIndex = 26;
			// 
			// patientBirthdate
			// 
			this->patientBirthdate->CustomFormat = L"yyyyMMdd";
			this->patientBirthdate->Format = System::Windows::Forms::DateTimePickerFormat::Short;
			this->patientBirthdate->Location = System::Drawing::Point(141, 159);
			this->patientBirthdate->Name = L"patientBirthdate";
			this->patientBirthdate->RightToLeft = System::Windows::Forms::RightToLeft::No;
			this->patientBirthdate->Size = System::Drawing::Size(200, 27);
			this->patientBirthdate->TabIndex = 28;
			// 
			// patientSex
			// 
			this->patientSex->FormattingEnabled = true;
			this->patientSex->Items->AddRange(gcnew cli::array< System::Object^  >(2) { L"M", L"F" });
			this->patientSex->Location = System::Drawing::Point(141, 206);
			this->patientSex->Name = L"patientSex";
			this->patientSex->Size = System::Drawing::Size(121, 27);
			this->patientSex->TabIndex = 29;
			// 
			// studyDate
			// 
			this->studyDate->CustomFormat = L"yyyyMMdd";
			this->studyDate->Format = System::Windows::Forms::DateTimePickerFormat::Short;
			this->studyDate->Location = System::Drawing::Point(121, 366);
			this->studyDate->Name = L"studyDate";
			this->studyDate->RightToLeft = System::Windows::Forms::RightToLeft::No;
			this->studyDate->Size = System::Drawing::Size(200, 27);
			this->studyDate->TabIndex = 30;
			// 
			// TransmisorF
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(96, 96);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Dpi;
			this->AutoSize = true;
			this->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			this->BackColor = System::Drawing::Color::AliceBlue;
			this->ClientSize = System::Drawing::Size(854, 578);
			this->Controls->Add(this->studyDate);
			this->Controls->Add(this->patientSex);
			this->Controls->Add(this->patientBirthdate);
			this->Controls->Add(this->label11);
			this->Controls->Add(this->apellido);
			this->Controls->Add(this->label10);
			this->Controls->Add(this->label9);
			this->Controls->Add(this->label8);
			this->Controls->Add(this->label7);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->enviarbtn);
			this->Controls->Add(this->compbtn);
			this->Controls->Add(this->convbtn);
			this->Controls->Add(this->ruta);
			this->Controls->Add(this->institutionDepartament);
			this->Controls->Add(this->institutionName);
			this->Controls->Add(this->studyDescription);
			this->Controls->Add(this->responsableRol);
			this->Controls->Add(this->responsable);
			this->Controls->Add(this->nombre);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->abrirbtn);
			this->Controls->Add(this->menuStrip1);
			this->Font = (gcnew System::Drawing::Font(L"Segoe Print", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->HelpButton = true;
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"TransmisorF";
			this->Text = L"Compresor de Imagenes";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void abrirbtn_Click(System::Object^  sender, System::EventArgs^  e) {
		OpenFileDialog^ openFileDialog1 = gcnew OpenFileDialog;

		openFileDialog1->InitialDirectory = "c:\\";
		openFileDialog1->Filter = "txt files (*.txt)|*.txt|All files (*.*)|*.*";
		openFileDialog1->FilterIndex = 2;
		openFileDialog1->RestoreDirectory = true;
		System::String^ str;

		if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			str = openFileDialog1->FileName;
			std::string str2 = msclr::interop::marshal_as<std::string>(str);
			int pos = str2.find(".");
			string ext = str2.substr(pos + 1);
			cout << ext << endl;
			if (ext == "dcm") {
				msclr::interop::marshal_context context;
				DicomExtractor extractor;
				DicomFileStructure file = extractor.extractDICOM((char*)context.marshal_as<const char*>(openFileDialog1->FileName));
				System::Drawing::Graphics^ graphics = pictureBox1->CreateGraphics();
				System::IntPtr ptr(file.getPixelData().ptr());
				System::Drawing::Bitmap^ bitmap = gcnew System::Drawing::Bitmap(file.getPixelData().cols,
					file.getPixelData().rows, file.getPixelData().step, System::Drawing::Imaging::PixelFormat::Format24bppRgb, ptr);
				System::Drawing::RectangleF rect(0, 0, pictureBox1->Width, pictureBox1->Height);
				graphics->DrawImage(bitmap, rect);

				Study study = file.getStudy();
				institutionDepartament->Text = gcnew System::String(study.institutionDepartament.c_str());
				institutionName->Text = gcnew System::String(study.institutionName.c_str());
				
				vector<string> v{ explode(study.patientName, '^') };
				if (v.size() >= 1) {
					apellido->Text = gcnew System::String(v[0].c_str());
					if(v.size() > 1)
					nombre->Text = gcnew System::String(v[1].c_str());
				}
				responsable->Text = gcnew System::String(study.responsable.c_str());
				responsableRol->Text = gcnew System::String(study.responsableRol.c_str());
				patientBirthdate->Text = gcnew System::String(study.patientBirthdate.c_str());
				patientSex->Text = gcnew System::String(study.patientSex.c_str());
				studyDate->Text = gcnew System::String(study.studyDate.c_str());
				studyDescription->Text = gcnew System::String(study.studyDescription.c_str());
			}
			else {
				pictureBox1->Load(openFileDialog1->FileName);
				ruta->Text = openFileDialog1->FileName;
			}
		}

	}


	private: System::Void Enviar_Click(System::Object^  sender, System::EventArgs^  e) {

		system("C:\\InterfazPT\\Envio\\WindowsFormsApp1\\WindowsFormsApp1\\bin\\Debug\\Envio.exe");
	}
	private: System::Void compbtn_Click(System::Object^  sender, System::EventArgs^  e) {

		ValoresEntrada^ vale = gcnew ValoresEntrada;
		vale->Show();

	}

	private: System::Void convbtn_Click_1(System::Object^  sender, System::EventArgs^  e) {

		System::String^ patientName = apellido->Text + "^" + nombre->Text;
		SaveFileDialog^ saveFileDialog1 = gcnew SaveFileDialog;
		saveFileDialog1->Filter = "Dicom (*.dcm)|*.dcm|All files (*.*)|*.*";
		saveFileDialog1->FilterIndex = 2;
		saveFileDialog1->RestoreDirectory = true;
		saveFileDialog1->ShowDialog();
		System::String^ str = saveFileDialog1->FileName;
		label10->Text = str;
		char* str2 = (char*)(void*)Marshal::StringToHGlobalAnsi(str);
		cout << str2 << endl;
		msclr::interop::marshal_context context;
		Study study;
		study.patientName = context.marshal_as<string>(patientName);
		study.patientBirthdate = context.marshal_as<string>(patientBirthdate->Text);
		study.patientSex = context.marshal_as<string>(patientSex->Text);
		study.institutionDepartament = context.marshal_as<string>(institutionDepartament->Text);
		study.institutionName = context.marshal_as<string>(institutionName->Text);
		study.studyDate = context.marshal_as<string>(studyDate->Text);
		study.studyDescription = context.marshal_as<string>(studyDescription->Text);
		study.responsable = context.marshal_as<string>(responsable->Text);
		study.responsableRol = context.marshal_as<string>(responsableRol->Text);
		DicomConverter converter;
		converter.convertImageToDicom(context.marshal_as<string>(ruta->Text), str2, study);
	}

	private: System::Void salirToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {

		this->Close();
	}
	private: System::Void ayudaToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {

		Info^ info = gcnew Info;
		info->Show();
	}
			 const vector<string> explode(const string& s, const char& c)
			 {
				 string buff{ "" };
				 vector<string> v;

				 for (auto n : s)
				 {
					 if (n != c) buff += n; else
						 if (n == c && buff != "") { v.push_back(buff); buff = ""; }
				 }
				 if (buff != "") v.push_back(buff);

				 return v;
			 }

	};
}

