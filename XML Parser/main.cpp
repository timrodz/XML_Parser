#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

void FillInformation();
void GenerateXML(ofstream &, string, string, string, string, string);
void GenerateCSV(ofstream &, string, string, string, string, string);
void XMLtoCSV(string, string);
void CSVtoXML(string, string);

int main() {

	int choice = -1;

	while (choice != 4) {

		//system("cls");
		cout << "Welcome to the XML parser\n1. Input information and genrate both XML and CSV files\n2. Convert XML to CSV\n3. Convert CSV to XML\n4. Quit\nOption: ";
		cin >> choice;

		cin.clear();
		cin.ignore(1000, '\n');

		switch (choice) {
			case 1:
				FillInformation();
				break;
			case 2:
			{
				cout << "Please input the file name: ";
				string file;
				getline(cin, file);

				if (file.find(".xml") != -1) {
					string fileName = file.substr(0, file.find(".xml"));
					fileName += "_parsed.csv";
					XMLtoCSV(file, fileName);
				}
				else {
					cout << endl << "Invalid file type. Please try again." << endl << endl;
					cin.ignore(1000, '\n');
				}

			}
			break;
			case 3:
			{
				cout << "Please input the file name: ";
				string file;
				getline(cin, file);

				if (file.find(".csv") != -1) {
					string fileName = file.substr(0, file.find(".csv"));
					fileName += "_parsed.xml";
					CSVtoXML(file, fileName);
				}
				else {
					cout << endl << "Invalid file type. Please try again." << endl << endl;
					cin.ignore(1000, '\n');
				}
			}
			break;
			case 4:
				cout << "Quitting XML Parser" << endl;
				break;
			default:
				break;
		}

	}

	return 0;

}

void FillInformation() {

	ofstream xmlFile;
	xmlFile.open("xmlFile.xml");

	xmlFile << "<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>" << endl;
	xmlFile << "<games>" << endl;

	ofstream csvFile;
	csvFile.open("csvFile.csv");

	csvFile << "Game name, Genre, Platform, Release date, Developer" << endl;

	string xmlLine, game, genre, platform, releaseDate, developer;
	string csvLine = "";

	int index = 0;

	for (int i = 0; i < 5; i++) {

		cout << "Input the game's name: ";
		getline(cin, game);
		cin.clear();

		cout << "Input the game's genre: ";
		getline(cin, genre);
		cin.clear();

		cout << "Input the game's platform: ";
		getline(cin, platform);
		cin.clear();

		cout << "Input the game's release date: ";
		getline(cin, releaseDate);
		cin.clear();

		cout << "Input the game's developer: ";
		getline(cin, developer);
		cin.clear();

		GenerateXML(xmlFile, game, genre, platform, releaseDate, developer);
		GenerateCSV(csvFile, game, genre, platform, releaseDate, developer);

	}

	xmlFile << "<\/games>";
	xmlFile.close();
	csvFile.close();

}

void GenerateXML(ofstream &xmlFile, string game, string genre, string platform, string releaseDate, string developer) {

	xmlFile << "\t<game>\n\t\t<name>" << game << "<\/name>" << endl;
	xmlFile << "\t\t<genre>" << genre << "<\/genre>" << endl;
	xmlFile << "\t\t<platform>" << platform << "<\/platform>" << endl;
	xmlFile << "\t\t<releaseDate>" << releaseDate << "<\/releaseDate>" << endl;
	xmlFile << "\t\t<developer>" << developer << "<\/developer>" << endl;
	xmlFile << "\t<\/game>" << endl;

}

void GenerateCSV(ofstream &csvFile, string game, string genre, string platform, string releaseDate, string developer) {

	csvFile << "\"" << game << "\", \"" << genre << "\", \"" << platform << "\", \"" << releaseDate << "\", \"" << developer << "\"" << endl;

}

void XMLtoCSV(string source, string dest) {

	ifstream sourceFile;
	sourceFile.open(source);

	string line = "";

	if (sourceFile) {

		cout << endl << "Generating " << dest << endl << endl;

		ofstream csvFile;
		csvFile.open(dest);
		csvFile << "Game name, Genre, Platform, Release date, Developer" << endl;

		while (getline(sourceFile, line)) {

			if (line.find("<name>") != -1) {

				int startIndex = line.find("<name>") + 4 + 2;

				string final = line.substr(startIndex, line.length());
				int symbol = final.find_first_of('<');
				if (symbol != -1) {
					final = final.substr(0, final.find_first_of('<'));
				}
				csvFile << "\"" << final << "\", ";

			}
			else if (line.find("<genre>") != -1) {

				int startIndex = line.find("<genre>") + 5 + 2;

				string final = line.substr(startIndex, line.length());
				int symbol = final.find_first_of('<');
				if (symbol != -1) {
					final = final.substr(0, final.find_first_of('<'));
				}
				csvFile << "\"" << final << "\", ";

			}
			else if (line.find("<platform>") != -1) {

				int startIndex = line.find("<platform>") + 8 + 2;

				string final = line.substr(startIndex, line.length());
				int symbol = final.find_first_of('<');
				if (symbol != -1) {
					final = final.substr(0, final.find_first_of('<'));
				}
				csvFile << "\"" << final << "\", ";

			}
			else if (line.find("<releaseDate>") != -1) {

				int startIndex = line.find("<releaseDate>") + 11 + 2;

				string final = line.substr(startIndex, line.length());
				int symbol = final.find_first_of('<');
				if (symbol != -1) {
					final = final.substr(0, final.find_first_of('<'));
				}
				csvFile << "\"" << final << "\", ";

			}
			else if (line.find("<developer>") != -1) {

				int startIndex = line.find("<developer>") + 9 + 2;

				string final = line.substr(startIndex, line.length());
				int symbol = final.find_first_of('<');
				if (symbol != -1) {
					final = final.substr(0, final.find_first_of('<'));
				}
				csvFile << "\"" << final << "\"";

			}
			else if (line.find("<\/game>") != -1) {

				csvFile << endl;

			}

		}

		cout << "Parsing of " + source + " to " + dest + " 100% successful!";

	}
	else {

		cout << "File could not be found. Perhaps try again?";

	}

	cin.ignore(1000, '\n');

}

void CSVtoXML(string source, string dest) {

	ofstream xmlFile;
	xmlFile.open(dest);

}