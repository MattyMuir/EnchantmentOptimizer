#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <unordered_map>
#include <ranges>

class Enchantment
{
	static int LoadEnchantData();
	struct Int3
	{
		int x[3];
	};

public:
	int id = 0;
	int max = 0, mulItem = 0, mulBook = 0;

	Enchantment();
	Enchantment(unsigned id_);
	Enchantment(const std::string& name);

	std::string ToString() const;

	static void LogAllEnchants();

protected:
	static int _;
	static std::unordered_map<std::string, int> strToID;
	static std::vector<Int3> enchantInfos;
	static std::vector<std::string> IDToStr;
};