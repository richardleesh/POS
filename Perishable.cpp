#include <iostream>
#include <cstring>
#include <iomanip>
#include <math.h>
#include "Perishable.h"
#include "Item.h"
#include "Date.h"
#include "ErrorMessage.h"

using namespace std;

namespace sict{
	Perishable::Perishable(){
		_expiry.dateOnly(true);
	}

	const Date& Perishable::expiry()const{
		return _expiry;
	}

	void Perishable::expiry(const Date &value){
		_expiry = value;
	}


	std::fstream& Perishable::save(std::fstream& file)const{
		file << "P," << sku() << "," << name() << ","
			<< price() << "," << taxed() << "," << quantity()
			<< ",";
		file << (_expiry.getYear()) << "/"
			<<_expiry.getMonth() <<"/"<<_expiry.getDay() << endl;
		return file;
	}


	std::fstream& Perishable::load(std::fstream& file){
		char s[101];
		double p;
		int qty;
		bool bl;
		Date d;
		char ty;
		//file.getline(s,100,',');
		file.getline(s, 100, ',');
		s[100] = '\0';
		sku(s);
		file.getline(s, 100, ',');
		s[100] = '\0';
		name(s);
		file >> p;		
		price(p);
		file >> ty;

		file >> bl;
		taxed(bl);
		file >> ty;


		file >> qty;
		quantity(qty);
		file >> ty;

	/*	int y;
		int m;
		int d1;
		file >> y;
		file.ignore(2000, '/');
		file >> m;
		file.ignore(2000, '/');
		file >> d ;
		file.ignore(2000, '\n');
*/
		//if (file.fail()) cout << "file out is failed";
		//file.ignore(2000, ',');
		if (file.fail()) cout << "file out is failed";
		_expiry.read(file);
		return file;

	}


	std::ostream& Perishable::write(std::ostream& os, bool linear)const{
		os.fill(' ');
		os.precision(2);
		os.setf(ios::fixed);
		if (!_err.isClear()){
			return os << _err.message();
		}
		else{
			if (linear) {
				os << " "<<setw(MAX_SKU_LEN) << left << sku() << "|"
					<< setw(20) << left << name() << "|"
					<< setw(7) << setprecision(2) << right << price() << "|";
				if (taxed()){
					os << setw(3) << " tp" << "|"
						<< setw(4) << right << quantity() << "|"
						<< setw(9) << setprecision(2) << right
						<< round(((quantity()*price()*(1 + TAX) + 0.001) * 100)) / 100 << "|";
				}
				else {
					os << setw(3) <<right<< "p" << "|"
						<< setw(4) << right << quantity() << "|"
						<< setw(9) << setprecision(2) << right
						<< round(((quantity()*price() + 0.001) * 100)) / 100 << "|";
				}


				return os;
			}
			else{
				if (taxed()){
					os << "Name:" << endl << name() << endl
						<< "Sku: " << sku() << endl

						<< "Price: " << price() << endl
						<< "Price after tax: " << price()*(1 + TAX) << endl
						<< "Quantity: " << quantity() << endl
						<< "Total Cost: " << price()*quantity()*(1 + TAX) << endl
						<< "Expiry date: ";
					_expiry.write(os);
					os << endl;
					return os;
				}
				else{
					os << "Name:" << endl << name() << endl 
						<< "Sku: " << sku() << endl
						<< "Price: " << price() << endl
						<< "Price after tax: N/A" << endl
						<< "Quantity: " << quantity() << endl
						<< "Total Cost: " << price()*quantity() << endl
						<< "Expiry date: ";
					_expiry.write(os);
					os << endl;
					return os;
				}
			}
		}
	}


	std::istream& Perishable::read(std::istream& is){
		_err.clear();
		char s[101];
		double p;
		int qty;
		char yn;

		cout << "Perishable Item Entry: " << endl;

		cout << "Sku: ";
		is.ignore(2000, '\n');
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
		is >> yn;
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
		
		cout << "Expiry date (YYYY/MM/DD): ";
		is >> _expiry;
		if (_expiry.errCode() != 0){
			switch (_expiry.errCode()){
			case 1 :
				_err.message("Invalid Date Entry");
				break;
			case 2:
				_err.message("Invalid Year in Date Entry");
				is.setstate(ios::failbit);
				break;
			case 3:
				_err.message("Invalid Month in Date Entry");
				is.setstate(ios::failbit);
				break;
			case 4:
				_err.message("Invalid Day in Date Entry");
				is.setstate(ios::failbit);
				break;
			}
			return is;
		}
		return is;
	}



};