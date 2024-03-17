// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2023/24)
// Department of Computer Science, Swansea University
//
// Author: 2130288
//
// Canvas: https://canvas.swansea.ac.uk/courses/44636
// -----------------------------------------------------

#include <string>

#include "task.h"

// TODO Write a constructor that takes one parameter, a string identifier
//  and initialises the object and member data.
//
// Example:
//  Task tObj{"Task Name"};

Task::Task(std::string ident) : ident(std::move(ident)) {};

// TODO Write a function, getIdent, that returns the identifier for the Task.
//
// Example:
//  Task tObj{"Task Name"};
//  auto ident = tObj.getIdent();

const std::string& Task::getIdent() const noexcept {
    return ident;
}

// TODO Write a function, setIdent, that takes one parameter, a string for a new
//  Task identifier, and updates the member variable. It returns nothing.
//
// Example:
//  Task tObj{"Task Name"};
//  auto ident = tObj.setIdent("New Task Name");

void Task::setIdent(std::string ident) noexcept {
    ident = std::move(ident);
}

// TODO Write a function, addTag, that takes one parameters, a tag
//  string and returns true if the entry was inserted into the
//  container or false if the tag already existed.
//
// Example:
//  Task tObj{"Task Name"};
//  tObj.addTag("tag");

bool Task::addTag(const std::string& tag) {
    if (containsTag(tag)) {
        return false;
    } else {
        tags.emplace(tag);
        return true;
    }
}

// TODO Write a function, deleteTag, that takes one parameter, a tag
// string, deletes it from the container, and returns true if the tag
// string was deleted. If no tag exists with that name, throw an appropriate
// exception.
//
// Example:
//  Task tObj{"Task Name"};
//  tObj.addTag("tag");
//  tObj.deleteTag("tag");

bool Task::deleteTag(const std::string& tag){
    if(!containsTag(tag)) {
        throw NoTagError(tag);
    } else {
        tags.erase(tag);
        return true;
    }
}

// TODO Write a function, numTags, that takes no parameters and returns an
// unsigned int of the number of tags in the Task contains.
//
// Example:
//  Task tObj{"Task Name"};
//  tObj.numTags();

unsigned int Task::numTags() const noexcept {
    return tags.size();
}

// TODO Write a function, containsTag, that takes one parameter, a tag string.
// If the tag exists, return true. Otherwise return false.
//
// Example:
//  Task tObj{"Task Name"};
//  tObj.addTag("tag");
//  tObj.findTag("tag");

bool Task::containsTag(const std::string& tag) const noexcept{
    return tags.find(tag) != tags.end();
}

// TODO Write a function, getDueDate, that returns the due date for the Task.
//
// Example:
//  Task tObj{"Task Name"};
//  tObj.getDueDate();

Date Task::getDueDate() const noexcept {
    return dueDate;
}

// TODO Write a function, setDueDate, that takes one parameter, a Date for
// a new due date, and updates the member variable. It returns nothing.
//
// Example:
//  Task tObj{"Task Name"};
//  Date d = Date();
//  tObj.setDueDate(d);

void Task::setDueDate(const Date& dueDate) noexcept {
    this->dueDate = dueDate;
}

// TODO Write a function, setComplete, that takes one parameter, a bool for
// a new completed state, and updates the member variable. It returns nothing.
//
// Example:
//  Task tObj{"Task Name"};
//  tObj.setComplete(true);

void Task::setComplete(bool complete) noexcept {
    this->complete = complete;
}

// TODO Write a function, isComplete, that returns the completed state for the
// Task.
//
// Example:
//  Task tObj{"Task Name"};
//  if(tObj.isComplete()) {
//   ...
//  }

bool Task::isComplete() const noexcept {
    return complete;
}

// TODO Write an == operator overload for the Task class, such that two
// Tasks objects are equal only if they have the same identifier, dueDate,
// completed state, and tags.
//
// Example:
//  Task tObj1{"Task Name"};
//  Task tObj2{"Task Name"};
//  if(tObj1 == tObj2) {
//   ...
//  }

bool operator==(const Task& task1, const Task& task2) noexcept {
    return task1.ident == task2.ident &&
           task1.dueDate == task2.dueDate &&
           task1.complete == task2.complete &&
           task1.tags == task2.tags;
}

// TODO Write a function, str, that takes no parameters and returns a
//  std::string of the JSON representation of the data in the Item.
//
// See the coursework specification for how this JSON should look.
//
// Example:
//  Item iObj{"itemIdent"};
//  std::string s = iObj.str();

std::string Task::str() const {
    nlohmann::json taskJson;
    taskJson["identifier"] = ident;
    taskJson["due_date"] = dueDate.str();
    taskJson["complete"] = complete;

    nlohmann::json tagsJson;
    for (const auto& tag : tags) {
        tagsJson.push_back(tag);
    }
    taskJson["tags"] = tagsJson;

    return taskJson.dump();
}

void Task::parse(const nlohmann::json& json) {
    if (json.contains("completed")) {
        setComplete(json["completed"].get<bool>());
    }
    if (json.contains("due")) {
        setDueDate(json["due"].get<std::string>());
    }
    if (json.contains("tags")) {
        for (const auto& tag : json["tags"]) {
            addTag(tag.get<std::string>());
        }
    }
}