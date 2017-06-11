#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

void FillInformation();
void ProcessFileLine(ofstream &, ofstream &, string, string, string, string, string);
void XMLtoCSV(string, string);
void CSVtoXML(string, string);
void GenerateDefaults();

int CharCount(string, char);
int FindNthChar(string, char, int);
void Replace(string&, char, char);

int main() {

	int choice = -1;

	while (choice != 5) {

		system("cls");
		cout << "Welcome to the XML parser\n1. Input information and genrate both XML and CSV files\n2. Convert XML to CSV\n3. Convert CSV to XML\n4. Generate default XML and CSV files\n5. Quit\nOption: ";
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
			{
				GenerateDefaults();
			}
			break;
			case 5:
			default:
				cout << "Quitting XML Parser" << endl;
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

	bool fillingInformation = true;

	do {

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

		ProcessFileLine(xmlFile, csvFile, game, genre, platform, releaseDate, developer);

		while (true) {

			char choice = '\0';
			cout << "\nInput another game? (y/n)> ";
			cin >> choice;
			if (choice == 'Y' || choice == 'y') {
				break;
			}
			else {
				if (choice == 'N' || choice == 'n') {
					fillingInformation = false;
					xmlFile << "</games>";
					break;
				}
				else {
					continue;
				}
			}

		}

	} while (fillingInformation);

	xmlFile.close();
	csvFile.close();

	cout << endl << "Successfully generated \"xmlFile.xml\" and \"csvFile.csv\" files!";

	cin.ignore(1000, '\n');

}

void ProcessFileLine(ofstream &xmlFile, ofstream &csvFile, string game, string genre, string platform, string releaseDate, string developer) {

	xmlFile << "\t<game>" << endl;
	xmlFile << "\t\t<title>" << game << "</title>" << endl;
	xmlFile << "\t\t<genre>" << genre << "</genre>" << endl;
	xmlFile << "\t\t<platform>" << platform << "</platform>" << endl;
	xmlFile << "\t\t<releaseDate>" << releaseDate << "</releaseDate>" << endl;
	xmlFile << "\t\t<developer>" << developer << "</developer>" << endl;
	xmlFile << "\t</game>" << endl;

	// Replace commas for spaces
	Replace(game, ',', ' ');
	Replace(genre, ',', ' ');
	Replace(platform, ',', ' ');
	Replace(releaseDate, ',', ' ');
	Replace(developer, ',', ' ');

	csvFile << game << ", " << genre << ", " << platform << ", " << releaseDate << ", " << developer << endl;

}
 
void GenerateDefaults() {

	cout << endl << "Generating default files" << endl;

	ofstream xmlFile;
	xmlFile.open("xmlFileDefault.xml");

	xmlFile << "<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>" << endl;
	xmlFile << "<games>" << endl;
	
	ofstream csvFile;
	csvFile.open("csvFileDefault.csv");

	csvFile << "Game name, Genre, Platform, Release date, Developer" << endl;

	ProcessFileLine(xmlFile, csvFile, "Donkey Kong Country", "Action, Adventure, Platform", "SNES", "11/21/1994", "Rare");
	ProcessFileLine(xmlFile, csvFile, "Fallout: New Vegas", "Action, Role Playing, Shooter", "PC", "19/10/2010", "Obsidian Entertainment");
	ProcessFileLine(xmlFile, csvFile, "Diablo III", "Adventure, Role Playing", "PC", "15/05/2012", "Blizzard Entertainment");
	ProcessFileLine(xmlFile, csvFile, "Dead Island", "Shooter", "PC", "09/09/2011", "Techland");
	ProcessFileLine(xmlFile, csvFile, "Saints Row: The Third", "Action, Sandbox, Shooter", "PC", "01/11/2011", "Volition");

	xmlFile << "</games>";

	cout << "Success! Press enter to continue> " << endl;

	cin.clear();
	cin.ignore(1000, '\n');

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

		int lineIndex = 0;

		while (getline(sourceFile, line)) {

			if ((CharCount(line, '<') == 2) && (CharCount(line, '>') == 2)) {

				int entryPoint = line.find_first_of('<');
				int lastEntryPoint = line.find_last_of('>');

				// Find the second '>' to begin counting the name e.g
				// <example>name</example>
				// Would begin counting from >name
				int nameBegin = FindNthChar(line, '>', 1) + 1;

				string final = line.substr(nameBegin, line.length());

				int symbol = final.find_first_of('<');
				if (symbol != -1) {
					final = final.substr(0, final.find_first_of('<'));
				}

				Replace(final, ',', ' ');

				if (lineIndex < 4) {
					csvFile << final << ", ";
				}
				else {
					csvFile << final << endl;
					lineIndex = 0;
				}

				lineIndex++;

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

	ifstream sourceFile;
	sourceFile.open(source);

	string line = "";

	if (sourceFile) {

		// Skip the first line since it's the header
		getline(sourceFile, line);

		cout << endl << "Generating " << dest << endl << endl;

		ofstream xmlFile;
		xmlFile.open(dest);

		xmlFile << "<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>" << endl;
		xmlFile << "<games>" << endl;

		while (getline(sourceFile, line)) {

			cout << "Line to read: " << line << endl;

			xmlFile << "\t<game>" << endl;

			for (int i = 0; i < 5; i++) {

				int endPoint = FindNthChar(line, ',', 1);

				string text = line.substr(0, endPoint);

				if (i >= 4) {
					text = line;
				}

				switch (i) {
					case 0:
					{
						xmlFile << "\t\t<title>" << text << "</title>" << endl;
					}
					break;
					case 1:
					{
						xmlFile << "\t\t<genre>" << text << "</genre>" << endl;
					}
					break;
					case 2:
					{
						xmlFile << "\t\t<platform>" << text << "</platform>" << endl;
					}
					break;
					case 3:
					{
						xmlFile << "\t\t<releaseDate>" << text << "</releaseDate>" << endl;
					}
					break;
					case 4:
					default:
					{
						xmlFile << "\t\t<developer>" << text << "</developer>" << endl;
					}
					break;
				}

				cout << "Resulting string: " << text << endl;

				// Trail the comma and the space
				int remainingComma = FindNthChar(line, ',', 1) + 2;
				line = line.substr(remainingComma, line.length());

			} // for loop

			xmlFile << "\t</game>" << endl;

		} // while

		xmlFile << "</games>";

		cout << "Parsing of " + source + " to " + dest + " 100% successful!";

	}
	else {

		cout << "File could not be found. Perhaps try again?";

	}

	cin.ignore(1000, '\n');

}

int CharCount(string s, char c) {

	int index = 0;

	for (unsigned int i = 0; i < s.length(); i++) {

		if (s[i] == c) {
			index++;
		}

	}

	return index;

}

int FindNthChar(string s, char c, int n) {

	int index = 0;

	if (n == 0) {
		n = 1;
	}

	for (unsigned int i = 0; i < s.length(); i++) {

		if (s[i] == c) {
			index++;
			if (index == n) {
				return i;
			}
		}

	}

	return 0;

}

void Replace(string& s, char src, char dst) {

	replace(s.begin(), s.end(), src, dst);

}