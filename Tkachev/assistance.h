#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "CPipe.h"
#include "CCompressorStation.h"

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
	for (unsigned int i = 0; i < vec.size(); i++) // оставил так, как из функции получаем иттератор
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
int findMaxId(const std::vector <T>& vec)
{
	int maxId = 0;
	for (auto& c : vec)
	{
		if (c.getId() > maxId)
		{
			maxId = c.getId();
		}
	}
	return maxId;
}

// Удаление объектов
template <typename T>
void deleteObj(std::vector <T>& vec, int i) {
	vec.erase(vec.begin() + i);// riptutorial.com/ru/cplusplus/example/2156/ удаление-элементов - удаляет выбранный элемент вектора и сдвигает все, что были справа
}