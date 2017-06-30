// add your information in here, 
// use dateTester.h comments an a template

#ifndef SICT_DATE_H__
#define SICT_DATE_H__
#include <iostream>
#include <fstream>

#define NO_ERROR (0)
#define CIN_FAILED (1)
#define YEAR_ERROR (2)
#define MON_ERROR (3)
#define DAY_ERROR (4)
#define HOUR_ERROR (5)
#define MIN_ERROR (6)

namespace sict{


   class Date{
   private:
	  int _year;
	  int _mon;
	  int _day;
	  int _hour;
	  int _min;
	  int _readErrorCode;
	  bool _dateOnly;

	  int value() const;
	  void errCode(int errorCode);
	  

   public:
	  Date();
	  Date(int year, int mon, int day);
	  Date(int year, int mon, int day, int hour, int min = 0);

	  void set();
	  int mdays()const;
	  

	  bool operator==(const Date& D) const;
	  bool operator!=(const Date& D) const;
	  bool operator< (const Date& D) const;
	  bool operator> (const Date& D) const;
	  bool operator<=(const Date& D) const;
	  bool operator>=(const Date& D) const;

	  int errCode() const;
	  bool bad() const;
	  bool dateOnly() const;
	  void dateOnly(bool value);

	  int getYear() const;
	  int getMonth() const;
	  int getDay() const;

	  std::istream& read(std::istream& is = std::cin);
	  std::ostream& write(std::ostream& ostr = std::cout) const;
	  std::fstream& read(std::fstream& fs );
	 
   };

   
   std::ostream& operator<< (std::ostream& os, Date& d);
   std::istream& operator>> (std::istream& is, Date& dis);
 
   
};
#endif