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
// This file contains tests saving JSON files from a
// the TodoList.
// -----------------------------------------------------

#include "../src/lib_catch.hpp"

#include <fstream>
#include <sstream>
#include <string>

#include "../src/lib_cxxopts.hpp"
#include "../src/lib_cxxopts_argv.hpp"

#include "../src/todolist.h"

SCENARIO("A TodoList object can save to a JSON file", "[wallet]") {

  const std::string filePath = "./tests/testdatabasealt.json";

  auto fileExists = [](const std::string &path) {
    return std::ifstream(path).is_open();
  };

  auto readFileContents = [](const std::string &path) {
    // Not a robust way to do this, but here it doesn't matter so much, if it
    // goes wrong we'll fail the test anyway…
    std::stringstream ss{std::stringstream::out};
    ss << std::ifstream(path).rdbuf();
    return ss.str();
  };

  auto writeFileContents = [](const std::string &path,
                              const std::string &contents) {
    // Not a robust way to do this, but here it doesn't matter so much, if it
    // goes wrong we'll fail the test anyway…
    std::ofstream f{path};
    f << contents;
  };

  GIVEN("a valid path to an empty database JSON file") {

    // Reset the file...
    REQUIRE(fileExists(filePath));
    REQUIRE_NOTHROW(writeFileContents(filePath, "{}"));

    WHEN("a new empty TodoList object is constructed") {

      TodoList tlObj1{};
      REQUIRE(tlObj1.size() == 0);

      const std::string tIdent1 = "task1";
      const std::string tIdent2 = "task2";

      const std::string pIdent1 = "project1";
      const std::string pIdent2 = "project2";

      const std::string tag1 = "tag1";
      const std::string tag2 = "tag2";

      AND_WHEN("the TodoList object is populated with dummy data") {

        Task tObj1{tIdent1};
        Task tObj2{tIdent2};

        Date d = Date();
        d.setDate(2023, 11, 11);

        tObj1.setComplete(true);
        tObj2.setComplete(false);

        tObj1.setDueDate(d);
        tObj2.setDueDate(d);

        tObj1.addTag(tag1);
        tObj1.addTag(tag2);
        tObj2.addTag(tag1);

        REQUIRE(tObj1.numTags() == 2);
        REQUIRE(tObj2.numTags() == 1);

        Project pObj1{pIdent1};
        Project pObj2{pIdent2};

        pObj1.addTask(tObj1);
        pObj1.addTask(tObj2);
        pObj2.addTask(tObj1);

        REQUIRE(pObj1.size() == 2);
        REQUIRE(pObj2.size() == 1);

        tlObj1.addProject(pObj1);
        tlObj1.addProject(pObj2);

        REQUIRE(tlObj1.size() == 2);

        THEN("the saving to file will not throw an exception") {

          REQUIRE_NOTHROW(tlObj1.save(filePath));

          AND_THEN("the file contents will be correct") {

            REQUIRE(readFileContents(filePath).find(
                        "{\"project1\":{\"task1\":{\"completed\":true,"
                        "\"dueDate\":\"2023-11-11\",\"tags\":[\"tag1\","
                        "\"tag2\"]},\"task2\":{\"completed\":false,\"dueDate\":"
                        "\"2023-11-11\",\"tags\":[\"tag1\"]}},\"project2\":{"
                        "\"task1\":{\"completed\":true,\"dueDate\":\"2023-11-"
                        "11\",\"tags\":[\"tag1\",\"tag2\"]}}}") == 0);

          } // AND_THEN

        } // THEN

      } // AND_WHEN

    } // WHEN

  } // GIVEN

} // SCENARIO
