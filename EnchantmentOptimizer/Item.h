#pragma once
#include <vector>
#include <string>

#include "Enchantment.h"

struct Item
{
	Item(bool isBook_, const std::vector<Enchantment>& enchants_, int prior_);
	Item(const Enchantment& enchant);

	bool isBook;
	std::vector<Enchantment> enchants;
	int prior;

	void operator+=(const Item& other);
	std::string ToString() const;
	static int CombineCost(const Item& i1, const Item& i2);
};