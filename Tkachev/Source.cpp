#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

struct Pipe 
{
	int id;
	int diameter;
	double length;
	bool repair;
};

struct CompressorStation 
{
	int id;
	string name;
	int shopsCount;
	int workingShopsCount;
	double efficiency;
};

// Проверка правильности ввода  
void tryInput( int& a, string alert) 
{
		cin.clear();
		cin.ignore(10000, '\n');
		cout << alert;
		cin >> a;
}

void tryInput(double& a, string alert) 
{
		cin.clear();
		cin.ignore(10000, '\n');
		cout << alert;
		cin >> a;
}

// Создание объектов
Pipe AddPipe(int i) 
{
	Pipe p;
	p.id = i;
	do 
	{
		tryInput(p.diameter ,"Type pipe's diametr: ");
	} while (cin.fail() || p.diameter < 0);
	do 
	{
		tryInput(p.length, "Type pipe's length: ");
	} while (cin.fail() || p.length < 0);
	p.repair = false;
	cout << endl;
	return p;
}

CompressorStation AddCS(int j) 
{
	CompressorStation CS;
	CS.id = j;
	cout << "Type Compressor Station's name: "; 
	cin >> CS.name; 
	do 
	{
		tryInput(CS.shopsCount, "Type Compressor Station's count of shops: ");
	} while (cin.fail() || CS.shopsCount < 0);
	do 
	{
		tryInput(CS.workingShopsCount, "Type Compressor Station's count of working shops (less/equal than total!): ");
	} while (cin.fail() || CS.workingShopsCount > CS.shopsCount || CS.workingShopsCount < 0);
	CS.efficiency = CS.workingShopsCount * (1./CS.shopsCount); // можно использовать static_cast с сайта docs.microsoft.com
	cout << endl;
	return CS;
}

// Вывод в консоль
void PrintPipe(const Pipe& p) 
{
	cout << "It is the pipe's data" << endl;
	cout << "id: " << p.id << endl;
	cout << "diametr: " << p.diameter << endl;
	cout << "length: " << p.length << endl;
	if (p.repair) 
	{
		cout << "The pipe needs repair" << endl;
	}
	else 
	{
		cout << "The pipe doesn't need repair" << endl;
	}
	cout << endl;
}

void PrintCS(const CompressorStation& CS) 
{
	cout << "It is the compressor station's data" << endl;
	cout << "id: " << CS.id << endl;
	cout << "name: " << CS.name << endl;
	cout << "Shops (total): " << CS.shopsCount << endl;
	cout << "Shops (online): " << CS.workingShopsCount << endl;
	cout << "Efficieny (online/total): " << CS.efficiency << endl;
	cout << endl;
}

// Изменение трубы
void EditPipe(Pipe& p) 
{
	p.repair = !p.repair;
}

// Изменение компрессорной станции
void EditCS(CompressorStation& CS) 
{
	int s;
	do 
	{
		tryInput(s, "do you want add[1] or remove[0] or add/remove several[2] working shops? ");
	} while (cin.fail());
	switch (s)
	{
	case 1:
		if (CS.workingShopsCount < CS.shopsCount) 
		{
			CS.workingShopsCount += 1;
		}
		else 
		{
			cout << "can't get more working shops " << endl;
		}
		break;
	case 0:
		if (CS.workingShopsCount > 0) 
		{
			CS.workingShopsCount -= 1;
		}
		else 
		{
			cout << "can't get less working shops " << endl;
		}
		break;
	case 2:
		do 
		{
			tryInput(CS.workingShopsCount, "Enter number of shops you want to be online (less/equal than total!): ");
		} while (cin.fail() || CS.workingShopsCount > CS.shopsCount || CS.workingShopsCount < 0);
		break;
	default:
		cout << "This action unacceptable " << endl;
	}
	CS.efficiency = CS.workingShopsCount * (1. / CS.shopsCount);
}

// Сохранение данных в файл
void SaveData(const vector <Pipe>& c, const vector <CompressorStation>& c1) 
{
	ofstream fout;
	fout.open("data.txt", ios::out);
	if (fout.is_open()) 
	{
		fout << c.size() << endl;
		fout << c1.size() << endl;
		for (int i = 0; i < c.size(); i++) 
		{
			fout << endl << c[i].id << endl << c[i].diameter << endl << c[i].length;
			if (c[i].repair) 
			{
				fout << "broken" << endl;
			}
			else 
			{
				fout << "fixed" << endl;
			}
			fout << '\n';
		}
		for (int i = 0; i < c1.size(); i++) 
		{
			fout << endl << c1[i].id << endl << c1[i].name << endl << c1[i].shopsCount
				<< endl << c1[i].workingShopsCount << endl << c1[i].efficiency;
		}
	}
	fout.close();
}

// Загрузка данных из файла
void LoadData(vector <Pipe>& c, vector <CompressorStation>& c1) 
{
	ifstream fin;
	fin.open("data.txt", ios::in);
	if (fin.is_open()) 
	{
		int a, b;
		fin >> a;
		fin >> b;
		c.resize(a);
		c1.resize(b);
		for (int i = 0; i < c.size(); i++) 
		{
			fin >> c[i].id;
			fin >> c[i].diameter;
			fin >> c[i].length;
			string s;
			fin >> s;
			if (s == "broken") 
			{
				c[i].repair = true;
			}
			else 
			{
				c[i].repair = false;
			}
		}
		for (int i = 0; i < c1.size(); i++) 
		{
			fin >> c1[i].id;
			fin >> c1[i].name;
			fin >> c1[i].shopsCount;
			fin >> c1[i].workingShopsCount;
			fin >> c1[i].efficiency;
		}
	}
}

