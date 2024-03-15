// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2023/24)
// Department of Computer Science, Swansea University
//
// Author: Thomas Reitmaier
//         thomas.reitmaier@swansea.ac.uk
//         Martin Porcheron (adapted from)
//         m.a.w.porcheron@swansea.ac.uk
//
// Canvas: https://canvas.swansea.ac.uk/courses/44636
// -----------------------------------------------------
// Catch2 — https://github.com/catchorg/Catch2
// Catch2 is licensed under the BOOST license
// -----------------------------------------------------
// This file contains tests for creating and setting
// Date objects.

#include "../src/lib_catch.hpp"

#include <string>

#include "../src/lib_cxxopts.hpp"
#include "../src/lib_cxxopts_argv.hpp"

#include "../src/date.h"

SCENARIO("An empty Date can be constructed successfully", "[date]") {

  WHEN("a new Date object is constructed") {

    Date dObj1{};

    THEN("it will NOT be initilised and year, month, day are set to 0") {

      REQUIRE(dObj1.isInitialised() == false);
      REQUIRE(dObj1.getDay() == 0);
      REQUIRE(dObj1.getMonth() == 0);
      REQUIRE(dObj1.getYear() == 0);

    } // THEN

  } // WHEN

} // SCENARIO

SCENARIO("A custom date can be set", "[date]") {

  Date dObj1 = Date();

  GIVEN("A default constructed (uninitalised) Date object") {

    REQUIRE_FALSE(dObj1.isInitialised());

    unsigned int year = 2024;
    unsigned int month = 1;
    unsigned int day = 2;

    AND_GIVEN("a year '" + std::to_string(year) + "' and month '" +
              std::to_string(month) + "'" + "' and day '" +
              std::to_string(day) + "'") {

      WHEN("the year, month, day are set") {
        REQUIRE_NOTHROW(dObj1.setDate(year, month, day));

        THEN("the Date object is initialised") {

          REQUIRE(dObj1.isInitialised());

          AND_THEN("getting the year will return the expected value '" +
                   std::to_string(year) + "'") {

            REQUIRE(dObj1.getYear() == year);

            AND_THEN("getting the month will return the expected value '" +
                     std::to_string(month) + "'") {

              REQUIRE(dObj1.getMonth() == month);

              AND_THEN("getting the day will return the expected value '" +
                       std::to_string(day) + "'") {

                REQUIRE(dObj1.getDay() == day);

              } // AND_THEN

            } // AND_THEN

          } // AND_THEN

        } // THEN

      } // WHEN

    } // AND_GIVEN

  } // GIVEN

} // SCENARIO

