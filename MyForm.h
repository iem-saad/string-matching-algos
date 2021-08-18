#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <msclr\marshal_cppstd.h>

namespace WindowsFormSetup {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Label^  label6;
	public:
		int occurances = 0;
		char to_lower(char ch, bool case_bit)
		{
			if (case_bit)
				return ch;
			else
				return (char)tolower(ch);
		}
		void prefix_calculator(char* to_find, int to_find_size, int* pie)
		{
			int len = 0;
			pie[0] = 0;
			int i = 1;
			while (i < to_find_size)
				if ((char)tolower(to_find[i]) == (char)tolower(to_find[len]))
				{
					len++;
					pie[i] = len;
					i++;
				}
				else
					if (len != 0)
						len = pie[len - 1];
					else
					{
						pie[i] = 0;
						i++;
					}
		}
		void rabin_karp_algorithm(char* to_find, bool case_bit, bool word_match)
		{
			std::fstream fin;
			std::string file_data;
			char ch;
			std::string file_name;
			int prime = 101;
			int base = 10;
			for (int i = 0; i < 10; i++)
			{
				file_name = "Research#" + std::to_string(i + 1) + ".txt";
				int to_find_size = 0;
				int file_size = 0;
				int k = 0, l = 0;
				fin.open(file_name.c_str());
				if (!fin.is_open())
					std::cout << "Something Went Wrong While Opening File\n";
				while (!fin.eof())
				{
					fin.get(ch);
					if (fin.eof())
						break;
					file_data.push_back(ch);
				}
				to_find_size = strlen(to_find);
				file_size = file_data.length();
				int j;
				int p_hash = 0;
				int t_hash = 0;
				int hash = 1;
				k = 0, l = 1;
				for (int i = 0; i < to_find_size - 1; i++)
					hash = (hash * base) % prime;

				for (int i = 0; i < to_find_size; i++)
				{
					p_hash = (base * p_hash + to_lower(to_find[i], case_bit)) % prime;
					t_hash = (base * t_hash + to_lower(file_data[i], case_bit)) % prime;
				}
				for (int i = 0; i <= file_size - to_find_size; i++)
				{
					if (file_data[i] == '\n')
						l = 0, k++;
					l++;
					if (p_hash == t_hash)
					{
						for (j = 0; j < to_find_size; j++)
							if (to_lower(file_data[i + j], case_bit) != to_lower(to_find[j], case_bit))
								break;

						if (j == to_find_size)
						{
							int start = i;
							int end = i;
							while (file_data[end] != ' ')
								end++;
							while (file_data[start] != ' ')
								start--;
							std::string full_word = file_data.substr(start + 1, end - start-1);
							if (!word_match)
							{
								this->occurances++;
								this->output_list->Items->Add("===================================================");
								std::string str = "******** Found at, i: " + std::to_string(l - 1) + " j: " + std::to_string(k + 1) + " in file: " + file_name + " ********";
								String ^ conv_str = msclr::interop::marshal_as<String ^>(str);
								this->output_list->Items->Add(conv_str);
								std::string str1 = "++++++++++++ Matching Word Was: " + full_word + " ++++++++++++ ";
								String ^ conv_str1 = msclr::interop::marshal_as<String ^>(str1);
								this->output_list->Items->Add(conv_str1);
								this->output_list->Items->Add("===================================================");
							}
							else
							{
								if (to_find == full_word)
								{
									this->occurances++;
									this->output_list->Items->Add("===================================================");
									std::string str = "******** Found at, i: " + std::to_string(l - 1) + " j: " + std::to_string(k + 1) + " in file: " + file_name + " ********";
									String ^ conv_str = msclr::interop::marshal_as<String ^>(str);
									this->output_list->Items->Add(conv_str);
									std::string temp(to_find);
									std::string str1 = "++++++++++++ Matching Word Was: " + temp + " ++++++++++++ ";
									String ^ conv_str1 = msclr::interop::marshal_as<String ^>(str1);
									this->output_list->Items->Add(conv_str1);
									this->output_list->Items->Add("===================================================");
								}

							}
						}
					}
					if (i < file_size - to_find_size)
					{
						t_hash = (base*(t_hash - to_lower(file_data[i], case_bit) * hash) + to_lower(file_data[i + to_find_size], case_bit)) % prime;
						if (t_hash < 0)
							t_hash = (t_hash + prime);
					}
				}

			}
		}
		void brute_force_algorithm(char* to_find, bool case_bit, bool word_match)
		{
			std::fstream fin;
			std::string file_data;
			char ch;
			std::string file_name;
			for (int i = 0; i < 10; i++)
			{
				file_name = "Research#" + std::to_string(i + 1) + ".txt";
				int to_find_size = 0;
				int file_size = 0;
				int k = 0, l = 0;
				fin.open(file_name.c_str());
				if (!fin.is_open())
					std::cout << "Something Went Wrong While Opening File\n";
				while (!fin.eof())
				{
					fin.get(ch);
					if (fin.eof())
						break;
					file_data.push_back(ch);
				}
				to_find_size = strlen(to_find);
				file_size = file_data.length();
				k = 0;
				l = 1;
				for (int i = 0; i <= file_size - to_find_size; i++)
				{
					int j;
					if (file_data[i] == '\n')
						l = 0, k++;
					l++;
					for (j = 0; j < to_find_size; j++)
						if (to_lower(file_data[i + j], case_bit) != to_lower(to_find[j], case_bit))
							break;
					if (j == to_find_size)
					{
						int start = i;
						int end = i;
						while (file_data[end] != ' ')
							end++;
						while (file_data[start] != ' ')
							start--;
						std::string full_word = file_data.substr(start + 1, end - start - 1);
						if (!word_match)
						{
							this->occurances++;
							this->output_list->Items->Add("===================================================");
							std::string str = "******** Found at, i: " + std::to_string(l - 1) + " j: " + std::to_string(k + 1) + " in file: " + file_name + " ********";
							String ^ conv_str = msclr::interop::marshal_as<String ^>(str);
							this->output_list->Items->Add(conv_str);
							std::string str1 = "++++++++++++ Matching Word Was: " + full_word + " ++++++++++++ ";
							String ^ conv_str1 = msclr::interop::marshal_as<String ^>(str1);
							this->output_list->Items->Add(conv_str1);
							this->output_list->Items->Add("===================================================");

						}
						else
						{
							if (to_find == full_word)
							{
								this->occurances++;
								this->output_list->Items->Add("===================================================");
								std::string str = "******** Found at, i: " + std::to_string(l - 1) + " j: " + std::to_string(k + 1) + " in file: " + file_name + " ********";
								String ^ conv_str = msclr::interop::marshal_as<String ^>(str);
								this->output_list->Items->Add(conv_str);
								std::string temp(to_find);
								std::string str1 = "++++++++++++ Matching Word Was: " + temp + " ++++++++++++ ";
								String ^ conv_str1 = msclr::interop::marshal_as<String ^>(str1);
								this->output_list->Items->Add(conv_str1);
								this->output_list->Items->Add("===================================================");
							}

						}
						
					}
				}
			}
		}

