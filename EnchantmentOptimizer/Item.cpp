#include "Item.h"

Item::Item(bool isBook_, const std::vector<Enchantment>& enchants_, int prior_)
	: isBook(isBook_), enchants(enchants_), prior(prior_)
{}

Item::Item(const Enchantment& enchant)
	: isBook(true), prior(0), enchants()
{
	enchants.push_back(enchant);
}

void Item::operator+=(const Item& other)
{
    enchants.reserve(enchants.size() + other.enchants.size());
    for (const Enchantment& ench : other.enchants)
        enchants.push_back(ench);

    prior = std::max(prior, other.prior) + 1;
}

std::string Item::ToString() const
{
	if (!isBook) return "Item";
	std::string s = "(";
	for (int i = 0; i < enchants.size(); i++)
	{
		if (i > 0) s += ", ";
		s += enchants[i].ToString();
	}
	s += ")";

	return s;
}

int Item::CombineCost(const Item& i1, const Item& i2)
{
    int totalCost = 0;

    for (const Enchantment& enchant : i2.enchants)
    {
        int multiplier = enchant.mulBook;
        if (!i2.isBook) [[unlikely]]
            multiplier = enchant.mulItem;

        int cost = multiplier * enchant.max;
        totalCost += cost;
    }

    return totalCost + (1 << i1.prior) + (1 << i2.prior) - 2;
}