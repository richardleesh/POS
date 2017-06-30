#ifndef SICT_NONPERISHABLE_H__
#define SICT_NONPERISHABLE_H__
#include <iostream>
#include <fstream>
#include "PosIO.h"
#include "POS.h"
#include "ErrorMessage.h"
#include "Item.h"

namespace sict{
	class NonPerishable : public Item {
	private:
		ErrorMessage _err;

	public:
		std::fstream& save(std::fstream& file)const;
		std::fstream& load(std::fstream& file);
		std::ostream& write(std::ostream& os, bool linear)const;
		std::istream& read(std::istream& is);
		
	};
};

#endif