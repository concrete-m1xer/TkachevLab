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

	static int maxId;

	CCompressorStation();
	CCompressorStation(std::ifstream& in);
//	CCompressorStation(const CCompressorStation& cs);
	//CCompressorStation(CCompressorStation&& cs);

	int getId() const;
	std::string getName() const;
	int getShopsCount() const;
	int getWorkingShopsCount() const;
	double getEfficiency() const;
	double getOccupancyPercentage() const;

	//void setId(int newId);
	//void setName(std::string newName);
	//void setShopsCount(int newShopsCount);
	//void setWorkingShopsCount(int newWorkingShopsCount);
	//void setEfficiency(double newEfficiency);

	void editCS();

//	void enhancedEditCS();

	friend std::ostream& operator << (std::ostream& out, const CCompressorStation& CS);
	friend std::ofstream& operator << (std::ofstream& fout, const CCompressorStation& CS);
	friend std::ifstream& operator >> (std::ifstream& fin, CCompressorStation& CS);
	friend std::istream& operator >> (std::istream& in, CCompressorStation& CS);
}; 

