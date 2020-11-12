#include "CCompressorStation.h"

int CCompressorStation::maxId = 0;

CCompressorStation::CCompressorStation()
{
	this->id = ++maxId;
	std::cout << "Type Compressor Station's name: ";
	std::cin >> this->name;
	this->shopsCount = tryInput("Type Compressor Station's count of shops: ", 0);
	this->workingShopsCount = tryInput("Type Compressor Station's count of working shops (less/equal than total!): ", 0, shopsCount);
	this->efficiency = tryInput("Type Compressor Station's efficiency (0 - 1000): ", 0, 1000);
}

//CCompressorStation::CCompressorStation()
//{
//}

CCompressorStation::CCompressorStation(std::ifstream& in)
{
	in >> this->id;
	in >> this->name;
	in >> this->shopsCount;
	in >> this->workingShopsCount;
	in >> this->efficiency;
}

//CCompressorStation::CCompressorStation(const CCompressorStation& cs)
//{
//	id = cs.id;
//	name = cs.name;
//	shopsCount = cs.shopsCount;
//	workingShopsCount = cs.workingShopsCount;
//	efficiency = cs.efficiency;
//}

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

double CCompressorStation::getOccupancyPercentage() const
{
	return workingShopsCount * (1.0 / shopsCount)*100;
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

std::istream& operator>>(std::istream& in, CCompressorStation& CS)
{
	CS.id = ++CCompressorStation::maxId;
	in >> CS.name;
	CS.shopsCount = tryInput("Please, enter count of shops: ", 1);
	CS.workingShopsCount = tryInput("Please, enter count of online shops: ", 1);
	CS.efficiency = tryInput("Please, enter efficiency: ", 1);
	return in;
}

void CCompressorStation::editCS()
{
	bool pick = tryInput<bool>("do you want run[1] or stop[0] working shops(0 - shops total)? ", 0, 1);
	if (pick && workingShopsCount < shopsCount)
	{
		++workingShopsCount;
	}
	if (!pick && workingShopsCount > 0)
	{
		--workingShopsCount;
	}
}

//void CCompressorStation::enhancedEditCS()
//{
//	workingShopsCount = tryInput("Enter number of shops you want to be online (less/equal than total!) ", 0, shopsCount);
//}