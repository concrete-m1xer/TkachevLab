#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "CPipe.h"
#include "CCompressorStation.h"
#include "assistance.h"

using namespace std;

// Сохранение данных в файл
void SaveData(const vector <CPipe>& vecPipe, const vector <CCompressorStation>& vecCS) 
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

// Загрузка данных из файла
template <typename T>
void LoadData(vector <T>& vec, int vecSize, ifstream& fin) 
{
	vec.resize(0); // исходя из того, что при загрузке откуда-либо удаляются все несохранённые данные 
	vec.reserve(vecSize);
	while(vecSize--)
	{
		T c;
		fin >> c;
		vec.push_back(c);
//		vec.push_back(CPipe(fin));
	}
}

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
		 << "12 - View/Edit all working/broken pipes \n"
 //		 << "13 - Sort compretion stations and show sorted \n"
		 << "0 - Exit from Program" << endl;
 }

 //поломок вроде не осталось
 //как лучше резервировать
 //стоит ли делать отдельную функцию для 


int main() 
{
	bool isRunning = true;
	int idp, idc;
	idp = 1;
	idc = 1;
	vector <CPipe> vecPipe;
	vector <CCompressorStation> vecCS;
	while (isRunning) 
	{
		printMenu();
		int menu;
		menu = tryInput("", 0);
		switch (menu)
		{
		case 1:
			{
				vecPipe.push_back(CPipe(findMaxId(vecPipe)+1));
			}
			break;
		case 2:
			{
				vecCS.reserve(vecCS.capacity() + 1);
				vecCS.push_back(CCompressorStation(findMaxId(vecCS)+1));
			}
			break;
		case 3:
			{
				if (vecPipe.size() != 0 || vecCS.size() != 0)
				{
					for (CPipe& p : vecPipe)
					{
						cout << p;
					}
					for (CCompressorStation& cs : vecCS)
					{
						cout << cs;
					}
				}
				else
				{
					cout << endl << "At first, add pipe or station \n" << endl;
				}
			}
			break;
		case 4:
			if (vecPipe.size() != 0) 
			{
				int id;
				id = tryInput("Please, enter correct id of pipe you want to edit: ", 1, findMaxId(vecPipe));
				if (getIndexById(vecPipe, id) != -1)
				{
					vecPipe[getIndexById(vecPipe, id)].editPipe();
					cout << vecPipe[getIndexById(vecPipe, id)];
				}
				else
				{
					cout << "This id does not exist" << endl;
				}
			}
			else 
			{
				cout << endl << "At first, add pipe or station \n" << endl;
			}
			break;
		case 5: 
			if (vecCS.size() != 0) 
			{
				int id;
				id = tryInput("Please, enter correct id of compressor station you want to edit: ", 1, findMaxId(vecCS));
				if (getIndexById(vecPipe, id) != -1)
				{
					cout << vecCS[getIndexById(vecCS, id)];
					vecCS[getIndexById(vecCS, id)].editCS();
				}
				else
				{
					cout << "This id does not exist" << endl;
				}
			}
			else 
			{
				cout << endl << "At first, add pipe or station \n" << endl;
			}
			break;
		case 6:
			if (vecPipe.size() != 0 || vecCS.size() != 0) 
			{
				SaveData(vecPipe, vecCS);
			}
			else 
			{
				cout << endl << "At first, add pipe or station \n" << endl;
			}
			break;
		case 7:
			{
				ifstream fin;
				fin.open("data.txt", ios::in);
				if (fin.is_open())
				{
					int sizePipe, sizeCS;
					fin >> sizePipe;
					fin >> sizeCS;
					LoadData(vecPipe, sizePipe, fin);
					LoadData(vecCS, sizeCS, fin);
					cout << "Data successfully loaded " << endl;
				}
				fin.close();
			}
			break;
		case 8: 
			if (vecPipe.size() != 0)
			{
				int id;
				id = tryInput("Please, enter correct id of pipe you want to see: ", 1, findMaxId(vecPipe));
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
				cout << endl << "At first, add pipe or station \n" << endl;
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
				cout << endl << "At first, add pipe or station \n" << endl;
			}
			break;
		case 10:
			if (vecPipe.size() != 0) 
			{
				int id;
				id = tryInput("Enter correct id of pipe you want to delete, please: ", 1, findMaxId(vecPipe));
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
				cout << endl << "At first, add pipe or station \n" << endl;
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
				cout << endl << "At first, add pipe or station \n" << endl;
			}
			break;
		case 12:
			if (vecPipe.size() != 0)
			{
				int pick = tryInput("Would you like to see all broken[1] or all workable[2] pipes? ", 1, 2);
				switch (pick)
				{
				case 1:
					for (CPipe& p : vecPipe)
					{
						if (p.getRepair())
						{
							cout << p;
						}
					}
					break;
				case 2:
					for (CPipe& p : vecPipe)
					{
						if (!p.getRepair())
						{
							cout << p;
						}
					}
					break;
				default:
					cout << "This action is unacceptable" << endl;
					break;
				}
			}
			else
			{
				cout << endl << "At first, add pipe or station \n" << endl;
			}
				break;
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