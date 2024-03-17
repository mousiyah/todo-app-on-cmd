// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2023/24)
// Department of Computer Science, Swansea University
//
// Author: 2130288
//
// Canvas: https://canvas.swansea.ac.uk/courses/44636
// -----------------------------------------------------

#include <string>

#include "project.h"

// TODO Write a constructor that takes one parameter, a string identifier and
// initialises the object and member data.
//
// Example:
//  Project p{"projectIdent"};
Project::Project(std::string ident) : ident(std::move(ident)) {};

// TODO Write a function, size, that takes no parameters and returns an unsigned
// int of the number of Tasks in the Project contains.
//
// Example:
//  Project p{"projectIdent"};
//  auto size = p.size();
unsigned int Project::size() const noexcept {
    return tasks.size();
}

// TODO Write a function, getIdent, that returns the identifier for the Project.
//
// Example:
//  Project pObj{"projectIdent"};
//  auto ident = pObj.getIdent();
const std::string& Project::getIdent() const noexcept {
    return ident;
}

// TODO Write a function, setIdent, that takes one parameter, a string for a new
// Project identifier, and updates the member variable. It returns nothing.
//
// Example:
//  Project pObj{"projectIdent"};
//  pObj.setIdent("projectIdent2");
void Project::setIdent(std::string pIdent) noexcept {
    ident = std::move(pIdent);
}

// TODO Write a function, newTask, that takes one parameter, a Task identifier,
// (a string) and returns the Task object as a reference. If an object with the
// same identifier already exists, then the existing object should be returned.
// Throw a std::runtime_error if the Task object cannot be inserted into the
// container for whatever reason.
//
// Example:
//  Project pObj{"projectIdent"};
//  pObj.newTask("newTaskName");

Task& Project::newTask(const std::string& tIdent) {
    if (containsTask(tIdent)) {
        return tasks[ident];
    } else {
        auto [it, success] = tasks.emplace(ident, Task(ident));

        if (!success) {
            throw AddTaskError(tIdent);
        } else {
            return it->second;
        }
    }
}

bool Project::containsTask(const std::string& tIdent) const noexcept {
    return tasks.find(tIdent) != tasks.end();
}

const TaskContainer& Project::getTasks() const noexcept {
    return tasks;
}

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

bool Project::addTask(Task task) {
    std::string tIdent = task.getIdent();

    if (containsTask(tIdent)) {
        mergeTasks(tasks[tIdent], task);
        return false;
    } else {
        auto [it, success] = tasks.emplace(tIdent, task);

        if (!success) {
            throw AddTaskError(tIdent);
        } else {
            return true;
        }
    }
}

// TODO
void Project::mergeTasks(const Task& oldTask, const Task& newTask) {

}

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

Task& Project::getTask(const std::string& tIdent) {
    if (!containsTask(tIdent)) {
        throw NoTaskError(tIdent);
    } else {
        return tasks[tIdent];
    }
}

// TODO Write a function, deleteTask, that takes one parameter, a Task
// identifier (a string), deletes it from the container, and returns true if the
// Task was deleted. If no Task exists, throw an appropriate exception.
//
// Example:
//  Project pObj{"projectIdent"};
//  pObj.newTask("newTaskName");
//  bool result = pObj.deleteTask("newTaskName");

bool Project::deleteTask(const std::string& tIdent) {
    if (!containsTask(tIdent)) {
        throw NoTaskError(tIdent);
    } else {
        auto it = tasks.find(tIdent);
        tasks.erase(it);
    }
}

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

bool operator==(const Project& project1, const Project& project2) {
    return project1.ident == project2.ident && project1.tasks == project2.tasks;
}

// TODO Write a function, str, that takes no parameters and returns a
// std::string of the JSON representation of the data in the Project.
//
// See the coursework specification for how this JSON should look.
//
// Example:
//  Project pObj{"projectIdent"};
//  std::string s = pObj.str();

std::string Project::str() const {
    return json().dump();
}

// TODO
nlohmann::json Project::json() const {
    nlohmann::json json_data;
    json_data["ident"] = ident;
    json_data["tasks"] = tasks;
    return json_data;
}