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

// ����� �� ������� ����� �����
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
	out << "Efficieny: " << CS.efficiency << endl;
	out << endl;
	return out;
}

// � ����
ifstream& operator >> (ifstream& fin, Pipe& pipe)
{
	fin >> pipe.id;
	fin >> pipe.diameter;
	fin >> pipe.length;
	fin >> pipe.repair;
	return fin;
}

ofstream& operator << (ofstream& fout, const Pipe& pipe)
{
	fout << endl << pipe.id << endl << pipe.diameter << endl << pipe.length << endl << pipe.repair << endl;
	return fout;
}

ifstream& operator >> (ifstream& fin, CompressorStation& CS)
{
	fin >> CS.id;
	fin >> CS.name;
	fin >> CS.shopsCount;
	fin >> CS.workingShopsCount;
	fin >> CS.efficiency;
	return fin;
}

ofstream& operator << (ofstream& fout, const CompressorStation& CS)
{
	fout << endl << CS.id << endl << CS.name << endl << CS.shopsCount
		<< endl << CS.workingShopsCount << endl << CS.efficiency << endl;
	return fout;
}


// �������� ������������ �����  
template <typename T>
T tryInput (string alert, T min, T max = 1000000) 
{
	T x;
	cout << alert;
	while ((cin >> x).fail() || x < min || x > max)
	{
		cin.clear();
		cin.ignore(10000, '\n');
		cout << alert;
	}
	return x;
}

// �������� �������� (������� ��� �������, ��� ��� �� ���� ���������� id ��� �������� ��� ������)
Pipe AddPipe(int i) 
{
	Pipe pipe;
	pipe.id = i;
	pipe.diameter = tryInput("Type pipe's diametr: ", 0);
	pipe.length= tryInput("Type pipe's length: ",0.0);
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
	CS.shopsCount = tryInput("Type Compressor Station's count of shops: ", 0);
	CS.workingShopsCount = tryInput("Type Compressor Station's count of working shops (less/equal than total!): ", 0, CS.shopsCount);
	CS.efficiency = tryInput( "Type Compressor Station's efficiency (0 - 1000): ", 0, 1000);
	cout << endl;
	return CS;
}

// ��������� �����
void EditPipe(Pipe& pipe) 
{
	pipe.repair = !pipe.repair;
}

// ��������� ������������� �������
void EditCS(CompressorStation& CS) 
{
	int menu;
	menu = tryInput("do you want run[1] or stop[0] or run/stop several[2] working shops? ", 0, 2);
	switch (menu)
	{
	case 1:
		if (CS.workingShopsCount < CS.shopsCount) 
		{
			++CS.workingShopsCount;
		}
		else 
		{
			cout << "can't get more working shops " << endl;
		}
		break;
	case 0:
		if (CS.workingShopsCount > 0) 
		{
			--CS.workingShopsCount;
		}
		else 
		{
			cout << "can't get less working shops " << endl;
		}
		break;
	case 2:
			CS.workingShopsCount = tryInput("Enter number of shops you want to be online (less/equal than total!) ", 0, CS.shopsCount);
		break;
	default:
		cout << "This action unacceptable " << endl;
	}
}

// ���������� ������ � ����
void SaveData(const vector <Pipe>& vecPipe, const vector <CompressorStation>& vecCS) 
{
	ofstream fout;
	fout.open("data.txt", ios::out);
	if (fout.is_open()) 
	{
		fout << vecPipe.size() << endl;
		fout << vecCS.size() << endl;
		for (auto& c : vecPipe)
		{
			fout << c;
		}
		for (auto& c : vecCS) 
		{
			fout << c;
		}
	}
	fout.close();
	cout << "Data saved " << endl;
}

// �������� ������ �� �����
void LoadData(vector <Pipe>& vecPipe, vector <CompressorStation>& vecCS) 
{
	ifstream fin;
	fin.open("data.txt", ios::in);
	if (fin.is_open()) 
	{
		int sizePipe, sizeCS;
		fin >> sizePipe;
		fin >> sizeCS;
		vecPipe.resize(sizePipe);
		vecCS.resize(sizeCS);
		for (Pipe& p : vecPipe)
		{
			fin >> p;
		}
		for (CompressorStation& cs : vecCS)
		{
			fin >> cs;
		}
		cout << "Data loaded" << endl;
	}
}

