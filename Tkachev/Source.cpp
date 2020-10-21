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

// вывод на консоль через поток
ostream& operator << (ostream& out, const Pipe& pipe)
{
	out << "It is the pipe's data" << endl;
	out << "id: " << pipe.id << endl;
	out << "diametr: " << pipe.diameter << endl;
	out << "length: " << pipe.length << endl;
	if (pipe.repair)
	{
		out << "The pipe needs repair" << endl;
	}
	else
	{
		out << "The pipe doesn't need repair" << endl;
	}
	out << endl;
	return out;
}

ostream& operator << (ostream& out, const CompressorStation& CS)
{
	out << "It is the compressor station's data" << endl;
	out << "id: " << CS.id << endl;
	out << "name: " << CS.name << endl;
	out << "Shops (total): " << CS.shopsCount << endl;
	out << "Shops (online): " << CS.workingShopsCount << endl;
	out << "Efficieny (online/total): " << CS.efficiency << endl;
	out << endl;
	return out;
}

// Проверка правильности ввода  
template <typename T>
void tryInput( T& a, string alert) 
{
		cin.clear();
		cin.ignore(10000, '\n');
		cout << alert;
		cin >> a;
}

// Создание объектов (оставил как функцию, так как не смог передавать id как аргумент для потока)
Pipe AddPipe(int i) 
{
	Pipe pipe;
	pipe.id = i;
	do 
	{
		tryInput(pipe.diameter ,"Type pipe's diametr: ");
	} while (cin.fail() || pipe.diameter < 0);
	do 
	{
		tryInput(pipe.length, "Type pipe's length: ");
	} while (cin.fail() || pipe.length < 0);
	pipe.repair = false;
	cout << endl;
	return pipe;
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

// Изменение трубы
void EditPipe(Pipe& pipe) 
{
	pipe.repair = !pipe.repair;
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
void SaveData(const vector <Pipe>& vecPipe, const vector <CompressorStation>& vecCS) 
{
	ofstream fout;
	fout.open("data.txt", ios::out);
	if (fout.is_open()) 
	{
		fout << vecPipe.size() << endl;
		fout << vecCS.size() << endl;
		for (int i = 0; i < vecPipe.size(); i++) 
		{
			fout << endl << vecPipe[i].id << endl << vecPipe[i].diameter << endl << vecPipe[i].length << endl;
			if (vecPipe[i].repair) 
			{
				fout << "broken" << endl;
			}
			else 
			{
				fout << "fixed" << endl;
			}
		}
		for (int i = 0; i < vecCS.size(); i++) 
		{
			fout << endl << vecCS[i].id << endl << vecCS[i].name << endl << vecCS[i].shopsCount
				<< endl << vecCS[i].workingShopsCount << endl << vecCS[i].efficiency << endl;
		}
	}
	fout.close();
	cout << "Data saved " << endl;
}

// Загрузка данных из файла
void LoadData(vector <Pipe>& vecPipe, vector <CompressorStation>& vecCS) 
{
	ifstream fin;
	fin.open("data.txt", ios::in);
	if (fin.is_open()) 
	{
		int a, b;
		fin >> a;
		fin >> b;
		vecPipe.resize(a);
		vecCS.resize(b);
		for (int i = 0; i < vecPipe.size(); i++) 
		{
			fin >> vecPipe[i].id;
			fin >> vecPipe[i].diameter;
			fin >> vecPipe[i].length;
			string s;
			fin >> s;
			if (s == "broken") 
			{
				vecPipe[i].repair = true;
			}
			else 
			{
				vecPipe[i].repair = false;
			}
		}
		for (int i = 0; i < vecCS.size(); i++) 
		{
			fin >> vecCS[i].id;
			fin >> vecCS[i].name;
			fin >> vecCS[i].shopsCount;
			fin >> vecCS[i].workingShopsCount;
			fin >> vecCS[i].efficiency;
		}
		cout << "Data loaded" << endl;
	}
}

// проверка существоавния данного id и получение индекса элемента с этим id
template <typename T>
bool findId(const T& vec, int id, int& a) 
{
	for (int i = 0; i < vec.size(); i++) 
	{
		if (vec[i].id == id) 
		{
			a = i;
			return true;
		}
	}
	return false;
}

template <typename T>
bool findId(const T& vec, int id)
{
	for (int i = 0; i < vec.size(); i++)
	{
		if (vec[i].id == id)
		{
			return true;
		}
	}
	return false;
}

// Удаление объектов
template <typename T>
void deleteObj(T& vec, int a) {
	vec.erase(vec.begin() + a);// riptutorial.com/ru/cplusplus/example/2156/ удаление-элементов - удаляет выбранный элемент вектора и сдвигает все, что были справа
}

// Вывод предупреждения о необходимости создать объекты
void notExist() {
	cout << endl << "At first, add pipe or station \n" << endl;
}

// создание массива всех сломанных или рабочих труб (можно сразу вывод сделать, но так можно и изменять трубы пакетом)
// vector <Pipe> getRepaired (const vector <Pipe>& vecPipe, bool workability)
//{
//	vector <Pipe> vecPipe1;
//	if (workability)
//	{
//		for (int i = 0; i < vecPipe.size(); i++)
//		{
//			if (!vecPipe[i].repair)
//			{
//				vecPipe1.push_back(vecPipe[i]);
//			}
//		}
//	}
//	else
//	{
//		for (int i = 0; i < vecPipe.size(); i++)
//		{
//			if (vecPipe[i].repair)
//			{
//				vecPipe1.push_back(vecPipe[i]);
//			}
//		}
//	}
//	return vecPipe1; 
//} 
//
//// создание массива кс отфильтрованных по эффективности
// vector <CompressorStation> getEffective (const vector <CompressorStation>& vecCS, double efficiency, bool over)
// {
//	 vector <CompressorStation> vecCS1;
//	 if (over)
//	 {
//		 for (int i = 0; i < vecCS.size(); i++)
//		 {
//			 if (vecCS[i].efficiency >= efficiency)
//			 {
//				 vecCS1.push_back(vecCS[i]);
//			 }
//		 }
//	 }
//	 else
//	 {
//		 for (int i = 0; i < vecCS.size(); i++)
//		 {
//			 if (vecCS[i].efficiency < efficiency)
//			 {
//				 vecCS1.push_back(vecCS[i]);
//			 }
//		 }
//	 }
//	 return vecCS1;
// }

// работа далее

 void printMenu()
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
 //		 << "12 - View/Edit all working/broken pipes \n"
 //		 << "13 - Sort compretion stations and show sorted \n"
		 << "0 - Exit from Program" << endl;
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
		printMenu();
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
				while (findId(vecPipe, idp)) 
				{
					idp++;
				}
				vecPipe.push_back(AddPipe(idp));
			}
			break;
		case 2:
			{
				while (findId(vecCS, idc)) 
				{
					idc++;
				}
				vecCS.push_back(AddCS(idc));
			}
			break;
		case 3:
			{
				if (vecPipe.size() != 0 || vecCS.size() != 0)
				{
					for (Pipe& p : vecPipe)
					{
						cout << p;
					}
					for (CompressorStation& cs : vecCS)
					{
						cout << cs;
					}
				}
				else
				{
					notExist();
				}
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
				cout << vecPipe[a];
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
				cout << vecCS[a];
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
				cout << vecPipe[a];
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
				cout << vecCS[a];
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
/*		case 12:

			break;*/
/*		case 13:

			break;*/
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