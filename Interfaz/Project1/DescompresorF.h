#pragma once

#pragma once
#include <stdio.h>
#include <iostream>
#include <ostream>
#include <vcclr.h>
#include <atlstr.h>
#include <stdio.h>
#include "Info.h"
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
	public ref class DescompresorF : public System::Windows::Forms::Form
	{
	public:
		DescompresorF(void)
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
		~DescompresorF()
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
			this->descobtn->Click += gcnew System::EventHandler(this, &DescompresorF::descobtn_Click);
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
			this->recibtn->Click += gcnew System::EventHandler(this, &DescompresorF::recibtn_Click);
			// 
			// pictureBox1
			// 
			this->pictureBox1->Location = System::Drawing::Point(24, 87);
			this->pictureBox1->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(254, 210);
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
			this->menuStrip1->Size = System::Drawing::Size(597, 25);
			this->menuStrip1->TabIndex = 5;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// ayudaToolStripMenuItem
			// 
			this->ayudaToolStripMenuItem->Name = L"ayudaToolStripMenuItem";
			this->ayudaToolStripMenuItem->Size = System::Drawing::Size(80, 19);
			this->ayudaToolStripMenuItem->Text = L"Acerca de...";
			this->ayudaToolStripMenuItem->Click += gcnew System::EventHandler(this, &DescompresorF::ayudaToolStripMenuItem_Click);
			// 
			// salirToolStripMenuItem
			// 
			this->salirToolStripMenuItem->Name = L"salirToolStripMenuItem";
			this->salirToolStripMenuItem->Size = System::Drawing::Size(41, 19);
			this->salirToolStripMenuItem->Text = L"Salir";
			this->salirToolStripMenuItem->Click += gcnew System::EventHandler(this, &DescompresorF::salirToolStripMenuItem_Click);
			// 
			// DescompresorF
			// 
			this->AllowDrop = true;
			this->AutoScaleDimensions = System::Drawing::SizeF(7, 19);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoScroll = true;
			this->BackColor = System::Drawing::Color::AliceBlue;
			this->ClientSize = System::Drawing::Size(597, 472);
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

		system("C:\\Users\\israd\\Dropbox\\TT\\InterfazPT\\Recepcion\\Recepcion\\bin\\Debug\\Recepcion.exe");

	}
	private: System::Void descobtn_Click(System::Object^  sender, System::EventArgs^  e) {

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