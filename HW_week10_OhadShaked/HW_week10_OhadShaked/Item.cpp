#include "Item.h"

using std::invalid_argument;

Item::Item(string name, string serialNumber, double unitPrice, ItemCategory category)
{
	if (serialNumber.length() != 5 || unitPrice < 0)
	{
		throw invalid_argument("Serial number length should be 5 letters, and price can't be negative.");
	}
	this->_name = name;
	this->_serialNumber = serialNumber;
	this->_unitPrice = unitPrice;
	this->_category = category;
	this->_count = 1;
}


Item::~Item()
{
	_count--;
}


double Item::totalPrice() const
{
	return (this->_count) * (this->_unitPrice);
}


string Item::getName()const
{
	return this->_name;
}


string Item::getSerial()const
{
	return this->_serialNumber;
}


double Item::getPrice()const
{
	return this->_unitPrice;
}


int Item::getCount() const
{
	return this->_count;
}


ItemCategory Item::getCategory() const
{
	return this->_category;
}


void Item::setCount(int newCount)
{
	if (newCount <= 0)
	{
		throw invalid_argument("Count must be positive.");
	}
	this->_count = newCount;
}


bool Item::operator<(const Item& other) const
{
	return (this->_serialNumber < other._serialNumber);
}


bool Item::operator>(const Item& other) const
{
	return (this->_serialNumber > other._serialNumber);
}


bool Item::operator==(const Item& other) const
{
	return (this->_serialNumber == other._serialNumber);
}

std::ostream& operator<<(std::ostream& os, const Item& item)
{
	os << "[Serial: " + item._serialNumber + ", Name: " + item._name + ", Category: " + getItemCategoryString(item._category) + ", Price: " + std::to_string(item._unitPrice) + ", Amount: " + std::to_string(item._count) + "]";
	return os;
}