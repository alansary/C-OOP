#include <iostream>
using namespace std;

class Product {
private:
	int id;
	char name[100];
	char *description; // Dynamically allocated array
	int maximum_retail_price;
	int selling_price;

public:
	// Constructor Overloading
	// Overloading = Multiple functions with same name

	// Constructor
	Product() {
//		cout << "Constructor" << endl;
	}

	// Parameterized Constructor
	Product(int id, char *n, char *desc, int maximum_retail_price, int selling_price) {
		(*this).id = id; // dereference to get the object first then access its id
		this->maximum_retail_price = maximum_retail_price;
		this->selling_price = selling_price;
		strcpy(name, n);
		description = new char[strlen(desc) + 1];
		strcpy(description, desc);
	}

	// Copy Constructor - must pass its first argument by reference
	// Initializes an object using another object of the same class
	// If passed by value, we would have infinite recursion because
	// "to make a copy, you need to make a copy; that is, call the copy constructor"
	// Why to define a copy constructor if the copy constructor is working?
	// Deep copy is possible only with user defined copy constructor
	Product(Product &p) {
		id = p.id;
		strcpy(name, p.name);
		maximum_retail_price = p.maximum_retail_price;
		selling_price = p.selling_price;

		// Create a deep copy instead of shallow copy
//		description = p.description; // default constructor
		description = new char[strlen(p.description) + 1];
		strcpy(description, p.description);
	}

	// Memory leak if we destroyed the object without deleting the dynamically allocated memory
	~Product() {
		if (description != NULL) {
			delete [] description;
			description = NULL;
		}
	}

	// Copy Assignment Operator
	// Overriding the assignment operator for the Product object
	void operator=(Product &p) {
		id = p.id;
		strcpy(name, p.name);
		maximum_retail_price = p.maximum_retail_price;
		selling_price = p.selling_price;

		// Create a deep copy instead of shallow copy
//		description = p.description; // default constructor
		description = new char[strlen(p.description) + 1];
		strcpy(description, p.description);
	}

	void setMaximumRetailPrice(int price) {
		if (price > 0) {
			maximum_retail_price = price;
		}
	}

	void setSellingPrice(int price) {
		if (price > maximum_retail_price) {
			selling_price = maximum_retail_price;
		} else {
			selling_price = price;
		}
	}

	void setDescription(char *desc) {
		description = new char[strlen(desc) + 1];
		strcpy(description, desc);
	}

	int getMaximumRetailPrice() {
		return maximum_retail_price;
	}

	int getSellingPrice() {
		return selling_price;
	}

	void showDetails() {
		cout << "ID: " << id << endl;
		cout << "Name: " << name << endl;
		cout << "Description: " << description << endl;
		cout << "Maximum Retail Price: " << maximum_retail_price << endl;
		cout << "Selling Price: " << selling_price << endl;
	}
};

int main() {
	Product p;
	p.setMaximumRetailPrice(100);
	p.setSellingPrice(50);
//	cout << p.getMaximumRetailPrice() << endl;
//	cout << p.getSellingPrice() << endl;

	Product iphone(1, "IPhone XR", "Description", 20000, 12000);
//	cout << iphone.getMaximumRetailPrice() << endl;
//	cout << iphone.getSellingPrice() << endl;
	iphone.showDetails();

	// Uses Copy Constructor
	Product iphone_xr(iphone);
	iphone_xr.showDetails();
	Product iphone_11;
	iphone_11 = iphone; // Copy Assignment Operator
	iphone_11.showDetails();
	iphone_11.setSellingPrice(20);
	iphone_11.setDescription("Iphone 11 Description");

	iphone_xr.setDescription("Iphone XR Description");
	iphone_xr.setSellingPrice(10);
	cout << endl;
	iphone.showDetails();
	iphone_xr.showDetails();
	iphone_11.showDetails();

	return 0;
}