// проверка существоавния данного id и получение элемента с этим id
bool findId(const vector<Pipe>& c, int id, int& a) 
{
	for (int i = 0; i < c.size(); i++) 
	{
		if (c[i].id == id) 
		{
			a = i;
			return true;
		}
	}
	return false;
}

bool findId(const vector<CompressorStation>& c, int id, int& a) 
{
	for (int i = 0; i < c.size(); i++) 
	{
		if (c[i].id == id) 
		{
			a = i;
			return true;
		}
	}
	return false;
}

// Удаление объектов
void deleteObj(vector<Pipe>& c, int a) {
	c.erase(c.begin() + a);// riptutorial.com/ru/cplusplus/example/2156/удаление-элементов
}

void deleteObj(vector<CompressorStation>& c, int a) {
	c.erase(c.begin() + a);// riptutorial.com/ru/cplusplus/example/2156/удаление-элементов
}

// Вывод предупреждения о необходимости создать объекты
void notExist() {
	cout << endl << "At first, add pipe or station \n" << endl;
}

int main() 
{
	bool isRunning = true;
	int idp, idc;
	idp = 1;
	idc = 1;
	vector <Pipe> vecPipe;
	vector <CompressorStation> vecCS;
	while (isRunning) 
	{
		cout << "Choose an action, please: \n" 
			<< "1 - Add pipe \n" 
			<< "2 - Add compretion station \n"
			<< "3 - View all objects \n" 
			<< "4 - Edit pipe \n" 
			<< "5 - Edit compretion station \n" 
			<< "6 - Save to file \n" 
			<< "7 - Load from file \n" 
			<< "8 - View one pipe \n"
			<< "9 - View one compretion station \n"
			<< "10 - Delete one pipe \n"
			<< "11 - Delete one compretion station \n"
			<< "0 - Exit from Programm" << endl;
		int menu;
		cin >> menu;
		while (cin.fail())
		{
			tryInput(menu, "");
		}
		switch (menu)
		{
		case 1:
			{
				int a;
				while (findId(vecPipe, idp, a)) 
				{
					idp++;
				}
				vecPipe.push_back(AddPipe(idp)); //www.cplusplus.com/reference/vector/vector/push_back/]   Добавляет в конец вектора элемент
			}
			break;
		case 2:
			{
				int a;
				while (findId(vecCS, idc, a)) 
				{
					idc++;
				}
				vecCS.push_back(AddCS(idc));
			}
			break;
		case 3:
			if (vecPipe.size() != 0 || vecCS.size() != 0) 
			{
				for (int a = 0; a < vecPipe.size(); a++) 
				{
					PrintPipe(vecPipe[a]);
				}
				for (int a = 0; a < vecCS.size(); a++) 
				{
					PrintCS(vecCS[a]); 
				}
			}
			else 
			{
				notExist();
			}
			break;
		case 4:
			if (vecPipe.size() != 0) 
			{
				int id, a;
				do 
				{
					tryInput(id, "Please, enter correct id of pipe you want to edit: ");
				} while (cin.fail() || !findId(vecPipe, id, a));
				EditPipe(vecPipe[a]);
			}
			else 
			{
				notExist();
			}
			break;
		case 5: 
			if (vecCS.size() != 0) 
			{
				int id, a;
				do 
				{
					tryInput(id , "Please, enter correct id of compressor station you want to edit: ");
				} while (cin.fail() || !findId(vecCS, id, a));
				EditCS(vecCS[a]);
			}
			else 
			{
				notExist();
			}
			break;
		case 6:
			if (vecPipe.size() != 0 || vecCS.size() != 0) 
			{
				SaveData(vecPipe, vecCS);
			}
			else 
			{
				notExist();
			}
			break;
		case 7:
			LoadData(vecPipe, vecCS);
			break;
		case 8: 
			if (vecPipe.size() != 0) 
			{
				int id, a;
				do 
				{
					tryInput(id, "Please, enter correct id of pipe you want to see: ");
				} while (cin.fail() || !findId(vecPipe, id, a));
				PrintPipe(vecPipe[a]);
			}
			else 
			{
				notExist();
			}
			break;
		case 9:
			if (vecCS.size() != 0) 
			{
				int id, a;
				do 
				{
					tryInput(id, "Please, enter correct id of compressor station you want to see: ");
				} while (cin.fail() || !findId(vecCS, id, a));
				PrintCS(vecCS[a]);
			}
			else 
			{
				notExist();
			}
			break;
		case 10:
			if (vecPipe.size() != 0) 
			{
				int id, a;
				do 
				{
					tryInput(id, "Enter correct id of pipe you want to delete, please: ");
				} while (cin.fail() || !findId(vecPipe, id, a));
				deleteObj(vecPipe, a);
//				i = a + 1;		id - индивидуален только для ныне живущих объектов?
			}
			else 
			{
				notExist();
			}
			break;
		case 11: 
			if (vecCS.size() != 0) 
			{
				int id, a;
				do 
				{
					tryInput(id, "Enter correct id of conpressor station you want to delete, please: ");
				} while (cin.fail() || !findId(vecCS, id, a));
				deleteObj(vecCS, a);
			}
			else 
			{
				notExist();
			}
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