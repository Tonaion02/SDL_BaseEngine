#pragma once

#include "PrecompiledHeaders.h"

#include "Item.h"





struct Inventory
{
public:
	Inventory() {}
	Inventory(const std::string& filePath);

	void add(Item* item);

public:
	std::vector<Item*> m_items;
	std::string filePath;
};