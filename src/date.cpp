// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2023/24)
// Department of Computer Science, Swansea University
//
// Author: <STUDENT NUMBER>
//
// Canvas: https://canvas.swansea.ac.uk/courses/44636
// -----------------------------------------------------

#include "date.h"
// Provided default constructor to create an unitialised date.
Date::Date() : year(0), month(0), day(0), initialized(false) {}

// TODO write a function setDateFromString that takes a string argument in
// "YYYY-MM-DD" format and sets the appropriate member variables (year, month,
// day, and initialised). If dateString is empty reset the object to its
// uninitialised state (see default constructor). If dateString is not valid
// throw an appropriate exception.
// Example:
//  Date d = Date();
//  d.setDateString("2024-01-01");

// TODO Write a function, isInitialised, that takes no parameters and returns true
//  if the Date object is initialised, and false if it is NOT initialised.
// Example:
//  Date d = Date();
//  if(d.isInitialised()) {
//    ...
//  }

// TODO Write a function, str, that takes no parameters and returns a
// std::string representation of the Date object in YYYY-MM-DD format.  If the
// Date object is NOT initialised, return an empty string.
// Example:
//  Date d = Date();
//  d.setDate(2024,1,1);
//  std::cout << d.str() << std::endl;

// TODO create a function, setDate, that takes three parameters: year, month,
// day and sets the appropriate member variables to those parameters and also
// sets the initilized flag.
// Example:
//  Date d = Date();
//  d.setDate(2024, 1, 1);

// TODO Write a function, getYear, that takes no parameters and returns year
// member variable
//  Date d = Date();
//  auto year = d.getYear();

// TODO Write a function, getMonth, that takes no parameters and returns month
// member variable
//  Date d = Date();
//  auto month = d.getMonth();

// TODO Write a function, getDay, that takes no parameters and returns day
// member variable
//  Date d = Date();
//  auto day = d.getDay();

// TODO Write an == operator overload for the Date class, such that two
// Date objects are equal only if they have the same member variables.
// Example
//  Date d1 = Date();
//   d1.setDate(2024, 1, 1);
//   Date d2 = Date();
//   d2.setDate(2024, 1, 2);
//   if (d1 == d2) {
//     ...
//   }

// TODO Write an < operator overload for the Date class, that returns true if
// the first Date object is chronologically before the second date object.
// Otherwise return false. Note: You can ignore the 'initialised' member
// variable when drawing the comparison.

//  Date d1 = Date();
//   d1.setDate(2024, 1, 1);
//   Date d2 = Date();
//   d2.setDate(2024, 1, 2);
//   if (d1 < d2) {
//     ...
//   }
