1. You might see commands like cmd --flag -- --notaflag. The -- is a special argument that tells the program to stop parsing flags. Everything after -- is treated as a positional argument. Why might this be useful?
-- is used to signal the end of the end of command options. That is useful when you have a file that starts with - if you try that without -- will fail. Because the command will think that it's a command option.

2. Read man ls and write an ls command that lists files in the following manner:
Includes all files, including hidden files
Sizes are listed in human readable format (e.g. 454M instead of 454279954)
Files are ordered by recency
Output is colorized
A sample output would look like this:

ls -lGth 
-l -> Long format
-G -> Colorized
-h -> Suffixes for Bytes
-t -> newest by last modified

3. Process substitution <(command) lets you use a command’s output as if it were a file. Use diff with process substitution to compare the output of printenv and export. Why are they different? (Hint: try diff <(printenv | sort) <(export | sort)).
printenv is a the data raw about the process environment, export is a reexecutable shell declaration.

## Environment Variables

1. Write bash functions marco and polo that do the following: whenever you execute marco the current working directory should be saved in some manner, then when you execute polo, no matter what directory you are in, polo should cd you back to the directory where you executed marco. For ease of debugging you can write the code in a file marco.sh and (re)load the definitions to your shell by executing source marco.sh.

## Return codes

1. Say you have a command that fails rarely. In order to debug it you need to capture its output but it can be time consuming to get a failure run. Write a bash script that runs the following script until it fails and captures its standard output and error streams to files and prints everything at the end. Bonus points if you can also report how many runs it took for the script to fail

## Signals and Job Control

1. Start a sleep 10000 job in a terminal, background it with Ctrl-Z and continue its execution with bg. Now use pgrep to find its pid and pkill to kill it without ever typing the pid itself. (Hint: use the -af flags).
pgrep sleep
pkill -af sleep

2. Say you don’t want to start a process until another completes. How would you go about it? In this exercise, our limiting process will always be sleep 60 &. One way to achieve this is to use the wait command. Try launching the sleep command and having an ls wait until the background process finishes.

However, this strategy will fail if we start in a different bash session, since wait only works for child processes. One feature we did not discuss in the notes is that the kill command’s exit status will be zero on success and nonzero otherwise. kill -0 does not send a signal but will give a nonzero exit status if the process does not exist. Write a bash function called pidwait that takes a pid and waits until the given process completes. You should use sleep to avoid wasting CPU unnecessarily.

## Files and Permissions 

1. (Advanced) Write a command or script to recursively find the most recently modified file in a directory. More generally, can you list all files by recency?
find . -type f -exec stat -f "%m %N" {} \; | sort -nr | head -1

## Terminal multiplexers

1. Follow this tmux tutorial and then learn how to do some basic customizations following these steps.
https://hamvocke.com/blog/a-quick-and-easy-guide-to-tmux/
https://hamvocke.com/blog/a-guide-to-customizing-your-tmux-conf/

## Aliases and Dotfiles

1. Create an alias dc that resolves to cd for when you type it wrong.
alias dc='cd'

2. Run history | awk '{$1="";print substr($0,2)}' | sort | uniq -c | sort -n | tail -n 10 to get your top 10 most used commands and consider writing shorter aliases for them. Note: this works for Bash; if you’re using ZSH, use history 1 instead of just history.
alias muc='history 1 | awk '"'"'{$1="";print substr($0,2)}'"'"' | sort | uniq -c | sort -n | tail -n 10'


3. Create a folder for your dotfiles and set up version control.


