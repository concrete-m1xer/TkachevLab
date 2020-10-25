#include "CPipe.h"

CPipe::CPipe(int id)
{
	std::cout << "------------------------CPipe(int id)----------------------------" << std::endl;
	this->id = id;
	this->diameter = tryInput("Type pipe's diametr: ", 0);
	this->length = tryInput("Type pipe's length: ", 0.0);
	this->repair = false;
}

CPipe::CPipe()
{
	std::cout << "------------------------CPipe()----------------------------" << std::endl;
}

CPipe::CPipe(const CPipe& pipe)
{
	std::cout << "------------------------CPipe(const CPipe& pipe)----------------------------" << std::endl;
	id = pipe.id;
	diameter = pipe.diameter;
	length = pipe.length;
	repair = pipe.repair;
}

// экспериментальный конструктор с потоком в качестве параметра. работает. интересно. ничего более.
//CPipe::CPipe(std::ifstream& in)
//{
//	std::cout << "------------------------CPipe(std::ifstream& in)----------------------------" << std::endl;
//	in >> this->id;
//	in >> this->diameter;
//	in >> this->length;
//	in >> this->repair;
//}

int CPipe::getId() const
{
	return id;
}

int CPipe::getDiameter() const
{
	return diameter;
}

double CPipe::getLength() const
{
	return length;
}

bool CPipe::getRepair() const
{
	return repair;
}

//void CPipe::setId(int newId)
//{
//	id = newId;
//}
//
//void CPipe::setDiameter(int newDiameter)
//{
//	diameter = newDiameter;
//}
//
//void CPipe::setLength(double newLength)
//{
//	length = newLength;
//}
//
//void CPipe::setRepair(bool newRepair)
//{
//	repair = newRepair;
//}

void CPipe::editPipe()
{
	repair = !repair;
}

//в консоль
std::ostream& operator << (std::ostream& out, const CPipe& pipe)
{
	out << "It is the pipe's data" << std::endl;
	out << "id: " << pipe.id << std::endl;
	out << "diametr: " << pipe.diameter << std::endl;
	out << "length: " << pipe.length << std::endl;
	if (pipe.repair)
	{
		out << "The pipe needs repair" << std::endl;
	}
	else
	{
		out << "The pipe doesn't need repair" << std::endl;
	}
	out << std::endl;
	return out;
}

// в/из файл(а)
std::ifstream& operator >> (std::ifstream& fin, CPipe& pipe)
{
	fin >> pipe.id;
	fin >> pipe.diameter;
	fin >> pipe.length;
	fin >> pipe.repair;
	return fin;
}

std::ofstream& operator << (std::ofstream& fout, const CPipe& pipe)
{
	fout << std::endl << pipe.id << std::endl << pipe.diameter << std::endl << pipe.length << std::endl << pipe.repair << std::endl;
	return fout;
}