# 371todo

You should use this README to document things you did that you thing are clever and could get you marks, or things you couldn't get working and perhaps why. It is fully expected that a lot of students will not complete this coursework—-it is designed to be challenging. The mark scheme is also designed to be fair—marks are awarded for everything you complete, with some given for the quality of the code you write.

-- -- -- -- -- -- -- -- -- -- --

HELLO

I have implemented everything specified and passed both unit and autograder tests. 

-- -- -- -- -- -- -- -- -- -- --

### MAIN PROGRAM LOGIC 

In namespace App (371todo.cpp & 371todo.h) I have implemented struct ActionOptions to extract, validate and apply Action options. It made my code more clear and efficient. Before the Action corresponding method is called, program extracts Acton argument options, and sets struct member variables accordingly. If they are valid, only then Action methods are called.

I have implemented action methods similar to how initially Action json (getJSON()) was provided. I did overload each CreateAction(), UpdateAction(), DeleteAction() methods with different arguments to perform corresponding logic. Initially called action methods call their overloads depending on extracted Action options.

These methods perform the rest of the logic. I made sure to catch any exceptions arising and handle them gracefully.

-- -- -- -- -- -- -- -- -- -- --

### LOAD/SAVE TODOLIST

To load the TodoList from json file, I made parse() method for each class that needs to be loaded. Each class's parse method loads passed json data into its object's container. e.g. todoList.parse() will load projects, each project will load its tasks, each task will load its attributes.

With the same logic works save(). Each class has its own json() tostr() methods.

-- -- -- -- -- -- -- -- -- -- --

### BONUS FEATURE

Delete many tags at the same time. 
In the specification it was said its possible to create many tags at the same time (--tag tag1,tag2,tag3). I used the same logic for deleting many tags.


- p.s. pray I can land a good job please ^^