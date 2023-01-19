#include "Store.h"
#include <fstream>
#include <sstream>

Store::Store(string storeName, string inventoryFileName)
{
	this->_storeName = storeName;
	getInventoryFromFile(inventoryFileName);
}

string Store::getName() const
{
	return this->_storeName;
}

std::ostream& operator<<(std::ostream& os, const Store& store)
{
	os << "Store Name: " + store._storeName + "\nProducts:\n";
	for (int i = 0; i < store._products.size(); i++)
	{
		os << "[" + std::to_string(i) + "] - ";
		os << store[i];
	}
	return os;
}

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

string Store::getProductsStr()
{
	string retStr;
	for (int i = 0; i < this->_products.size(); i++)
	{
		retStr += "[Serial: " + this->_products[i].getSerial() + ", Name: " + this->_products[i].getName() + ", Category: " + getItemCategoryString(this->_products[i].getCategory()) + ", Price: " + std::to_string(this->_products[i].getPrice()) + ", Amount: " + std::to_string(this->_products[i].getCount()) + "]\n";
	}
	return retStr;
}

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

Item Store::operator[](const int itemNumber) const
{
	if (itemNumber < this->_products.size() && itemNumber >= 0)
	{
		return this->_products[itemNumber];
	}
	else
	{
		throw std::invalid_argument("ERROR: index was out of the deque's boundarys.\n");
	}
}
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