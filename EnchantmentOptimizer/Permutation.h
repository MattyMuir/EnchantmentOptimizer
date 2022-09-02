#pragma once
#include <string>
#include <sstream>
#include <vector>
#include <format>

#include "Item.h"

class Permutation
{
public:
	std::vector<int> steps;

	bool operator++();
	const std::pair<int, int>& operator[](int n) const;

	void Initialize(int size);
	void LogSteps(const std::vector<Item>& itemSet);

	static void SetMaxLength(int maxLength);
protected:

	static std::vector<std::vector<std::pair<int, int>>> allSteps;
};