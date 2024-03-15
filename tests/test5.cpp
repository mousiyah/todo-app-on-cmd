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
// Project objects in the TodoList container.
// -----------------------------------------------------

#include "../src/lib_catch.hpp"

#include <string>

#include "../src/lib_cxxopts.hpp"
#include "../src/lib_cxxopts_argv.hpp"

#include "../src/todolist.h"

SCENARIO("An empty TodoList can be constructed successfully", "[todolist]") {

  GIVEN("nothing") {

    WHEN("a new TodoList object is constructed") {

      TodoList w{};

      THEN("it will contain zero Projects") { REQUIRE(w.size() == 0); } // THEN

    } // WHEN

  } // GIVEN

} // SCENARIO

SCENARIO("Project objects can be added to and retrieved from a TodoList",
         "[todolist]") {

  GIVEN("a empty TodoList object") {

    TodoList tlObj1{};

    REQUIRE(tlObj1.size() == 0);

    const std::string ident = "Test";

    AND_GIVEN("an empty Project with identifier '" + ident + "'") {

      Project pObj1{ident};

      REQUIRE(pObj1.size() == 0);

      WHEN("adding the Project") {

        THEN("true is returned") {

          REQUIRE(tlObj1.addProject(pObj1) == true);

          AND_THEN("the TodoList contains 1 Project") {

            REQUIRE(tlObj1.size() == 1);
            REQUIRE_FALSE(tlObj1.size() == 0);

            AND_THEN("getting the Project using the ident '" + ident +
                     "' will return the expected object") {

              REQUIRE(tlObj1.getProject(ident) == pObj1);

            } // AND_THEN

          } // AND_THEN

          AND_GIVEN("adding a second empty Project with the same ident, '" +
                    ident) {

            Project pObj2{ident};

            REQUIRE(pObj2.size() == 0);

            WHEN("adding the Project") {

              THEN("false is returned and the size of the TodoList will not "
                   "change") {

                REQUIRE_FALSE(tlObj1.addProject(pObj2));
                REQUIRE(tlObj1.size() == 1);
                REQUIRE_FALSE(tlObj1.size() == 0);

              } // THEN

            } // WHEN

          } // AND_GIVEN

          const std::string ident3 = "Test2";
          Project pObj3{ident3};

          AND_GIVEN("another empty Project with a different ident, '" +
                    ident3) {

            REQUIRE(pObj3.size() == 0);

            WHEN("the Project is added") {

              THEN("true is returned and the size of the TodoList will be 2") {

                REQUIRE(tlObj1.addProject(pObj3) == true);
                REQUIRE(tlObj1.size() == 2);
                REQUIRE_FALSE(tlObj1.size() == 0);

                AND_THEN("getting the Project using the ident '" + ident3 +
                         "' will return the expected object") {

                  REQUIRE(tlObj1.getProject(ident3) == pObj3);

                } // AND_THEN

              } // THEN

            } // WHEN

          } // AND_GIVEN

        } // THEN

      } // WHEN

    } // AND_GIVEN

  } // GIVEN

} // SCENARIO

SCENARIO("Project objects can be added to and deleted from a TodoList",
         "[todolist]") {

  GIVEN("an empty TodoList object") {

    TodoList tlObj1{};

    REQUIRE(tlObj1.size() == 0);

    const std::string ident = "Test";

    WHEN("a Project with identifier '" + ident + "' can be added") {

      Project pObj1{ident};

      REQUIRE(pObj1.size() == 0);

      REQUIRE(tlObj1.addProject(pObj1) == true);

      THEN("the TodoList contains 1 Project") {

        REQUIRE(tlObj1.size() == 1);
        REQUIRE_FALSE(tlObj1.size() == 0);

      } // THEN

      THEN("the Project can be retrieved by the ident '" + ident + "'") {

        REQUIRE(tlObj1.getProject(ident) == pObj1);

      } // THEN

      THEN("deleting the existent Project ('" + ident +
           "') will leave the TodoList empty") {

        REQUIRE(tlObj1.deleteProject(ident));
        REQUIRE_THROWS_AS(tlObj1.getProject(ident), std::out_of_range);
        REQUIRE(tlObj1.size() == 0);

      } // THEN

    } // WHEN

  } // GIVEN

} // SCENARIO