		void KMP_algorithm(char* to_find, bool case_bit, bool word_match)
		{
			std::fstream fin;
			std::string file_data;
			char ch;
			std::string file_name;
			for (int i = 0; i < 10; i++)
			{
				file_name = "Research#" + std::to_string(i + 1) + ".txt";
				int to_find_size = 0;
				int file_size = 0;
				int k = 0, l = 0;
				fin.open(file_name.c_str());
				if (!fin.is_open())
					std::cout << "Something Went Wrong While Opening File\n";
				while (!fin.eof())
				{
					fin.get(ch);
					if (fin.eof())
						break;
					file_data.push_back(ch);
				}
				to_find_size = strlen(to_find);
				file_size = file_data.length();
				k = 0;
				l = 1;
				int* pie = new int[to_find_size];
				prefix_calculator(to_find, to_find_size, pie);
				int z = 0;
				int j = 0;
				while (z < file_size)
				{
					if (to_lower(to_find[j], case_bit) == to_lower(file_data[z], case_bit))
					{
						j++;
						z++;
					}
					if (file_data[z] == '\n')
						l = 0, k++;
					l++;
					if (j == to_find_size)
					{
						int start = z-1;
						int end = z-1;
						while (file_data[end] != ' ')
							end++;
						while (file_data[start] != ' ')
							start--;
						std::string full_word = file_data.substr(start + 1, end - start-1);
						if (!word_match)
						{
							this->occurances++;
							this->output_list->Items->Add("===================================================");
							std::string str = "******** Found at, i: " + std::to_string(l - 2) + " j: " + std::to_string(k + 1) + " in file: " + file_name + " ********";
							String ^ conv_str = msclr::interop::marshal_as<String ^>(str);
							this->output_list->Items->Add(conv_str);
							std::string str1 = "++++++++++++ Matching Word Was: " + full_word + " ++++++++++++ ";
							String ^ conv_str1 = msclr::interop::marshal_as<String ^>(str1);
							this->output_list->Items->Add(conv_str1);
							this->output_list->Items->Add("===================================================");
						}
						else
						{
							if (to_find == full_word)
							{
								this->occurances++;
								this->output_list->Items->Add("===================================================");
								std::string str = "******** Found at, i: " + std::to_string(l - 2) + " j: " + std::to_string(k + 1) + " in file: " + file_name + " ********";
								String ^ conv_str = msclr::interop::marshal_as<String ^>(str);
								this->output_list->Items->Add(conv_str);
								std::string temp(to_find);
								std::string str1 = "++++++++++++ Matching Word Was: " + temp + " ++++++++++++ ";
								String ^ conv_str1 = msclr::interop::marshal_as<String ^>(str1);
								this->output_list->Items->Add(conv_str1);
								this->output_list->Items->Add("===================================================");
							}

						}
						j = pie[j - 1];
					}
					else if (z < file_size  && to_lower(to_find[j], case_bit) != to_lower(file_data[z], case_bit))
					{
						if (j != 0)
							j = pie[j - 1];
						else
							z++;
					}
				}
				free(pie);
			}
		}


	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  naive_algo;
	private: System::Windows::Forms::TextBox^  find_str;
	protected:


	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Button^  rabin_karp;
	private: System::Windows::Forms::Button^  kmp_algo;


