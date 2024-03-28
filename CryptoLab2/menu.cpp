#include "menu.h"
#include <iostream>
#include <string>
#include "msclr\marshal_cppstd.h"

using namespace CryptoLab2;

[STAThreadAttribute]
void main(array<String^>^ args) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	CryptoLab2::menu form;
	Application::Run(% form);
}

//Encryption
System::Void CryptoLab2::menu::button1_Click(System::Object^ sender, System::EventArgs^ e)
{
	using namespace std;

	//Collecting data

	//File path
	string p = msclr::interop::marshal_as<string>(menu::PathOpen->Text);

	//Number of characters in a face line with input error checking
	string temp = msclr::interop::marshal_as<string>(menu::Size->Text);
	string temp2;

	int Size = -1;

	//Dimension check
	if (temp != "") {
		for (int i = 0; i < size(temp); i++) {
			if (int(temp[i]) < 48 || int(temp[i]) > 58) {
				break;
			}
			else {
				temp2 += temp[i];
			}
		}

		if (size(temp2) == size(temp)) {
			Size = stoi(temp);
			temp = "";
			temp2 = "";
		}
		else {
			temp = "";
			temp2 = "";
		}
	}
	else {
		Size = -1;
	}

	//Key with error checking
	string key = msclr::interop::marshal_as<string>(menu::KeyOpen->Text);
	string s1 = "LRUD";
	string tempKey;
	int Key = 0;

	for (int i = 0; i < key.size(); i++) {
		tempKey = key.substr(i);
		int temp = -1;

		try {
			int n = stoi(tempKey);
			temp = n;
		}
		catch (invalid_argument) {
			Key = -1;
			break;
		}
		
		if (temp == 0) {
			Key = -1;
			break;
		}

		if (temp > Size && Size != -1) {
			Key = -1;
			break;
		}

		i += to_string(temp).size();
		tempKey = key.substr(i);
		
		if (i == key.size() - 2) {
			Key = -1;
			break;
		}
		
		for (int m = 0; m < s1.size(); m++) {
			if (key[i] == s1[m]) {
				break;
			}
			else {
				if (m == s1.size() - 1) {
					Key = -1;
					break;
				}
			}
		}

		if (Key == -1) {
			break;
		}
	}

	//Opening a file and checking conditions
	FILE* f = fopen(p.c_str(), "r");
	if (Size < 2) {
		menu::ErrorOpen->Text = "Error in specifying dimensions";
	}
	else {
		if (Key == -1) {
			menu::ErrorOpen->Text = "Error when entering a key or out of dimension";
		}
		else {
			if (f == NULL) {
				menu::ErrorOpen->Text = "Error opening file";
			}
			else {
				//Collecting data from a file into a string
				string text;
				char c;
				while ((c = fgetc(f)) != EOF) {
					text.push_back(c);
					c = '\0';
				}

				fclose(f);

				int cube = Size * Size * 6;
				if (text.size() % cube != 0) {
					int tmp = cube - (text.size() % cube);
					for (int i = 0; i < tmp; i++) {
						text += " ";
					}
				}

				//Creating a string with encrypted text
				string ctext;

				int textkrat = text.size() / cube;
				for (int i = 0; i < textkrat; i++) {

					//Creating a multidimensional dynamic array
					char*** block = new char** [6];
					for (int j = 0; j < 6; j++) {
						block[j] = new char* [Size];
						for (int k = 0; k < Size; k++) {
							block[j][k] = new char[Size];
						}
					}

					//Filling the "cube"
					int str = 0;
					for (int n = 0; n < 6; n++) {
						for (int m = 0; m < Size; m++) {
							for (int k = 0; k < Size; k++) {
								block[n][m][k] = text[str];
								str++;
							}
						}
					}

					//Shortening a line (important)
					text = text.substr(str);
					
					//Performing steps by key

					string tm;
					for (int n = 0; n < key.size(); n++) {
						tm = key.substr(n);
						int row = stoi(tm);
						n += to_string(row).size();
						char command = key[n];

						//List the actions in accordance with the command
						int R = row - 1;
						int S = Size - 1;
						if (command == 'R') {
							if (row == 1) {
								string tmp;
								char** temp = new char* [Size];
								for (int i = 0; i < Size; i++) {
									temp[i] = new char[Size];
								}

								for (int i = 0; i < Size; i++) {
									for (int j = 0; j < Size; j++) {
										temp[S - j][i] = block[4][i][j];
									}
								}

								for (int i = 0; i < Size; i++) {
									for (int j = 0; j < Size; j++) {
										block[4][i][j] = temp[i][j];
									}
								}

								for (int i = 0; i < Size; i++) {
									delete[] temp[i];
								}
								delete[] temp;
							}

							if (row == Size) {
									string tmp;
									char** temp = new char* [Size];
									for (int i = 0; i < Size; i++) {
										temp[i] = new char[Size];
									}

									for (int i = 0; i < Size; i++) {
										for (int j = 0; j < Size; j++) {
											temp[j][S-i] = block[5][i][j];
										}
									}

									for (int i = 0; i < Size; i++) {
										for (int j = 0; j < Size; j++) {
											block[5][i][j] = temp[i][j];
										}
									}

									for (int i = 0; i < Size; i++) {
										delete[] temp[i];
									}
									delete[] temp;
								}
							
							string tmp = "";
							for (int i = 0; i < Size; i++) {
								tmp.push_back(block[0][R][i]);
								block[0][R][i] = block[3][R][i];
							}
							for (int k = 1; k < 4; k++) {
								string tmp2;
								for (int i = 0; i < Size; i++) {
									tmp2.push_back(block[k][R][i]);
									block[k][R][i] = tmp[i];
									tmp[i] = tmp2[i];
								}
							}
						}

						if (command == 'L') {
							if (row == 1) {
								string tmp;
								char** temp = new char* [Size];
								for (int i = 0; i < Size; i++) {
									temp[i] = new char[Size];
								}

								for (int i = 0; i < Size; i++) {
									for (int j = 0; j < Size; j++) {
										temp[j][S - i] = block[4][i][j];
									}
								}

								for (int i = 0; i < Size; i++) {
									for (int j = 0; j < Size; j++) {
										block[4][i][j] = temp[i][j];
									}
								}

								for (int i = 0; i < Size; i++) {
									delete[] temp[i];
								}
								delete[] temp;
							}

							if (row == Size) {
									string tmp;
									char** temp = new char* [Size];
									for (int i = 0; i < Size; i++) {
										temp[i] = new char[Size];
									}

									for (int i = 0; i < Size; i++) {
										for (int j = 0; j < Size; j++) {
											temp[S - j][i] = block[5][i][j];
										}
									}

									for (int i = 0; i < Size; i++) {
										for (int j = 0; j < Size; j++) {
											block[5][i][j] = temp[i][j];
										}
									}

									for (int i = 0; i < Size; i++) {
										delete[] temp[i];
									}
									delete[] temp;
								}

							string tmp = "";
							for (int i = 0; i < Size; i++) {
								tmp.push_back(block[3][R][i]);
								block[3][R][i] = block[0][R][i];
							}
							for (int k = 2; k > -1; k--) {
								string tmp2;
								for (int i = 0; i < Size; i++) {
									tmp2.push_back(block[k][R][i]);
									block[k][R][i] = tmp[i];
									tmp[i] = tmp2[i];
								}
							}

						}

						if (command == 'U') {
							if (row == 1) {
								string tmp,tmp2;
								char** temp = new char* [Size];
								for (int i = 0; i < Size; i++) {
									temp[i] = new char[Size];
								}

								for (int i = 0; i < Size; i++) {
									for (int j = 0; j < Size; j++) {
										temp[S - j][i] = block[3][i][j];
									}
								}

								for (int i = 0; i < Size; i++) {
									for (int j = 0; j < Size; j++) {
										block[3][i][j] = temp[i][j];
									}
								}

								for (int i = 0; i < Size; i++) {
									delete[] temp[i];
								}
								delete[] temp;
							}
							
							if (row == Size) {
									string tmp,tmp2;
									char** temp = new char* [Size];
									for (int i = 0; i < Size; i++) {
										temp[i] = new char[Size];
									}

									for (int i = 0; i < Size; i++) {
										for (int j = 0; j < Size; j++) {
											temp[j][S-i] = block[1][i][j];
										}
									}

									for (int i = 0; i < Size; i++) {
										for (int j = 0; j < Size; j++) {
											block[1][i][j] = temp[i][j];
										}
									}

									for (int i = 0; i < Size; i++) {
										delete[] temp[i];
									}
									delete[] temp;
								}
							

							string tmp = "", tmp2 = "";
							for (int i = 0; i < Size; i++) {
								tmp.push_back(block[0][i][R]);
								block[0][i][R] = block[5][i][R];
							}
							for (int i = 0; i < Size; i++) {
								tmp2.push_back(block[4][i][R]);
								block[4][i][R] = tmp[i];
								tmp[i] = tmp2[i];
							}
							tmp2 = "";
							for (int i = 0; i < Size; i++) {
								tmp2.push_back(block[2][S-i][S-R]);
								block[2][S-i][S-R] = tmp[i];
								tmp[i] = tmp2[i];
							}
							for (int i = 0; i < Size; i++) {
								block[5][i][R] = tmp[i];
							}
						}

						if (command == 'D') {
							if (row == 1) {
								string tmp, tmp2;
								char** temp = new char* [Size];
								for (int i = 0; i < Size; i++) {
									temp[i] = new char[Size];
								}

								for (int i = 0; i < Size; i++) {
									for (int j = 0; j < Size; j++) {
										temp[j][S-i] = block[3][i][j];
									}
								}

								for (int i = 0; i < Size; i++) {
									for (int j = 0; j < Size; j++) {
										block[3][i][j] = temp[i][j];
									}
								}

								for (int i = 0; i < Size; i++) {
									delete[] temp[i];
								}
								delete[] temp;
							}
							
							if (row == Size) {
									string tmp, tmp2;
									char** temp = new char* [Size];
									for (int i = 0; i < Size; i++) {
										temp[i] = new char[Size];
									}

									for (int i = 0; i < Size; i++) {
										for (int j = 0; j < Size; j++) {
											temp[S-j][i] = block[1][i][j];
										}
									}

									for (int i = 0; i < Size; i++) {
										for (int j = 0; j < Size; j++) {
											block[1][i][j] = temp[i][j];
										}
									}

									for (int i = 0; i < Size; i++) {
										delete[] temp[i];
									}
									delete[] temp;
								}
							
							string tmp = "", tmp2 = "";
							for (int i = 0; i < Size; i++) {
								tmp.push_back(block[5][i][R]);
								block[5][i][R] = block[0][i][R];
							}
							for (int i = 0; i < Size; i++) {
								tmp2.push_back(block[2][S-i][S-R]);
								block[2][S-i][S-R] = tmp[i];
								tmp[i] = tmp2[i];
							}
							tmp2 = "";
							for (int i = 0; i < Size; i++) {
								tmp2.push_back(block[4][i][R]);
								block[4][i][R] = tmp[i];
								tmp[i] = tmp2[i];
							}
							for (int i = 0; i < Size; i++) {
								block[0][i][R] = tmp[i];
							}
						}
					}
					
					//Reading the "cube" into a variable
					for (int i = 0; i < 6; i++) {
						for (int j = 0; j < Size; j++) {
							for (int k = 0; k < Size; k++) {
								ctext.push_back(block[i][j][k]);
							}
						}
					}
					

					fclose(f);

					//Clearing a multidimensional dynamic array
					for (int j = 0; j < 6; j++) {
						for (int k = 0; k < Size; k++) {
							delete[] block[j][k];
						}
						delete[] block[j];
					}

					delete[] block;
				}

				//We write the result to a file
				FILE* f = fopen("chiper.omg", "wb");
				for (int i = 0; i < ctext.size(); i++) {
					int tmp = fputc(ctext[i], f);
				}

				fclose(f);

				//Notifying about success
				menu::ErrorOpen->Text = "Successful!";
			}
		}
	}
}


