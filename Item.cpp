#include<iostream>
#include<cstring>
#include "Item.h"
using namespace std;
namespace sict{
	
	Item::Item(){
		setEmpty();
	}

	Item::Item(const char* sk, const char* nam,
		double p, bool t){
		setEmpty();
		if (validSku(sk) && validPrice(p) && validName(nam)){
			sku(sk);
			price(p);
			name(nam);
			taxed(t);
		}
		else{
			setEmpty();
		}
	}


	Item::Item(const Item& it){
		sku(it._sku);
		price(it._price);
		name(it._name);
		taxed(it._taxed);
		quantity(it._quantity);
	}



	void Item::deAllocate(){
		delete[] _name;
		_name = (char*)0;
	}
	void Item::allocate(const char* name){
			_name = new char[strlen(name)+1];
	}
	

	void Item::setEmpty(){
		_sku[0] =0;
		_name = new char[2];
		_name[0]= 0;
		_price = 0.0;
		_taxed = true;
		_quantity = 0;
	}


	//validate data members
	bool Item::validSku(const char* sku) const{
		return (strlen(sku) <= MAX_SKU_LEN);
	}
	bool Item::validPrice(double price) const{
		return price >= 0;
	}

	bool Item::validName(const char* name) const{
		return strlen(name) > 0;
	}
	bool Item::validQuantity(int qty) const{
		return(qty >= 0);
	}





	Item& Item::operator=(const Item& it){
		if (this == &it){ 
			return *this;
		}
		else {
			deAllocate();
			allocate(it._name);
			sku(it._sku);
			price(it._price);
			name(it._name);
			taxed(it._taxed);
			quantity(it._quantity);
			return *this;
			
		}
	}


	Item::~Item(){
		deAllocate();
	}


	//setter functions
	void Item::sku(const char* sku){		
			strncpy(_sku, sku, 7);
			_sku[7] = '\0';
	}

	void Item::price(double price){
		_price = price;
		
	}

	void Item::name(const char* name){
		allocate(name);
		strcpy(_name, name);
		
	}
	void Item::taxed(bool taxed){
		_taxed = taxed;
	}
	void Item::quantity(int qty){
		if (validQuantity(qty)){ 
			_quantity = qty;
		}
		else{
			cout << "quatity value is invalid, quatity change failed";
		}
	}


	//getter functions
	const char* Item::sku() const{
		return _sku;
	}
	double Item::price() const{
		return _price;
	}
	const char* Item::name() const{
		return _name;
	}
	bool Item::taxed() const{
		return _taxed;
	}
	int Item::quantity() const{
		return _quantity;
	}
	double Item::cost() const{
		if (_taxed){
			return _price*(1+TAX);
		}
		else{
			return _price;
		}
	}
	bool Item::isEmpty() const{
		return _name == (char*)0;
	}


	bool Item::operator==(const char* sku){
		return strcmp(_sku, sku) == 0;
	}
	int Item::operator+=(int qty){
		return _quantity += qty;
	}
	int Item::operator-=(int qty){
		return _quantity -= qty;
	}

	double operator+=(double& q, const Item& item){
		return q=q + (item.cost() * item.quantity());
	}

	std::fstream& Item::save(std::fstream& file) const{
		file<< sku() << "," << name() << ","
			<< price() << "," << taxed() << "," << quantity() << endl;
		return file;
	}



	std::fstream& Item::load(std::fstream& file){
		char s[101];
		double p;
		int qty;
		bool bl;
		
		file.getline(s, 100, ',');
		s[100] = '\0';
		sku(s);
		file.getline(s, 100, ',');
		s[100] = '\0';
		name(s);
		file >> p;
		file.ignore(2000, ',');
		price(p);

		file >> bl;
		file.ignore(2000, ',');
		taxed(bl);

		file >> qty;
		file.ignore(2000, '\n');
		quantity(qty);

		return file;
	}


	std::ostream& Item::write(std::ostream& os, bool linear)const{
		if (linear == true) {
			return os << _sku << " " << _name << " " << _price << " " << _quantity << endl;
		}
		else{
			return os << _sku << " " << _name << " " << _price << " " << _quantity << endl;
		}
	}
	std::istream& Item::read(std::istream& is){
		is.ignore(2000, '\n');
		is.getline(_sku, 7, ' ');
		_sku[7] = '\0';
		deAllocate();
		is.getline(_name, 100, ' ');
		is>> _price >> _taxed >> _quantity;
		
		is.ignore(2000, '\n');

		return is;
	}

	std::ostream& operator << (std::ostream & os, const Item& it){
		if (it.sku()[0] == 0) {
			return os; 
		}
		else { 
			return it.write(os, true);
		}
	}
	std::istream& operator >> (std::istream & is, Item& it){
		return it.read(is);
	}


	std::fstream& operator << (std::fstream & os, const Item& it){
		return it.save(os);
	}
	std::fstream& operator >> (std::fstream & is, Item& it){
		return it.load(is);
	}


};
