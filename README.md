*This project has been created as part of the 42 curriculum by nmeunier, hulescur.*

## Description

minishell is a simplified UNIX shell written in C, inspired by Bash. The program reads user input interactively using GNU Readline (with command history), then processes it through three stages:

1. **Lexer** — splits raw input into typed tokens: words, pipes (`|`), redirections (`<`, `>`, `>>`, `<<`), and quoted strings (`'...'`, `"..."`)
2. **Parser** — assembles tokens into a linked list of command structures, each holding its arguments, input/output files, and redirection type
3. **Executor** — forks child processes, sets up pipes and file descriptors, resolves binary paths via `PATH`, and runs commands with `execve`

**Supported features:**
- Pipes between an arbitrary number of commands
- Input/output redirections: `<`, `>`, `>>`
- Heredoc (`<<`) with a delimiter
- Single and double quoted strings

## Instructions

### Dependencies

GNU Readline must be installed:

```bash
# Debian/Ubuntu
sudo apt-get install libreadline-dev

# macOS
brew install readline
```

### Compilation

```bash
make        # build the minishell binary
make clean  # remove object files
make fclean # remove object files and binary
make re     # full rebuild
```

Compiled with `cc -Wall -Wextra -Werror`.

### Execution

```bash
./minishell
```

No arguments are accepted. The prompt `minishell$` appears for each command. Exit with `Ctrl+D`.

**Examples:**
```
minishell$ ls -la
minishell$ cat file.txt | grep hello | wc -l
minishell$ echo "world" > out.txt
minishell$ cat < in.txt >> out.txt
```

## Resources

- [GNU Bash Reference Manual](https://www.gnu.org/software/bash/manual/bash.html) — reference for shell behavior and syntax
- [GNU Readline Library](https://tiswww.case.edu/php/chet/readline/rltop.html) — API used for the interactive prompt and history
- [Writing Your Own Shell — Stephen Brennan](https://brennan.io/2015/01/16/write-a-shell-in-c/) — practical walkthrough of shell implementation in C
- [POSIX Shell Command Language](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html) — formal grammar and behavior specification
- Man pages: [`execve(2)`](https://man7.org/linux/man-pages/man2/execve.2.html), [`fork(2)`](https://man7.org/linux/man-pages/man2/fork.2.html), [`pipe(2)`](https://man7.org/linux/man-pages/man2/pipe.2.html), [`dup2(2)`](https://man7.org/linux/man-pages/man2/dup2.2.html), [`readline(3)`](https://man7.org/linux/man-pages/man3/readline.3.html)

**AI usage:** AI was used for debugging (segfaults in the lexer and pipe execution logic, memory leaks).
