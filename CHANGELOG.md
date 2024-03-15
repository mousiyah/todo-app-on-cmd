// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2023/24)
// Department of Computer Science, Swansea University
//
// Author: Thomas Reitmaier
//         thomas.reitmaier@swansea.ac.uk
//
// Canvas: https://canvas.swansea.ac.uk/courses/44636
// -----------------------------------------------------
// 371todo Coursework — Changelog
// -----------------------------------------------------

Releases
--------

v1.2    Fixed date formatting issues in json db   11th Mar 2024
v1.1    Clarified json key clashes                 6th Mar 2024
v1.0    Initial coursework release                29th Feb 2024


v1.2 — 11th Mar 2024
--------------------
Fixed date formatting issue with `database.json`, the local test suite, and output tests on csautograder. These were incorrectly formatting date strings. They should have been formatted as YYYY-MM-DD, per coursework specification. Changes compared to previous release are:
- `tests/test1.cpp` ... `tests/test9.cpp` (in coursework framework and on cs autograder)
- `database.json` (in coursework framework and on cs autograder)
- `tests/testdatabase.json` (in coursework framework and on cs autograder)
- `tests/testdatabasealt.json` (in coursework framework and on cs autograder)
- output tests on csautograder

Note: all files in `src/` directory have not been affected by this update.

v1.1 — 6th Mar 2024
-------------------
Clarified how project/task key clashes should be handled when loading from json db.
- See comments in todolist.cpp for `TodoList::load()` function.


