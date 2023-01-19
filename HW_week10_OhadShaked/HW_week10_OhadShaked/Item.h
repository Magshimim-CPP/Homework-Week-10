#pragma once
#include<iostream>
#include<string>

using std::string;

enum ItemCategory {NONE = 0, FOOD = 1, PHARM = 2, CLEANING = 3, HOME = 4};

static std::string getItemCategoryString(const ItemCategory type)
{
    if (type == NONE)
        return "NONE";
    else if (type == FOOD)
        return "Food";
    else if (type == PHARM)
        return "Pharm";
    else if (type == CLEANING)
        return "Cleaning";
    else if (type == HOME)
        return "Home";
	return "Unknown";
}

class Item
{
public:

    Item(string name, string serialNumber, double unitPrice, ItemCategory category);
    ~Item();

	double totalPrice() const; //returns _count * _unitPrice
	
	bool operator <(const Item& other) const; //compares the _serialNumber of those items.
	bool operator >(const Item& other) const; //compares the _serialNumber of those items.
	bool operator ==(const Item& other) const; //compares the _serialNumber of those items.
	friend std::ostream& operator<<(std::ostream& os, const Item& item);

    string getName() const;
    string getSerial() const;
    double getPrice() const;
    int getCount() const;
    ItemCategory getCategory() const;
    void setCount(int newCount);

private:

    string _name;
    string _serialNumber;
    int _count;
    double _unitPrice;
    ItemCategory _category;

};