#pragma once

#include <msclr\marshal_cppstd.h>

#include"CompressionResults.h"

namespace Interfaz{

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Resumen de Resultados
	/// </summary>
	public ref class Resultados : public System::Windows::Forms::Form
	{
	public:
		Resultados(void)
		{
			InitializeComponent();
			//
			//TODO: agregar código de constructor aquí
			//
		}
		void setResults(CompressionResults results) {
			this->psnr->Text = results.getPeakSignalToNoiseToRatio().ToString() + " dB";
			this->entropy->Text = results.getEntropy().ToString() + " bits/symbol";
			this->tc->Text = results.getCompressionRate().ToString();
			msclr::interop::marshal_context context;
			this->rutacom->Text = context.marshal_as<System::String^>(results.getCompressedFilePath());
		}

	protected:
		/// <summary>
		/// Limpiar los recursos que se estén usando.
		/// </summary>
		~Resultados()
		{
			if (components)
			{
				delete components;
			}
		}
	
	private: System::Windows::Forms::TextBox^  psnr;
	private: System::Windows::Forms::TextBox^  entropy;

	private: System::Windows::Forms::TextBox^  tc;
	protected:



	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::TextBox^  rutacom;
	private: System::Windows::Forms::Label^  label4;


	protected:

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
			this->psnr = (gcnew System::Windows::Forms::TextBox());
			this->entropy = (gcnew System::Windows::Forms::TextBox());
			this->tc = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->rutacom = (gcnew System::Windows::Forms::TextBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// psnr
			// 
			this->psnr->Location = System::Drawing::Point(12, 43);
			this->psnr->Name = L"psnr";
			this->psnr->Size = System::Drawing::Size(100, 20);
			this->psnr->TabIndex = 0;
			// 
			// entropy
			// 
			this->entropy->Location = System::Drawing::Point(12, 86);
			this->entropy->Name = L"entropy";
			this->entropy->Size = System::Drawing::Size(100, 20);
			this->entropy->TabIndex = 1;
			// 
			// tc
			// 
			this->tc->Location = System::Drawing::Point(12, 122);
			this->tc->Name = L"tc";
			this->tc->Size = System::Drawing::Size(100, 20);
			this->tc->TabIndex = 2;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(141, 46);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(37, 13);
			this->label1->TabIndex = 4;
			this->label1->Text = L"PSNR";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(141, 89);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(48, 13);
			this->label2->TabIndex = 5;
			this->label2->Text = L"Entropía";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(141, 125);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(104, 13);
			this->label3->TabIndex = 6;
			this->label3->Text = L"Tasa de Compresion";
			// 
			// rutacom
			// 
			this->rutacom->Location = System::Drawing::Point(12, 164);
			this->rutacom->Name = L"rutacom";
			this->rutacom->Size = System::Drawing::Size(100, 20);
			this->rutacom->TabIndex = 7;
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(141, 164);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(62, 13);
			this->label4->TabIndex = 8;
			this->label4->Text = L"Ruta .comp";
			// 
			// Resultados
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(284, 261);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->rutacom);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->tc);
			this->Controls->Add(this->entropy);
			this->Controls->Add(this->psnr);
			this->Name = L"Resultados";
			this->Text = L"Resultados";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	};
}
