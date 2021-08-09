#pragma once
#include <vector>
#include <string>

#include "Enchants Data.h"

class Item
{
public:
	bool isBook;
	std::vector<Enchant> enchants;
	int priorPenalty;

	Item(bool isBook_, std::vector<Enchant>& enchants_, int priorPenalty_)
		: isBook(isBook_), enchants(enchants_), priorPenalty(priorPenalty_)
	{}
	Item(bool isBook_, std::vector<Enchant>&& enchants_, int priorPenalty_)
		: isBook(isBook_), enchants(enchants_), priorPenalty(priorPenalty_)
	{}
};