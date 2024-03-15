// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2023/24)
// Department of Computer Science, Swansea University
//
// Author: <STUDENT NUMBER>
//
// Canvas: https://canvas.swansea.ac.uk/courses/44636
// -----------------------------------------------------
// A Project contains one or more Tasks, each with
// their own identifier ('ident').
// -----------------------------------------------------

#ifndef PROJECT_H
#define PROJECT_H

#include <map>
#include <string>
#include <utility>

#include "lib_json.hpp"

#include "task.h"

using TaskContainer = std::vector<Task>;

class Project {
  std::string ident;
  TaskContainer tasks;

public:
  explicit Project(std::string ident);
  ~Project() = default;

  unsigned int size() const noexcept;
  const std::string &getIdent() const noexcept;

  void setIdent(std::string pIdent) noexcept;

  const TaskContainer &getTasks() const noexcept;
  Task &newTask(const std::string &tIdent);
  TaskContainer::iterator findTask(const std::string &tIdent);
  bool containsTask(const std::string &tIdent) const noexcept;

  bool addTask(Task task);
  Task &getTask(const std::string &tIdent);
  bool deleteTask(const std::string &tIdent);

  friend bool operator==(const Project &c1, const Project &c2);

  nlohmann::json json() const;
  std::string str() const;

  // Wrappers for iterating over the nested container
  inline TaskContainer::iterator begin() { return tasks.begin(); }
  inline TaskContainer::const_iterator cbegin() const { return tasks.cbegin(); }

  inline TaskContainer::iterator end() { return tasks.end(); }
  inline TaskContainer::const_iterator cend() const { return tasks.cend(); }

  inline TaskContainer::reverse_iterator rbegin() { return tasks.rbegin(); }
  inline TaskContainer::const_reverse_iterator crbegin() const {
    return tasks.crbegin();
  }

  inline TaskContainer::reverse_iterator rend() { return tasks.rend(); }
  inline TaskContainer::const_reverse_iterator crend() const {
    return tasks.crend();
  }
};

struct AddTaskError : public std::runtime_error {
  explicit AddTaskError(const std::string &tIdent)
      : std::runtime_error("could not add task with identifier '" + tIdent +
                           "'") {
    /* do nothing */
  }

  ~AddTaskError() override = default;
};

struct NoTaskError : public std::out_of_range {
  explicit NoTaskError(const std::string &tIdent)
      : std::out_of_range("unknown task with identifier '" + tIdent + "'") {
    /* do nothing */
  }

  ~NoTaskError() override = default;
};

#endif // PROJECT_H
