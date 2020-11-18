#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include "CPipe.h"
#include "CCompressorStation.h"
#include "assistance.h"

using namespace std;

// вся работа с словарями взята с сайтов: www.cyberforum.ru/cpp-beginners/thread1745799.html  
//cppstudio.com/post/9535/      codelessons.ru/cplusplus/map-v-c-chto-eto-i-kak-s-etim-rabotat.html   www.cplusplus.com/reference/map/map/

// Сохранение данных в файл
void SaveData(const unordered_map <int, CPipe>& mapPipe, const unordered_map <int, CCompressorStation>& mapCS)
{
	ofstream fout;
	cout << "Enter filename, please: ";
	string filename;
	cin >> filename;
	fout.open(filename+".txt", ios::out);
	if (fout.is_open()) 
	{
		fout << mapPipe.size() << endl;
		fout << mapCS.size() << endl;
		for (const auto& itp : mapPipe)
		{
			fout << itp.second;
		}
		for (const auto& itc : mapCS) 
		{
			fout << itc.second;
		}
	cout << "Data saved \n" << endl;
	}
	fout.close();
}

// Загрузка данных из файла
template <typename T>
void LoadData(unordered_map <int, T>& myMap, int mapSize, ifstream& fin)
{
	vector <int> idVec;
	idVec.reserve(myMap.size());
	for (const auto& it : myMap)
	{
		idVec.push_back(it.first);
	} 
	for (int i : idVec)
	{
		myMap.erase(i);
	} // из логики того, что всё несохранённые данные удаляются
	while(mapSize--)
	{
		T val(fin);
		myMap.insert(pair<int, T>(val.getId(), val));
	}
}

