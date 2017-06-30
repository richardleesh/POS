#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include <math.h>
#include "Item.h"
#include "NonPerishable.h"
#include "ErrorMessage.h"

using namespace std;

namespace sict{


	std::fstream& NonPerishable::save(std::fstream& file)const{
		file << "N," << sku() << "," << name() << ","
			<< price() << "," << taxed() << "," << quantity() << endl;
		return file;
	}


	std::fstream& NonPerishable::load(std::fstream& file){
		char s[101];
		double p;
		int qty;
		bool bl;
		char ty;
		
		file.getline(s,100,',');
		s[100] = '\0';
		sku(s);

		file.getline(s, 100, ',');
		s[100] = '\0';
		name(s);

		file >> p;
		file >> ty;
		price(p);
		
		file >> bl;		
		taxed(bl);
		file >> ty;

		file >> qty;
		quantity(qty);	

		return file;		

	}


	std::ostream& NonPerishable::write(std::ostream& os, bool linear)const{
		os.fill(' ');
		os.precision(2);
		os.setf(ios::fixed);
		if (!_err.isClear()){
			return os << _err.message();
		}
		else{
			if (linear) {
				os << " " << setw(MAX_SKU_LEN) << left << sku() << "|"
					<< setw(20) << left << name() << "|"
					<< setw(7) << setprecision(2) << right << price() << "|";
				if (taxed()){
					os << setw(3) << " t " << "|"
						<< setw(4) << right << quantity() << "|"
						<< setw(9) << setprecision(2) << right
						<< round(((quantity()*price()*(1 + TAX)+0.001) * 100)) / 100 << "|";
				}
				else {
					os << setw(3) << " " << "|"
						<< setw(4) << right << quantity() << "|"
						<< setw(9) << setprecision(2) << right
						<< round(((quantity()*price() + 0.001) * 100)) / 100 << "|";
				}


				return os;
			}
			else{
				if (taxed()){
					return os << "Name:" << endl << name() << endl
						<< "Sku: " << sku() << endl
						<< "Price: " << price() << endl
						<< "Price after tax: " << price()*(1 + TAX) << endl
						<< "Quantity: " <<quantity() << endl
						<< "Total Cost: " << price()*quantity()*(1+TAX)<< endl;
				}
				else{
					return os << "Sku: " << sku() << endl
						<< "Name:" << endl << name() << endl
						<< "Price: " << price() << endl
						<< "Quantity: " << quantity() << endl
						<< "Total Cost: " << price()*quantity()<< endl;
						
				}
			}
		}
	}


	std::istream& NonPerishable::read(std::istream& is){
		_err.clear();
		char s[101];
		double p;
		int qty;
		char yn;
		
		cout << "NonPerishable Item Entry:" << endl;
		is.ignore(2000, '\n');
		cout << "Sku: ";		
		is.getline(s, 100, '\n');
		s[100] = '\0';
		sku(s);
		//is.ignore(2000, '\n');

		cout << "Name:" << endl;
		is.getline(s, 100, '\n');
		s[100] = '\0';
		name(s);
		//is.ignore(2000, '\n');

		cout << "Price: ";
		is >> p;
		if (is.fail()) { 
			_err.message("Invalid Price Entry");
			return is; 
		}
		//is.ignore(2000, '\n');		
		price(p);

		cout << "Taxed: ";
		is >>yn;
		if (yn == 'y'){
			taxed(true);
		}		
		else if (yn == 'n')	{ 
			taxed(false); 
		}
		else{
			_err.message("Invalid Taxed Entry, (y)es or (n)o");
			is.setstate(ios::failbit);
			return is;
		}
		//is.ignore(2000, ',');
		


		cout << "Quantity: ";
		is >> qty;
		if (is.fail()) {
			_err.message("Invalid Quantity Entry");
			return is;
		}
		//is.ignore(2000, '\n');
		quantity(qty);


		return is;
	}

	

};