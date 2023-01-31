#include "Store.h"
#include <fstream>
#include <sstream>

/*
Constructor function for a Store object.
Input: string storeName, string inventoryFileName
Output: none
*/
Store::Store(string storeName, string inventoryFileName)
{
	this->_storeName = storeName;
	getInventoryFromFile(inventoryFileName);
}

/*
Const 'get' function that returns the '_storeName' field of a Store object (string).
Input: none
Output: this->_storeName (string).
*/
string Store::getName() const
{
	return this->_storeName;
}

/*
Const 'get' function that returns the '_products' field of a Store object (std::deque<Item>).
Input: none
Output: this->_products (std::deque<Item>).
*/
std::deque<Item> Store::getProducts() const
{
	return this->_products;
}

/*
Operator overloading on '<<', to return output stream of all the items in the shop, in the requested format.
Input: std::ostream& os, const Store& store
Output: the constructed output stream (std::ostream&).
*/
std::ostream& operator<<(std::ostream& os, const Store& store)
{
	os << "Store Name: " + store._storeName + "\nProducts:\n";
	for (int i = 0; i < store._products.size(); i++) //looping through all the store products.
	{
		os << "[" + std::to_string(i) + "] - "; //the element's index number [i] (requested format)
		os << store[i] << std::endl; //using the overload on '<<' from the item class.
	}
	return os;
}

/*
Function return's a list of all products from a specificly selected category.
Input: ItemCategory category
Output: a list of all products from a specificly selected category (string retStr).
*/
string Store::getProductListFilteredByCategory(ItemCategory category)
{
	string retStr;
	for (int i = 0; i < this->_products.size(); i++)
	{
		if (this->_products[i].getCategory() == category)
		{
			retStr += "[Serial: " + this->_products[i].getSerial() + ", Name: " + this->_products[i].getName() + ", Category: " + getItemCategoryString(this->_products[i].getCategory()) + ", Price: " + std::to_string(this->_products[i].getPrice()) + ", Amount: " + std::to_string(this->_products[i].getCount()) + "]\n";
		}
	}
	return retStr;
}

/*
SELF ADDED - Function return's a string of all the products in the store by their current order.
Input: none
Output: a string of all the products in the store by their current order (string retStr).
*/
string Store::getProductsStr()
{
	string retStr;
	for (int i = 0; i < this->_products.size(); i++)
	{
		retStr += "[Serial: " + this->_products[i].getSerial() + ", Name: " + this->_products[i].getName() + ", Category: " + getItemCategoryString(this->_products[i].getCategory()) + ", Price: " + std::to_string(this->_products[i].getPrice()) + ", Amount: " + std::to_string(this->_products[i].getCount()) + "]\n";
	}
	return retStr;
}

/*
Function return's a string of all the store's products sorted by a selected criteria.
Input: SortingCriteria sortingCriteria
Output: a string of all the store's products sorted by a selected criteria (string).
*/
string Store::getSortedProductList(SortingCriteria sortingCriteria)
{
	if (sortingCriteria == SERIAL)
	{
		sort(this->_products.begin(), this->_products.end(), SerialComparator);
	}
	if (sortingCriteria == NAME)
	{
		sort(this->_products.begin(), this->_products.end(), NameComparator);
	}
	if (sortingCriteria == PRICE)
	{
		sort(this->_products.begin(), this->_products.end(), PriceComparator);
	}
	if (sortingCriteria == CATEGORY)
	{
		sort(this->_products.begin(), this->_products.end(), CategoryComparator);
	}
	return this->getProductsStr();
}

/*
Operator overloading on '[]', to return the Item in the n'th place from the store's _products deque.
Input: const int itemNumber
Output: the Item in the n'th place from the store's _products deque (this->_products[itemNumber]) (Item).
*/
Item Store::operator[](const int itemNumber) const
{
	if (itemNumber < this->_products.size() && itemNumber >= 0)
	{
		return this->_products[itemNumber];
	}
	else //if the given number was out of the index bounds, throwing an invalid_argument exception.
	{
		throw std::invalid_argument("ERROR: index was out of the deque's boundarys.\n");
	}
}

/*
GIVEN FUNCTION - GET'S THE INVENTORY FROM A GIVEN FILE.
Input: const std::string inventoryFileName
Output: none
*/
void Store::getInventoryFromFile(const std::string inventoryFileName)
{
	// This function reads a CSV file into the object inventory (std::deque<Item>)

	std::deque<std::deque<std::string>> content;	// the entire file as strings
	std::deque<std::string> row;					// a row in the file as string
	std::string line, word;							

	std::fstream file(inventoryFileName, std::ios::in);		// openning the csv file for read
	if (file.is_open())
	{
		while (std::getline(file, line))		// reading line by line
		{
			row.clear();

			std::stringstream str(line);		// adding the line to a std::stringstream

			while (std::getline(str, word, ','))	// reading each word seperated by ','
				row.push_back(word);
			content.push_back(row);
		}
	}
	else
	{
		std::cerr << "Could not open the file " << inventoryFileName << "\n" << std::endl;
		throw std::invalid_argument("Could not open the file " + inventoryFileName);
	}

	/* Indexes
		0 --- Item's Name
		1 --- Item's Serial
		2 --- Item's Unit Price
		3 --- Item's Category (int)
	*/

	for (int i = 1; i < content.size(); i++)
	{
		std::string itemName = content[i][0];
		std::string itemSerial = content[i][1];
		double itemPrice = strtod(content[i][2].c_str(), nullptr);
		ItemCategory itemCategory = ItemCategory(stoi(content[i][3]));
		this->_products.push_back(Item(itemName, itemSerial, itemPrice, itemCategory));
	}

	// To print the content remove the comments:
	// for (int i = 0; i < content.size(); i++)
	//{
	//	for (int j = 0; j < content[i].size(); j++)
	//	{
	//		std::cout << content[i][j] << " ";
	//	}
	//	std::cout << "\n";
	//}

}