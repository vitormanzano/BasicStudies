# Exercises

## 1 - What does the -l flag to ls do? Run ls -l / and examine the output. What do the first 10 characters of each line mean? (Hint: man ls)
List files in the long format.
### Long format
- file mode
- number of links
- owner name
- group name 
- number of bytes in the file
- abbreviated month
- day-of-month file was last modified
- hour file last modified
- minute file last modified
- pathname

If the file or directory has extended attributes, the permissions field is followed by a '@' character. Otherwise if the file or directory has extended security information(like an access control list), the permissions field is followed by a '+' character. If the -% option is given, a '%' character follows the permissions field for dataless filer or directories, possibly replacing the '@' or  '+' character.
The file mode printed consists of the entry type and permissions. The entry type character describes the type of the file:
- '-' Regular file
- b block special file
- c character special file
- d directory
- l symbolic link 
- p FIFO
- s Socket
- w whiteout

The next fields are three characters each: owner permissions, group permissions, and others permissions. Each field has three character positions:

1.   If r, the file is readable; if -, it is not readable.

2.   If w, the file is writable; if -, it is not writable.

3.   The first of the following that applies:

S If in the owner permissions, the file is not executable and set-user-ID mode is set.  If in the group permissions, the file is not executable and set-group-ID mode is set.

s     If in the owner permissions, the file is executable and set-user-ID mode is set.  If in the group permissions, the file is executable and setgroup-ID mode is set.

x     The file is executable or the directory is searchable.

'-'     The file is neither readable, writable, executable, nor set-user-ID nor set-group-ID mode, nor sticky.  (See below.)

These next two apply only to the third character in the last group (other permissions).

T     The sticky bit is set (mode 1000), but not execute or search permission.  (See chmod(1) or sticky(7).)

t     The sticky bit is set (mode 1000), and is searchable or executable.  (See chmod(1) or sticky(7).)

The next field contains a plus (‘+’) character if the file has an ACL, or a space (‘ ’) if it does not.  The ls utility does not show the actual ACL unless the -e option is used in conjunction with the -l option.

The first 10 characters is the permission to the owner of the file, group and anyone permissions.

## 2 - In the command find ~/Downloads -type f -name "*.zip" -mtime +30, the *.zip is a “glob”. What is a glob? Create a test directory with some files and experiment with patterns like ls *.txt, ls file?.txt, and ls {a,b,c}.txt. See Pattern Matching in the Bash manual.
A glob is a string of characters (often containing wildcards like * or ?) used to match file paths or filenames in programming and cli's. Allows user to identify groups of files based on patterns.
This command looks for:
In ~/Downloads, find regular files whose name matches anything ending in .zip and which were last modified more than 30 days ago.
https://www.gnu.org/software/bash/manual/html_node/Pattern-Matching.html

## 3 - What’s the difference between 'single quotes', "double quotes", and $'ANSI quotes'? Write a command that echoes a string containing a literal $, a !, and a newline character. See Quoting.

