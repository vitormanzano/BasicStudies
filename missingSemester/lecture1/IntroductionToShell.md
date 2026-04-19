# The terminal | The shell

https://missing.csail.mit.edu/2026/course-shell/

## Notes
https://missing.csail.mit.edu/2026/course-shell/

The shell is a program in the computer that allow us to give inputs(commands) and prints the outputs of this commands

Arguments: Things that follow the program name in the command.
echo hello world
\ -> It's a escape 
echo hello\ \ \ \world -> Means after the backslash that is a space

man -> For manual

sort -u file -> Sorts and remove duplicates lines

hear or tail has the argument -n<num>, the number of lines to print
head -n3 date -> will print the first 3 lines 

### grep
example:
cd ./././
grep -r grep . -> Will search recursively in this path to the word grep

find has a maxdepth argument that will search just through this depth
0 is the current folder

awk '{print $2}' file
Will print just the second column of each row.

ssh is a way to run a command in a remote machine.
