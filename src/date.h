// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2023/24)
// Department of Computer Science, Swansea University
//
// Author: 2130288
//
// Canvas: https://canvas.swansea.ac.uk/courses/44636
// -----------------------------------------------------
// An Date class that contains the following member variables
// - year
// - month
// - day
// - initialised
//
// A Date object should only be set to initialised if it is a valid date.
// Otherwise it is should remain unintialised.
// -----------------------------------------------------

#ifndef DATE_H
#define DATE_H

#include "lib_json.hpp"

class Date {
  
private:
  unsigned int year, month, day;
  bool initialised;

public:
  explicit Date();
  ~Date() = default;

  void setDateFromString(const std::string& dateString);

  bool isValidDate(unsigned int year, unsigned int month, unsigned int day) const;

  bool isInitialised() const noexcept;
  void setUninitialised() noexcept;

  std::string str() const;

  void setDate(unsigned int year, unsigned int month, unsigned int day) noexcept;

  unsigned int getYear() const noexcept;
  unsigned int getMonth() const noexcept;
  unsigned int getDay() const noexcept;

  friend bool operator==(const Date& date1, const Date& date2) noexcept;
  friend bool operator<(const Date& date1, const Date& date2) noexcept;

};



struct InvalidDateError : public std::runtime_error {
  explicit InvalidDateError(const std::string &date)
      : std::runtime_error("Invalid Date format '" + date + "'") {}

  ~InvalidDateError() override = default;
};



#endif // DATE_H
