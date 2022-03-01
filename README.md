# Shell
The objective of this assignment is to become familiar with the use and programming in the Linux
Operating System environment. In this project, you will create an application which is a
simplified version of the UNIX SHELL using C.

## Your Task
Create an application called myshell to parse command line input from the user and execute it
as if it is a built-in command. You will implement the following built-in commands:
- pwd - print name of current/working directory. [1 point]
- cd - change the current directory. You should handle:
  - cd ..
  - cd with no argument : display error message “missing argument”
  - cd correct_destination : verify with pwd after execution
  - cd wrong_destintation : display error message “Command failed: No such file or directory”
- exit - exit the application. 
- ls – display the contents of your current working directory (ls only, no need for additional arguments such as ls –l) 

Make sure the shell doesn’t stop after executing one command. It should keep allowing the
user to enter new commands till exit is typed or Ctrl+D is clicked.
Proper and clear comment for every part of the code
