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
// This file contains tests adding, getting and deleting
// Tasks in the Project container.
// -----------------------------------------------------

#include "../src/lib_catch.hpp"

#include <string>

#include "../src/lib_cxxopts.hpp"
#include "../src/lib_cxxopts_argv.hpp"

#include "../src/project.h"

SCENARIO("An empty Project can be constructed successfully", "[project]") {

  const std::string ident = "Test";

  GIVEN("the project identifier '" + ident + "'") {

    WHEN("a new Project object is constructed") {

      Project pObj1{ident};

      THEN("it will contain zero Tasks") { REQUIRE(pObj1.size() == 0); } // THEN

    } // WHEN

  } // GIVEN

} // SCENARIO

SCENARIO("Tasks can be added to and retrieved from a Project", "[project]") {

  const std::string ident = "Test";

  GIVEN("an empty Project object with identifier '" + ident + "'") {

    Project pObj1{ident};

    REQUIRE(pObj1.size() == 0);

    AND_GIVEN("an empty Task with identifier '" + ident + "'") {

      Task tObj1{ident};

      REQUIRE(tObj1.numTags() == 0);

      WHEN("adding the Task") {

        THEN("true is returned") {

          REQUIRE(pObj1.addTask(tObj1) == true);

          AND_THEN("the Project contains 1 Task") {

            REQUIRE(pObj1.size() == 1);

            AND_THEN("getting the Task using the ident '" + ident +
                     "' will return the expected object") {

              REQUIRE(pObj1.getTask(ident) == tObj1);
              REQUIRE_FALSE(pObj1.size() == 0);

            } // AND_THEN

          } // AND_THEN

          AND_GIVEN("another empty Task with the same ident, '" + ident + "'") {

            Task tObj2{ident};

            REQUIRE(tObj2.numTags() == 0);

            WHEN("adding the Task") {

              THEN("false is returned and the size of the Project will not "
                   "change") {

                REQUIRE(pObj1.addTask(tObj2) == false);
                REQUIRE(pObj1.size() == 1);

              } // THEN

            } // WHEN

          } // AND_GIVEN

          const std::string ident3 = "Test2";

          AND_GIVEN("another empty Task with the a different ident, '" +
                    ident3 + "'") {

            Task tObj3{ident3};

            REQUIRE(tObj3.numTags() == 0);

            WHEN("adding the Task") {

              THEN("true is returned and the size of the Project will be 2") {

                REQUIRE(pObj1.addTask(tObj3) == true);
                REQUIRE(pObj1.size() == 2);

                AND_THEN("getting the Task using the ident '" + ident3 +
                         "' will return the expected object") {

                  REQUIRE(pObj1.getTask(ident3) == tObj3);

                } // AND_THEN

              } // THEN

            } // WHEN

          } // AND_GIVEN

        } // THEN

      } // WHEN

    } // AND_GIVEN

  } // GIVEN

} // SCENARIO

SCENARIO("Tasks can be added to and deleted from a Project", "[project]") {

  const std::string ident = "Test";

  GIVEN("a empty Project object with identifier '" + ident + "'") {

    Project pObj1{ident};

    REQUIRE(pObj1.size() == 0);

    AND_GIVEN("an empty Task with identifier '" + ident + "") {

      Task tObj1{ident};

      REQUIRE(tObj1.numTags() == 0);

      WHEN("the entry is added") {

        THEN("true is returned") {

          REQUIRE(pObj1.addTask(tObj1) == true);

          AND_THEN("the Project contains 1 Task") {

            REQUIRE(pObj1.size() == 1);

            WHEN("getting the Task using the ident '" + ident + "'") {

              THEN("the Task object is returned") {

                REQUIRE(pObj1.getTask(ident) == tObj1);

              } // THEN

            } // WHEN

            WHEN("deleting a non-existent Task with ident 'blah'") {

              THEN("an std::out_of_range exception is thrown and the Project "
                   "will not change") {

                REQUIRE_THROWS_AS(pObj1.deleteTask("blah"), std::out_of_range);
                REQUIRE(pObj1.getTask(ident) == tObj1);
                REQUIRE(pObj1.size() == 1);

              } // THEN

            } // WHEN

            WHEN("deleting the added Task with ident '" + ident) {

              THEN("true is returned and the Project will be empty") {

                REQUIRE(pObj1.deleteTask(ident) == true);
                REQUIRE_THROWS_AS(pObj1.getTask(ident), std::out_of_range);
                REQUIRE(pObj1.size() == 0);

              } // THEN

            } // WHEN

          } // AND_THEN

        } // THEN

      } // WHEN

    } // AND_GIVEN

  } // GIVEN

} // SCENARIO