// �������� ������������� ������� id � ��������� ������� �������� � ���� id
template <typename T>
int getIndexById(const vector <T>& vec, int id)
{
	for (unsigned int i = 0; i < vec.size(); i++ ) // ������� ���, ��� �� ������� �������� ���������
	{
		if (vec[i].id == id) 
		{
			return i;
		}
	}
	return -1;
}

template <typename T>
// ���� ���� id ������ 1, �� ������� ������ 1, ���� ������ ������, �� 0
int findMaxId(const vector <T>& vec)
{
	int maxId = 0;
	for (auto& c : vec)
	{
		if (c.id > maxId)
		{
			maxId = c.id;
		}
	}
	return maxId;
}

// �������� ��������
template <typename T>
void deleteObj(vector <T>& vec, int i) {
	vec.erase(vec.begin() + i);// riptutorial.com/ru/cplusplus/example/2156/ ��������-��������� - ������� ��������� ������� ������� � �������� ���, ��� ���� ������
}

// ����� �������������� � ������������� ������� �������
void notExist() {
	cout << endl << "At first, add pipe or station \n" << endl;
}

// �������� ������� ���� ��������� ��� ������� ���� (����� ����� ����� �������, �� ��� ����� � �������� ����� �������)
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
//// �������� ������� �� ��������������� �� �������������
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

// ������ �����

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
		menu = tryInput("", 0);
		switch (menu)
		{
		case 1:
			{
				
				vecPipe.push_back(AddPipe(findMaxId(vecPipe)+1));
			}
			break;
		case 2:
			{
				vecCS.push_back(AddCS(findMaxId(vecCS)+1));
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
				int id;
				id = tryInput("Please, enter correct id of pipe you want to edit ", 1, findMaxId(vecPipe));
				if (getIndexById(vecPipe, id) != -1)
				{
					EditPipe(vecPipe[getIndexById(vecPipe, id)]);
					cout << vecPipe[getIndexById(vecPipe, id)];
				}
				else
				{
					cout << "This id does not exist" << endl;
				}
			}
			else 
			{
				notExist();
			}
			break;
		case 5: 
			if (vecCS.size() != 0) 
			{
				int id;
				id = tryInput("Please, enter correct id of compressor station you want to edit ", 1, findMaxId(vecCS));
				if (getIndexById(vecPipe, id) != -1)
				{
					cout << vecCS[getIndexById(vecCS, id)];
					EditCS(vecCS[getIndexById(vecCS, id)]);
				}
				else
				{
					cout << "This id does not exist" << endl;
				}
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
				int id;
				id = tryInput("Please, enter correct id of pipe you want to see ", 1, findMaxId(vecPipe));
				if (getIndexById(vecPipe, id) != -1)
				{
					cout << vecPipe[getIndexById(vecPipe, id)];
				}
				else
				{
					cout << "This id does not exist" << endl;
				}
			}
			else 
			{
				notExist();
			}
			break;
		case 9:
			if (vecCS.size() != 0) 
			{
				int id;
				id = tryInput( "Please, enter correct id of compressor station you want to see: ", 1, findMaxId(vecCS));
				if (getIndexById(vecCS, id) != -1)
				{
					cout << vecCS[getIndexById(vecCS, id)];
				}
				else
				{
					cout << "This id does not exist" << endl;
				}
			}
			else 
			{
				notExist();
			}
			break;
		case 10:
			if (vecPipe.size() != 0) 
			{
				int id;
				id = tryInput("Enter correct id of pipe you want to delete, please ", 1, findMaxId(vecPipe));
				if (getIndexById(vecPipe, id) != -1)
				{
					deleteObj(vecPipe, getIndexById(vecPipe, id));
				}
				else
				{
					cout << "This id does not exist" << endl;
				}
			}
			else 
			{
				notExist();
			}
			break;
		case 11: 
			if (vecCS.size() != 0) 
			{
				int id;
				id = tryInput("Enter correct id of conpressor station you want to delete, please: ", 1, findMaxId(vecCS));
				if (getIndexById(vecCS, id) != -1)
				{
					deleteObj(vecCS, getIndexById(vecCS, id));
				}
				else
				{
					cout << "This id does not exist" << endl;
				}
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