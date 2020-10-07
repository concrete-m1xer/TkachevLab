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
	return CS;
}

void PrintPipe(const Pipe& p) {
	cout << "Here's the pipe that you have required" << endl;
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
	cout << "It is compressor station that you have required" << endl;
	cout << "id: " << CS.id << endl;
	cout << "name: " << CS.name << endl;
	cout << "Shops (total): " << CS.shopsCount << endl;
	cout << "Shops (online)" << CS.workingShopsCount << endl;
	cout << "Efficieny: " << CS.efficiency << endl;
}

void EditPipe(Pipe& p) {
	p.repair = !p.repair;
}

void SavePipe(const Pipe& p) {
	ofstream fout;
	fout.open("data.txt", ios::out);
	if (fout.is_open()) {
		fout << p.id << endl << p.diametr << endl << p.length << endl;
		if (p.repair) {
			fout << "broken";
		}
		else {
			fout << "fixed" << endl;
		}
		fout.close();
	}
}

Pipe LoadPipe() {
	ifstream fin;
	fin.open("data.txt", ios::in);
	Pipe p;
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
		fin.close();
		return p;
	}
}

int main() {
	Pipe P1 = AddPipe();
	PrintPipe(P1);
	CompressorStation CS1 = AddCS();
	PrintCS(CS1);
	//EditPipe(P1);
	//PrintPipe(P1);
	//SavePipe(P1);
	//Pipe P2 = LoadPipe();
	//PrintPipe(P2);
	return 0;
}