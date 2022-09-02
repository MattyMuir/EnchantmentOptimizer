#include "Enchantment.h"

decltype(Enchantment::strToID) Enchantment::strToID = decltype(Enchantment::strToID)();
decltype(Enchantment::enchantInfos) Enchantment::enchantInfos = decltype(Enchantment::enchantInfos)();
decltype(Enchantment::IDToStr) Enchantment::IDToStr = decltype(Enchantment::IDToStr)();
int Enchantment::_= LoadEnchantData();

Enchantment::Enchantment() {}

Enchantment::Enchantment(unsigned id_)
	: id(id_)
{
	max = enchantInfos[id].x[0];
	mulItem = enchantInfos[id].x[1];
	mulBook = enchantInfos[id].x[2];
}

Enchantment::Enchantment(const std::string& name)
{
	id = strToID[name];

	max = enchantInfos[id].x[0];
	mulItem = enchantInfos[id].x[1];
	mulBook = enchantInfos[id].x[2];
}

std::string Enchantment::ToString() const
{
	return IDToStr[id];
}

void Enchantment::LogAllEnchants()
{
	for (int i = 0; i < IDToStr.size(); i++)
	{
		std::cout << i << ": " << IDToStr[i] << '\n';
	}
}

int Enchantment::LoadEnchantData()
{
	// Statically load enchantment data
	std::ifstream data("enchants.txt");

	std::string line;
	std::string parts[4];
	int id = 0;
	while (std::getline(data, line))
	{
		// Split line
		int index = 0;
		for (const auto& part : std::views::split(line, std::string_view(",")))
		{
			parts[index] = std::string(part.begin(), part.end());
			index++;
		}

		// Add enchant to static variables
		IDToStr.push_back(parts[0]);
		strToID.insert({ parts[0], id });
		enchantInfos.push_back({ std::stoi(parts[1]), std::stoi(parts[2]), std::stoi(parts[3]) });

		id++;
	}

	return 0;
}