#pragma once
class EnchantInfo
{
public:
	int max;
	int mul_item;
	int mul_book;

	EnchantInfo()
	{
		max = 0;
		mul_item = 0;
		mul_book = 0;
	}

	EnchantInfo(int max_, int mul_item_, int mul_book_)
		: max(max_), mul_item(mul_item_), mul_book(mul_book_)
	{}
};