#include <map>
#include "Customer.h"
#include "Store.h"

//using specific functions from std.
using std::cout;
using std::cin;
using std::endl;

//global variables for the customers map and the stores array.
std::map<string, Customer> abcCustomers;
//(creating the store objects and adding them to the stores array.)
Store stores[3] = { Store("Shefa Isaschar", "InventorySuperMarket.csv"),  Store("MagshIKEA", "InventoryIKEA.csv"),  Store("MagshiPharm", "InventoryPharm.csv") };

//declaring functions at the top of the code.
int MenuChoice();
void printTopCustomer();
void newCustomerMenu();
void existingCustomerMenu();
void addCartToCustomer(Customer& customer);
void itemsMenu(Customer& customer, string name);

//defined strings for the menus.
#define MAIN_MENU "Welcome to MagshiMart!\n1. Sign up as customer and buy items\n2. Update existing customer's items\n3. Print the customer who pays the most\n4. Exit\n"
#define ITEMS_MENU "\nSelect the store to buy from:\n1. Shefa Isaschar (Super Market)\n2. MagshIKEA (Home products)\n3. MagshiPharm (Pharm and utils)\n4. Back to main menu\n"
#define NEW_CUSTOMER_MENU "\n1. Create a new shopping cart\n2. Back to main menu\n"
#define EXISTING_CUSTOMER_MENU "\n1. Create a new shopping cart\n2. Update existing shopping cart\n3. Back to main menu\n"

int main()
{
	bool menuLoop = true;
	int choice;

	//looping the main menu until the user chooses to exit.
	while (menuLoop)
	{
		choice = MenuChoice();

		switch (choice)
		{
		case(1): //creating a new customer (sign up menu).
			newCustomerMenu();
			break;

		case(2): //updating an existing customer (existing menu).
			existingCustomerMenu();
			break;

		case(3): //printing the customer who paid the most in total.
			printTopCustomer();
			break;

		case(4): //quiting the main menu loop (exit).
			cout << "THANK'S FOR USING MagshiMart!" << endl;
			menuLoop = false;
			break;

		default: //if the choice was out of range.
			cout << "ERROR: Invalid input!" << endl;
		}

	}
	return 0;
}

/*
Function take's user's input for the main menu options, and returns the result.
Input: none
Output: int choice
*/
int MenuChoice()
{
	int choice = 0;

	cout << MAIN_MENU << endl;

	cout << "Please enter your choice:  ";
	cin >> choice;
	cin.clear();

	return choice;
}

/*
Function creates a new customer with given values, and adds him to the customers map.
Input: none
Output: none
*/
void newCustomerMenu()
{
	string customerName;
	string cartName;
	int choice = 0;

	//taking customer's name input.
	cout << "Please enter your name:  ";
	cin >> customerName;
	cin.clear();

	//checking that the name does not already exist in the customers map.
	if (abcCustomers.find(customerName) == abcCustomers.end())
	{
		//inserting a new customer with the given name to the customers map.
		abcCustomers.insert(make_pair(customerName, Customer(customerName)));

		cout << NEW_CUSTOMER_MENU << endl;
		cout << "Please enter your choice:  ";
		cin >> choice;
		cin.clear();

		//if the user chose to create a shopping cart.
		if (choice == 1)
		{
			addCartToCustomer(abcCustomers.at(customerName));;
		}
	}

	//if a customer with that name already exist, printing error.
	else
	{
		cout << "ERROR: identical customer name already exists." << endl;
	}
}

/*
Function creates a new cart for a customer, with a given cart name.
Input: Customer& customer
Output: none
*/
void addCartToCustomer(Customer& customer)
{
	string cartName;

	//taking input for the cart's name.
	cout << "Enter the new shopping cart name:  ";
	cin >> cartName;
	cin.clear();

	//if there isn't already a cart with this name, creating the cart.
	if (!customer.getShoppingCart(cartName))
	{
		customer.createNewShoppingCart(cartName);
		itemsMenu(customer, cartName);
	}

	//if there is already a cart with this name, printing error message.
	else
	{
		cout << "ERROR: A cart with the same name already exists." << endl;
	}
}

