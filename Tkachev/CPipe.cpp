#include "CPipe.h"

int CPipe::maxId = 0;

CPipe::CPipe()
{
	this->id = ++maxId;
	this->diameter = tryInput("Type pipe's diametr: ", 0);
	this->length = tryInput("Type pipe's length: ", 0.0);
	this->repair = false;
}

//CPipe::CPipe()
//{
//}

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

double CPipe::getPressureDropValue() const
{
	return length* 1.0/diameter;
}

double CPipe::getPerformance() const
{
	return diameter* 1.0/length;
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

//� �������
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

// �/�� ����(�)
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

std::istream& operator>>(std::istream& in, CPipe& pipe)
{
	pipe.id = ++CPipe::maxId;
	pipe.length = tryInput("Please, enter length: ", 1.0);
	pipe.diameter = tryInput("Please, enter diameter: ", 1);
	pipe.repair = false;
	return in;
}

void CPipe::editPipe()
{
	repair = !repair;
}