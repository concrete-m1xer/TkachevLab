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
	cout << "Enter filename, please: ";
	string filename;
	cin >> filename;
	fout.open(filename+".txt", ios::out);
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
	cout << "Data saved \n" << endl;
	}
	fout.close();
}

// Загрузка данных из файла
template <typename T>
void LoadData(vector <T>& vec, int vecSize, ifstream& fin) 
{
	vec.resize(0); // исходя из того, что при загрузке откуда-либо удаляются все несохранённые данные 
	vec.reserve(vecSize);
	while(vecSize--)
	{
		//T c;
		//fin >> c;
		//vec.push_back(c);
		vec.push_back(T(fin));
	}
}

template <typename C, typename T>
 using filter = bool(*) (const C& p, T param, bool bParam);

 bool checkRepair(const CPipe& p, bool workable, bool bParam)
 {
	 return (workable && !p.getRepair()) || (!workable && p.getRepair());
 }
 
 bool checkName(const CCompressorStation& cs, string name, bool bParam) // bParam если нужно вывести КС с именем отличным от введённого
 {
	 return cs.getName() == name && bParam || cs.getName() != name && !bParam;
 }

 bool Efficiency(const CCompressorStation& cs, double efficiency, bool isMore)
 {
	 return cs.getEfficiency() >= efficiency && isMore || (cs.getEfficiency() < efficiency) && !isMore;
 }

 bool percentOfWorkingShops(const CCompressorStation& cs, double percent, bool isMore)
 {
	 return cs.getOccupancyPercentage() >= percent && isMore || (cs.getOccupancyPercentage() < percent) && !isMore;
 }

 template <typename C, typename T>
 vector <int> findAllIndexByFilter(const vector <C>& vec, filter<C, T> f, T param, bool bParam = true)
 {
	 vector <int> res;
	 res.reserve(vec.size());
	 int i = 0;
	 for (auto& elem : vec)
	 {
		 if (f(elem, param, bParam))
		 {
			 res.push_back(i);
		 }
		 i++;
	 }
	 return res;
 }

 void printMenu()
 {
	 std::cout << "Choose an action, please: \n"
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
		 << "12 - Find required pipes \n"
		 << "13 - Batch editing of pipes \n"
		 << "14 - Find required compretion stations \n"
		 << "15 - Batch editing of compretion stations \n"
		 << "0 - Exit from Program" << std::endl;
 }

