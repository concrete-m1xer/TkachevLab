#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Pipe {
	int id;
	int diametr;
	double length;
	bool repair;
};

struct CompressorStation {
	int id;
	string name;
	int shopsCount;
	int workingShopsCount;
	float efficiency;
};

Pipe AddPipe() {
	Pipe p;
	do {
		cin.clear();
		cin.ignore(10000, '\n');
 		cout << "Type id: ";
		cin >> p.id;
	} while (cin.fail());
	do {
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "Type diametr: ";
		cin >> p.diametr;
	} while (cin.fail());
	do {
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "Type length: ";
		cin >> p.length;
	} while (cin.fail());
	p.repair = false;
	cout << endl;
	return p;
}

CompressorStation AddCS() {
	CompressorStation CS;
	do { cin.clear(); 
		cin.ignore(10000, '\n'); 
		cout << "Type Compressor Station's id: "; 
		cin >> CS.id; 
	} while (cin.fail());
	do { cin.clear();
		cin.ignore(10000, '\n');
		cout << "Type Compressor Station's name: "; 
		cin >> CS.name; 
	} while (cin.fail());
	do { cin.clear();
		cin.ignore(10000, '\n');
		cout << "Type Compressor Station's count of shops: "; cin >> CS.shopsCount;
	} while (cin.fail());
	do {
		cin.clear();
		cin.ignore(10000, '\n'); 
		cout << "Type Compressor Station's count of working shops (less than total number!): "; 
		cin >> CS.workingShopsCount; 
	} while (cin.fail() || CS.workingShopsCount > CS.shopsCount);
	CS.efficiency = (static_cast<double>(CS.workingShopsCount)/CS.shopsCount);
	cout << endl;
	return CS;
}

void PrintPipe(const Pipe& p) {
	cout << "It is the pipe's data" << endl;
	cout << "id: " << p.id << endl;
	cout << "diametr: " << p.diametr << endl;
	cout << "length: " << p.length << endl;
	if (p.repair) {
		cout << "The pipe is needs repiar" << endl;
	}
	else {
		cout << "The pipe doesn't need repair" << endl;
	}
	cout << endl;
}

void PrintCS(const CompressorStation& CS) {
	cout << "It is the compressor station's data" << endl;
	cout << "id: " << CS.id << endl;
	cout << "name: " << CS.name << endl;
	cout << "Shops (total): " << CS.shopsCount << endl;
	cout << "Shops (online): " << CS.workingShopsCount << endl;
	cout << "Efficieny (online/total): " << CS.efficiency << endl;
	cout << endl;
}

void EditPipe(Pipe& p) {
	p.repair = !p.repair;
}

void EditCS(CompressorStation& CS) {
	string s;
	cout << "do you want add[1] or remove[0] working shops?" << endl;
	cin >> s;
	if (s == "1") {
		if (CS.workingShopsCount < CS.shopsCount) {
			CS.workingShopsCount += 1;
		}
		else {
			cout << "can't get more working shops" << endl;
		}
		cout << "Shops (online): " << CS.workingShopsCount << endl;
	}
	else if (s == "0") {
		if (CS.workingShopsCount > 0) {
			CS.workingShopsCount -= 1;
		}
		else {
			cout << "can't get less working shops" << endl;
		}
		cout << "Shops (online): " << CS.workingShopsCount << endl;
	}
	else {
		cout << "input error" << endl;
		cout << "Shops (online): " << CS.workingShopsCount << endl;
	}
}

void SaveData(const Pipe& p, const CompressorStation& cs) {
	ofstream fout;
	fout.open("data.txt", ios::out);
	if (fout.is_open()) {
		fout << p.id << endl << p.diametr << endl << p.length << endl;
		if (p.repair) {
			fout << "broken" << endl;
		}
		else {
			fout << "fixed" << endl;
		}
		fout << cs.id << endl << cs.name << endl << cs.shopsCount << cs.workingShopsCount << endl << cs.workingShopsCount << endl
			<< cs.efficiency << endl;
		fout.close();
	}
}

Pipe LoadData() {
	ifstream fin;
	fin.open("data.txt", ios::in);
	Pipe p;
	CompressorStation cs;
	if (fin.is_open()) {
		fin >> p.id;
		fin >> p.diametr;
		fin >> p.length;
		string s;
		fin >> s;
		if (s == "broken") {
			p.repair = true;
		}
		else if (s == "fixed"){
			p.repair = false;
		}
		else {
			p.repair = false;
			cout << "Attention, due to file error, this pipe will be considered as fixed!" << endl;
		}
		fin >> cs.id;
		fin >> cs.name;
		fin >> cs.shopsCount;
		fin >> cs.workingShopsCount;
		fin >> cs.efficiency;
		fin.close();
		return p;
	}
}

int main() {
	bool isRunning = true;
	while (isRunning) {
		cout << "Choose an action: " << endl << "1 - Add Pipe" << endl << "2 - Add Compretion Station" << endl
			<< "3 - View all objects" << endl << "4 - Edit Pipe" << endl << "5 - Edit Compretion Station" << endl <<
			"6 - Save to file" << endl << "7 - Load from file" << endl << "0 - Exit from Programm" << endl;
		int s;
		do {
			cin >> s;
		} while (cin.fail());
		Pipe P;
		CompressorStation CS;
		switch (s)
		{
		case 1:
			P = AddPipe();
			break;
		case 2:
			CS = AddCS();
			break;
		case 3:
			PrintCS(CS);
			PrintPipe(P);
			break;
		case 4:
			EditPipe(P);
			break;
		case 5:
			EditCS(CS);
			break;
		case 6:
			SaveData(P, CS);
			break;
		case 7:
			P = LoadData();
			break;
		case 0: 
			isRunning = false;
			break;
		default:
			cout << "This command does not exist" << endl;
			break;
		}

	}
	return 0;
}