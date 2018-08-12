In the Operating Systems class, this challenging assignment was meant to replicate the behavior of a typical BASH Shell. The program is able to execute commands on the Kernel level such as where, grep, ls, etc. The shell was also responsible for tracking the command history and saving the last N commands into a file between sessions, as well as tracking user entered alias commands. 

- PATH and redirection not implemented

Known issues: On exit an error from freeing an invalid pointer inside the clearList() function that frees the linkedlist

Future improvements: - Change local file to a local db using mySQLli
                     - fix a minimum memory leak issue on exit, implement GUI
                     - Clean up code, improve eficiency
