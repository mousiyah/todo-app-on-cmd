// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2023/24)
// Department of Computer Science, Swansea University
//
// Author: 2130288
//
// Canvas: https://canvas.swansea.ac.uk/courses/44636
// -----------------------------------------------------

#include <algorithm>
#include <exception>
#include <iostream>
#include <string>

#include "371todo.h"
#include "lib_cxxopts.hpp"

// TODO Complete this function. You have been provided some skeleton code which
//  retrieves the database file name from cxxopts.
//  1. Load the database file by calling load() on a TodoList object
//  2. Parse the 'action' argument to decide what action should be taken
//     (json, create, delete, update).  'json' is the easiest to implement, and
//     'update' is the hardest. The details of how these arguments work is in
//     the coursework specification.
//  3. Save the updated TodoList object to the JSON file if there have been
//     changes (calling save() on the TodoList object).
//
// Some commented out code has been provided. Using some of this will be
// demonstrated in the coursework video on Canvas. Remember, this coursework is
// meant to be challenging and testing your understanding of programming in C++.
// Part of the challenge is figuring things out on your own. That is a major
// part of software development.
//
// Example:
//  int main(int argc, char *argv[]) { return App::run(argc, argv); }
int App::run(int argc, char *argv[]) {
  auto options = App::cxxoptsSetup();
  auto args = options.parse(argc, argv);

  // Print the help usage if requested
  if (args.count("help")) {
    std::cout << options.help() << '\n';
    return 0;
  }

  // Open the database and construct the TodoList
  const std::string db = args["db"].as<std::string>();
  TodoList tlObj{};

  // Only uncomment this once you have implemented the load function!
  tlObj.load(db);

  const Action a = parseActionArgument(args);
  extractArgs(args);

  switch (a) {
    case Action::CREATE:
      createAction(tlObj);
      break;

    case Action::JSON:
      std::cout << getJSON(tlObj);
      break;

    case Action::UPDATE:
      throw std::runtime_error("update not implemented");
      break;

    case Action::DELETE:
      deleteAction(tlObj);
      break;

    default:
      throw std::runtime_error("unknown action not implemented");
  }
  
  tlObj.save(db);

  return 0;
}

// Create a cxxopts instance. You do not need to modify this function.
//
// Example:
//  auto options = App::cxxoptsSetup();
//  auto args = options.parse(argc, argv);
cxxopts::Options App::cxxoptsSetup() {
  cxxopts::Options cxxopts("371todo", "Student ID: " + STUDENT_NUMBER + "\n");

  cxxopts.add_options()(
      "db", "Filename of the 371todo database",
      cxxopts::value<std::string>()->default_value("database.json"))(

      "action", "Action to take, can be: 'create', 'json', 'update', 'delete'.",
      cxxopts::value<std::string>())(

      "project",
      "Apply action (create, json, update, delete) to a project. If you want to "
      "add a project, set the action argument to 'create' and the project "
      "argument to your chosen project identifier.",
      cxxopts::value<std::string>())(

      "task",
      "Apply action (create, json, update, detele) to a task. If you want to add "
      "a task, set the action argument to 'create', the project argument to your "
      "chosen project identifier and the task argument to the task identifier).",

      cxxopts::value<std::string>())(

      "tag",
      "Apply action (create, json, delete) to a tag.  If you want to add an tag, "
      "set the action argument to 'create', the project argument to your chosen "
      "project identifier, the task argument to your chosen task identifier, and "
      "the tag argument to a single tag 'tag' or comma seperated list of tags: "
      "'tag1,tag2').  If you are simply retrieving a tag through the json action "
      "(and checking that it exists), set the tag argument to the tag name "
      "(e.g. 'example tag'). The action update is unsupported here.",
      cxxopts::value<std::string>())(

      "completed",
      "When creating or updating a task, set the completed flag to change the "
      "task's state to completed. This flag is not compatible in combination "
      "with the incomplete flag.",
      cxxopts::value<bool>())(

      "incomplete",
      "When creating or updating a task, set the incomplete flag to change the "
      "task's state to incomplete. This flag is not compatible in combination "
      "with the completed flag",
      cxxopts::value<bool>())(

      "due",
      "When creating or updating a task, set the due date flag to change the "
      "task's due date to the one specified as an argument (e.g. '2024-11-23')."
      "Ommitting the argument removes the due date from the task.",
      cxxopts::value<std::string>())(

      "h,help", "Print usage.");

  return cxxopts;
}

