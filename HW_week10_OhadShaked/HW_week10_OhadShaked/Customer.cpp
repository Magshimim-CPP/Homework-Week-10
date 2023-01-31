#include "Customer.h"

/*
Constructor function for a Customer object.
Input: string name
Output: none
*/
Customer::Customer(string name)
{
	this->_name = name;
}

/*
Default Constructor function for a Customer object.
Input: none
Output: none
*/
Customer::Customer()
{
	this->_name = "";
}

/*
Destructor function for a Customer111 object.
Input: none
Output: none
*/
Customer::~Customer()
{
	//erasing the _shoppingCarts field and all dynamicly allocated memory stored in it.
	_shoppingCarts.erase(_shoppingCarts.begin(), _shoppingCarts.end());
}

/*
Function to calculate and return the price of all the items in all of the selected customer's shopping carts.
Input: none
Output: the price of all the items in all of the selected customer's shopping carts (double sum).
*/
double Customer::totalSum()
{
	double sum = 0;

	//using auto as an iterator to the current cart, and looping to sum up the prices of all the customer's carts.
	for (auto it = _shoppingCarts.begin(); it != _shoppingCarts.end(); ++it)
	{
		sum += shoppingCartSum(it->first);
	}

	return sum;
}

/*
Const 'get' function that returns the '_name' field of a Customer object (string).
Input: none
Output: this->_name (string).
*/
string Customer::getName() const
{
	return this->_name;
}

/*
Const 'get' function that returns the '_shoppingCarts' field of a Customer object (std::map<std::string, std::set<Item>*>).
Input: none
Output: this->_shoppingCarts (std::map<std::string, std::set<Item>*>).
*/
std::map<std::string, std::set<Item>*> Customer::getShoppingCarts() const
{
	return this->_shoppingCarts;
}

/*
Function create's a new shopping cart with the given name, and adds it to the customer's _shoppingCarts.
Input: string shoppingCartName
Output: none.
*/
void Customer::createNewShoppingCart(string shoppingCartName)
{
	//if a shopping cart with this name doesn't already exist, creating a new cart with the given name.
	if (!_shoppingCarts[shoppingCartName])
	{
		_shoppingCarts[shoppingCartName] = new std::set<Item>();
	}
}

/*
Function to calculate and return the price of all the items in a selected shopping cart.
Input: string shoppingCartName.
Output: the price of all the items in a selected shopping cart (double sum).
*/
double Customer::shoppingCartSum(string shoppingCartName) const
{
	double sum = 0;

	std::set<Item>* cart = _shoppingCarts.at(shoppingCartName);

	//using auto as an iterator to the current Item, and looping to sum up the prices of all the items in the cart.
	for (auto it = cart->begin(); it != cart->end(); ++it)
	{
		sum += (it->getPrice() * it->getCount());
	}

	return sum;
}

/*
Const 'get' function that returns a selected shopping cart from the _shoppingCarts map (std::set<Item>*).
Input: string shoppingCartName.
Output: this->_shoppingCarts.at(shoppingCartName) (std::set<Item>*).
*/
std::set<Item>* Customer::getShoppingCart(string shoppingCartName) const
{
	try
	{
		return _shoppingCarts.at(shoppingCartName);
	}
	catch (const std::out_of_range& e)
	{
		return nullptr;
	}
	
}

/*
Function to insert a given Item to a given Shopping Cart.
Input: const Item& item, string shoppingCartName
Output: none.
*/
void Customer::addItem(const Item& item, string shoppingCartName)
{
	//creating a set of items pointer variable for the specified by name shopping cart.
	std::set<Item>* cart = _shoppingCarts.at(shoppingCartName);

	//setting an iterator (using auto) for this item from the given shopping cart.
	auto it = cart->find(item);

	//if the item already exists in the cart.
	if (it != cart->end())
	{
		Item copy = *it; //making a copy of the item that already exists in the cart.
		copy.setCount(copy.getCount() + 1); //setting the count field of the copy to itself +1.
		cart->erase(it); //erasing the old item object from the cart.
		cart->insert(copy); //adding the new item object with upgraded count to the cart
	}
	//if the item dose not already exists in the cart.
	else
	{
		Item copy = item; //making a copy of the passed Item object.
		copy.setCount(1); //setting the item's count to 1.
		cart->insert(copy); //using insert() to add the item to the cart.
	}
}

/*
Function to remove a given Item from a given Shopping Cart.
Input: const Item& item, string shoppingCartName
Output: none.
*/
void Customer::removeItem(const Item& item, string shoppingCartName)
{
	//creating a set of items pointer variable for the specified by name shopping cart.
	std::set<Item>* cart = _shoppingCarts.at(shoppingCartName);

	//setting an iterator (using auto) for this item from the given shopping cart.
	auto it = cart->find(item);

	//if the item already exists in the cart.
	if (it != cart->end())
	{
		Item copy = *it; //making a copy of the item that already exists in the cart.

		if (copy.getCount() > 1) //if there is more then one item like this in the cart:
		{
			copy.setCount(copy.getCount() - 1); //decreasing the copyed item's count field by 1.
			cart->erase(it); //erasing the old item object from the cart.
			cart->insert(copy); //adding the new item object with upgraded count to the cart
		}
		else //if there is only one item like this in the cart, erasing it.
		{
			cart->erase(it); 
		}
	}
}