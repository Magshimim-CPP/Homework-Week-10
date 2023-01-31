#pragma once
#include <string>
#include <iostream>
#include <deque>
#include <algorithm>
#include "Item.h"

using std::string;

/////////////////////////////
// Comparators for Sorting //
/////////////////////////////

// More examples here:
// https://www.geeksforgeeks.org/comparator-class-in-c-with-examples/

struct {
	bool operator()(const Item& a, const Item& b)
	{
		return a.getCategory() < b.getCategory();
	}
} CategoryComparator;

struct {
	bool operator()(const Item& a, const Item& b)
	{
		return 	a.getName() < b.getName();
	}
} NameComparator;

struct {
	bool operator()(const Item& a, const Item& b)
	{
		return a.getPrice() < b.getPrice();
	}
} PriceComparator;

struct {
	bool operator()(const Item& a, const Item& b)
	{
		return 	a.getSerial() < b.getSerial();
	}
} SerialComparator;


enum SortingCriteria {CATEGORY = 0, NAME = 1, PRICE = 2, SERIAL = 3};

//////////////////////
// Class Definition //
//////////////////////

class Store
{
public:

	//Constructor function for a Store object.
	Store(string storeName, string inventoryFileName);

	//Const 'get' function that returns the '_storeName' field of a Store object(string).
	string getName() const;

	//Const 'get' function that returns the '_products' field of a Store object (std::deque<Item>).
	std::deque<Item> getProducts() const;

	//Function return's a string of all the store's products sorted by a selected criteria.
	string getSortedProductList(SortingCriteria sortingCriteria);

	//Function return's a list of all products from a specificly selected category.
	string getProductListFilteredByCategory(ItemCategory category);

	//Operator overloading on '[]', to return the Item in the n'th place from the store's _products deque.
	Item operator[](const int itemNumber) const;

	//Operator overloading on '<<', to return output stream of all the items in the shop, in the requested format.
	friend std::ostream& operator<<(std::ostream& os, const Store& store);

private:

	//Helper Method, reads a '.csv' file and adding the items to the products list.
	void getInventoryFromFile(const std::string inventoryFileName);
	//SELF ADDED - Function return's a string of all the products in the store by their current order.
	string getProductsStr();
	string _storeName;
	std::deque<Item> _products;
};

