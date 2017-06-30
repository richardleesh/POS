#ifndef SICT_ITEM_H__
#define SICT_ITEM_H__
#include <iostream>
#include <fstream>
#include "PosIO.h"
#include "POS.h"

namespace sict{
	class Item : public PosIO {
	private:
		char _sku[MAX_SKU_LEN + 1];
		char* _name;
		double _price;
		bool _taxed;
		int _quantity;

		bool validSku(const char* sku) const;
		bool validPrice(double price) const;
		bool validName(const char* name) const;
		bool validQuantity(int qty) const;
		void setEmpty();

		

	public:
		Item();
		Item(const char* sku, const char* name, double price, bool taxed = true);
		Item(const Item& it);
		virtual ~Item();

		void allocate(const char* name);
		void deAllocate();

		Item& operator=(const Item& it);
		

		void sku(const char* sk);
		void price(double p);
		void name(const char* nam);
		void taxed(bool t);
		void quantity(int qty);
		

		const char* sku() const;
		double price() const;
		const char* name() const;
		bool taxed() const;
		int quantity() const;
		double cost() const;
		bool isEmpty() const;

		bool operator==(const char* sku);
		int operator+=(int qty);
		int operator-=(int qty);


		std::fstream& save(std::fstream& file) const;
		std::fstream& load(std::fstream& file);
		std::ostream& write(std::ostream& os, bool linear)const;
		std::istream& read(std::istream& is);
		
	};

	double operator+=(double& q, const Item& item);
	std::ostream& operator << (std::ostream & os, const Item& it);
	std::istream& operator >> (std::istream & is, Item& it);
	std::fstream& operator << (std::fstream & os, const Item& it);
	std::fstream& operator >> (std::fstream & is, Item& it);

};

#endif