/*
Function adds items to a given customer's cart (with a given cart name)
Input: Customer& customer, string cartName
Output: none
*/
void itemsMenu(Customer& customer, string cartName)
{
	int shopChoice = 0;
	int itemChoice = 0;

	cout << ITEMS_MENU << endl;
	cout << "Please enter your choice:  ";
	cin >> shopChoice;
	shopChoice--;
	cin.clear();

	//if the user's shop choice was in range.
	if (shopChoice >= 0 && shopChoice <= 2)
	{
		//using overloaded "<<" to print the store's content.
		cout << stores[shopChoice];

		//looping until item choice is out of range.
		while (itemChoice >= 0 && itemChoice <= stores[shopChoice].getProducts().size())
		{
			cout << "Please enter product number:  ";
			cin >> itemChoice;
			cin.clear();

			if (itemChoice >= 0 && itemChoice <= stores[shopChoice].getProducts().size())
			{
				customer.addItem(stores[shopChoice].getProducts().at(itemChoice), cartName);
				abcCustomers.at(customer.getName()) = customer;
			}
		}

	}

}

/*
Function with the existing customer menu, to preform actions and change an already existing user.
Input: none
Output: none
*/
void existingCustomerMenu()
{
	int choice = 0;
	int cartChoice = 0;
	int cartNum = 1;
	string customerName;
	string cartName;

	cout << "Enter customer name: ";
	cin >> customerName;

	//if the user already exists.
	if (abcCustomers.find(customerName) != abcCustomers.end())
	{
		Customer tempCustomer = abcCustomers.at(customerName);
		std::map<string, std::set<Item>*> shoppingCarts = tempCustomer.getShoppingCarts();

		cout << EXISTING_CUSTOMER_MENU << endl;
		cout << "Please enter your choice:  ";
		cin >> choice;
		cin.clear();

		//if choice == 1 --> creating a new cart for the customer.
		if (choice == 1)
		{
			addCartToCustomer(tempCustomer);
		}

		//if choice == 2 --> adding items to an already existing selected cart.
		if (choice == 2)
		{
			cout << "Select Shopping Cart:" << endl;

			//printing all of the user's carts.
			for (auto it = shoppingCarts.begin(); it != shoppingCarts.end(); it++)
			{
				cout << "[" << cartNum << "] - Name: " << it->first << " | Current size: " << it->second->size() << endl;
				cartNum++;
			}

			//getting position input for the wanted cart.
			cartNum = 1;
			cin >> cartChoice;
			cin.clear();

			//looping to get the name of the cart in the stated position.
			for (auto it = shoppingCarts.begin(); it != shoppingCarts.end(); it++)
			{
				if (cartNum == cartChoice)
				{
					cartName = it->first;
				}
				cartNum++;
			}

			//if the user selected an existing cart.
			if (cartName != "")
			{
				itemsMenu(tempCustomer, cartName);
			}
		}
	}

	//if the user dosen't exist in the map.
	else
	{
		cout << "ERROR: User does not exist." << endl;
	}
}

/*
Function checks how much each customer paied in total, and print's the info of the customer who paid the most.
Input: none
Output: none
*/
void printTopCustomer()
{
	double largestAmount = 0;
	string topCustomer;

	//looping through the customers map.
	for (auto it = abcCustomers.begin(); it != abcCustomers.end(); it++)
	{
		//if the current customer's spendings are bigger then largestAmount, setting topCustomer to the current customer, and largestAmount to the current customer's total spendings.
		if (it->second.totalSum() > largestAmount)
		{
			largestAmount = it->second.totalSum();
			topCustomer = it->first;
		}
	}

	cout << "The customer who spent the most is: " << topCustomer << ", with a total spending of: " << largestAmount << endl;
}