SCENARIO("The < operator on Date evaluates its contents correctly", "[date]") {

  Date dObj1 = Date();
  Date dObj2 = Date();

  GIVEN("Two default constructed (uninitalised) Date object") {

    REQUIRE_FALSE(dObj1.isInitialised());
    REQUIRE_FALSE(dObj2.isInitialised());

    AND_THEN("The two default constructed objects are equals") {

      REQUIRE(dObj1 == dObj2);

      unsigned int year = 2024;
      unsigned int month = 1;
      unsigned int day = 2;

      AND_GIVEN("a year '" + std::to_string(year) + "' and month '" +
                std::to_string(month) + "'" + "' and day '" +
                std::to_string(day) + "'") {

        WHEN("the year, month, day are set on both objects") {
          REQUIRE_NOTHROW(dObj1.setDate(year, month, day));
          REQUIRE_NOTHROW(dObj2.setDate(year, month, day));

          THEN("the Date objects are initialised") {

            REQUIRE(dObj1.isInitialised());
            REQUIRE(dObj2.isInitialised());

            AND_THEN("getting the year will return the expected value '" +
                     std::to_string(year) + "'") {

              REQUIRE(dObj1.getYear() == year);
              REQUIRE(dObj2.getYear() == year);

              AND_THEN("getting the month will return the expected value '" +
                       std::to_string(month) + "'") {

                REQUIRE(dObj1.getMonth() == month);
                REQUIRE(dObj2.getMonth() == month);

                AND_THEN("getting the day will return the expected value '" +
                         std::to_string(day) + "'") {

                  REQUIRE(dObj1.getDay() == day);
                  REQUIRE(dObj2.getDay() == day);

                } // AND_THEN

                AND_THEN("The two date objects equal and not less than one or "
                         "the other") {
                  REQUIRE_FALSE(dObj1 < dObj2);
                  REQUIRE_FALSE(dObj2 < dObj1);
                } // AND_THEN

                auto month2 = month + 1;
                AND_GIVEN("A third date object set to a different a year '" +
                          std::to_string(year) + "' and month '" +
                          std::to_string(month2) + "'" + "' and day '" +
                          std::to_string(day) + "'") {
                  Date dObj3 = Date();
                  REQUIRE_NOTHROW(dObj3.setDate(year, month2, day));

                  AND_THEN(
                      "The first two objects are less than the third object") {
                    REQUIRE(dObj1 < dObj3);
                    REQUIRE(dObj2 < dObj3);
                    REQUIRE_FALSE(dObj3 < dObj2);
                    REQUIRE_FALSE(dObj3 < dObj1);
                  } // AND_THEN
                }

              } // AND_THEN

            } // AND_THEN

          } // THEN

        } // WHEN

      } // AND_GIVEN
    }   // AND_THEN

  } // GIVEN

} // SCENARIO
SCENARIO("The == operator on Date evaluates its contents correctly", "[date]") {

  Date dObj1 = Date();
  Date dObj2 = Date();

  GIVEN("Two default constructed (uninitalised) Date object") {

    REQUIRE_FALSE(dObj1.isInitialised());
    REQUIRE_FALSE(dObj2.isInitialised());

    AND_THEN("The two default constructed objects are equals") {

      REQUIRE(dObj1 == dObj2);

      unsigned int year = 2024;
      unsigned int month = 1;
      unsigned int day = 2;

      AND_GIVEN("a year '" + std::to_string(year) + "' and month '" +
                std::to_string(month) + "'" + "' and day '" +
                std::to_string(day) + "'") {

        WHEN("the year, month, day are set on both objects") {
          REQUIRE_NOTHROW(dObj1.setDate(year, month, day));
          REQUIRE_NOTHROW(dObj2.setDate(year, month, day));

          THEN("the Date objects are initialised") {

            REQUIRE(dObj1.isInitialised());
            REQUIRE(dObj2.isInitialised());

            AND_THEN("getting the year will return the expected value '" +
                     std::to_string(year) + "'") {

              REQUIRE(dObj1.getYear() == year);
              REQUIRE(dObj2.getYear() == year);

              AND_THEN("getting the month will return the expected value '" +
                       std::to_string(month) + "'") {

                REQUIRE(dObj1.getMonth() == month);
                REQUIRE(dObj2.getMonth() == month);

                AND_THEN("getting the day will return the expected value '" +
                         std::to_string(day) + "'") {

                  REQUIRE(dObj1.getDay() == day);
                  REQUIRE(dObj2.getDay() == day);

                } // AND_THEN

                AND_THEN("The two date objects are equal") {
                  REQUIRE(dObj1 == dObj2);
                } // AND_THEN

                auto day2 = 3;
                AND_GIVEN("A third date object set to a different a year '" +
                          std::to_string(year) + "' and month '" +
                          std::to_string(month) + "'" + "' and day '" +
                          std::to_string(day2) + "'") {
                  Date dObj3 = Date();
                  REQUIRE_NOTHROW(dObj3.setDate(year, month, day2));

                  AND_THEN("The third objects does not equal, the first two") {
                    REQUIRE_FALSE(dObj1 == dObj3);
                    REQUIRE_FALSE(dObj3 == dObj2);
                  } // AND_THEN
                }

              } // AND_THEN

            } // AND_THEN

          } // THEN

        } // WHEN

      } // AND_GIVEN
    }   // AND_THEN

  } // GIVEN

} // SCENARIO

