#include <iomanip>
#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;
#include "Date.h"
#include "POS.h"
//#define Debug
namespace sict{

  void Date::set(){
    time_t t = time(NULL);
    tm lt = *localtime(&t);
    _day = lt.tm_mday;
    _mon = lt.tm_mon + 1;
    _year = lt.tm_year + 1900;
    if (dateOnly()){
      _hour = _min = 0;
    }
    else{
      _hour = lt.tm_hour;
      _min = lt.tm_min;
    }
  }

  int Date::value()const{
    return _year * 535680 + _mon * 44640 + _day * 1440 + _hour * 60 + _min;
  }


  int Date::mdays()const{
    int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
    int mon = _mon >= 1 && _mon <= 12 ? _mon : 13;
    mon--;
    return days[mon] + int((mon == 1)*((_year % 4 == 0) && (_year % 100 != 0)) || (_year % 400 == 0));
  }

  //default constructor, set Date to system date and set hour and minute to 0
  Date::Date(){
	 _dateOnly = false;
	 set();
  }

  Date::Date(int year, int mon, int day){
	 _dateOnly = true;
	 _year = year;
	 _mon = mon;
	 _day = day;
	 _hour = 0;
	 _min = 0;
	 _readErrorCode = NO_ERROR;
  }

  Date::Date(int year, int mon, int day, int hour, int min){
	  _dateOnly = false;
	  _year = year;
	  _mon = mon;
	  _day = day;
	  _hour = hour;
	  _min = min;
	  _readErrorCode = NO_ERROR;

  }


  bool Date::operator==(const Date& D) const{
	  return value() == D.value();
  }
  bool Date::operator!=(const Date& D) const{
	  return value() != D.value();
  }
  bool Date::operator< (const Date& D) const{
	  return value() < D.value();
  }
  bool Date::operator> (const Date& D) const{
	  return value() > D.value();
  }
  bool Date::operator<=(const Date& D) const{
	  return value() <= D.value();
  }
  bool Date::operator>=(const Date& D) const{
	  return value() >= D.value();
  }


  //get error code
  int Date::errCode() const{
	 return _readErrorCode;
  }

  //check date status,return ture if _readErrorCode is not equal to zero
  bool Date::bad() const{
	 if (_readErrorCode != 0) {
		return true;
	 }
	 else {
		return false;
	 }
  }

  //get dateOnly status
  bool Date::dateOnly() const{
	 return _dateOnly;
  }

  //set dateonly to "value"
  void Date::dateOnly(bool value){
	 _dateOnly = value;
  }

  int Date::getYear() const{
	  return _year;
  }
  int Date::getMonth() const {
	  return _mon;
  }
  int Date::getDay() const {
	  return _day;

  }

  std::istream& Date::read(std::istream& is){
	  
	  if (_dateOnly){
		  is >> setw(4) >> _year;
		  is.ignore(2000, '/');
		  is >> setw(2) >> _mon;
		  is.ignore(2000, '/');
		  is >> setw(2) >> _day;
		  is.ignore(2000, '\n');
	  }
	  else {
		  is >> setw(4) >> _year;
		  is.ignore(2000, '/');
		  is >> setw(2) >> _mon;
		  is.ignore(2000, '/');
		  is >> setw(2) >> _day;
		  is.ignore(2000, ',');
		  is >> setw(2) >> _hour;
		  is.ignore(2000, ':');
		  is >> setw(2) >> _min;
		  is.ignore(2000, '\n');
		  
	  }
	  
#ifdef Debug
	  cout <<"input is : " << _year << "," << _mon << "," << _day << "," << endl;
#endif
	  if (is.fail()) {
		  _readErrorCode = CIN_FAILED;
	  }
	  else {
		  _readErrorCode = NO_ERROR;

		  if (_year <2000 || _year >= 2030) {
			  _readErrorCode = YEAR_ERROR;
		  }


		  else if (_mon < 1 || _mon >12) {
			  _readErrorCode = MON_ERROR;
		  }

		  else if (_day < 1 || _day >mdays()) {
			  _readErrorCode = DAY_ERROR;
		  }

		  else if (_hour < 0 || _hour > 23) {
			  _readErrorCode = HOUR_ERROR;
		  }

		  else if (_min < 0 || _min > 59) {
			  _readErrorCode = MIN_ERROR;
		  }
	  }		  
	  return is;
  }

  std::fstream& Date::read(std::fstream& fs){
	  //char a[100];
	  if (_dateOnly){
		  fs >>_year;		  fs.ignore(2000, '/');
		  if (fs.fail()) cout << "file out is failed";
		  fs >>  _mon;
		  fs.ignore(2000, '/');
		  if (fs.fail()) cout << "file out is failed";
		  fs >> _day;
		  if (fs.fail()) cout << "file out is failed";
		  //fs.ignore(2000, '\n');
		 // fs.getline(a, 100, '\n');
		  //cout << a;
		  if (fs.fail()) cout << "file out is failed";
	  }
	  else {
		  fs >> setw(4) >> _year;
		  fs.ignore(2000, '/');
		  fs >> setw(2) >> _mon;
		  fs.ignore(2000, '/');
		  fs >> setw(2) >> _day;
		  fs.ignore(2000, ',');
		  fs >> setw(2) >> _hour;
		  fs.ignore(2000, ':');
		  fs >> setw(2) >> _min;
		 // fs.ignore(2000, '\n');
	  }

#ifdef Debug
	  cout << "input fs : " << _year << "," << _mon << "," << _day << "," << endl;
#endif
	  if (fs.fail()) {
		  _readErrorCode = CIN_FAILED;
	  }
	  else {
		  _readErrorCode = NO_ERROR;

		  if (_year <2000 || _year >= 2030) {
			  _readErrorCode = YEAR_ERROR;
		  }


		  else if (_mon < 1 || _mon >12) {
			  _readErrorCode = MON_ERROR;
		  }

		  else if (_day < 1 || _day >mdays()) {
			  _readErrorCode = DAY_ERROR;
		  }

		  else if (_hour < 0 || _hour > 23) {
			  _readErrorCode = HOUR_ERROR;
		  }

		  else if (_min < 0 || _min > 59) {
			  _readErrorCode = MIN_ERROR;
		  }
	  }
	  return fs;
  }
  
  std::ostream& Date::write(std::ostream& ostr) const{
	  if (_dateOnly == false){
		  ostr.setf(ios::right);
		  ostr << _year <<"/"<< setw(2) << setfill('0') << _mon <<"/"<< setw(2) << _day << ", ";
		  ostr << setw(2) << _hour <<":"<< setw(2) << _min;
	  }
	  else {
		  ostr.setf(ios::right);
		  ostr << _year << "/" << setw(2) << setfill('0') << _mon << "/" << setw(2) << _day;
	  }
	  return ostr;
  }

  std::ostream& operator<< (std::ostream& os, Date& d) {
	  return d.write(os);
  }
  std::istream& operator>> (std::istream& is, Date& dis){
	  return dis.read(is);
  }


};
