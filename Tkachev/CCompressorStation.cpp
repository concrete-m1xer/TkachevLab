#include "CCompressorStation.h"

CCompressorStation::CCompressorStation(int id)
{
	std::cout << "-------------------------CCompressorStation(int id)-------------------------------" << std::endl;
	this->id = id;
	std::cout << "Type Compressor Station's name: ";
	std::cin >> this->name;
	this->shopsCount = tryInput("Type Compressor Station's count of shops: ", 0);
	this->workingShopsCount = tryInput("Type Compressor Station's count of working shops (less/equal than total!): ", 0, shopsCount);
	this->efficiency = tryInput("Type Compressor Station's efficiency (0 - 1000): ", 0, 1000);
}

CCompressorStation::CCompressorStation()
{
	std::cout << "-------------------------CCompressorStation()-------------------------------" << std::endl;
}

CCompressorStation::CCompressorStation(const CCompressorStation& cs)
{
	std::cout << "-------------------------CCompressorStation(const CCompressorStation& cs)-------------------------------" << std::endl;
	id = cs.id;
	name = cs.name;
	shopsCount = cs.shopsCount;
	workingShopsCount = cs.workingShopsCount;
	efficiency = cs.efficiency;
}

int CCompressorStation::getId() const
{
	return id;
}

std::string CCompressorStation::getName() const
{
	return name;
}

int CCompressorStation::getShopsCount() const
{
	return shopsCount;
}

int CCompressorStation::getWorkingShopsCount() const
{
	return workingShopsCount;
}

double CCompressorStation::getEfficiency() const
{
	return efficiency;
}

//сетторы
//void CCompressorStation::setId(int newId)
//{
//	id = newId;
//}
//
//void CCompressorStation::setName(std::string newName)
//{
//	name = newName;
//}
//
//void CCompressorStation::setShopsCount(int newShopsCount)
//{
//	shopsCount = newShopsCount;
//}
//
//void CCompressorStation::setWorkingShopsCount(int newWorkingShopsCount)
//{
//	workingShopsCount = newWorkingShopsCount;
//}
//
//void CCompressorStation::setEfficiency(double newEfficiency)
//{
//	efficiency = newEfficiency;
//}


std::ostream& operator << (std::ostream& out, const CCompressorStation& CS)
{
	out << "It is the compressor station's data" << std::endl;
	out << "id: " << CS.id << std::endl;
	out << "name: " << CS.name << std::endl;
	out << "Shops (total): " << CS.shopsCount << std::endl;
	out << "Shops (online): " << CS.workingShopsCount << std::endl;
	out << "Efficieny: " << CS.efficiency << std::endl;
	out << std::endl;
	return out;
}

std::ofstream& operator << (std::ofstream& fout, const CCompressorStation& CS)
{
	fout << std::endl << CS.id << std::endl << CS.name << std::endl << CS.shopsCount
		<< std::endl << CS.workingShopsCount << std::endl << CS.efficiency << std::endl;
	return fout;
}

std::ifstream& operator >> (std::ifstream& fin, CCompressorStation& CS)
{
	fin >> CS.id;
	fin >> CS.name;
	fin >> CS.shopsCount;
	fin >> CS.workingShopsCount;
	fin >> CS.efficiency;
	return fin;
}

void CCompressorStation::editCS()
{
	int menu;
	menu = tryInput("do you want run[1] or stop[0] or run/stop several[2] working shops? ", 0, 2);
	switch (menu)
	{
	case 1:
		if (workingShopsCount < shopsCount)
		{
			++workingShopsCount;
		}
		else
		{
			std::cout << "can't get more working shops " << std::endl;
		}
		break;
	case 0:
		if (workingShopsCount > 0)
		{
			--workingShopsCount;
		}
		else
		{
			std::cout << "can't get less working shops " << std::endl;
		}
		break;
	case 2:
		workingShopsCount = tryInput("Enter number of shops you want to be online (less/equal than total!) ", 0, shopsCount);
		break;
	default:
		std::cout << "This action unacceptable " << std::endl;
	}
}