// NEXT make hidden
SCENARIO(
    "An properly formatted but invalid date can not be set from date string",
    "[date]") {

  Date dObj1 = Date();

  GIVEN("A default constructed (uninitalised) Date object") {

    REQUIRE_FALSE(dObj1.isInitialised());

    unsigned int year = 2024;
    unsigned int month = 22;
    unsigned int day = 22;
    const std::string dateString = std::to_string(year) + "-" +
                                   std::to_string(month) + "-" +
                                   std::to_string(day);

    AND_GIVEN("an invalid date string in the form of '" + dateString + "'") {

      WHEN("the year, month, day are set") {
        REQUIRE_THROWS(dObj1.setDateFromString(dateString));

        THEN("the Date object is uninitialised") {

          REQUIRE_FALSE(dObj1.isInitialised());

          AND_THEN("getting the year will return the uninitialised value '" +
                   std::to_string(0) + "'") {

            REQUIRE(dObj1.getYear() == 0);

            AND_THEN("getting the month will return the unitialised value '" +
                     std::to_string(0) + "'") {

              REQUIRE(dObj1.getMonth() == 0);

              AND_THEN("getting the day will return the uninitialised value '" +
                       std::to_string(0) + "'") {

                REQUIRE(dObj1.getDay() == 0);

              } // AND_THEN

            } // AND_THEN

          } // AND_THEN

        } // THEN

      } // WHEN

    } // AND_GIVEN

  } // GIVEN

} // SCENARIO

// NEXT make hidden
SCENARIO(
    "An inproperly formatted and invalid date can not be set from date string",
    "[date]") {

  Date dObj1 = Date();

  GIVEN("A default constructed (uninitalised) Date object") {

    REQUIRE_FALSE(dObj1.isInitialised());

    const std::string dateString = "2024,11,10";

    AND_GIVEN("an invalid date string in the form of '" + dateString + "'") {

      WHEN("the year, month, day are set") {
        REQUIRE_THROWS(dObj1.setDateFromString(dateString));

        THEN("the Date object is uninitialised") {

          REQUIRE_FALSE(dObj1.isInitialised());

        } // THEN

      } // WHEN

    } // AND_GIVEN

  } // GIVEN

} // SCENARIO
SCENARIO("A custom date can be set from a date string", "[date]") {

  Date dObj1 = Date();

  GIVEN("A default constructed (uninitalised) Date object") {

    REQUIRE_FALSE(dObj1.isInitialised());

    unsigned int year = 2024;
    unsigned int month = 11;
    unsigned int day = 22;
    const std::string dateString = std::to_string(year) + "-" +
                                   std::to_string(month) + "-" +
                                   std::to_string(day);

    AND_GIVEN("a date string in the form of '" + dateString + "'") {

      WHEN("the year, month, day are set") {
        REQUIRE_NOTHROW(dObj1.setDateFromString(dateString));

        THEN("the Date object is initialised") {

          REQUIRE(dObj1.isInitialised());

          AND_THEN("getting the year will return the expected value '" +
                   std::to_string(year) + "'") {

            REQUIRE(dObj1.getYear() == year);

            AND_THEN("getting the month will return the expected value '" +
                     std::to_string(month) + "'") {

              REQUIRE(dObj1.getMonth() == month);

              AND_THEN("getting the day will return the expected value '" +
                       std::to_string(day) + "'") {

                REQUIRE(dObj1.getDay() == day);

              } // AND_THEN

            } // AND_THEN

          } // AND_THEN

        } // THEN

      } // WHEN

    } // AND_GIVEN

  } // GIVEN

} // SCENARIO

SCENARIO("A custom date can be reset from an empty date string", "[date]") {

  Date dObj1 = Date();

  GIVEN("A default constructed (uninitalised) Date object") {

    REQUIRE_FALSE(dObj1.isInitialised());

    unsigned int year = 2024;
    unsigned int month = 11;
    unsigned int day = 22;
    const std::string dateString = std::to_string(year) + "-" +
                                   std::to_string(month) + "-" +
                                   std::to_string(day);

    AND_GIVEN("a date string in the form of '" + dateString + "'") {

      WHEN("the year, month, day are set") {
        REQUIRE_NOTHROW(dObj1.setDateFromString(dateString));

        THEN("the Date object is initialised") {

          REQUIRE(dObj1.isInitialised());

          const std::string emptyDateString = "";
          AND_GIVEN("an empty date string \"\"") {
            WHEN("the date is set to the empty date string") {

              REQUIRE_NOTHROW(dObj1.setDateFromString(emptyDateString));

              THEN("the Date object is uninitialised") {
                REQUIRE_FALSE(dObj1.isInitialised());
              }
            }
          }

        } // THEN

      } // WHEN

    } // AND_GIVEN

  } // GIVEN

} // SCENARIO
