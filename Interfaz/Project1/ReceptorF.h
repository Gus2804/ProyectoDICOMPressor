#pragma once

#pragma once
#include <stdio.h>
#include <iostream>
#include <ostream>
#include <vcclr.h>
#include <atlstr.h>
#include <stdio.h>
#include "Info.h"
#include <msclr\marshal_cppstd.h>
#include "Decompressor.h"

#using <mscorlib.dll>
namespace Interfaz{

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Resumen de MyForm
	/// </summary>
	public ref class ReceptorF : public System::Windows::Forms::Form
	{
	public:
		ReceptorF(void)
		{
			InitializeComponent();
			//
			//TODO: agregar código de constructor aquí
			//
		}

	protected:
		/// <summary>
		/// Limpiar los recursos que se estén usando.
		/// </summary>
		~ReceptorF()
		{
			if (components)
			{
				delete components;
			}
		}

	protected:
	private: System::Windows::Forms::Button^  descobtn;

	private: System::Windows::Forms::Button^  recibtn;
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog1;
	private: System::Windows::Forms::HelpProvider^  helpProvider1;
	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  salirToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  ayudaToolStripMenuItem;
	private: System::Windows::Forms::Label^  label10;
	private: System::Windows::Forms::Label^  label9;
	private: System::Windows::Forms::Label^  label8;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::TextBox^  ruta;
	private: System::Windows::Forms::TextBox^  institutionDepartament;
	private: System::Windows::Forms::TextBox^  institutionName;
	private: System::Windows::Forms::TextBox^  studyDate;
	private: System::Windows::Forms::TextBox^  studyDescription;
	private: System::Windows::Forms::TextBox^  responsableRol;
	private: System::Windows::Forms::TextBox^  responsable;
	private: System::Windows::Forms::TextBox^  patientSex;
	private: System::Windows::Forms::TextBox^  patientBirthdate;
	private: System::Windows::Forms::TextBox^  patientName;


	private:
		/// <summary>
		/// Variable del diseñador necesaria.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Método necesario para admitir el Diseñador. No se puede modificar
		/// el contenido de este método con el editor de código.
		/// </summary>
		void InitializeComponent(void)
		{
			this->descobtn = (gcnew System::Windows::Forms::Button());
			this->recibtn = (gcnew System::Windows::Forms::Button());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->helpProvider1 = (gcnew System::Windows::Forms::HelpProvider());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->ayudaToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->salirToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->ruta = (gcnew System::Windows::Forms::TextBox());
			this->institutionDepartament = (gcnew System::Windows::Forms::TextBox());
			this->institutionName = (gcnew System::Windows::Forms::TextBox());
			this->studyDate = (gcnew System::Windows::Forms::TextBox());
			this->studyDescription = (gcnew System::Windows::Forms::TextBox());
			this->responsableRol = (gcnew System::Windows::Forms::TextBox());
			this->responsable = (gcnew System::Windows::Forms::TextBox());
			this->patientSex = (gcnew System::Windows::Forms::TextBox());
			this->patientBirthdate = (gcnew System::Windows::Forms::TextBox());
			this->patientName = (gcnew System::Windows::Forms::TextBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->menuStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// descobtn
			// 
			this->descobtn->Location = System::Drawing::Point(170, 388);
			this->descobtn->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
			this->descobtn->Name = L"descobtn";
			this->descobtn->Size = System::Drawing::Size(87, 34);
			this->descobtn->TabIndex = 1;
			this->descobtn->Text = L"Descomprimir";
			this->descobtn->UseVisualStyleBackColor = true;
			this->descobtn->Click += gcnew System::EventHandler(this, &ReceptorF::descobtn_Click);
			// 
			// recibtn
			// 
			this->recibtn->Location = System::Drawing::Point(39, 388);
			this->recibtn->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
			this->recibtn->Name = L"recibtn";
			this->recibtn->Size = System::Drawing::Size(87, 34);
			this->recibtn->TabIndex = 3;
			this->recibtn->Text = L"Recibir";
			this->recibtn->UseVisualStyleBackColor = true;
			this->recibtn->Click += gcnew System::EventHandler(this, &ReceptorF::recibtn_Click);
			// 
			// pictureBox1
			// 
			this->pictureBox1->Location = System::Drawing::Point(18, 34);
			this->pictureBox1->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(315, 351);
			this->pictureBox1->TabIndex = 4;
			this->pictureBox1->TabStop = false;
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->ayudaToolStripMenuItem,
					this->salirToolStripMenuItem
			});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Padding = System::Windows::Forms::Padding(7, 3, 0, 3);
			this->menuStrip1->Size = System::Drawing::Size(693, 25);
			this->menuStrip1->TabIndex = 5;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// ayudaToolStripMenuItem
			// 
			this->ayudaToolStripMenuItem->Name = L"ayudaToolStripMenuItem";
			this->ayudaToolStripMenuItem->Size = System::Drawing::Size(80, 19);
			this->ayudaToolStripMenuItem->Text = L"Acerca de...";
			this->ayudaToolStripMenuItem->Click += gcnew System::EventHandler(this, &ReceptorF::ayudaToolStripMenuItem_Click);
			// 
			// salirToolStripMenuItem
			// 
			this->salirToolStripMenuItem->Name = L"salirToolStripMenuItem";
			this->salirToolStripMenuItem->Size = System::Drawing::Size(41, 19);
			this->salirToolStripMenuItem->Text = L"Salir";
			this->salirToolStripMenuItem->Click += gcnew System::EventHandler(this, &ReceptorF::salirToolStripMenuItem_Click);
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Location = System::Drawing::Point(364, 361);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(78, 19);
			this->label10->TabIndex = 45;
			this->label10->Text = L"Ruta Imagen";
			this->label10->Visible = false;
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Location = System::Drawing::Point(364, 328);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(89, 19);
			this->label9->TabIndex = 44;
			this->label9->Text = L"Departamento";
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(367, 292);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(66, 19);
			this->label8->TabIndex = 43;
			this->label8->Text = L"Institución";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(367, 262);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(86, 19);
			this->label7->TabIndex = 42;
			this->label7->Text = L"Fecha Estudio";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(369, 228);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(73, 19);
			this->label6->TabIndex = 41;
			this->label6->Text = L"Descripción";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(358, 195);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(95, 19);
			this->label5->TabIndex = 40;
			this->label5->Text = L"Rol Responsable";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(355, 162);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(116, 19);
			this->label4->TabIndex = 39;
			this->label4->Text = L"Medico Responsable";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(388, 129);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(34, 19);
			this->label3->TabIndex = 38;
			this->label3->Text = L"Sexo";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(347, 96);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(124, 19);
			this->label2->TabIndex = 37;
			this->label2->Text = L"Fecha de Nacimiento";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(339, 60);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(124, 19);
			this->label1->TabIndex = 36;
			this->label1->Text = L"Nombre del Paciente";
			// 
			// ruta
			// 
			this->ruta->Cursor = System::Windows::Forms::Cursors::No;
			this->ruta->Location = System::Drawing::Point(476, 358);
			this->ruta->Name = L"ruta";
			this->ruta->ReadOnly = true;
			this->ruta->Size = System::Drawing::Size(205, 27);
			this->ruta->TabIndex = 35;
			this->ruta->Visible = false;
			// 
			// institutionDepartament
			// 
			this->institutionDepartament->Cursor = System::Windows::Forms::Cursors::No;
			this->institutionDepartament->Location = System::Drawing::Point(476, 325);
			this->institutionDepartament->Name = L"institutionDepartament";
			this->institutionDepartament->ReadOnly = true;
			this->institutionDepartament->Size = System::Drawing::Size(205, 27);
			this->institutionDepartament->TabIndex = 34;
			// 
			// institutionName
			// 
			this->institutionName->Cursor = System::Windows::Forms::Cursors::No;
			this->institutionName->Location = System::Drawing::Point(476, 292);
			this->institutionName->Name = L"institutionName";
			this->institutionName->ReadOnly = true;
			this->institutionName->Size = System::Drawing::Size(205, 27);
			this->institutionName->TabIndex = 33;
			// 
			// studyDate
			// 
			this->studyDate->Cursor = System::Windows::Forms::Cursors::No;
			this->studyDate->Location = System::Drawing::Point(476, 259);
			this->studyDate->Name = L"studyDate";
			this->studyDate->ReadOnly = true;
			this->studyDate->Size = System::Drawing::Size(205, 27);
			this->studyDate->TabIndex = 32;
			// 
			// studyDescription
			// 
			this->studyDescription->Cursor = System::Windows::Forms::Cursors::No;
			this->studyDescription->Location = System::Drawing::Point(476, 225);
			this->studyDescription->Name = L"studyDescription";
			this->studyDescription->ReadOnly = true;
			this->studyDescription->Size = System::Drawing::Size(205, 27);
			this->studyDescription->TabIndex = 31;
			// 
			// responsableRol
			// 
			this->responsableRol->Cursor = System::Windows::Forms::Cursors::No;
			this->responsableRol->Location = System::Drawing::Point(476, 192);
			this->responsableRol->Name = L"responsableRol";
			this->responsableRol->ReadOnly = true;
			this->responsableRol->Size = System::Drawing::Size(205, 27);
			this->responsableRol->TabIndex = 30;
			// 
			// responsable
			// 
			this->responsable->Cursor = System::Windows::Forms::Cursors::No;
			this->responsable->Location = System::Drawing::Point(476, 159);
			this->responsable->Name = L"responsable";
			this->responsable->ReadOnly = true;
			this->responsable->Size = System::Drawing::Size(205, 27);
			this->responsable->TabIndex = 29;
			// 
			// patientSex
			// 
			this->patientSex->Cursor = System::Windows::Forms::Cursors::No;
			this->patientSex->Location = System::Drawing::Point(476, 126);
			this->patientSex->Name = L"patientSex";
			this->patientSex->ReadOnly = true;
			this->patientSex->Size = System::Drawing::Size(205, 27);
			this->patientSex->TabIndex = 28;
			// 
			// patientBirthdate
			// 
			this->patientBirthdate->Cursor = System::Windows::Forms::Cursors::No;
			this->patientBirthdate->Location = System::Drawing::Point(476, 93);
			this->patientBirthdate->Name = L"patientBirthdate";
			this->patientBirthdate->ReadOnly = true;
			this->patientBirthdate->Size = System::Drawing::Size(205, 27);
			this->patientBirthdate->TabIndex = 27;
			// 
			// patientName
			// 
			this->patientName->Cursor = System::Windows::Forms::Cursors::No;
			this->patientName->Location = System::Drawing::Point(476, 57);
			this->patientName->Name = L"patientName";
			this->patientName->ReadOnly = true;
			this->patientName->Size = System::Drawing::Size(205, 27);
			this->patientName->TabIndex = 26;
			// 
			// DescompresorF
			// 
			this->AllowDrop = true;
			this->AutoScaleDimensions = System::Drawing::SizeF(7, 19);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoScroll = true;
			this->BackColor = System::Drawing::Color::AliceBlue;
			this->ClientSize = System::Drawing::Size(693, 471);
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
			this->Controls->Add(this->ruta);
			this->Controls->Add(this->institutionDepartament);
			this->Controls->Add(this->institutionName);
			this->Controls->Add(this->studyDate);
			this->Controls->Add(this->studyDescription);
			this->Controls->Add(this->responsableRol);
			this->Controls->Add(this->responsable);
			this->Controls->Add(this->patientSex);
			this->Controls->Add(this->patientBirthdate);
			this->Controls->Add(this->patientName);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->recibtn);
			this->Controls->Add(this->descobtn);
			this->Controls->Add(this->menuStrip1);
			this->Font = (gcnew System::Drawing::Font(L"Segoe Print", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->HelpButton = true;
			this->MainMenuStrip = this->menuStrip1;
			this->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
			this->Name = L"DescompresorF";
			this->Text = L"Descompresor";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void recibtn_Click(System::Object^  sender, System::EventArgs^  e) {

		system("C:\\InterfazPT\\Recepcion\\Recepcion\\bin\\Debug\\Recepcion.exe");

	}
	private: System::Void descobtn_Click(System::Object^  sender, System::EventArgs^  e) {
		OpenFileDialog^ openFileDialog1 = gcnew OpenFileDialog;

		openFileDialog1->InitialDirectory = "c:\\";
		openFileDialog1->Filter = "Imagenes comprimidas (*.comp)|*.comp|All files (*.*)|*.*";
		openFileDialog1->FilterIndex = 2;
		openFileDialog1->RestoreDirectory = true;


		if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			msclr::interop::marshal_context context;
			/*DicomExtractor extractor;
			DicomFileStructure file = extractor.extractDICOM((char*)context.marshal_as<const char*>(openFileDialog1->FileName));
			*/
			Decompressor decompressor;
			DicomFileStructure file = decompressor.decompress(context.marshal_as<const char*>(openFileDialog1->FileName));

			System::Drawing::Graphics^ graphics = pictureBox1->CreateGraphics();
			System::IntPtr ptr(file.getPixelData().ptr());
			System::Drawing::Bitmap^ bitmap = gcnew System::Drawing::Bitmap(file.getPixelData().cols,
				file.getPixelData().rows, file.getPixelData().step, System::Drawing::Imaging::PixelFormat::Format24bppRgb, ptr);
			System::Drawing::RectangleF rect(0, 0, pictureBox1->Width, pictureBox1->Height);
			graphics->DrawImage(bitmap, rect);
		}
	}
	private: System::Void mostbtn_Click(System::Object^  sender, System::EventArgs^  e) {
		
	}
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {

	}

	private: System::Void salirToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {

		this->Close();
	}
	private: System::Void ayudaToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {

		Info^ info = gcnew Info;
		info->Show();
	}
	};
}