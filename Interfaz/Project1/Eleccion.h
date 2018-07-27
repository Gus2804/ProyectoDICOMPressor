#pragma once
#include <stdio.h>
#include <iostream>
#include <ostream>
#include <vcclr.h>
#include <atlstr.h>
#include <stdio.h>
#include "Info.h"
#include "TransmisorF.h"
#include "ReceptorF.h"
#using <mscorlib.dll>
namespace Interfaz{

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Resumen de Eleccion
	/// </summary>
	public ref class Eleccion : public System::Windows::Forms::Form
	{
	public:
		Eleccion(void)
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
		~Eleccion()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	protected:
	private: System::Windows::Forms::PictureBox^  pictureBox2;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label3;

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
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->BeginInit();
			this->SuspendLayout();
			// 
			// pictureBox1
			// 
			this->pictureBox1->Cursor = System::Windows::Forms::Cursors::Hand;
			this->pictureBox1->ImageLocation = L"C:\\InterfazPT\\Interfaz\\images\\Compr.jpg";
			this->pictureBox1->Location = System::Drawing::Point(89, 108);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(102, 96);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			this->pictureBox1->Click += gcnew System::EventHandler(this, &Eleccion::pictureBox1_Click);
			// 
			// pictureBox2
			// 
			this->pictureBox2->Cursor = System::Windows::Forms::Cursors::Hand;
			this->pictureBox2->ImageLocation = L"C:\\InterfazPT\\Interfaz\\images\\descom.jpg";
			this->pictureBox2->Location = System::Drawing::Point(326, 108);
			this->pictureBox2->Name = L"pictureBox2";
			this->pictureBox2->Size = System::Drawing::Size(102, 96);
			this->pictureBox2->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox2->TabIndex = 1;
			this->pictureBox2->TabStop = false;
			this->pictureBox2->Click += gcnew System::EventHandler(this, &Eleccion::pictureBox2_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(101, 271);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(57, 13);
			this->label1->TabIndex = 2;
			this->label1->Text = L"Compresor";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(362, 271);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(75, 13);
			this->label2->TabIndex = 3;
			this->label2->Text = L"Descompresor";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Arial", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label3->Location = System::Drawing::Point(197, 9);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(131, 42);
			this->label3->TabIndex = 4;
			this->label3->Text = L"Buen dia: \r\n\r\nQue realizaremos hoy ";
			this->label3->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			// 
			// Eleccion
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(529, 307);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->pictureBox2);
			this->Controls->Add(this->pictureBox1);
			this->Name = L"Eleccion";
			this->Text = L"Eleccion";
			this->Load += gcnew System::EventHandler(this, &Eleccion::Eleccion_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void pictureBox1_Click(System::Object^  sender, System::EventArgs^  e) {
		
		this->Hide();
		TransmisorF^ trans = gcnew TransmisorF;
		trans->ShowDialog();
		this->Show();

	}
private: System::Void pictureBox2_Click(System::Object^  sender, System::EventArgs^  e) {

	this->Hide();
	ReceptorF^ recep = gcnew ReceptorF;
	recep->ShowDialog();
	this->Show();

}
private: System::Void Eleccion_Load(System::Object^  sender, System::EventArgs^  e) {
}
};
}