int main() 
{
	bool isRunning = true;
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
				vecPipe.push_back(CPipe());
			}
			break;
		case 2:
			{
				vecCS.push_back(CCompressorStation());
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
				cout << endl << "At first, add station \n" << endl;
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
				cout << "Please, enter filename: ";
				string filename;
				cin >> filename;
				fin.open(filename+".txt", ios::in);
				if (fin.is_open())
				{
					int sizePipe, sizeCS;
					fin >> sizePipe;
					fin >> sizeCS;
					LoadData(vecPipe, sizePipe, fin);
					LoadData(vecCS, sizeCS, fin);
					cout << "Data successfully loaded \n " << endl;
				}
				fin.close();
				CPipe::maxId = findMaxId(vecPipe);
				CCompressorStation::maxId = findMaxId(vecCS);
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
				cout << endl << "At first, add pipe \n" << endl;
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
				cout << endl << "At first, add station \n" << endl;
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
				cout << endl << "At first, add pipe \n" << endl;
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
				cout << endl << "At first, add station \n" << endl;
			}
			break;
		case 12:
			if (vecPipe.size() != 0)
			{
				bool workable = tryInput<bool>("You want to find all workable[1] or send for repair[0]? ", 0, 1);
				for (int& i : findAllIndexByFilter(vecPipe, checkRepair, workable))
				{
					cout << vecPipe[i];
				}
			}
			else
			{
				cout << endl << "At first, add pipe \n" << endl;
			}
			break;
		case 13:
			if (vecPipe.size() != 0)
			{
				cout << "Choose correct action: \n"
					 << "1 - Edit all broken pipes \n"
					 << "2 - Edit all workable pipes \n"
					 << "3 - Edit all pipes \n"
					 << "4 - Edit several pipes with entered id \n"
					 << "0 - Leave this menu "
					 <<endl;
				int sort = tryInput("", 0);
				switch (sort)
				{
				case 0:
					break;
				case 1:
					for (int& i : findAllIndexByFilter(vecPipe, checkRepair, false))
					{
						vecPipe[i].editPipe();
						cout << vecPipe[i];
					}
					break;
				case 2:
					for (int& i : findAllIndexByFilter(vecPipe, checkRepair, true))
					{
						vecPipe[i].editPipe();
						cout << vecPipe[i];
					}
					break;
				case 3:
					for (CPipe& p : vecPipe)
					{
						p.editPipe();
					}
					break;
				case 4:
				{
					vector <int> vecIndex;
					bool input = true;
					while (input)
					{
						int id = tryInput("Please, enter correct id of next pipe you want to edit or enter [0] to stop input: ", 0);
						if (id != 0)
						{
							if (getIndexById(vecPipe, id) != -1)
							{
								vecIndex.push_back(getIndexById(vecPipe, id));
							}
							else
							{
								cout << "Could not find this id" << endl;
							}
						}
						else
						{
							input = false;
						}
					}
					for (int& i : vecIndex)
					{
						vecPipe[i].editPipe();
						cout << vecPipe[i];
					}
				}
					break;
				default:
					cout << "This action is unacceptable \n" << endl;
					break;
				}
			}
			else
			{
				cout << endl << "At first, add pipe \n" << endl;
			}
			break;
		case 14:
			if (vecCS.size() != 0)
			{
				int pick = tryInput("You want to find all compressor station by name[0], by persentage of occupaton[1] or by efficiency[2]? ", 0, 2);
				switch (pick)
				{
				case 0:
					{
						cout << "Please, enter name you want to find: ";
						string name;
						cin >> name;
						for (int& i : findAllIndexByFilter(vecCS, checkName, name))
						{
							cout << vecCS[i];
						}
					}
					break;
				case 1:
					{
						double percent = tryInput("Please, enter percentage of occupation: ", 0.0, 100.0);
						bool sort = tryInput<bool>("You want to filter compressor stations with occupation percentage larger[1] or smaller[0] than entered : ", 0, 1);
						for (int& i : findAllIndexByFilter(vecCS, percentOfWorkingShops, percent, sort))
						{
							cout << vecCS[i];
						}
					}
					break;
				case 2: 
					{
						double efficiency = tryInput("Please enter efficiency: ", 0.0, 1000.0);
						bool sort = tryInput<bool>("You want to filter compressor stations with efficiency larger[1] or smaller[0] than entered : ", 0, 1);
						for (int& i : findAllIndexByFilter(vecCS, Efficiency, efficiency, sort))
						{
							cout << vecCS[i];
						}
					}
					break;
				default:
					cout << "This action unacceptable. " << endl;
					break;
				}
			}
			else
			{
				cout << endl << "At first, add station \n" << endl;
			}
			break;
		case 15:
			if (vecCS.size() != 0)
			{
				cout << "Choose correct action: \n"
					<< "1 - Edit compressor stations sorted by name \n"
					<< "2 - Edit all compressor stations sorted by efficiency \n"
					<< "3 - Edit all compressor stations sorted by percentage of occupation \n"
					<< "4 - Edit several pipes with entered id \n"
					<< "0 - Leave this menu "
					<< endl;
				int sort = tryInput("", 0);
				switch (sort)
				{
				case 0:
					break;
				case 1:
				{
					cout << "Please, enter correct name of stations you want to edit: ";
					string name;
					cin >> name;
					for (int& i : findAllIndexByFilter(vecCS, checkName, name))
					{
						cout << vecCS[i];
						vecCS[i].editCS();
					}
				}
					break;
				case 2:
				{
					double efficiency = tryInput("Please enter efficiency: ", 0.0, 1000.0);
					bool sort = tryInput<bool>("You want to edit compressor stations with efficiency larger[1] or smaller[0] than entered : ", 0, 1);
					for (int& i : findAllIndexByFilter(vecCS, Efficiency, efficiency, sort))
					{
						cout << vecCS[i];
						vecCS[i].editCS();
					}
				}
					break;
				case 3:
				{
					double percent = tryInput("Please, enter percentage of occupation: ", 0.0, 100.0);
					bool sort = tryInput<bool>("You want to filter compressor stations with occupation percentage larger[1] or smaller[0] than entered : ", 0, 1);
					for (int& i : findAllIndexByFilter(vecCS, percentOfWorkingShops, percent, sort))
					{
						cout << vecCS[i];
						vecCS[i].editCS();
					}
				}
					break;
				case 4:
				{
					vector <int> vecIndex;
					bool input = true;
					while (input)
					{
						int id = tryInput("Please, enter correct id of next pipe you want to edit or enter [0] to stop input: ", 0);
						if (id != 0)
						{
							if (getIndexById(vecCS, id) != -1)
							{
								vecIndex.push_back(getIndexById(vecCS, id));
							}
							else
							{
								cout << "Could not find this id" << endl;
							}
						}
						else
						{
							input = false;
						}
					}
					for (int& i : vecIndex)
					{
						cout << vecCS[i];
						vecCS[i].editCS();
					}
				}
				break;
				default:
					cout << "This action is unacceptable \n" << endl;
					break;
				}
			}
			else
			{
				cout << endl << "At first, add station \n" << endl;
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