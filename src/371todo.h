// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2023/24)
// Department of Computer Science, Swansea University
//
// Author: <STUDENT NUMBER>
//
// Canvas: https://canvas.swansea.ac.uk/courses/44636
// -----------------------------------------------------
// This file contains declarations for the helper
// functions used for initialising and running 371todo.
// -----------------------------------------------------

#ifndef _371TODO_H
#define _371TODO_H

#include <string>

#include "lib_cxxopts.hpp"
#include "todolist.h"

namespace App {

// TODO: Enter your student number here!
const std::string STUDENT_NUMBER = "987654";

// Enums (short for enumerations) are similar to their Java implementation.
// It is a user-defined type, used to assign names to internal constants
// in code, instead of simply passing in integers/strings etc.
//
// For example, functions can take a value/constant from a specific enum
// and use it in a switch statement, doing different things
//
// As such, it is a useful way for us to specify information in both a
// machine and human-readable format.
//
// Unlike Java, enums in C++ only map to integer values. You can either let
// the compiler generate the values automatically, in which it allocates a
// unique integer (0-indexed). Or, you can set the value by giving the name
// followed by = <value> (e.g. CREATE=0).
//
// This enum specifies the four different values we support in the action
// program argument.
enum Action { CREATE, JSON, DELETE, UPDATE };

int run(int argc, char *argv[]);

cxxopts::Options cxxoptsSetup();

App::Action parseActionArgument(cxxopts::ParseResult &args);

std::string getJSON(TodoList &tl);
std::string getJSON(TodoList &tl, const std::string &p);
std::string getJSON(TodoList &tl, const std::string &p, const std::string &t);
std::string getJSON(TodoList &tl, const std::string &p, const std::string &task,
                    const std::string &tag);

} // namespace App

#endif // _371TODO_H
