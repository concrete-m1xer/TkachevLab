#pragma once
#include <iostream>
#include <fstream>
#include "assistance.h"

class CPipe
{
	int id;
	int diameter;
	double length;
	bool repair;
public:

	static int maxId;

	CPipe();
	//CPipe(const CPipe& pipe);
	CPipe(std::ifstream& in);

	int getId() const;
	int getDiameter() const;
	double getLength() const;
	bool getRepair() const;
	double getPressureDropValue() const;
	double getPerformance() const;

	//void setId(int newId);
	//void setDiameter(int newDiameter);
	//void setLength(double newLength);
	//void setRepair(bool newRepair);

	void editPipe();

	friend std::ostream& operator << (std::ostream& out, const CPipe& pipe);
	friend std::ifstream& operator >> (std::ifstream& fin, CPipe& pipe);
	friend std::ofstream& operator << (std::ofstream& fout, const CPipe& pipe);
	friend std::istream& operator >> (std::istream& in, CPipe& pipe);
};

