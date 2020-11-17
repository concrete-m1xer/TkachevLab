#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>

template <typename T>
T tryInput(std::string alert, T min, T max = 1000000)
{
	T x;
	std::cout << alert;
	while ((std::cin >> x).fail() || x < min || x > max)
	{
		std::cin.clear();
		std::cin.ignore(10000, '\n');
		std::cout << alert;
	}
	return x;
}

template <typename T>
int getIndexById(const std::vector <T>& vec, int id)
{
	for (unsigned int i = 0; i < vec.size(); i++) 
	{
		if (vec[i].getId() == id)
		{
			return i;
		}
	}
	return -1;
}

template <typename T>
// если есть id больше 1, то находит больше 1, если вектор пустой, то 0
int findMaxId(const std::map <int, T>& myMap)
{
	int maxId = 0;
	for (const auto& p : myMap)
	{
		if (p.second.getId() > maxId)
		{
			maxId = p.second.getId();
		}
	}
	return maxId;
}

// Удаление объектов
template <typename T>
void deleteObj(std::map <int, T>& myMap, int id) {
	myMap.erase(id);
}