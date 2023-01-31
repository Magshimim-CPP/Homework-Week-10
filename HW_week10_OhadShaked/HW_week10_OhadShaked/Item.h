#pragma once
#include <exception>
#include <string>
#include <iostream>
#include <string>

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

    //Constructor function for an Item object.
    Item(string name, string serialNumber, double unitPrice, ItemCategory category);

    //Destructor function for an Item object.
    ~Item();

    //Const function that returns the total price of all the items like this avilable [the item's count times the item's price] (double).
	double totalPrice() const; 
	
    //Operator overloading on '<' to check if 'this' item's serial number is smaller then the compared-to item's serial number (bool).
	bool operator <(const Item& other) const; //compares the _serialNumber of those items.

    //Operator overloading on '>' to check if 'this' item's serial number is larger then the compared-to item's serial number (bool).
	bool operator >(const Item& other) const; //compares the _serialNumber of those items.

    //Operator overloading on '==' to check if 'this' item's serial number is equal to the compared-to item's serial number (bool).
	bool operator ==(const Item& other) const; //compares the _serialNumber of those items.

    //Operator overloading on '<<', to return output stream of : SerianNumber: --, Name : --, Category : --, Price : --, Amount : --.
	friend std::ostream& operator<<(std::ostream& os, const Item& item);

    //getters and setters
    string getName() const; //Const 'get' function that returns the '_name' field of an Item object(string).
    string getSerial() const; //Const 'get' function that returns the '_serialNumber' field of an Item object (string).
    double getPrice() const; //Const 'get' function that returns the '_unitPrice' field of an Item object (double).
    int getCount() const; //Const 'get' function that returns the '_count' field of an Item object (int).
    ItemCategory getCategory() const; //Const 'get' function that returns the '_category' field of an Item object (ItemCategory).
    void setCount(int newCount); //Set function to change the '_count' field of an item.

private:

    int _count;
    string _name;
    string _serialNumber;
    double _unitPrice;
    ItemCategory _category;

};