// TODO Rewrite this function so that it works. This function should
// case-insensitively check the action argument retrieved from cxxopts and
// convert this to a value from the ACTION enum. If an invalid value is given
// in a string, throw an std::invalid_argument exception.
//
// Example:
//  auto options = App::cxxoptsSetup();
//  auto args = options.parse(argc, argv);
//  App::Action action = parseActionArgument(args);
App::Action App::parseActionArgument(cxxopts::ParseResult &args) {
// enum Action { CREATE, JSON, DELETE, UPDATE };
  std::string input = args["action"].as<std::string>();
  std::transform(input.begin(), input.end(), input.begin(), ::tolower);
  
  if(input == "create") {
    return Action::CREATE;
  } else if(input == "json") {
    return Action::JSON;
  } else if(input == "delete") {
    return Action::DELETE;
  } else if(input == "update") {
    return Action::UPDATE;
  }
  throw std::invalid_argument("action");
}

// TODO Write a function, getJSON, that returns a std::string containing the
// JSON representation of a TodoList object.
//
// This function has been implemented for you, but you may wish to adjust it.
// You will have to uncomment the code, which has been left commented to ensure
// the coursework framework compiles (i.e., it calls functions that you must
// implement, once you have implemented them you may uncomment this function).
//
// Example:
//  TodoList tlObj{};
//  std::cout << getJSON(tlObj);
std::string App::getJSON(TodoList &tlObj) {

  if (!opt.hasProject) {
    return tlObj.str();
  }

  // The action program argument json can be ignored for 'due'.
  // Outputs and exit code values should delegated to the tag, task, and project arguments instead
  opt.hasDue = true;

  if(opt.tagParsable()) {
    return getJSON(tlObj, opt.project, opt.task, opt.tag);
  }

  if (opt.taskParsable()) {
    return getJSON(tlObj, opt.project, opt.task);
  }
  
  if (opt.projectParsable()) {
    return getJSON(tlObj, opt.project);
  }

  return {};
}

// TODO Write a function, getJSON, that returns a std::string containing the
// JSON representation of a specific Project in a TodoList object.
//
// This function has been implemented for you, but you may wish to adjust it.
// You will have to uncomment the code, which has been left commented to ensure
// the coursework framework compiles (i.e., it calls functions that you must
// implement, once you have implemented them you may uncomment this function).
//
// Example:
//  TodoList tlObj{};
//  std::string p = "project argument value";
//  std::cout << getJSON(tlObj, p);
std::string App::getJSON(TodoList &tlObj, const std::string &p) {

  // If such a project does not exist, 
  // output an error message to stderr and return an exit code of 1.
  try {
    auto pObj = tlObj.getProject(p);
    return pObj.str();
  } catch (const std::exception& e) {
    exitWithError(e.what());
    return {};
  }

}

// TODO Write a function, getJSON, that returns a std::string containing the
//  JSON representation of a specific Task in a TodoList object.
//
// This function has been implemented for you, but you may wish to adjust it.
// You will have to uncomment the code, which has been left commented to ensure
// the coursework framework compiles (i.e., it calls functions that you must
// implement, once you have implemented them you may uncomment this function).
//
// Example:
//  TodoList tlObj{};
//  std::string p = "project argument value";
//  std::string t = "task argument value";
//  std::cout << getJSON(tlObj, p, t);
std::string App::getJSON(TodoList &tlObj, const std::string &p,
                         const std::string &t) {

  // If such a task or project does not exist, 
  // output an error message to stderr and return an exit code of 1.
  try {
    auto pObj = tlObj.getProject(p);
    const auto tObj = pObj.getTask(t);
    return tObj.str();
  } catch (const std::exception& e) {
    exitWithError(e.what());
    return {};
  }
}

// DONE Write a function, getJSON, that returns a std::string containing the
//  JSON representation of a specific Tag in a TodoList object. If the tag
//  does not exist, return an empty string "".
//
// This function has been implemented for you, but you may wish to adjust it.
// You will have to uncomment the code, which has been left commented to ensure
// the coursework framework compiles (i.e., it calls functions that you must
// implement, once you have implemented them you may uncomment this function).
//
// Example:
//  TodoList tlObj{};
//  std::string p = "project argument value";
//  std::string task = "task argument value";
//  std::string tag = "tag argument value";
//  std::cout << getJSON(tlObj, p, task, tag);
std::string App::getJSON(TodoList &tlObj, const std::string &p,
                         const std::string &task, const std::string &tag) {

  auto pObj = tlObj.getProject(p);
  const auto tObj = pObj.getTask(task);
  if (tObj.containsTag(tag)) {
    return tag;
  } else {
    exitWithError("Task does not contain such a tag");
    return {};
  }
}



