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
// This file tests 371todo output for the database
// argument and 'create' value of the action argument.
// This test works by calling on your program to create
// a project, task, and a tag, and each time
// calls upon your program to load the JSON file to
// check the project/task/tag exists.
// -----------------------------------------------------

#include "../src/lib_catch.hpp"

#include <fstream>
#include <iostream>
#include <string>

#include "../src/lib_cxxopts.hpp"
#include "../src/lib_cxxopts_argv.hpp"

#include "../src/371todo.h"

SCENARIO(
    "The database and action program arguments can be parsed correctly "
    "such that a file can be opened, read, parsed, data added, and written to",
    "[args]") {

  const std::string filePath = "./tests/testdatabasealt.json";

  auto fileExists = [](const std::string &path) {
    return std::ifstream(path).is_open();
  };

  auto writeFileContents = [](const std::string &path,
                              const std::string &contents) {
    // Not a robust way to do this, but here it doesn't matter so much, if it
    // goes wrong we'll fail the test anyway…
    std::ofstream f{path};
    f << contents;
  };

  GIVEN("a valid path to a reset database JSON file") {

    // Reset the file...
    REQUIRE(fileExists(filePath));
    REQUIRE_NOTHROW(writeFileContents(
        filePath,
        "{ \"CSC371\": { \"Lab Assignment 1\": { \"completed\": true, "
        "\"dueDate\": \"2024-11-13\", \"tags\": [ \"uni\", \"c\", "
        "\"programming\" ] }, \"Lab Assignment 6\": { \"completed\": false, "
        "\"dueDate\": \"2024-11-23\", \"tags\": [ \"uni\", \"c++\", "
        "\"programming\", \"standard library\" ] } }, \"CSC307\": { \"Write "
        "Mobile App\": { \"completed\": true, \"dueDate\": \"2023-11-30\", "
        "\"tags\": [ \"uni\", \"programming\", \"android\" ] } } }"));

    const std::string testProject = "TestProject";
    const std::string testTask = "TestTask";
    const std::string testTag = "TestTag";

    WHEN("the db program argument is '" + filePath +
         "', the action program argument is 'create'") {

      AND_WHEN("and the project program argument is '" + testProject + "'") {

        Argv argvObj({"test", "--db", filePath.c_str(), "--action", "create",
                      "--project", testProject.c_str()});
        auto **argv = argvObj.argv();
        auto argc = argvObj.argc();

        THEN("no exception is thrown") {

          REQUIRE_NOTHROW(App::run(argc, argv));

          AND_WHEN("loading the saved file into a new TodoList object") {

            TodoList wObj1{};
            REQUIRE(wObj1.size() == 0);
            REQUIRE_NOTHROW(wObj1.load(filePath));

            THEN("the new TodoList will contain the Project object") {

              REQUIRE_NOTHROW(wObj1.getProject(testProject));
              REQUIRE(wObj1.getProject(testProject).size() == 0);

            } // THEN

            AND_WHEN("and the task program argument is '" + testTask + "'") {

              Argv argvObj({"test", "--db", filePath.c_str(), "--action",
                            "create", "--project", testProject.c_str(),
                            "--task", testTask.c_str()});
              auto **argv = argvObj.argv();
              auto argc = argvObj.argc();

              THEN("no exception is thrown") {

                REQUIRE_NOTHROW(App::run(argc, argv));

                AND_WHEN("loading the saved file into a new TodoList object") {

                  TodoList wObj2{};
                  REQUIRE(wObj2.size() == 0);
                  REQUIRE_NOTHROW(wObj2.load(filePath));

                  THEN("the new TodoList will contain the Project and Task "
                       "objects") {

                    REQUIRE_NOTHROW(wObj2.getProject(testProject));
                    REQUIRE(wObj2.getProject(testProject).size() == 1);
                    REQUIRE_NOTHROW(
                        wObj2.getProject(testProject).getTask(testTask));
                    REQUIRE(wObj2.getProject(testProject)
                                .getTask(testTask)
                                .numTags() == 0);

                  } // THEN

                  AND_WHEN("and the tag program argument is '" + testTag +
                           "'") {

                    Argv argvObj({
                        "test",
                        "--db",
                        filePath.c_str(),
                        "--action",
                        "create",
                        "--project",
                        testProject.c_str(),
                        "--task",
                        testTask.c_str(),
                        "--tag",
                        testTag.c_str(),
                    });
                    auto **argv = argvObj.argv();
                    auto argc = argvObj.argc();

                    THEN("no exception is thrown") {

                      REQUIRE_NOTHROW(App::run(argc, argv));

                      AND_WHEN("loading the saved file into a new TodoList "
                               "object") {

                        TodoList wObj3{};
                        REQUIRE(wObj3.size() == 0);
                        REQUIRE_NOTHROW(wObj3.load(filePath));

                        THEN("the new TodoList will contain the Project and "
                             "Task objects and tag") {

                          REQUIRE_NOTHROW(wObj3.getProject(testProject));
                          REQUIRE(wObj3.getProject(testProject).size() == 1);
                          REQUIRE_NOTHROW(
                              wObj3.getProject(testProject).getTask(testTask));
                          REQUIRE(wObj3.getProject(testProject)
                                      .getTask(testTask)
                                      .numTags() == 1);
                          REQUIRE(wObj3.getProject(testProject)
                                      .getTask(testTask)
                                      .containsTag(testTag));

                        } // THEN

                      } // AND_WHEN

                    } // THEN

                  } // AND_WHEN

                } // AND_WHEN

              } // THEN

            } // AND_WHEN

          } // AND_WHEN

        } // THEN

      } // AND_WHEN

    } // WHEN

  } // GIVEN

} // SCENARIO
