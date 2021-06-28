#pragma once

#include "PrecompiledHeaders.h"





enum TypeItem
{
	NoneTypeItem = -1,
	HealingItem,
	EquipableBattleItem
};





struct Item
{
public:
	Item() 
		:type(TypeItem::NoneTypeItem) 
	{}

	virtual void use(); 

public:
	TypeItem type;
};





struct HealingItem : public Item
{
public:
	HealingItem(const std::string& filePath);
};





struct EquipableBattleItem : public Item
{
public:
	EquipableBattleItem(const std::string& filePath);
};