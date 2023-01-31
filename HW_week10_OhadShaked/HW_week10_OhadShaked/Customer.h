#pragma once
#include "Item.h"
#include <set>
#include <map>

using std::string;

class Customer
{
public:
	// constructors
	Customer(string name);
	Customer();

	// destructors
	~Customer();
	
	// methods
	void createNewShoppingCart(string shoppingCartName);
	double shoppingCartSum(string shoppingCartName) const; // returns the payment sum for a given shopping cart;
	double totalSum();//returns the total sum for payment

	void addItem(const Item& item, string shoppingCartName);//add item to the set
	void removeItem(const Item& item, string shoppingCartName);//remove item from the set

	//get and set functions

	string getName() const;	// returns the customer name
	std::map<string, std::set<Item>*> getShoppingCarts() const;
	std::set<Item>* getShoppingCart(string shoppingCartName) const; // returns the shopping cart with the given name

private:
	string _name; // Customer name
	std::map<string, std::set<Item>*> _shoppingCarts; // Shopping carts
};
