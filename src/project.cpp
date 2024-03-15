// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2023/24)
// Department of Computer Science, Swansea University
//
// Author: <STUDENT NUMBER>
//
// Canvas: https://canvas.swansea.ac.uk/courses/44636
// -----------------------------------------------------

#include "project.h"

// TODO Write a constructor that takes one parameter, a string identifier and
// initialises the object and member data.
//
// Example:
//  Project p{"projectIdent"};

// TODO Write a function, size, that takes no parameters and returns an unsigned
// int of the number of Tasks in the Project contains.
//
// Example:
//  Project p{"projectIdent"};
//  auto size = p.size();

// TODO Write a function, getIdent, that returns the identifier for the Project.
//
// Example:
//  Project pObj{"projectIdent"};
//  auto ident = pObj.getIdent();

// TODO Write a function, setIdent, that takes one parameter, a string for a new
// Project identifier, and updates the member variable. It returns nothing.
//
// Example:
//  Project pObj{"projectIdent"};
//  pObj.setIdent("projectIdent2");

// TODO Write a function, newTask, that takes one parameter, a Task identifier,
// (a string) and returns the Task object as a reference. If an object with the
// same identifier already exists, then the existing object should be returned.
// Throw a std::runtime_error if the Task object cannot be inserted into the
// container for whatever reason.
//
// Example:
//  Project pObj{"projectIdent"};
//  pObj.newTask("newTaskName");

// TODO Write a function, addTask, that takes one parameter, a Task object, and
// returns true if the object was successfully inserted. If an object with the
// same identifier already exists, then:
//  - the tags should be merged
//  - completed status overwritten by the task being added
//  - dueDate overwritten by the task being added
//  - false should be returned.
//
// Example:
//  Project pObj{"projectIdent"};
//  Task tObj{"taskIdent"};
//  pObj.addItem(tObj);

// TODO Write a function, getTask, that takes one parameter, a Task identifier
// (a string) and returns the Task as a reference. If no Task exists, throw an
// appropriate exception.
//
// Hint:
//  See the test scripts for the exception expected.
//
// Example:
//  Project pObj{"projectIdent"};
//  pObj.newTask("newTaskName");
//  auto tObj = pObj.getTask("newTaskName");

// TODO Write a function, deleteTask, that takes one parameter, a Task
// identifier (a string), deletes it from the container, and returns true if the
// Task was deleted. If no Task exists, throw an appropriate exception.
//
// Example:
//  Project pObj{"projectIdent"};
//  pObj.newTask("newTaskName");
//  bool result = pObj.deleteTask("newTaskName");

// TODO Write an == operator overload for the Project class, such that two
// Project objects are equal only if they have the same identifier and same
// Tasks.
//
// Example:
//  Project pObj{"projectIdent1"};
//  pObj.newTask("newTaskName");
//  Project pObj1{"projectIdent2"};
//  if(pObj1 == pObj2) {
//    ...
//  }


// TODO Write a function, str, that takes no parameters and returns a
// std::string of the JSON representation of the data in the Project.
//
// See the coursework specification for how this JSON should look.
//
// Example:
//  Project pObj{"projectIdent"};
//  std::string s = pObj.str();