//Decryption
System::Void CryptoLab2::menu::button2_Click(System::Object^ sender, System::EventArgs^ e)
{
	using namespace std;

	//Collecting data

	//File path
	string p = msclr::interop::marshal_as<string>(menu::CPathOpen->Text);

	//Number of characters in a face line with input error checking
	string temp = msclr::interop::marshal_as<string>(menu::CSize->Text);
	string temp2;

	int Size = -1;

	//Dimension check
	if (temp != "") {
		for (int i = 0; i < size(temp); i++) {
			if (int(temp[i]) < 48 || int(temp[i]) > 58) {
				break;
			}
			else {
				temp2 += temp[i];
			}
		}

		if (size(temp2) == size(temp)) {
			Size = stoi(temp);
			temp = "";
			temp2 = "";
		}
		else {
			temp = "";
			temp2 = "";
		}
	}
	else {
		Size = -1;
	}

	//Key with error checking
	string key = msclr::interop::marshal_as<string>(menu::KeyClose->Text);
	string s1 = "LRUD";
	string tempKey;
	int Key = 0;

	for (int i = 0; i < key.size(); i++) {
		tempKey = key.substr(i);
		int temp = -1;

		try {
			int n = stoi(tempKey);
			temp = n;
		}
		catch (invalid_argument) {
			Key = -1;
			break;
		}

		if (temp == 0) {
			Key = -1;
			break;
		}

		if (temp > Size && Size != -1) {
			Key = -1;
			break;
		}

		i += to_string(temp).size();
		tempKey = key.substr(i);

		if (i == key.size() - 2) {
			Key = -1;
			break;
		}

		for (int m = 0; m < s1.size(); m++) {
			if (key[i] == s1[m]) {
				break;
			}
			else {
				if (m == s1.size() - 1) {
					Key = -1;
					break;
				}
			}
		}

		if (Key == -1) {
			break;
		}
	}

	//Opening a file and checking conditions
	FILE* f = fopen(p.c_str(), "r");
	if (Size < 2) {
		menu::CErrorOpen->Text = "Error in specifying dimensions";
	}
	else {
		if (Key == -1) {
			menu::CErrorOpen->Text = "Error when entering a key or out of dimension";
		}
		else {
			if (f == NULL) {
				menu::CErrorOpen->Text = "Error opening file";
			}
			else {
				//Collecting data from a file into a string
				string text;
				char c;
				while ((c = fgetc(f)) != EOF) {
					text.push_back(c);
					c = '\0';
				}

				fclose(f);

				int cube = Size * Size * 6;
				if (text.size() % cube != 0) {
					int tmp = cube - (text.size() % cube);
					for (int i = 0; i < tmp; i++) {
						text += " ";
					}
				}

				//I create a string with decrypted text
				string ctext;

				int textkrat = text.size() / cube;
				for (int i = 0; i < textkrat; i++) {

					//Creating a multidimensional dynamic array
					char*** block = new char** [6];
					for (int j = 0; j < 6; j++) {
						block[j] = new char* [Size];
						for (int k = 0; k < Size; k++) {
							block[j][k] = new char[Size];
						}
					}

					//Filling the "cube"
					int str = 0;
					for (int n = 0; n < 6; n++) {
						for (int m = 0; m < Size; m++) {
							for (int k = 0; k < Size; k++) {
								block[n][m][k] = text[str];
								str++;
							}
						}
					}

					//Shortening a String
					text = text.substr(str);

					//Performing steps by key
					for (int n = key.size() - 1; n >= 0; n--) {
						char command = key[n];
						n--;

						string num;
						while (int(key[n]) > 47 && int(key[n]) < 59) {
							num += key[n];
							n--;
							if (n == -1) {
								break;
							}
						}
						n++;

						string numr;
						for (int i = num.size() - 1; i >= 0; i--) {
							numr += num;
						}
						
						int row = stoi(numr);
						//I list the actions in accordance with the command
						int R = row - 1;
						int S = Size - 1;
						if (command == 'L') {
							if (row == 1) {
								string tmp;
								char** temp = new char* [Size];
								for (int i = 0; i < Size; i++) {
									temp[i] = new char[Size];
								}

								for (int i = 0; i < Size; i++) {
									for (int j = 0; j < Size; j++) {
										temp[S - j][i] = block[4][i][j];
									}
								}

								for (int i = 0; i < Size; i++) {
									for (int j = 0; j < Size; j++) {
										block[4][i][j] = temp[i][j];
									}
								}

								for (int i = 0; i < Size; i++) {
									delete[] temp[i];
								}
								delete[] temp;
							}

							if (row == Size) {
								string tmp;
								char** temp = new char* [Size];
								for (int i = 0; i < Size; i++) {
									temp[i] = new char[Size];
								}

								for (int i = 0; i < Size; i++) {
									for (int j = 0; j < Size; j++) {
										temp[j][S - i] = block[5][i][j];
									}
								}

								for (int i = 0; i < Size; i++) {
									for (int j = 0; j < Size; j++) {
										block[5][i][j] = temp[i][j];
									}
								}

								for (int i = 0; i < Size; i++) {
									delete[] temp[i];
								}
								delete[] temp;
							}

							string tmp = "";
							for (int i = 0; i < Size; i++) {
								tmp.push_back(block[0][R][i]);
								block[0][R][i] = block[3][R][i];
							}
							for (int k = 1; k < 4; k++) {
								string tmp2;
								for (int i = 0; i < Size; i++) {
									tmp2.push_back(block[k][R][i]);
									block[k][R][i] = tmp[i];
									tmp[i] = tmp2[i];
								}
							}
						}

						if (command == 'R') {
							if (row == 1) {
								string tmp;
								char** temp = new char* [Size];
								for (int i = 0; i < Size; i++) {
									temp[i] = new char[Size];
								}

								for (int i = 0; i < Size; i++) {
									for (int j = 0; j < Size; j++) {
										temp[j][S - i] = block[4][i][j];
									}
								}

								for (int i = 0; i < Size; i++) {
									for (int j = 0; j < Size; j++) {
										block[4][i][j] = temp[i][j];
									}
								}

								for (int i = 0; i < Size; i++) {
									delete[] temp[i];
								}
								delete[] temp;
							}

							if (row == Size) {
								string tmp;
								char** temp = new char* [Size];
								for (int i = 0; i < Size; i++) {
									temp[i] = new char[Size];
								}

								for (int i = 0; i < Size; i++) {
									for (int j = 0; j < Size; j++) {
										temp[S - j][i] = block[5][i][j];
									}
								}

								for (int i = 0; i < Size; i++) {
									for (int j = 0; j < Size; j++) {
										block[5][i][j] = temp[i][j];
									}
								}

								for (int i = 0; i < Size; i++) {
									delete[] temp[i];
								}
								delete[] temp;
							}

							string tmp = "";
							for (int i = 0; i < Size; i++) {
								tmp.push_back(block[3][R][i]);
								block[3][R][i] = block[0][R][i];
							}
							for (int k = 2; k > -1; k--) {
								string tmp2;
								for (int i = 0; i < Size; i++) {
									tmp2.push_back(block[k][R][i]);
									block[k][R][i] = tmp[i];
									tmp[i] = tmp2[i];
								}
							}

						}

						if (command == 'D') {
							if (row == 1) {
								string tmp, tmp2;
								char** temp = new char* [Size];
								for (int i = 0; i < Size; i++) {
									temp[i] = new char[Size];
								}

								for (int i = 0; i < Size; i++) {
									for (int j = 0; j < Size; j++) {
										temp[S - j][i] = block[3][i][j];
									}
								}

								for (int i = 0; i < Size; i++) {
									for (int j = 0; j < Size; j++) {
										block[3][i][j] = temp[i][j];
									}
								}

								for (int i = 0; i < Size; i++) {
									delete[] temp[i];
								}
								delete[] temp;
							}

							if (row == Size) {
								string tmp, tmp2;
								char** temp = new char* [Size];
								for (int i = 0; i < Size; i++) {
									temp[i] = new char[Size];
								}

								for (int i = 0; i < Size; i++) {
									for (int j = 0; j < Size; j++) {
										temp[j][S - i] = block[1][i][j];
									}
								}

								for (int i = 0; i < Size; i++) {
									for (int j = 0; j < Size; j++) {
										block[1][i][j] = temp[i][j];
									}
								}

								for (int i = 0; i < Size; i++) {
									delete[] temp[i];
								}
								delete[] temp;
							}


							string tmp = "", tmp2 = "";
							for (int i = 0; i < Size; i++) {
								tmp.push_back(block[0][i][R]);
								block[0][i][R] = block[5][i][R];
							}
							for (int i = 0; i < Size; i++) {
								tmp2.push_back(block[4][i][R]);
								block[4][i][R] = tmp[i];
								tmp[i] = tmp2[i];
							}
							tmp2 = "";
							for (int i = 0; i < Size; i++) {
								tmp2.push_back(block[2][S - i][S - R]);
								block[2][S - i][S - R] = tmp[i];
								tmp[i] = tmp2[i];
							}
							for (int i = 0; i < Size; i++) {
								block[5][i][R] = tmp[i];
							}
						}

						if (command == 'U') {
							if (row == 1) {
								string tmp, tmp2;
								char** temp = new char* [Size];
								for (int i = 0; i < Size; i++) {
									temp[i] = new char[Size];
								}

								for (int i = 0; i < Size; i++) {
									for (int j = 0; j < Size; j++) {
										temp[j][S - i] = block[3][i][j];
									}
								}

								for (int i = 0; i < Size; i++) {
									for (int j = 0; j < Size; j++) {
										block[3][i][j] = temp[i][j];
									}
								}

								for (int i = 0; i < Size; i++) {
									delete[] temp[i];
								}
								delete[] temp;
							}

							if (row == Size) {
								string tmp, tmp2;
								char** temp = new char* [Size];
								for (int i = 0; i < Size; i++) {
									temp[i] = new char[Size];
								}

								for (int i = 0; i < Size; i++) {
									for (int j = 0; j < Size; j++) {
										temp[S - j][i] = block[1][i][j];
									}
								}

								for (int i = 0; i < Size; i++) {
									for (int j = 0; j < Size; j++) {
										block[1][i][j] = temp[i][j];
									}
								}

								for (int i = 0; i < Size; i++) {
									delete[] temp[i];
								}
								delete[] temp;
							}

							string tmp = "", tmp2 = "";
							for (int i = 0; i < Size; i++) {
								tmp.push_back(block[5][i][R]);
								block[5][i][R] = block[0][i][R];
							}
							for (int i = 0; i < Size; i++) {
								tmp2.push_back(block[2][S - i][S - R]);
								block[2][S - i][S - R] = tmp[i];
								tmp[i] = tmp2[i];
							}
							tmp2 = "";
							for (int i = 0; i < Size; i++) {
								tmp2.push_back(block[4][i][R]);
								block[4][i][R] = tmp[i];
								tmp[i] = tmp2[i];
							}
							for (int i = 0; i < Size; i++) {
								block[0][i][R] = tmp[i];
							}
						}
					}

					//Reading the "cube" into a variable
					for (int i = 0; i < 6; i++) {
						for (int j = 0; j < Size; j++) {
							for (int k = 0; k < Size; k++) {
								ctext.push_back(block[i][j][k]);
							}
						}
					}


					fclose(f);

					//Clearing a multidimensional dynamic array
					for (int j = 0; j < 6; j++) {
						for (int k = 0; k < Size; k++) {
							delete[] block[j][k];
						}
						delete[] block[j];
					}

					delete[] block;
				}

				//We write the result to a file
				FILE* f = fopen("result.txt", "wb");
				for (int i = 0; i < ctext.size(); i++) {
					int tmp = fputc(ctext[i], f);
				}

				fclose(f);

				//Notifying about success
				menu::CErrorOpen->Text = "Successful!";
			}
		}
	}
}
