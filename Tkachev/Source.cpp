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

void WrongInput() {
	cin.clear();
	cin.ignore(10000, '\n');
}

Pipe AddPipe() {
	Pipe p;
	do {
		WrongInput();
 		cout << "Type id: ";
		cin >> p.id;
	} while (cin.fail() || p.id == -1);
	do {
		WrongInput();
		cout << "Type diametr: ";
		cin >> p.diametr;
	} while (cin.fail());
	do {
		WrongInput();
		cout << "Type length: ";
		cin >> p.length;
	} while (cin.fail());
	p.repair = false;
	cout << endl;
	return p;
}

CompressorStation AddCS() {
	CompressorStation CS;
	do {
		WrongInput();
		cout << "Type Compressor Station's id: "; 
		cin >> CS.id; 
	} while (cin.fail() || CS.id == -1);
	cout << "Type Compressor Station's name: "; 
	cin >> CS.name; 
	do {
		WrongInput();
		cout << "Type Compressor Station's count of shops: "; 
		cin >> CS.shopsCount;
	} while (cin.fail() || CS.shopsCount < 0);
	do {
		WrongInput();
		cout << "Type Compressor Station's count of working shops (less/equal than total!): "; 
		cin >> CS.workingShopsCount; 
	} while (cin.fail() || CS.workingShopsCount > CS.shopsCount || CS.workingShopsCount < 0);
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
	int s;
	cout << "do you want add[1] or remove[0] or add/remove several[2] working shops?" << endl;
	do {
		WrongInput();
		cin >> s;
	} while (cin.fail());
	switch (s)
	{
	case 1:
		if (CS.workingShopsCount < CS.shopsCount) {
			CS.workingShopsCount += 1;
		}
		else {
			cout << "can't get more working shops" << endl;
		}
		break;
	case 0:
		if (CS.workingShopsCount > 0) {
			CS.workingShopsCount -= 1;
		}
		else {
			cout << "can't get less working shops" << endl;
		}
		break;
	case 2:
		cout << "Enter number of shops you want to be online (less/equal than total!)" << endl;
		do {
			WrongInput();
			cin >> CS.workingShopsCount;
		} while (cin.fail() || CS.workingShopsCount > CS.shopsCount || CS.workingShopsCount < 0);
	default:
		cout << "This action unacceptable" << endl;
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
		fout << '\n';
		fout << cs.id << endl << cs.name << endl << cs.shopsCount << endl << cs.workingShopsCount << endl
			<< cs.efficiency << endl;
		fout.close();
	}
}

void LoadData(Pipe& p, CompressorStation& cs) {
	ifstream fin;
	fin.open("data.txt", ios::in);
	char s;
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
	}
}

bool isDefined(const Pipe& a) {
	if (a.id == -1) {
		return false;
	}
	else {
		return true;
	}
}

bool isDefined(const CompressorStation& a) {
	if (a.id == -1) {
		return false;
	}
	else { 
		return true;
	}
}

void NotDefined() {
	cout << "At first, add pipe and station " << endl;
}

int main() {
	bool isRunning = true;
	Pipe P;
	CompressorStation CS;
	P.id = -1;
	CS.id = -1;
	while (isRunning) {
		cout << "Choose an action: " << endl << "1 - Add Pipe" << endl << "2 - Add Compretion Station" << endl
			<< "3 - View all objects" << endl << "4 - Edit Pipe" << endl << "5 - Edit Compretion Station" << endl <<
			"6 - Save to file" << endl << "7 - Load from file" << endl << "0 - Exit from Programm" << endl;
		int s;
		do {
			cin >> s;
		} while (cin.fail());
		switch (s)
		{
		case 1:
			P = AddPipe();
			break;
		case 2:
			CS = AddCS();
			break;
		case 3:
			if (isDefined(P) && isDefined(CS)) {
				PrintPipe(P);
				PrintCS(CS);
			}
			else {
				NotDefined();
			}
			break;
		case 4:
			if (isDefined(P)) {
				EditPipe(P);
			}
			else {
				NotDefined();
			}
			break;
		case 5:
			if (isDefined(CS)) {
				EditCS(CS);
			}
			else {
				NotDefined();
			}
			break;
		case 6:
			if (isDefined(P)) {
				SaveData(P, CS);
			}
			else {
				NotDefined();
			}
			break;
		case 7:
			LoadData(P, CS);
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