	private: System::Windows::Forms::CheckBox^  whole_word;

	private: System::Windows::Forms::CheckBox^  match_case;

	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::ListBox^  output_list;

	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label4;
	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->naive_algo = (gcnew System::Windows::Forms::Button());
			this->find_str = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->rabin_karp = (gcnew System::Windows::Forms::Button());
			this->kmp_algo = (gcnew System::Windows::Forms::Button());
			this->whole_word = (gcnew System::Windows::Forms::CheckBox());
			this->match_case = (gcnew System::Windows::Forms::CheckBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->output_list = (gcnew System::Windows::Forms::ListBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// naive_algo
			// 
			this->naive_algo->Location = System::Drawing::Point(314, 33);
			this->naive_algo->Name = L"naive_algo";
			this->naive_algo->Size = System::Drawing::Size(83, 23);
			this->naive_algo->TabIndex = 0;
			this->naive_algo->Text = L"Brute Force";
			this->naive_algo->UseVisualStyleBackColor = true;
			this->naive_algo->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// find_str
			// 
			this->find_str->Location = System::Drawing::Point(88, 33);
			this->find_str->Name = L"find_str";
			this->find_str->Size = System::Drawing::Size(204, 20);
			this->find_str->TabIndex = 1;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(23, 37);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(59, 13);
			this->label1->TabIndex = 2;
			this->label1->Text = L"Find What:";
			this->label1->Click += gcnew System::EventHandler(this, &MyForm::label1_Click);
			// 
			// rabin_karp
			// 
			this->rabin_karp->Location = System::Drawing::Point(314, 62);
			this->rabin_karp->Name = L"rabin_karp";
			this->rabin_karp->Size = System::Drawing::Size(83, 23);
			this->rabin_karp->TabIndex = 3;
			this->rabin_karp->Text = L"Rabin Karp";
			this->rabin_karp->UseVisualStyleBackColor = true;
			this->rabin_karp->Click += gcnew System::EventHandler(this, &MyForm::rabin_karp_Click);
			// 
			// kmp_algo
			// 
			this->kmp_algo->Location = System::Drawing::Point(314, 91);
			this->kmp_algo->Name = L"kmp_algo";
			this->kmp_algo->Size = System::Drawing::Size(83, 23);
			this->kmp_algo->TabIndex = 4;
			this->kmp_algo->Text = L"KMP Matcher";
			this->kmp_algo->UseVisualStyleBackColor = true;
			this->kmp_algo->Click += gcnew System::EventHandler(this, &MyForm::kmp_algo_Click);
			// 
			// whole_word
			// 
			this->whole_word->AutoSize = true;
			this->whole_word->Location = System::Drawing::Point(26, 107);
			this->whole_word->Name = L"whole_word";
			this->whole_word->Size = System::Drawing::Size(143, 17);
			this->whole_word->TabIndex = 5;
			this->whole_word->Text = L"Match Whole Word Only";
			this->whole_word->UseVisualStyleBackColor = true;
			// 
			// match_case
			// 
			this->match_case->AutoSize = true;
			this->match_case->Location = System::Drawing::Point(26, 130);
			this->match_case->Name = L"match_case";
			this->match_case->Size = System::Drawing::Size(83, 17);
			this->match_case->TabIndex = 6;
			this->match_case->Text = L"Match Case";
			this->match_case->UseVisualStyleBackColor = true;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label2->Location = System::Drawing::Point(239, 144);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(150, 16);
			this->label2->TabIndex = 7;
			this->label2->Text = L"iem.saad@hotmail.com";
			this->label2->Click += gcnew System::EventHandler(this, &MyForm::label2_Click);
			// 
			// output_list
			// 
			this->output_list->FormattingEnabled = true;
			this->output_list->Location = System::Drawing::Point(22, 196);
			this->output_list->Name = L"output_list";
			this->output_list->Size = System::Drawing::Size(374, 186);
			this->output_list->TabIndex = 8;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(22, 389);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(77, 13);
			this->label3->TabIndex = 9;
			this->label3->Text = L"Time Elapsed: ";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(19, 180);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(179, 13);
			this->label4->TabIndex = 10;
			this->label4->Text = L"Found Match At Following Locations";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(23, 416);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(111, 13);
			this->label5->TabIndex = 11;
			this->label5->Text = L"No Of Occurances : 0";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label6->Location = System::Drawing::Point(280, 414);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(91, 13);
			this->label6->TabIndex = 12;
			this->label6->Text = L"Applied Algorithm:";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(430, 453);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->output_list);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->match_case);
			this->Controls->Add(this->whole_word);
			this->Controls->Add(this->kmp_algo);
			this->Controls->Add(this->rabin_karp);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->find_str);
			this->Controls->Add(this->naive_algo);
			this->Name = L"MyForm";
			this->Text = L"String Matching Problem";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void MyForm_Load(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
		output_list->Items->Clear();
		label5->Text = "Occurances Found: ";
		this->occurances = 0;
		label6->Text = "Applied Brute Froce Algo";
		if (find_str->Text->Length < 1)
		{
			label4->Text = "Time Eclapsed: ";
			label5->Text = "Occurances Found: ";
			label6->Text = "Applied Algorithm: ";
			MessageBox::Show("Please Enter Text For Searching First!", "Empty Field Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
		std::string to_find = msclr::interop::marshal_as<std::string>(find_str->Text);
		auto start = std::chrono::steady_clock::now();
		this->brute_force_algorithm(const_cast<char*>(to_find.c_str()), match_case->Checked, whole_word->Checked);
		auto end = std::chrono::steady_clock::now();
		std::chrono::duration<double> elapsed_seconds = end - start;
		std::string str = "Total Time Elapsed is: " + std::to_string(elapsed_seconds.count()) + " sec";
		String ^ conv_str = msclr::interop::marshal_as<String ^>(str);
		label3->Text = conv_str;
		if (this->occurances > 0)
		{
			std::string str = "Found " + std::to_string(this->occurances) + " Occurances.";
			String ^ conv_str = msclr::interop::marshal_as<String ^>(str);
			label5->Text = conv_str;
		}
		else
			this->output_list->Items->Add("Ops! Can't Find Matching String, In Any of Given Files!");

	}
	private: System::Void label1_Click(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void rabin_karp_Click(System::Object^  sender, System::EventArgs^  e) {
		output_list->Items->Clear();
		this->occurances = 0;
		label5->Text = "Occurances Found: ";
		label6->Text = "Applied Rabin Karp Algo";
		if (find_str->Text->Length < 1)
		{
			label4->Text = "Time Eclapsed: ";
			label5->Text = "Occurances Found: ";
			MessageBox::Show("Please Enter Text For Searching First!", "Empty Field Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
			label6->Text = "Applied Algorithm: ";
		}
		std::string to_find = msclr::interop::marshal_as<std::string>(find_str->Text);
		auto start = std::chrono::steady_clock::now();
		this->rabin_karp_algorithm(const_cast<char*>(to_find.c_str()), match_case->Checked, whole_word->Checked);
		auto end = std::chrono::steady_clock::now();
		std::chrono::duration<double> elapsed_seconds = end - start;
		std::string str = "Total Time Elapsed is: " + std::to_string(elapsed_seconds.count()) + " sec";
		String ^ conv_str = msclr::interop::marshal_as<String ^>(str);
		label3->Text = conv_str;
		if (this->occurances > 0)
		{
			std::string str = "Found " + std::to_string(this->occurances) + " Occurances.";
			String ^ conv_str = msclr::interop::marshal_as<String ^>(str);
			label5->Text = conv_str;
		}
		else
			this->output_list->Items->Add("Ops! Can't Find Matching String, In Any of Given Files!");

	}
	private: System::Void kmp_algo_Click(System::Object^  sender, System::EventArgs^  e) {
		output_list->Items->Clear();
		this->occurances = 0;
		label5->Text = "Occurances Found: ";
		label6->Text = "Applied KMP Algo";
		if (find_str->Text->Length < 1)
		{
			label4->Text = "Time Eclapsed: ";
			label5->Text = "Occurances Found: ";
			MessageBox::Show("Please Enter Text For Searching First!", "Empty Field Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
			label6->Text = "Applied Algorithm: ";
		}
		std::string to_find = msclr::interop::marshal_as<std::string>(find_str->Text);
		auto start = std::chrono::steady_clock::now();
		this->KMP_algorithm(const_cast<char*>(to_find.c_str()), match_case->Checked, whole_word->Checked);
		auto end = std::chrono::steady_clock::now();
		std::chrono::duration<double> elapsed_seconds = end - start;
		std::string str = "Total Time Elapsed is: " + std::to_string(elapsed_seconds.count()) + " sec";
		String ^ conv_str = msclr::interop::marshal_as<String ^>(str);
		label3->Text = conv_str;
		if (this->occurances > 0)
		{
			std::string str = "Found " + std::to_string(this->occurances) + " Occurances.";
			String ^ conv_str = msclr::interop::marshal_as<String ^>(str);
			label5->Text = conv_str;
		}
		else
			this->output_list->Items->Add("Ops! Can't Find Matching String, In Any of Given Files!");
	}
private: System::Void label2_Click(System::Object^  sender, System::EventArgs^  e) {
}
};
}
