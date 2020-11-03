#include "CPipe.h"

int CPipe::maxId = 0;

CPipe::CPipe(int id)
{
	this->id = id;
	this->diameter = tryInput("Type pipe's diametr: ", 0);
	this->length = tryInput("Type pipe's length: ", 0.0);
	this->repair = false;
}

CPipe::CPipe()
{
}

//CPipe::CPipe(const CPipe& pipe)
//{
//	id = pipe.id;
//	diameter = pipe.diameter;
//	length = pipe.length;
//	repair = pipe.repair;
//}

CPipe::CPipe(std::ifstream& in)
{
	in >> this->id;
	in >> this->diameter;
	in >> this->length;
	in >> this->repair;
}

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

void CPipe::editPipe()
{
	repair = !repair;
}