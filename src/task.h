// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2023/24)
// Department of Computer Science, Swansea University
//
// Author: 2130288
//
// Canvas: https://canvas.swansea.ac.uk/courses/44636
// -----------------------------------------------------
// A Task class contains multiple 'tags' (e.g., a tag might be 'home' and
// another tag could be 'uni'). A Task also has a identifier (e.g. 'Complete
// Coursework') a completed status (completed or not) and due date. An
// uninitialised due date (see date.cpp/date.h) means the task does not have a
// due date.
// -----------------------------------------------------

#ifndef TASK_H
#define TASK_H

#include "date.h"

using TagContainer = std::vector<std::string>;

class Task {

private:
  std::string ident;
  Date dueDate;
  bool complete = false;
  TagContainer tags;

public:
  explicit Task(const std::string& ident);
  ~Task() = default;

  const std::string& getIdent() const noexcept;
  void setIdent(std::string tIdent) noexcept;

  bool addTag(const std::string& tag);
  bool addTags(const TagContainer& newTags);
  bool deleteTag(const std::string& tag);
  unsigned int numTags() const noexcept;
  bool containsTag(const std::string& tag) const noexcept;
  TagContainer::const_iterator findTag(const std::string &tag) const noexcept;

  Date getDueDate() const noexcept;
  void setDueDate(const Date& dueDate) noexcept;

  void setComplete(bool complete) noexcept;
  bool isComplete() const noexcept;

  friend bool operator==(const Task& task1, const Task& task2) noexcept;

  void mergeTask(const Task& newTask) noexcept;

  std::string str() const;
  nlohmann::json json() const;
  void parse(const nlohmann::json& json);

};


struct NoTagError : public std::out_of_range {
  explicit NoTagError(const std::string &tag)
      : std::out_of_range("unknown tag with identifier '" + tag + "'") {}

  ~NoTagError() override = default;
};


#endif // TASK_H
