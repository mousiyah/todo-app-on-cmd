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
  opt.extractArgs(args);
  opt.checkValidity(a);

  switch (a) {
    case Action::CREATE:
      createAction(tlObj);
      break;

    case Action::JSON:
      std::cout << getJSON(tlObj);
      break;

    case Action::UPDATE:
      updateAction(tlObj);
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

  // The action program argument json can be ignored for 'due'.
  // Outputs and exit code values should delegated to the tag, task, and project arguments instead
  opt.hasDue = false;

  if (opt.noneParsable()) {
    return tlObj.str();
  }

  if (opt.projectParsable()) {
    return getJSON(tlObj, opt.project);
  }

  if (opt.taskParsable()) {
    return getJSON(tlObj, opt.project, opt.task);
  }

  if(opt.tagParsable()) {
    return getJSON(tlObj, opt.project, opt.task, opt.tag);
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

  std::string result;
  // If such a project does not exist, 
  // output an error message to stderr and return an exit code of 1.
  try {
    auto pObj = tlObj.getProject(p);
    result = pObj.str();
  } catch (const std::exception& e) {
    exitWithError(InvalidProjectErr);
  }

  return result;
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
  
  std::string result;
  // If such a task or project does not exist, 
  // output an error message to stderr and return an exit code of 1.
  try {
    auto pObj = tlObj.getProject(p);

    try {
      const auto tObj = pObj.getTask(t);
      result = tObj.str();
    } catch (const std::exception& e) {
      exitWithError(InvalidTaskErr);
    }   

  } catch (const std::exception& e) {
    exitWithError(InvalidProjectErr);
  }

  return result;
    
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

  std::string result;
  try {
    auto pObj = tlObj.getProject(p);

    try {
      const auto tObj = pObj.getTask(task);


      if (tObj.containsTag(tag)) {
        result = tag;
      } else {
        exitWithError(InvalidTagErr);
      }

    } catch (const std::exception& e) {
      exitWithError(InvalidTaskErr);
    }  

  } catch (const std::exception& e) {
    exitWithError(InvalidProjectErr);
  }

  return result;

}





// --action create implementation
void App::createAction(TodoList &tlObj) {

  if (opt.projectParsable()) {
    createAction(tlObj, opt.project);
  }

  if (opt.taskParsable()) {
    createAction(tlObj, opt.project, opt.task);
  }

  if(opt.tagParsable()) {
    createAction(tlObj, opt.project, opt.task, opt.tag);
  }

  if(opt.dueParsable()) {
    createAction(tlObj, opt.project, opt.task, opt.due, opt.hasDue);
  }

  if(opt.completeParsable()) {
    createAction(tlObj, opt.project, opt.task, opt.completed? true : false);
  }

}


// Create new project in database.
// Dont output anything and return an exit code of 0.
// If a project exists already with that identifier, do nothing.
void App::createAction(TodoList &tlObj, const std::string &p) {
    tlObj.newProject(p);
}


// New tasks default to incomplete and without a due date (Date is uninitialised).
// Dont output anything and return an exit code of 0.
// If a task exists already with that identifier, do nothing.
// If project doesn't exist, error message to stderr and return an exit code of 1.
void App::createAction(TodoList &tlObj, const std::string &p,
                         const std::string &t) {
  
  try {
    auto& pObj = tlObj.getProject(p);
    pObj.newTask(t);

  } catch (const std::exception& e) {
    exitWithError(InvalidProjectErr);
  }
    
}


// tag argument can also be comma‐separated list without spaces 
// (e.g. “tag1,tag2”) 
// If a tag exists already with that identifier, do nothing
// (and continue adding other tags in the tag list, if applicable). 
// In both cases, should not output anything and exit with a code of 0.
// If project/task doesn't exist, error message to stderr and return exit code of 1.
void App::createAction(TodoList &tlObj, const std::string &p,
                         const std::string &task,  const std::string &tags) {

  try {
    auto& pObj = tlObj.getProject(p);

    try {
      auto& tObj = pObj.getTask(task);

      std::istringstream iss(tags);
      std::string tag;
      while (std::getline(iss, tag, ',')) {
        tObj.addTag(tag);
      }

    } catch (const std::exception& e) {
      exitWithError(InvalidTaskErr);
    }

  } catch (const std::exception& e) {
    exitWithError(InvalidProjectErr);
  }
    
}


// Set to true (for completed) or false (for incomplete).
// If project/task doesn't exist, error message to stderr and return exit code of 1.
void App::createAction(TodoList &tlObj, const std::string &p,
                         const std::string &t,  const bool complete) {

  try {
    auto& pObj = tlObj.getProject(p);

    try {
      auto& tObj = pObj.getTask(t);

      tObj.setComplete(complete);

    } catch (const std::exception& e) {
      exitWithError(InvalidTaskErr);
    }

  } catch (const std::exception& e) {
    exitWithError(InvalidProjectErr);
  }
    
}


// If the due argument is empty, (re)set the due date to uninitalised.
// If the due argument is not a valid date and is also not empty, 
// output an error message to stderr and return an exit code of 1. 
// Otherwise set the due date, if it has not been set yet.
// If a due date already exists, overwrite it. 
// In both cases should not output anything and exit with a code of 0.
// If project/task doesn't exist, error message to stderr and return exit code of 1.
void App::createAction(TodoList &tlObj, const std::string &p,
                         const std::string &t,  const std::string &due, bool isDue) {

  try {
    auto& pObj = tlObj.getProject(p);

    try {
      auto& tObj = pObj.getTask(t);

      tObj.getDueDate().setDateFromString(due);

    } catch (const std::exception& e) {
      exitWithError(InvalidTaskErr);
    }

  } catch (const std::exception& e) {
    exitWithError(InvalidProjectErr);
  }
    
}





// --action delete implementation
void App::deleteAction(TodoList &tlObj) {

    if (opt.projectParsable()) {
        deleteAction(tlObj, opt.project);
    }

    if (opt.taskParsable()) {
        deleteAction(tlObj, opt.project, opt.task);
    }

    if (opt.tagParsable()) {
        deleteAction(tlObj, opt.project, opt.task, opt.tag);
    }

    if (opt.dueParsable()) {
        deleteAction(tlObj, opt.project, opt.task, opt.hasDue);
    }

}


// If there is a project in the database delete it. 
// If successful, don't output anything and return an exit code of 0. 
// If not successful, (i.e., no project exists), 
// output an error message to stderr and return an exit code of 1.
void App::deleteAction(TodoList &tlObj, const std::string &p) {
    try {
        tlObj.deleteProject(p);
    } catch (const std::exception &e) {
        exitWithError(InvalidProjectErr);
    }
}


// If there is a task that belongs to project in the database delete it. 
// If successful, don't output anything and return an exit code of 0. 
// If not successful, (i.e., no task/project exists), 
// output an error message to stderr and return an exit code of 1.
void App::deleteAction(TodoList &tlObj, const std::string &p, const std::string &t) {
    try {
        auto& pObj = tlObj.getProject(p);
        
        try {
          pObj.deleteTask(t);

        } catch (const std::exception &e) {
        exitWithError(InvalidTaskErr);
        }

    } catch (const std::exception &e) {
        exitWithError(InvalidProjectErr);
    }
}


// If there is a tag that belongs to task in the database delete it. 
// If successful, don't output anything and return an exit code of 0. 
// If not successful, (i.e., no tag/task/project exists),
// output an error message to stderr and return an exit code of 1.
void App::deleteAction(TodoList &tlObj, const std::string &p,
                         const std::string &task,  const std::string &tags) {

  try {
    auto& pObj = tlObj.getProject(p);

    try {
      auto& tObj = pObj.getTask(task);

      std::istringstream iss(tags);
      std::string tag;
      while (std::getline(iss, tag, ',')) {

        try{
        tObj.deleteTag(tag);
        } catch (const std::exception& e) {
          exitWithError(InvalidTagErr);
        }

      }

    } catch (const std::exception& e) {
      exitWithError(InvalidTaskErr);
    }

  } catch (const std::exception& e) {
    exitWithError(InvalidProjectErr);
  }
    
}


// If there is a due date set for the task reset the Date object to uninitialised. 
// If successful, don't output anything and return an exit code of 0. 
// If not successful, (i.e., no task/project exists), 
// output an error message to stderr and return an exit code of 1.
void App::deleteAction(TodoList &tlObj, const std::string &p,
                         const std::string &t, bool isDue) {

  try {
    auto& pObj = tlObj.getProject(p);

    try {
      auto& tObj = pObj.getTask(t);

      tObj.getDueDate().setUninitialised();

    } catch (const std::exception& e) {
      exitWithError(InvalidTaskErr);
    }

  } catch (const std::exception& e) {
    exitWithError(InvalidProjectErr);
  }
    
}





// --action update implementation
void App::updateAction(TodoList &tlObj) {
  
  // The action program argument update can be ignored for 'tag'.
  // Outputs and exit code values should delegated to the task and/or project arguments instead
  opt.hasTag = false;

  if (opt.projectParsable()) {
    updateAction(tlObj, opt.project);
  }

  if (opt.taskParsable()) {
    updateAction(tlObj, opt.project, opt.task);
  }

  // for --due same behaviour as create
  if(opt.dueParsable()) {
    createAction(tlObj, opt.project, opt.task, opt.due, opt.hasDue);
  }

  // for --complete/--incomplete same behaviour as create
  if(opt.completeParsable()) {
    createAction(tlObj, opt.project, opt.task, opt.completed? true : false);
  }

}


// Rename project in database.
// project argument in the format oldidentifier:newidentifier
// If successfull dont output anything and return an exit code of 0.
// If such a project does not exist 
// output an error message to stderr and return an exit code of 1.
void App::updateAction(TodoList &tlObj, const std::string &p){

    if (opt.project.find(':') != std::string::npos) {
      std::istringstream iss(opt.project);
      std::string oldIdent, newIdent;
      std::getline(iss, oldIdent, ':');
      std::getline(iss, newIdent);

      try{
        auto& pObj = tlObj.getProject(oldIdent);
        pObj.setIdent(newIdent);

      } catch (const std::exception& e) {
        exitWithError(InvalidProjectErr);
      }
     
    } else {
      exitWithError(UpdateProjectValueErr);
    }

  }


  // Rename task that belongs to project in database.
  // task argument in the format oldidentifier:newidentifier
  // If successfull dont output anything and return an exit code of 0.
  // If such a task does not exist 
  // output an error message to stderr and return an exit code of 1.

void App::updateAction(TodoList &tlObj, const std::string &p, const std::string &t) {

    if (opt.task.find(':') != std::string::npos) {
      std::istringstream iss(opt.task);
      std::string oldIdent, newIdent;
      std::getline(iss, oldIdent, ':');
      std::getline(iss, newIdent);

      try {
        auto& pObj = tlObj.getProject(opt.project);
        
        try {
          auto& tObj = pObj.getTask(oldIdent);
          tObj.setIdent(newIdent);

        } catch (const std::exception& e) {
          exitWithError(InvalidTaskErr);
        }

      } catch (const std::exception& e) {
        exitWithError(InvalidProjectErr);
      }

    } else {
      exitWithError(UpdateTaskValueErr);
    }

}





// Action Options Struct methods implementation
// if options given are enough to perform certain action, it returns true.
// For example, if the Action is '--action create --project value',
// projectParsable() returns true.
bool App::ActionOptions::noneParsable() {
  return !hasDue && !hasTag && !completed && !incomplete && !hasTask
            && !hasProject;
}

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
void App::ActionOptions::extractArgs(const cxxopts::ParseResult &args) {

    hasProject = args.count("project") > 0;
    hasTask = args.count("task") > 0;
    hasTag = args.count("tag") > 0;
    hasDue = args.count("due") > 0;

    if (hasProject) {
      project = args["project"].as<std::string>();
    }

    if(hasTask) {
       task = args["task"].as<std::string>();
    }

    if(hasTag) {
      tag = args["tag"].as<std::string>();
    }

    if(hasDue) {
      opt.due = args["due"].as<std::string>();
    }

    completed = args.count("completed") > 0;
    incomplete = args.count("incomplete") > 0;

}

// Check validity of options given
void App::ActionOptions::checkValidity(Action a) {
  
  // for JSON we can provide no option
  if (noneParsable() && a != Action::JSON ) {
    exitWithError(MissingArgsErr);
  }

  // The flags are incompatible with one another 
  if (completed && incomplete) {
    exitWithError(BothCompletedFlagsErr);
  }

  // no project argument given
  if(hasTask && !hasProject) {
    exitWithError(MissingProjectArgsErr);
  }

  // no task argument given
  if(!hasTask && (hasTag || hasDue || completed || incomplete)) {
    exitWithError(MissingTaskArgsErr);
  }

}

// Outputs error message and returns exits code 1.
void App::exitWithError(const std::string& message) {
  std::cerr << message << std::endl;
  exit(1);
}