#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
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
// если есть id больше 1, то находит больше 1, если вектор пустой, то 0
int findMaxId(const std::unordered_map <int, T>& myMap)
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
void deleteObj(std::unordered_map <int, T>& myMap, int id) {
	myMap.erase(id);
}

template <typename T>
void swapValues(T& value1, T& value2)
{
	T temp = value1;
	value1 = value2;
	value2 = temp;
}

void stringAlert(std::string s)
{
	std::cout << std::endl << s << std::endl;
}

template <typename T>
std::vector <int> inputVecId(std::unordered_map <int, T> myMap)
{
	std::vector <int> vecId;
	bool input = true;
	while (input)
	{
		int id = tryInput("Please, enter correct id of next pipe you want to edit or enter [0] to stop input: ", 0);
		if (id != 0)
		{
			if (myMap.find(id) != myMap.end())
			{
				vecId.push_back(id);
			}
		}
		else
		{
			input = false;
		}
	}
	return vecId;
}