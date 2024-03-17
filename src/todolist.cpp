// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2023/24)
// Department of Computer Science, Swansea University
//
// Author: 2130288
//
// Canvas: https://canvas.swansea.ac.uk/courses/44636
// -----------------------------------------------------
#include <string>
#include <fstream>

#include "todolist.h"

// TODO Write a TodoList constructor that takes no parameters and constructs an
//  empty todolist.
//
// Example:
//  TodoList tObj{};

TodoList::TodoList() {}

// TODO Write a function, size, that takes no parameters and returns an unsigned
//  int of the number of projects the TodoList contains.
//
// Example:
//  TodoList tObj{};
//  auto size = tObj.size();

unsigned int TodoList::size() const noexcept{
    return projects.size();
}

const ProjectContainer& TodoList::getProjects() const noexcept {
    return projects;
}

// TODO Write a function, newProject, that takes one parameter, a project
//  identifier, and returns the Project object as a reference. If an object
//  with the same identifier already exists, then the existing object should be
//  returned. Throw a std::runtime_error if the Project object cannot be
//  inserted into the container.
//
// Example:
//  TodoList tObj{};
//  tObj.newProject("projectIdent");

Project& TodoList::newProject(const std::string& ident) {

    if (containsProject(ident)) {
        return projects[ident];
    } else {
        auto [it, success] = projects.emplace(ident, Project(ident));

        if (!success) {
            throw AddProjectError(ident);
        } else {
            return it->second;
        }
    }
}

bool TodoList::containsProject(const std::string& ident) {
    return projects.find(ident) != projects.end();
}

// TODO Write a function, addProject, that takes one parameter, a Project
//  object, and returns true if the object was successfully inserted. If an
//  object with the same identifier already exists, then the contents should be
//  merged (see also Project::addTask) and then return false. Throw a
//  std::runtime_error if the Project object cannot be inserted into the
//  container for whatever reason.
//
// Example:
//  TodoList tObj{};
//  Project cObj{"projectIdent"};
//  tObj.addProject(cObj);

bool TodoList::addProject(const Project& project) {

    std::string ident = project.getIdent();

    if (containsProject(ident)) {
        mergeProjects(projects[ident], project);
        return false;
    } else {
        auto [it, success] = projects.emplace(ident, project);

        if (!success) {
            throw AddProjectError(ident);
        } else {
            return true;
        }
    }
}

// TODO
void TodoList::mergeProjects(const Project& oldProject, const Project& newProject) {

}

// TODO Write a function, getProject, that takes one parameter, a Project
//  identifier and returns the Project. If no Project exists, throw an
//  appropriate exception.
//
// Example:
//  TodoList tObj{};
//  tObj.newProject("projectIdent");
//  auto cObj = tObj.getProject("projectIdent");

Project& TodoList::getProject(const std::string& ident) {
    
    if(containsProject(ident)) {
        return projects[ident];
    } else {
        throw NoProjectError(ident);
    }

}

// TODO Write a function, deleteProject, that takes one parameter, a Project
//  identifier, and deletes it from the container, and returns true if the
//  Project was deleted. If no Project exists, throw an appropriate exception.
//
// Example:
//  TodoList tObj{};
//  tObj.newProject("projectIdent");
//  tObj.deleteProject("projectIdent");

bool TodoList::deleteProject(const std::string& ident) {

    if(containsProject(ident)) {
        auto erased = projects.erase(ident);
        return erased > 0;
    } else {
        throw NoProjectError(ident);
    }
    
}

// TODO Write a function, load, that takes one parameter, a std::string,
//  containing the filename for the database. Open the file, read the contents,
//  and populates the container for this TodoList. If the file does open throw
//  an appropriate exception (either std::runtime_error or a derived class).
//
// A note on clashes:
//  If you encounter two projects with the same key, or two tasks with the same
//  key within the same project, you may choose whichever project/task is parsed
//  by the nlohmann json library. The json spec on duplicate keys is undefined, so
//  you can default to the behaviour of the nlohmann json library.
//
// JSON formatting:
//  The JSON file has the following format (see the sample database.json file
//  also provided with the coursework framework):
// {
//     "Project 1" : {
//         "Task 1":  {
//             "completed": true,
//             "due": "2024-11-23",
//             "tags" : ["uni",
//                       "c++",
//                       "programming",
//                       "standard library"
//                       ...
//                      ]
//             ...
//         },
//         "Task 2":  {
//             "completed": false,
//             "tags" : ["uni",
//                       "c++",
//                       "programming",
//                       "inheritance"
//                       ...
//                      ]
//         },
//         ...
//     },
//     "Project 2": {
//         "Task 1": {
//             "completed": true
//         }
//         ...
//     }
// }
//
// More help:
//  To help you with this function, I've selected the nlohmann::json
//  library that you must use for your coursework. Read up on how to use it
//  here: https://github.com/nlohmann/json. You may not use any other external
//  library other than the one I have provided. You may choose to process the
//  JSON yourself without the help of the library but I guarantee this will be
//  more work.
//
//  Understanding how to use external libraries is part of this coursework! You
//  will need to use this file to deserialize the JSON from string
//  to the JSON object provided by this library. Don't just look at the code
//  provided below, or in the README on the GitHub and despair. Google search,
//  look around, try code out in a separate file to all figure out how to use
//  this library.
//
//  Once you have deserialized the JSON string into an object, you will need to
//  loop through this object, constructing Project and Task objects according
//  to the JSON data in the file.
//
// Example:
//  TodoList tObj{};
//  tObj.load("database.json");

void TodoList::load(const std::string& filename) {

    auto file = FileIO::openFile(filename);

    nlohmann::json jsonData;
    file >> jsonData;

    parse(jsonData);
    
}

void TodoList::parse(const nlohmann::json& json) {
    for (const auto& [pIdent, jsonProject] : json.items()) {

        Project& project = newProject(pIdent);

        if (jsonProject.is_object()) {
            project.parse(jsonProject);
        }
    }
}


// TODO Write a function, save, that takes one parameter, the path of the file
//  to write the database to. The function should serialise the TodoList object
//  as JSON.
//
// Example:
//  TodoList tObj{};
//  tObj.load("database.json");
//  ...
//  tObj.save("database.json");

void TodoList::save(const std::string& filename) {
    // TODO: Implement saving to JSON file
}

// TODO Write an == operator overload for the TodoList class, such that two
//  TodoList objects are equal only if they have the exact same data.
//
// Example:
//  TodoList tObj1{};
//  TodoList tObj2{};
//  if(tObj1 == tObj2) {
//    ...
//  }

bool operator==(const TodoList& todoList1, const TodoList& todoList2) {
    return todoList1.getProjects() == todoList2.getProjects();
}

// TODO Write a function, str, that takes no parameters and returns a
//  std::string of the JSON representation of the data in the TodoList.
//
// Hint:
//  See the coursework specification for how this JSON should look.
//
// Example:
//  TodoList tObj{};
//  std::string s = tObj.str();

std::string TodoList::str() const {
    // TODO: Implement converting TodoList to JSON string
    return "";
}





// FileIO.cpp
std::ifstream FileIO::openFile(const std::string& filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        throw FileOpenError(filename);
    }
    return file;
}