Single quotes (‘'’) preserves the literal value of each character within the quotes. A single quote may not occur between single quotes, even when preceded by a backslash.
Double quotes (‘"’) preserves the literal value of all characters within the quotes, with the exception of ‘$’, ‘`’, ‘\’, and, when history expansion is enabled, ‘!’. When the shell is in POSIX mode (see Bash and POSIX), the ‘!’ has no special meaning within double quotes, even when history expansion is enabled. The characters ‘$’ and ‘'’ retain their special meaning within double quotes (see Shell Expansions). The backslash retains its special meaning only when followed by one of the following characters: ‘$’, ‘`’, ‘"’, ‘\’, or newline. Within double quotes, backslashes that are followed by one of these characters are removed. Backslashes preceding characters without a special meaning are left unmodified.

A double quote may be quoted within double quotes by preceding it with a backslash. If enabled, history expansion will be performed unless an ‘!’ appearing in double quotes is escaped using a backslash. The backslash preceding the ‘!’ is not removed.

The special parameters ‘*’ and ‘@’ have special meaning when in double quotes (see Shell Parameter Expansion).

Character sequences of the form $'string' are treated as a special kind of single quotes. The sequence expands to string, with backslash-escaped characters in string replaced as specified by the ANSI C standard. Backslash escape sequences, if present, are decored. Like \n, \t, \v \a
https://www.gnu.org/software/bash/manual/html_node/Quoting.html

## 4 - The shell has three standard streams: stdin (0), stdout (1), and stderr (2). Run ls /nonexistent /tmp and redirect stdout to one file and stderr to another. How would you redirect both to the same file? See Redirections.
ls /nonexistent /tmp > out.txt 2> err.txt
The error is the function with FD 2

## 5 - $? holds the exit status of the last command (0 = success). && runs the next command only if the previous succeeded; || runs it only if the previous failed. Write a one-liner that creates /tmp/mydir only if it doesn’t already exist. See Exit Status.
```bash if [ ! -d /tmp/myDir ]; then mkdir /tmp/myDir; echo "myDir created"; fi ```

## 6 - Why does cd have to be built into the shell itself rather than a standalone program? (Hint: think about what a child process can and cannot affect in its parent.)
1. fork() — creates a child process (copy of the shell).                                                                                                                                                                               
2. exec() — the child replaces itself with the requested program.                                                                                                                                                                      
3. The child runs, possibly modifying its own state (cwd, env vars, etc.).                                                                                                                                                             
4. The child exits. Its state dies with it; the parent is untouched.                                                                                                                                                                   
                                                                               
If cd were a standalone binary, it would call chdir() inside the child process, then exit. The shell (parent) would stay in the original directory — nothing would change from the user's perspective.                                 
That's why cd is a builtin: a command the shell executes in its own process, without fork/exec. The shell itself calls chdir(), so its cwd actually changes. The same reason applies to export, source, exit, alias, etc.   

## 7 - Write a script that takes a filename as an argument ($1) and checks whether the file exists using test -f or [ -f ... ]. It should print different messages depending on whether the file exists. See Bash Conditional Expressions.
File script.sh

## 8 - Save the script from the previous exercise to a file (e.g., check.sh). Try running it with ./check.sh somefile. What happens? Now run chmod +x check.sh and try again. Why is this step necessary? (Hint: look at ls -l check.sh before and after the chmod.)
Verify if the file exists. The chmod + x able everyone to execute the file.

## 9 - What happens if you add -x to the set flags in a script? Try it with a simple script and observe the output. See The Set Builtin.
Add the permission to execute the file.

## 10 - Write a command that copies a file to a backup with today’s date in the filename (e.g., notes.txt → notes_2026-01-12.txt). (Hint: $(date +%Y-%m-%d)). See Command Substitution.
cp notes.txt "notes_$(date +%Y-%m-Yd)"

## 11 - Modify the flaky test script from the lecture to accept the test command as an argument instead of hardcoding cargo test my_test. (Hint: $1 or $@). See Special Parameters.
scriptLecture.sh

## 12 - Use pipes to find the 5 most common file extensions in your home directory. (Hint: combine find, grep or sed or awk, sort, uniq -c, and head.)
find ~ -type f -name '*.*' | sed -E 's/.*\.//' | sort | uniq -c | sort -rn | head -n 5                                                                                                                                                   


## 13 - xargs converts lines from stdin into command arguments. Use find and xargs together (not find -exec) to find all .sh files in a directory and count the lines in each with wc -l. Bonus: make it handle filenames with spaces. (Hint: -print0 and -0). See man xargs.
find ~/dev/BasicStudies -type f -name "*.sh" -print0 | xargs -0 wc -l

## 14 - Use curl to fetch the HTML of the course website (https://missing.csail.mit.edu/) and pipe it to grep to count how many lectures are listed. (Hint: look for a pattern that appears once per lecture; use curl -s to silence the progress output.)
 curl -s https://missing.csail.mit.edu/ | grep -oE 'href="/2026/[^"]+/"' | wc -l

## 15 - jq is a powerful tool for processing JSON data. Fetch the sample data at https://microsoftedge.github.io/Demos/json-dummy-data/64KB.json with curl and use jq to extract just the names of people whose version is greater than 6. (Hint: pipe to jq . first to see the structure; then try jq '.[] | select(...) | .name')
curl -s https://microsoftedge.github.io/Demos/json-dummy-data/64KB.json | jq '.[] | select(.version > 6) | .name'

## 16 - awk can filter lines based on column values and manipulate output. For example, awk '$3 ~ /pattern/ {$4=""; print}' prints only lines where the third column matches pattern, while omitting the fourth column. Write an awk command that prints only lines where the second column is greater than 100, and swaps the first and third columns. Test with: printf 'a 50 x\nb 150 y\nc 200 z\n'
printf 'a 50 x\nb 150 y\nc 200 z\n' | awk '{ t = $1; $1 = $3; $3 = t; }($2 > 100 ) '

## 17 - Dissect the SSH log pipeline from the lecture: what does each step do? Then build something similar to find your most-used shell commands from ~/.bash_history (or ~/.zsh_history).
ssh myserver 'journalctl -u sshd -b-1 | grep "Disconnected from"'
connect with myserver and exec the command between single quotes.
read the journal from the systemd
-u sshd -> filter by the sshd unity.
-b-1 -> the previous boot (b0 would be the current)
grep "Disconnected from" -> just these lines

sed -E 's/.*Disconnected from .* user (.*) [^ ]+ port.*/\1/'
extract the username, -E is extended Regex.
.*Disconnected from .* user -> Get everything until " user"
(.*) -> Capture group 1 -> username followed by space
\[^ ]+ -> non-space token, followed by space
port.* -> port and everything
replace every line by \1

sort
Without the uniq would be wrong.

uniq -c 
get all lines consecutives and get them in one, count them 

sort -nk1,1
numerically ordered just the column 1

tail -n10
get the last 10 lines.

awk '{print $2}'
get just the second line

paste -sd
concat all the lines separated them by comma

history 1 | awk '{print $2}' | sort | uniq -c | sort -nk1,1 | tail -n10 > ./BasicStudies/missingSemester/lecture1/mostUsedCommands.txt
