#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include "assistance.h"

class CCompressorStation
{
	int id;
	std::string name;
	int shopsCount;
	int workingShopsCount;
	double efficiency;
public:

	CCompressorStation(int id);
	CCompressorStation();
	CCompressorStation(const CCompressorStation& cs);
	//CCompressorStation(CCompressorStation&& cs);

	int getId() const;
	std::string getName() const;
	int getShopsCount() const;
	int getWorkingShopsCount() const;
	double getEfficiency() const;

	//void setId(int newId);
	//void setName(std::string newName);
	//void setShopsCount(int newShopsCount);
	//void setWorkingShopsCount(int newWorkingShopsCount);
	//void setEfficiency(double newEfficiency);

	void editCS();

	friend std::ostream& operator << (std::ostream& out, const CCompressorStation& CS);
	friend std::ofstream& operator << (std::ofstream& fout, const CCompressorStation& CS);
	friend std::ifstream& operator >> (std::ifstream& fin, CCompressorStation& CS);
}; 

