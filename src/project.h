// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2023/24)
// Department of Computer Science, Swansea University
//
// Author: 2130288
//
// Canvas: https://canvas.swansea.ac.uk/courses/44636
// -----------------------------------------------------
// A Project contains one or more Tasks, each with
// their own identifier ('ident').
// -----------------------------------------------------

#ifndef PROJECT_H
#define PROJECT_H

#include "lib_json.hpp"

#include "task.h"

using TaskContainer = std::vector<Task>;

class Project {
  
private:
  std::string ident;
  TaskContainer tasks;

public:
  explicit Project(const std::string& ident);
  ~Project() = default;

  unsigned int size() const noexcept;

  const std::string &getIdent() const noexcept;
  void setIdent(std::string pIdent) noexcept;

  const TaskContainer &getTasks() const noexcept;
  Task &newTask(const std::string &tIdent);
  TaskContainer::iterator findTask(const std::string &tIdent) noexcept;
  bool containsTask(const std::string &tIdent) noexcept;

  bool addTask(Task task);
  Task &getTask(const std::string &tIdent);
  bool deleteTask(const std::string &tIdent);

  friend bool operator==(const Project& project1, const Project& project2) noexcept;
  
  void mergeProjects(const Project& newProject) noexcept;

  nlohmann::json json() const;
  std::string str() const;
  void parse(const nlohmann::json& json);

};


struct AddTaskError : public std::runtime_error {
  explicit AddTaskError(const std::string &tIdent)
      : std::runtime_error("could not add task with identifier '" + tIdent + "'") {}

  ~AddTaskError() override = default;
};

struct DeleteTaskError : public std::runtime_error {
  explicit DeleteTaskError(const std::string &tIdent)
      : std::runtime_error("could not delete task with identifier '" + tIdent + "'") {}

  ~DeleteTaskError() override = default;
};

struct NoTaskError : public std::out_of_range {
  explicit NoTaskError(const std::string &tIdent)
      : std::out_of_range("unknown task with identifier '" + tIdent + "'") {}

  ~NoTaskError() override = default;
};

struct NewTaskError : public std::runtime_error {
  explicit NewTaskError(const std::string &tIdent)
      : std::runtime_error("could not create new task with identifier '" + tIdent + "'") {}

  ~NewTaskError() override = default;
};


#endif // PROJECT_H
