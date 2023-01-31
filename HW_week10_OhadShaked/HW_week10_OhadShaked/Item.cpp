#include "Item.h"

using std::invalid_argument;

/*
Constructor function for an Item object.
Input: string name, string serialNumber, double unitPrice, ItemCategory category
Output: none
*/
Item::Item(string name, string serialNumber, double unitPrice, ItemCategory category)
{
	//if the length of the given serial number is not 5 letters or the price of the product is negative, throwing invalid_argument exception.
	if (serialNumber.length() != 5 || unitPrice < 0)
	{
		throw invalid_argument("Serial number length should be 5 letters, and price can't be negative.");
	}
	//inisializing the item fields to the given values (count to 1).
	this->_name = name;
	this->_serialNumber = serialNumber;
	this->_unitPrice = unitPrice;
	this->_category = category;
	this->_count = 1;
}

/*
Destructor function for an Item object.
Input: none
Output: none
*/
Item::~Item() {}

/*
Const function that returns the total price of all the items like this avilable [the item's count times the item's price] (double).
Input: none
Output: the total price of all the items like this avilable [the item's count times the item's price] (double).
*/
double Item::totalPrice() const
{
	return (this->_count) * (this->_unitPrice);
}

/*
Const 'get' function that returns the '_name' field of an Item object (string).
Input: none
Output: this->_name (string).
*/
string Item::getName() const
{
	return this->_name;
}

/*
Const 'get' function that returns the '_serialNumber' field of an Item object (string).
Input: none
Output: this->_serialNumber (string).
*/
string Item::getSerial() const
{
	return this->_serialNumber;
}

/*
Const 'get' function that returns the '_unitPrice' field of an Item object (double).
Input: none
Output: this->_unitPrice (double).
*/
double Item::getPrice() const
{
	return this->_unitPrice;
}

/*
Const 'get' function that returns the '_count' field of an Item object (int).
Input: none
Output: this->_count (int).
*/
int Item::getCount() const
{
	return this->_count;
}

/*
Const 'get' function that returns the '_category' field of an Item object (ItemCategory).
Input: none
Output: this->_category (ItemCategory).
*/
ItemCategory Item::getCategory() const
{
	return this->_category;
}

/*
Set function to change the '_count' field of an item.
Input: int newCount
Output: none
*/
void Item::setCount(int newCount)
{
	//if the given count is not positive, throwing invalid_argument exception.
	if (newCount <= 0)
	{
		throw invalid_argument("Count must be positive.");
	}
	//changing the _count field to the new given count.
	this->_count = newCount;
}

/*
Operator overloading on '<' to check if 'this' item's serial number is smaller then the compared-to item's serial number (bool).
Input: const Item& other
Output: true/false (bool)
*/
bool Item::operator<(const Item& other) const
{
	return (this->_serialNumber < other._serialNumber);
}

/*
Operator overloading on '>' to check if 'this' item's serial number is larger then the compared-to item's serial number (bool).
Input: const Item& other
Output: true/false (bool)
*/
bool Item::operator>(const Item& other) const
{
	return (this->_serialNumber > other._serialNumber);
}

/*
Operator overloading on '==' to check if 'this' item's serial number is equal to the compared-to item's serial number (bool).
Input: const Item& other
Output: true/false (bool)
*/
bool Item::operator==(const Item& other) const
{
	return (this->_serialNumber == other._serialNumber);
}

/*
Operator overloading on '<<', to return output stream of: SerianNumber: --, Name: --, Category: --, Price: --, Amount: --.
Input: std::ostream& os, const Item& item
Output: the constructed output stream (std::ostream&).
*/
std::ostream& operator<<(std::ostream& os, const Item& item)
{
	os << "[Serial: " + item._serialNumber + ", Name: " + item._name + ", Category: " + getItemCategoryString(item._category) + ", Price: " + std::to_string(item._unitPrice) + ", Amount: " + std::to_string(item._count) + "]";
	return os;
}