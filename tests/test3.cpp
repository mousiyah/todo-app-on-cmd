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
// entries in the tag container of the Task class.
// -----------------------------------------------------

#include "../src/lib_catch.hpp"

#include <string>

#include "../src/lib_cxxopts.hpp"
#include "../src/lib_cxxopts_argv.hpp"

#include "../src/task.h"

SCENARIO("An empty Task can be constructed successfully", "[task]") {

  const std::string ident = "Test Task";

  GIVEN("the task identifier '" + ident + "'") {

    WHEN("a new Task object is constructed") {

      Task tObj1{ident};

      THEN("it will not be completed") {

        REQUIRE_FALSE(tObj1.isComplete());

        AND_THEN("it will have no tags") {
          REQUIRE(tObj1.numTags() == 0);
        } // AND_THEN

      } // THEN

    } // WHEN

  } // GIVEN

} // SCENARIO

SCENARIO("Tags can be added to and retrieved from a Task", "[task]") {

  const std::string ident = "Test Task";

  GIVEN("the task identifier '" + ident + "'") {

    WHEN("a new Task object is constructed") {

      Task tObj1{ident};

      std::string tag = "tagName";

      AND_GIVEN("a tag called '" + tag + "'") {

        WHEN("the tag is added") {

          THEN("true is returned") {

            REQUIRE(tObj1.addTag(tag));

            AND_THEN("it will have one tag(s)") {
              REQUIRE(tObj1.numTags() == 1);

              AND_THEN("The task contains the tag '" + tag + "'") {

                REQUIRE(tObj1.containsTag(tag));

              } // AND_THEN

            } // AND_THEN

            AND_GIVEN("another tag with the same name, '" + tag + "'") {

              WHEN("adding the tag") {

                THEN("false is returned and the number of the Tags will not "
                     "change") {

                  REQUIRE_FALSE(tObj1.addTag(tag));
                  REQUIRE(tObj1.numTags() == 1);

                } // THEN

              } // WHEN

            } // AND_GIVEN

            std::string tag2 = "tag2";

            AND_GIVEN("another tag with a different name: '" + tag2 + "'") {

              WHEN("adding the tag") {

                THEN("true is returned and the number of the tags will be 2") {

                  REQUIRE(tObj1.addTag(tag2) == true);
                  REQUIRE(tObj1.numTags() == 2);

                  AND_THEN("The task contains the tag '" + tag + "'") {

                    REQUIRE(tObj1.containsTag(tag));

                  } // AND_THEN

                } // THEN

              } // WHEN

            } // AND_GIVEN

          } // THEN

        } // WHEN

      } // AND_GIVEN

    } // WHEN

  } // GIVEN

} // SCENARIO

SCENARIO("Tags can be added to and deleted from a Task", "[task]") {

  const std::string ident = "Test Task";

  GIVEN("the task identifier '" + ident + "'") {

    WHEN("a new Task object is constructed") {

      Task tObj1{ident};

      std::string tag = "tagName";

      AND_GIVEN("a tag called '" + tag + "'") {

        WHEN("the tag is added") {

          THEN("true is returned") {

            REQUIRE(tObj1.addTag(tag));

            AND_THEN("it will have one tag(s)") {
              REQUIRE(tObj1.numTags() == 1);

              AND_THEN("The task contains the tag '" + tag + "'") {

                REQUIRE(tObj1.containsTag(tag));

              } // WHEN

              WHEN("deleting a non-existent entry with key 'blah'") {

                THEN("the Item will not change") {

                  REQUIRE_THROWS_AS(tObj1.deleteTag("blah"), std::out_of_range);
                  REQUIRE(tObj1.containsTag(tag));
                  REQUIRE(tObj1.numTags() == 1);

                } // THEN

              } // WHEN

              WHEN("deleting the added entry with tag '" + tag + "'") {

                THEN("the tags will be empty") {

                  REQUIRE(tObj1.deleteTag(tag));
                  REQUIRE(tObj1.numTags() == 0);

                } // THEN

              } // WHEN

            } // AND_THEN

          } // THEN

        } // WHEN

      } // AND_GIVEN

    } // WHEN

  } // GIVEN
} // SCENARIO