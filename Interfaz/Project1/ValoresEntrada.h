#pragma once

#include <msclr\marshal_cppstd.h>

#include "Resultados.h"
#include "Compresor.h"
#include "DicomExtractor.h"

using namespace System;
using namespace System::Windows::Forms;

namespace Interfaz {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Resumen de ValoresEntrada
	/// </summary>
	public ref class ValoresEntrada : public System::Windows::Forms::Form
	{
	public:
		ValoresEntrada(void)
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
		~ValoresEntrada()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::RadioButton^  radioInBi;
	protected:
	private: System::Windows::Forms::RadioButton^  radioRand;
	private: System::Windows::Forms::TextBox^  Umbraltext;
	private: System::Windows::Forms::TextBox^  Mtext;
	private: System::Windows::Forms::TextBox^  Ntext;
	private: System::Windows::Forms::TextBox^  Cuantext;




	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Button^  Compbtn;
	private: System::Windows::Forms::Label^  label5;

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
			this->radioInBi = (gcnew System::Windows::Forms::RadioButton());
			this->radioRand = (gcnew System::Windows::Forms::RadioButton());
			this->Umbraltext = (gcnew System::Windows::Forms::TextBox());
			this->Mtext = (gcnew System::Windows::Forms::TextBox());
			this->Ntext = (gcnew System::Windows::Forms::TextBox());
			this->Cuantext = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->Compbtn = (gcnew System::Windows::Forms::Button());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// radioInBi
			// 
			this->radioInBi->AutoSize = true;
			this->radioInBi->Location = System::Drawing::Point(24, 66);
			this->radioInBi->Name = L"radioInBi";
			this->radioInBi->Size = System::Drawing::Size(122, 17);
			this->radioInBi->TabIndex = 0;
			this->radioInBi->TabStop = true;
			this->radioInBi->Text = L"Interpolacion Bilineal";
			this->radioInBi->UseVisualStyleBackColor = true;
			this->radioInBi->CheckedChanged += gcnew System::EventHandler(this, &ValoresEntrada::radioInBi_CheckedChanged);
			// 
			// radioRand
			// 
			this->radioRand->AutoSize = true;
			this->radioRand->Location = System::Drawing::Point(24, 132);
			this->radioRand->Name = L"radioRand";
			this->radioRand->Size = System::Drawing::Size(91, 17);
			this->radioRand->TabIndex = 1;
			this->radioRand->TabStop = true;
			this->radioRand->Text = L"Aleatorizacion";
			this->radioRand->UseVisualStyleBackColor = true;
			this->radioRand->CheckedChanged += gcnew System::EventHandler(this, &ValoresEntrada::radioRand_CheckedChanged);
			// 
			// Umbraltext
			// 
			this->Umbraltext->Location = System::Drawing::Point(187, 47);
			this->Umbraltext->Name = L"Umbraltext";
			this->Umbraltext->Size = System::Drawing::Size(37, 20);
			this->Umbraltext->TabIndex = 2;
			// 
			// Mtext
			// 
			this->Mtext->Location = System::Drawing::Point(187, 83);
			this->Mtext->Name = L"Mtext";
			this->Mtext->Size = System::Drawing::Size(37, 20);
			this->Mtext->TabIndex = 3;
			// 
			// Ntext
			// 
			this->Ntext->Location = System::Drawing::Point(187, 118);
			this->Ntext->Name = L"Ntext";
			this->Ntext->Size = System::Drawing::Size(37, 20);
			this->Ntext->TabIndex = 4;
			// 
			// Cuantext
			// 
			this->Cuantext->Location = System::Drawing::Point(187, 153);
			this->Cuantext->Name = L"Cuantext";
			this->Cuantext->Size = System::Drawing::Size(37, 20);
			this->Cuantext->TabIndex = 5;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(242, 50);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(40, 13);
			this->label1->TabIndex = 6;
			this->label1->Text = L"Umbral";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(242, 86);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(16, 13);
			this->label2->TabIndex = 7;
			this->label2->Text = L"M";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(242, 156);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(68, 13);
			this->label3->TabIndex = 8;
			this->label3->Text = L"Cuantizacion";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(242, 121);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(15, 13);
			this->label4->TabIndex = 9;
			this->label4->Text = L"N";
			// 
			// Compbtn
			// 
			this->Compbtn->Location = System::Drawing::Point(40, 199);
			this->Compbtn->Name = L"Compbtn";
			this->Compbtn->Size = System::Drawing::Size(75, 23);
			this->Compbtn->TabIndex = 10;
			this->Compbtn->Text = L"Comprimir";
			this->Compbtn->UseVisualStyleBackColor = true;
			this->Compbtn->Click += gcnew System::EventHandler(this, &ValoresEntrada::Compbtn_Click);
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(35, 9);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(273, 13);
			this->label5->TabIndex = 11;
			this->label5->Text = L"Elija el Algoritmo que desea usar y sus valores solcitados";
			// 
			// ValoresEntrada
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(322, 245);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->Compbtn);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->Cuantext);
			this->Controls->Add(this->Ntext);
			this->Controls->Add(this->Mtext);
			this->Controls->Add(this->Umbraltext);
			this->Controls->Add(this->radioRand);
			this->Controls->Add(this->radioInBi);
			this->Name = L"ValoresEntrada";
			this->Text = L"ValoresEntrada";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	
	private: System::Void Compbtn_Click(System::Object^  sender, System::EventArgs^  e) {
		OpenFileDialog^ openFileDialog1 = gcnew OpenFileDialog;

		openFileDialog1->InitialDirectory = "c:\\";
		openFileDialog1->Filter = "Dicom (*.dcm)|*.dcm|All files (*.*)|*.*";
		openFileDialog1->FilterIndex = 2;
		openFileDialog1->RestoreDirectory = true;


		if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			int m = int::Parse(Mtext->Text);
			int n = int::Parse(Ntext->Text);
			float u = float::Parse(Umbraltext->Text);
			int c = int::Parse(Cuantext->Text);
			msclr::interop::marshal_context context;
			DicomExtractor extractor;
			DicomFileStructure file = extractor.extractDICOM((char*)context.marshal_as<const char*>(openFileDialog1->FileName));
			Compresor compresor;
			CompressionResults results;
			if (radioInBi->Checked) {
				results = compresor.compressByBilinearInterpolation(file,m,n,u,c);
			}
			else {
				results = compresor.compressByRandomization(file,u);
			}
			Resultados^ resultados = gcnew Resultados;
			resultados->setResults(results);
			resultados->Show();
		}
	}
private: System::Void radioInBi_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {

	label2->Show();
	label3->Show();
	label4->Show();
	Mtext->Show();
	Ntext->Show();
	Cuantext->Show();

}
private: System::Void radioRand_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {

	label2->Hide();
	label3->Hide();
	label4->Hide();
	Mtext->Hide();
	Ntext->Hide();
	Cuantext->Hide();

}
};
}