template <typename C, typename T>
 using filter = bool(*) (const C& p, T param, bool bParam);

 bool checkRepair(const CPipe& p, bool workable, bool bParam = true)
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
 vector <int> findAllByFilter(const unordered_map <int, C>& myMap, filter<C, T> f, T param, bool bParam = true)
 {
	 vector <int> res;
	 res.reserve(myMap.size());
	 for (const auto& p : myMap)
	 {
		 if (f(p.second, param, bParam))
		 {
			 res.push_back(p.first);
		 }
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
	unordered_map <int, CPipe> mapPipe;
	unordered_map <int, CCompressorStation> mapCS;
	while (isRunning) 
	{
		printMenu();
		int menu;
		menu = tryInput("", 0);
		switch (menu)
		{
		case 1:
			{
				//mapPipe[CPipe::maxId+1] = CPipe();
				mapPipe.insert(pair<int, CPipe>(CPipe::maxId + 1, CPipe()));
			}
			break;
		case 2:
			{
				mapCS.insert(pair<int, CCompressorStation>(CCompressorStation::maxId + 1, CCompressorStation()));
			}
			break;
		case 3:
			{
				if (mapPipe.size() != 0 || mapCS.size() != 0)
				{
					for (const pair<const int, CPipe>& p : mapPipe)
					{
						cout << p.second;
					}
					for (const pair<const int, CCompressorStation>& p : mapCS)
					{
						cout << p.second;
					}
				}
				else
				{
					cout << endl << "At first, add pipe or station \n" << endl;
				}
			}
			break;
		case 4:
			if (mapPipe.size() != 0) 
			{
				int id = tryInput("Please, enter correct id of pipe you want to edit: ", 1, findMaxId(mapPipe));
				unordered_map<int, CPipe>::iterator it = mapPipe.find(id);
				if (it != mapPipe.end())
				{
					it->second.editPipe();
					cout << it->second;
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
			if (mapCS.size() != 0) 
			{
				int id = tryInput("Please, enter correct id of compressor station you want to edit: ", 1, findMaxId(mapCS));
				unordered_map <int, CCompressorStation>::iterator it = mapCS.find(id);
				if (it != mapCS.end())
				{
					cout << it->second;
					it->second.editCS();
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
			if (mapPipe.size() != 0 || mapCS.size() != 0) 
			{
				SaveData(mapPipe, mapCS);
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
					LoadData(mapPipe, sizePipe, fin);
					LoadData(mapCS, sizeCS, fin);
					cout << "Data successfully loaded \n " << endl;
				}
				fin.close();
				CPipe::maxId = findMaxId(mapPipe);
				CCompressorStation::maxId = findMaxId(mapCS);
			}
			break;
		case 8: 
			if (mapPipe.size() != 0)
			{
				int id = tryInput("Please, enter correct id of pipe you want to see: ", 1, findMaxId(mapPipe));
				unordered_map <int, CPipe>::iterator it = mapPipe.find(id);
				if (it != mapPipe.end())
				{
					cout << it->second;
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
			if (mapCS.size() != 0) 
			{
				int id;
				id = tryInput( "Please, enter correct id of compressor station you want to see: ", 1, findMaxId(mapCS));
				unordered_map <int, CCompressorStation>::iterator it = mapCS.find(id);
				if (it != mapCS.end())
				{
					cout << it->second;
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
			if (mapPipe.size() != 0) 
			{
				int id = tryInput("Enter correct id of pipe you want to delete, please: ", 1, findMaxId(mapPipe));
				if (mapPipe.find(id) != mapPipe.end())
				{
					deleteObj(mapPipe, id);
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
			if (mapCS.size() != 0) 
			{
				int id = tryInput("Enter correct id of conpressor station you want to delete, please: ", 1, findMaxId(mapCS));
				if (mapCS.find(id) != mapCS.end())
				{
					deleteObj(mapCS, id);
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
			if (mapPipe.size() != 0)
			{
				bool workable = tryInput<bool>("You want to find all workable[1] or send for repair[0]? ", 0, 1);
				for (int& i : findAllByFilter(mapPipe, checkRepair, workable))
				{
					cout << mapPipe[i];
				}
			}
			else
			{
				cout << endl << "At first, add pipe \n" << endl;
			}
			break;
		case 13:
			if (mapPipe.size() != 0)
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
					for (int& i : findAllByFilter(mapPipe, checkRepair, false))
					{
						mapPipe[i].editPipe();
						cout << mapPipe[i];
					}
					break;
				case 2:
					for (int& i : findAllByFilter(mapPipe, checkRepair, true))
					{
						mapPipe[i].editPipe();
						cout << mapPipe[i];
					}
					break;
				case 3:
					for (pair<const int, CPipe>& p : mapPipe)
					{
						p.second.editPipe();
					}
					break;
				case 4:
				{
					vector <int> vecId = inputVecId(mapPipe);
					for (int& i : vecId)
					{
						mapPipe[i].editPipe();
						cout << mapPipe[i];
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
			if (mapCS.size() != 0)
			{
				int pick = tryInput("You want to find all compressor station by name[0], by persentage of occupaton[1] or by efficiency[2]? ", 0, 2);
				switch (pick)
				{
				case 0:
					{
						cout << "Please, enter name you want to find: ";
						string name;
						cin >> name;
						for (int& i : findAllByFilter(mapCS, checkName, name))
						{
							cout << mapCS[i];
						}
					}
					break;
				case 1:
					{
						double percent = tryInput("Please, enter percentage of occupation: ", 0.0, 100.0);
						bool sort = tryInput<bool>("You want to filter compressor stations with occupation percentage larger[1] or smaller[0] than entered : ", 0, 1);
						for (int& i : findAllByFilter(mapCS, percentOfWorkingShops, percent, sort))
						{
							cout << mapCS[i];
						}
					}
					break;
				case 2: 
					{
						double efficiency = tryInput("Please enter efficiency: ", 0.0, 1000.0);
						bool sort = tryInput<bool>("You want to filter compressor stations with efficiency larger[1] or smaller[0] than entered : ", 0, 1);
						for (int& i : findAllByFilter(mapCS, Efficiency, efficiency, sort))
						{
							cout << mapCS[i];
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
			if (mapCS.size() != 0)
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
					for (int& i : findAllByFilter(mapCS, checkName, name))
					{
						cout << mapCS[i];
						mapCS[i].editCS();
					}
				}
					break;
				case 2:
				{
					double efficiency = tryInput("Please enter efficiency: ", 0.0, 1000.0);
					bool sort = tryInput<bool>("You want to edit compressor stations with efficiency larger[1] or smaller[0] than entered : ", 0, 1);
					for (int& i : findAllByFilter(mapCS, Efficiency, efficiency, sort))
					{
						cout << mapCS[i];
						mapCS[i].editCS();
					}
				}
					break;
				case 3:
				{
					double percent = tryInput("Please, enter percentage of occupation: ", 0.0, 100.0);
					bool sort = tryInput<bool>("You want to filter compressor stations with occupation percentage larger[1] or smaller[0] than entered : ", 0, 1);
					for (int& i : findAllByFilter(mapCS, percentOfWorkingShops, percent, sort))
					{
						cout << mapCS[i];
						mapCS[i].editCS();
					}
				}
					break;
				case 4:
				{
					vector <int> vecId = inputVecId(mapCS);
					for (int& i : vecId)
					{
						cout << mapCS[i];
						mapCS[i].editCS();
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