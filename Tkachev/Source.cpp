#include <iostream>
#include <fstream>
#include <string>
#include <vector>
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
	double efficiency;
};

void WrongInput() {
	cin.clear();
	cin.ignore(10000, '\n');
}

Pipe AddPipe(int i) {
	Pipe p;
	p.id = i;
	do {
		WrongInput();
		cout << "Type pipe's diametr: ";
		cin >> p.diametr;
	} while (cin.fail() || p.diametr < 0);
	do {
		WrongInput();
		cout << "Type pipe's length: ";
		cin >> p.length;
	} while (cin.fail() || p.length < 0);
	p.repair = false;
	cout << endl;
	return p;
}

CompressorStation AddCS(int j) {
	CompressorStation CS;
	CS.id = j;
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
	CS.efficiency = CS.workingShopsCount * (1./CS.shopsCount); // можно использовать static_cast с сайта docs.microsoft.com
	cout << endl;
	return CS;
}

void PrintPipe(const Pipe& p) {
	cout << "It is the pipe's data" << endl;
	cout << "id: " << p.id << endl;
	cout << "diametr: " << p.diametr << endl;
	cout << "length: " << p.length << endl;
	if (p.repair) {
		cout << "The pipe is needs repair" << endl;
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
	CS.efficiency = CS.workingShopsCount * (1. / CS.shopsCount);
}

void SaveData(const vector <Pipe>& c, const vector <CompressorStation>& c1) {
	ofstream fout;
	fout.open("data.txt", ios::out); //cyberforum "at end of file"
	if (fout.is_open()) {
		for (unsigned int i = 0; i < c.size() - 1; i++) { //в предупреждении предложил сделать i unsigned
			fout << c[i].id << endl << c[i].diametr << endl << c[i].length << endl;
			if (c[i].repair) {
				fout << "broken" << endl;
			}
			else {
				fout << "fixed" << endl;
			}
			fout << '\n';
		}for (unsigned int i = 0; i < c1.size() - 1; i++) {
			fout << c1[i].id << endl << c1[i].name << endl << c1[i].shopsCount
				<< endl << c1[i].workingShopsCount << endl << c1[i].efficiency << endl;
			fout << '\n';
		}
	}
	fout.close();
}

void LoadData(Pipe& p, CompressorStation& cs) {
	ifstream fin;
	fin.open("data.txt", ios::in);
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
  //!!!

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
	cout << "At first, add pipe or station " << endl;
}

int main() {
	bool isRunning = true;
	unsigned int i, j;
	i = 0;
	j = 0;
	vector <Pipe> vecPipe;
	vector <CompressorStation> vecCS;
	vecPipe.resize(1);
	vecCS.resize(1);
	while (isRunning) {
		vecPipe[i].id = -1;
		vecCS[j].id = -1;
		cout << "Choose an action, please: \n" 
			<< "1 - Add Pipe \n" 
			<< "2 - Add Compretion Station \n"
			<< "3 - View all objects \n" 
			<< "4 - Edit Pipe \n" 
			<< "5 - Edit Compretion Station \n" 
			<< "6 - Save to file \n" 
			<< "7 - Load from file \n" 
			<< "0 - Exit from Programm" << endl;
		int s;
		do {
			cin >> s;
		} while (cin.fail());
		switch (s)
		{
		case 1:
			vecPipe[i] = AddPipe(i+1);
			i++;
			vecPipe.resize(i+1);
			break;
		case 2:
			vecCS[j] = AddCS(j+1);
			j++;
			vecCS.resize(j+1);
			break;
		case 3:
			if (isDefined(vecPipe[0]) || isDefined(vecCS[0])) {
				for (int a = 0; a < i; a++) {
					PrintPipe(vecPipe[a]);
				}
				for (int a = 0; a < j; a++) {
					PrintCS(vecCS[a]); 
				}
			}
			else {
				NotDefined();
			}
			break;
		case 4:
			if (isDefined(vecPipe[0])) {
				int a;
				do {
					cout << "Please, enter correct number of pipe you want to edit" << endl;
					WrongInput();
					cin >> a;
				} while (cin.fail() || a > i || a <= 0);
				if (isDefined(vecPipe[a - 1])) {
					EditPipe(vecPipe[a - 1]);
				}
			}
			else {
				NotDefined();
			}
			break;
		case 5:
			if (isDefined(vecCS[0])) {
				int a;
				do {
					cout << "Please, enter correct number of Compressor Station you want to edit" << endl;
					WrongInput();
					cin >> a;
				} while (cin.fail() || a > j || a < 0);
				if (isDefined(vecCS[a - 1])) {
					EditCS(vecCS[a - 1]);
				}
			}
			else {
				NotDefined();
			}
			break;
		case 6:
			if (isDefined(vecPipe[0]) || isDefined(vecCS[0])) {
				SaveData(vecPipe, vecCS);
			}
			else {
				NotDefined();
			}
			break;
		case 7:
			//LoadData(P, CS);
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