#ifndef SICT_PERISHABLE_H__
#define SICT_PERISHABLE_H__
#include <iostream>
#include <fstream>
#include "PosIO.h"
#include "POS.h"
#include "ErrorMessage.h"
#include "Item.h"
#include "Date.h"

namespace sict{
	class Perishable : public Item {
	private:
		ErrorMessage _err;
		Date _expiry;

	public:
		Perishable();
		const Date& expiry()const;
		void expiry(const Date &value);
		std::fstream& save(std::fstream& file)const;
		std::fstream& load(std::fstream& file);
		std::ostream& write(std::ostream& os, bool linear)const;
		std::istream& read(std::istream& is);

	};
};

#endif