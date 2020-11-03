#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "CPipe.h"
#include "CCompressorStation.h"
#include "assistance.h"

using namespace std;

// ���������� ������ � ����
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
	}
	fout.close();
	cout << "Data saved \n" << endl;
}

// �������� ������ �� �����
template <typename T>
void LoadData(vector <T>& vec, int vecSize, ifstream& fin) 
{
	vec.resize(0); // ������ �� ����, ��� ��� �������� ������-���� ��������� ��� ������������� ������ 
	vec.reserve(vecSize);
	while(vecSize--)
	{
		T c;
		fin >> c;
		vec.push_back(c);
//		vec.push_back(CPipe(fin));
	}
}

 //��� ����� �������������

template <typename T>
 using filterPipe = bool(*) (const CPipe& p, T param);

 bool checkRepair(const CPipe& p, bool workable)
 {
	 if (workable)
	 {
		 return !p.getRepair();
	 } 
	 else
	 {
		return p.getRepair();
	 }
 }

 template <typename T>
 vector <int> findAllPipeIndexByFilter(const vector <CPipe>& vec, filterPipe<T> f, T param)
 {
	 vector <int> res;
	 res.reserve(vec.size());
	 int i = 0;
	 for (auto& elem : vec)
	 {
		 if (f(elem, param))
		 {
			 res.push_back(i);
		 }
		 i++;
	 }
	 return res;
 }

 template <typename T>
 using filterCS = bool(*) (const CCompressorStation& cs, T param);

 bool checkName(const CCompressorStation& cs, string name)
 {
	 return cs.getName() == name;
 }

 bool largerEfficiency(const CCompressorStation& cs, double efficiency)
 {
	 return cs.getEfficiency() >= efficiency;
 }
 
 bool smallerEfficiency(const CCompressorStation& cs, double efficiency)
 {
	 return cs.getEfficiency() < efficiency;
 }

 template <typename T>
 vector <int> findAllCSIndexByFilter(const vector <CCompressorStation>& vec, filterCS<T> f, T param)
 {
	 vector <int> res;
	 res.reserve(vec.size());
	 int i = 0;
	 for (auto& elem : vec)
	 {
		 if (f(elem, param))
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
				vecPipe.push_back(CPipe(++CPipe::maxId));
			}
			break;
		case 2:
			{
				vecCS.push_back(CCompressorStation(++CCompressorStation::maxId));
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
				bool workable;
				int a;
				a = tryInput("You want to find all workable[1] or send for repair[0]? ", 0, 1);
				a > 0 ? workable = true : workable = false;
				for (int& i : findAllPipeIndexByFilter(vecPipe, checkRepair, workable))
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
					for (int& i : findAllPipeIndexByFilter(vecPipe, checkRepair, false))
					{
						vecPipe[i].editPipe();
						cout << vecPipe[i];
					}
					break;
				case 2:
					for (int& i : findAllPipeIndexByFilter(vecPipe, checkRepair, true))
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
				int pick = tryInput("You want to find all compressor station by name[1] or by efficiency[0]? ", 0, 1);
				if (pick > 0)
				{
					cout << "Please, enter name you want to find: ";
					string name;
					cin >> name;
					for (int& i : findAllCSIndexByFilter(vecCS, checkName, name))
					{
						cout << vecCS[i];
					}
				}
				else
				{
					double efficiency = tryInput("Please enter efficiency: ", 0, 1000);
					int sort = tryInput("You want to filter compressor station with efficiency larger[1] or smaller[0] than entered : ", 0, 1);
					if (sort > 0)
					{
						for (int& i : findAllCSIndexByFilter(vecCS, largerEfficiency, efficiency))
						{
							cout << vecCS[i];
						}
					}
					else
					{
						for (int& i : findAllCSIndexByFilter(vecCS, smallerEfficiency, efficiency))
						{
							cout << vecCS[i];
						}
					}
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
					<< "2 - Edit all compressor stations with efficiency larger than entered \n"
					<< "3 - Edit all compressor stations with efficiency smaller than entered \n"
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
					for (int& i : findAllCSIndexByFilter(vecCS, checkName, name))
					{
						cout << vecCS[i];
						vecCS[i].editCS();
					}
				}
					break;
				case 2:
				{
					double efficiency = tryInput("Please, enter lower bound of efficiency: ", 0, 1000);
					for (int& i : findAllCSIndexByFilter(vecCS, largerEfficiency, efficiency))
					{
						cout << vecCS[i];
						vecCS[i].editCS();
					}
				}
					break;
				case 3:
				{
					double efficiency = tryInput("Please, enter upper bound of efficiency: ", 0, 1000);
					for (int& i : findAllCSIndexByFilter(vecCS, smallerEfficiency, efficiency))
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