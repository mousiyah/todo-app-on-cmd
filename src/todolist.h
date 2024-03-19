// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2023/24)
// Department of Computer Science, Swansea University
//
// Author: 2130288
//
// Canvas: https://canvas.swansea.ac.uk/courses/44636
// -----------------------------------------------------
// The root object that holds all data for 371todo. This
// class contains Projects, which in turn hold Tasks,
// which have a name, due date, completed status, and tags.
// -----------------------------------------------------

#ifndef TODOLIST_H
#define TODOLIST_H

#include "project.h"

#include "lib_cxxopts.hpp"

using ProjectContainer = std::vector<Project>;

class TodoList {

private:
  ProjectContainer projects;
        
public:
  explicit TodoList();
  ~TodoList() = default;

  unsigned int size() const noexcept;

  const ProjectContainer &getProjects() const noexcept;
  Project& newProject(const std::string& ident);
  bool containsProject(const std::string& ident) noexcept;
  ProjectContainer::iterator findProject(const std::string &ident) noexcept;

  bool addProject(const Project& project);
  void mergeProjects(const Project& oldProject, const Project& newProject);
  Project& getProject(const std::string& ident);
  bool deleteProject(const std::string& ident);

  void load(const std::string& filename);
  void save(const std::string& filename);

  friend bool operator==(const TodoList& todoList1, const TodoList& todoList2);

  std::string str() const;
  
  nlohmann::json json() const;
  
  void parse(const nlohmann::json& json);

};



struct NoProjectError : public std::out_of_range {
  explicit NoProjectError(const std::string &ident)
      : std::out_of_range("unknown project with identifier '" + ident + "'") {}

  ~NoProjectError() override = default;
};

struct DeleteProjectError : public std::runtime_error {
  explicit DeleteProjectError(const std::string &ident)
      : std::runtime_error("could not delete project with identifier '" + ident + "'") {}

  ~DeleteProjectError() override = default;
};

struct NewProjectError : public std::runtime_error {
  explicit NewProjectError(const std::string &ident)
      : std::runtime_error("could not create new project with identifier '" + ident + "'") {}

  ~NewProjectError() override = default;
};

struct AddProjectError : public std::runtime_error {
  explicit AddProjectError(const std::string &ident)
      : std::runtime_error("could not add project with identifier '" + ident + "'") {}

  ~AddProjectError() override = default;
};

struct FileOpenError : public std::runtime_error {
    explicit FileOpenError(const std::string &filename)
        : std::runtime_error("failed to open file with name " + filename + "'") {}

    ~FileOpenError() override = default;
};



#endif // TODOLIST_H