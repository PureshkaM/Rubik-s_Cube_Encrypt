#pragma once

namespace CryptoLab2 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// —водка дл€ menu
	/// </summary>
	public ref class menu : public System::Windows::Forms::Form
	{
	public:
		menu(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// ќсвободить все используемые ресурсы.
		/// </summary>
		~menu()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::TextBox^ PathOpen;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::TextBox^ Size;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::TextBox^ KeyOpen;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Label^ ErrorOpen;
	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::TextBox^ CPathOpen;
	private: System::Windows::Forms::Label^ label7;
	private: System::Windows::Forms::TextBox^ CSize;
	private: System::Windows::Forms::Label^ label8;
	private: System::Windows::Forms::TextBox^ KeyClose;

	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Label^ CErrorOpen;


	protected:

	private:
		/// <summary>
		/// ќб€зательна€ переменна€ конструктора.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// “ребуемый метод дл€ поддержки конструктора Ч не измен€йте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->PathOpen = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->Size = (gcnew System::Windows::Forms::TextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->KeyOpen = (gcnew System::Windows::Forms::TextBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->ErrorOpen = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->CPathOpen = (gcnew System::Windows::Forms::TextBox());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->CSize = (gcnew System::Windows::Forms::TextBox());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->KeyClose = (gcnew System::Windows::Forms::TextBox());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->CErrorOpen = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(12, 9);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(63, 13);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Set file path";
			// 
			// PathOpen
			// 
			this->PathOpen->Location = System::Drawing::Point(81, 6);
			this->PathOpen->Name = L"PathOpen";
			this->PathOpen->Size = System::Drawing::Size(394, 20);
			this->PathOpen->TabIndex = 1;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(12, 61);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(313, 13);
			this->label2->TabIndex = 2;
			this->label2->Text = L"Specify the dimension of the cube face (a number greater than 1)";
			// 
			// Size
			// 
			this->Size->Location = System::Drawing::Point(327, 58);
			this->Size->Name = L"Size";
			this->Size->Size = System::Drawing::Size(68, 20);
			this->Size->TabIndex = 3;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(12, 81);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(374, 13);
			this->label3->TabIndex = 4;
			this->label3->Text = L"In the next field you should specify the key in the format \"row number, action\".";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(12, 94);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(328, 13);
			this->label4->TabIndex = 5;
			this->label4->Text = L"For the key, replacement is used (right - R, left - L, up - U, down - D).";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(12, 107);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(153, 13);
			this->label5->TabIndex = 6;
			this->label5->Text = L"An example is given in the box.";
			// 
			// KeyOpen
			// 
			this->KeyOpen->Location = System::Drawing::Point(12, 123);
			this->KeyOpen->Name = L"KeyOpen";
			this->KeyOpen->Size = System::Drawing::Size(463, 20);
			this->KeyOpen->TabIndex = 7;
			this->KeyOpen->Text = L"2D1R2L";
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(12, 175);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(102, 31);
			this->button1->TabIndex = 8;
			this->button1->Text = L"Encrypt";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &menu::button1_Click);
			// 
			// ErrorOpen
			// 
			this->ErrorOpen->AutoSize = true;
			this->ErrorOpen->Location = System::Drawing::Point(12, 159);
			this->ErrorOpen->Name = L"ErrorOpen";
			this->ErrorOpen->Size = System::Drawing::Size(0, 13);
			this->ErrorOpen->TabIndex = 9;
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(12, 231);
			this->label6->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(63, 13);
			this->label6->TabIndex = 10;
			this->label6->Text = L"Set file path";
			// 
			// CPathOpen
			// 
			this->CPathOpen->Location = System::Drawing::Point(81, 228);
			this->CPathOpen->Margin = System::Windows::Forms::Padding(2);
			this->CPathOpen->Name = L"CPathOpen";
			this->CPathOpen->Size = System::Drawing::Size(394, 20);
			this->CPathOpen->TabIndex = 11;
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(8, 283);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(313, 13);
			this->label7->TabIndex = 12;
			this->label7->Text = L"Specify the dimension of the cube face (a number greater than 1)";
			// 
			// CSize
			// 
			this->CSize->Location = System::Drawing::Point(327, 280);
			this->CSize->Name = L"CSize";
			this->CSize->Size = System::Drawing::Size(68, 20);
			this->CSize->TabIndex = 13;
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(8, 309);
			this->label8->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(52, 13);
			this->label8->TabIndex = 14;
			this->label8->Text = L"Send key";
			// 
			// KeyClose
			// 
			this->KeyClose->Location = System::Drawing::Point(12, 326);
			this->KeyClose->Name = L"KeyClose";
			this->KeyClose->Size = System::Drawing::Size(463, 20);
			this->KeyClose->TabIndex = 15;
			this->KeyClose->Text = L"2D1R2L";
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(12, 380);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(102, 31);
			this->button2->TabIndex = 16;
			this->button2->Text = L"Decrypt";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &menu::button2_Click);
			// 
			// CErrorOpen
			// 
			this->CErrorOpen->AutoSize = true;
			this->CErrorOpen->Location = System::Drawing::Point(12, 364);
			this->CErrorOpen->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->CErrorOpen->Name = L"CErrorOpen";
			this->CErrorOpen->Size = System::Drawing::Size(0, 13);
			this->CErrorOpen->TabIndex = 17;
			// 
			// menu
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(487, 434);
			this->Controls->Add(this->CErrorOpen);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->KeyClose);
			this->Controls->Add(this->label8);
			this->Controls->Add(this->CSize);
			this->Controls->Add(this->label7);
			this->Controls->Add(this->CPathOpen);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->ErrorOpen);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->KeyOpen);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->Size);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->PathOpen);
			this->Controls->Add(this->label1);
			this->Name = L"menu";
			this->Text = L"menu";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e);
};
}
