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

Task::Task(const std::string& tIdent) : ident(tIdent) {
    complete = false;
};

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

void Task::setIdent(std::string tIdent) noexcept {
    ident = std::move(tIdent);
}

// TODO Write a function, addTag, that takes one parameters, a tag
//  string and returns true if the entry was inserted into the
//  container or false if the tag already existed.
//
// Example:
//  Task tObj{"Task Name"};
//  tObj.addTag("tag");

bool Task::addTag(const std::string& tag) {
    auto it = findTag(tag);

    if (it != tags.end()) {
        return false;
    }

    try {
        tags.push_back(std::move(tag));
    } catch (const std::exception& e) {
        throw e;
    }

    return true;
}

bool Task::addTags(const TagContainer& newTags) {
    bool allTagsAdded = true;
    for (const auto& tag : newTags) {
        if (!addTag(tag)) {
            allTagsAdded = false;
        }
    }
    return allTagsAdded;
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

bool Task::deleteTag(const std::string& tag) {
    auto it = findTag(tag);
    if (it == tags.end()) {
        throw NoTagError(tag);
    }

    try {
        tags.erase(it);
    } catch (const std::exception& e) {
        throw e;
    }
    return true;
}

bool Task::deleteTags(const TagContainer& tagsToDelete) {
    bool allTagsDeleted = true;
    for (const auto& tag : tagsToDelete) {
        if (!deleteTag(tag)) {
            allTagsDeleted = false;
        }
    }
    return allTagsDeleted;
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
    return findTag(tag) != tags.end();
}

TagContainer::const_iterator Task::findTag(const std::string &tag) const noexcept {
    return std::find(tags.begin(), tags.end(), tag);
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

bool operator==(const Task& task1, const Task& task2) noexcept{
    return task1.ident == task2.ident &&
           task1.dueDate == task2.dueDate &&
           task1.complete == task2.complete &&
           task1.tags == task2.tags;
}

//  - Merge two tasks
//  - the tags should be merged
//  - completed status overwritten by the task being added
//  - dueDate overwritten by the task being added
void Task::mergeTask(const Task& newTask) noexcept{

    for (const auto& tag : newTask.tags) {
        if (!containsTag(tag)) {
            addTag(tag);
        }
    }

    complete = newTask.complete;
    dueDate = newTask.dueDate;
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
    return json().dump();
}

nlohmann::json Task::json() const {
    nlohmann::json jsonTask;
    
    jsonTask["dueDate"] = dueDate.str();
    jsonTask["completed"] = complete;

    nlohmann::json tagsJson;
    for (const auto& tag : tags) {
        tagsJson.push_back(tag);
    }
    jsonTask["tags"] = tagsJson;

    return jsonTask;
}

void Task::parse(const nlohmann::json& json) {
    if (json.contains("completed")) {
        setComplete(json["completed"].get<bool>());
    }
    if (json.contains("dueDate")) {
        Date* date = new Date();
        date->setDateFromString(json["dueDate"].get<std::string>());
        setDueDate(*date);
    }
    if (json.contains("tags")) {
        for (const auto& tag : json["tags"]) {
            addTag(tag.get<std::string>());
        }
    }
}