// create action argument
void App::createAction(TodoList &tlObj) {
  
  if (!opt.hasProject) {
    exitWithError(MissingArgsErr);
  }

  if (opt.completed && opt.incomplete) {
    exitWithError(BothCompletedFlagsErr);
  }

  if (opt.projectParsable()) {
    tlObj.newProject(opt.project);
  }

  if (opt.taskParsable()) {
    tlObj.getProject(opt.project).newTask(opt.task);
  }

  if(opt.tagParsable()) {
    std::istringstream iss(opt.tag);
    std::string token;
    while (std::getline(iss, token, ',')) {
        tlObj.getProject(opt.project).getTask(opt.task).addTag(token);
    }
  }

  if(opt.dueParsable()) {
    tlObj.getProject(opt.project).getTask(opt.task).getDueDate().setDateFromString(opt.due);
  }

  if(opt.completeParsable()) {
    tlObj.getProject(opt.project).getTask(opt.task).setComplete(opt.completed? true : false);
  }

}



// delete action argument
void App::deleteAction(TodoList &tlObj) {

  if (!opt.hasProject) {
    exitWithError(MissingArgsErr);
  }

  // If there is a project in the database delete it. 
  // If successful, don't output anything and return an exit code of 0. 
  // If not successful, (i.e., no project exists), 
  // output an error message to stderr and return an exit code of 1.
  if (opt.projectParsable()) {
    try {
      tlObj.deleteProject(opt.project);
    } catch (const std::exception& e) {
      exitWithError(e.what());
    }
  }
  
  // If there is a task that belongs to project in the database delete it. 
  // If successful, don't output anything and return an exit code of 0. 
  // If not successful, (i.e., no task/project exists), 
  // output an error message to stderr and return an exit code of 1.
  if (opt.taskParsable()) {
    try {
      tlObj.getProject(opt.project).deleteTask(opt.task);
    } catch (const std::exception& e) {
      exitWithError(e.what());
    }
  }

  // If there is a tag that belongs to task in the database delete it. 
  // If successful, don't output anything and return an exit code of 0. 
  // If not successful, (i.e., no tag/task/project exists),
  // output an error message to stderr and return an exit code of 1.
  if(opt.tagParsable()) {
    try {
      tlObj.getProject(opt.project).getTask(opt.task).deleteTag(opt.tag);
    } catch (const std::exception& e) {
      exitWithError(e.what());
    }
  }

  // If there is a due date set for the task reset the Date object to uninitialised. 
  // If successful, don't output anything and return an exit code of 0. 
  // If not successful, (i.e., no tag/task/project exists), 
  // output an error message to stderr and return an exit code of 1.
  if(opt.dueParsable()) {
    tlObj.getProject(opt.project).getTask(opt.task).getDueDate().setUninitialised();
  }

}




// Action Options Struct methods implementation
// if options given are enough to perform certain action, it returns true.
// For example, if the Action is '--action create --project value',
// projectParsable() returns true.

bool App::ActionOptions::projectParsable() {
  return !hasDue && !hasTag && !completed && !incomplete && !hasTask
            && hasProject;
}

bool App::ActionOptions::taskParsable() {
  return !hasDue && !hasTag && !completed && !incomplete
            && hasTask && hasProject;
}

bool App::ActionOptions::tagParsable() {
  return hasTag && hasTask && hasProject;
}

bool App::ActionOptions::dueParsable() {
  return hasDue && hasTask && hasProject;
}

bool App::ActionOptions::completeParsable() {
  return (completed || incomplete) && hasTask && hasProject;
}



// Extracts options given with an action and initialises ActionOptions opt.
void App::extractArgs(const cxxopts::ParseResult &args) {

    opt.hasProject = args.count("project") > 0;
    opt.hasTask = args.count("task") > 0;
    opt.hasTag = args.count("tag") > 0;
    opt.hasDue = args.count("due") > 0;

    if (opt.hasProject) {
      opt.project = args["project"].as<std::string>();
    }

    if(opt.hasTask) {
       opt.task = args["task"].as<std::string>();
    }

    if(opt.hasTag) {
      opt.tag = args["tag"].as<std::string>();
    }

    if(opt.hasDue) {
      opt.due = args["due"].as<std::string>();
    }

    opt.completed = args.count("completed") > 0;
    opt.incomplete = args.count("incomplete") > 0;

}

// Outputs error message and returns exits code 1.
void App::exitWithError(const std::string& message) {
  std::cerr << message << std::endl;
  exit(1);
}