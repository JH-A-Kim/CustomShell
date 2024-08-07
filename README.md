# Simple Shell Program

## Overview

This is a simple shell program written in C that provides basic command-line functionality, including executing commands, managing history, handling signals, and supporting built-in commands like `cd`, `pwd`, `history`, and `exit`. It also supports special commands like `!!` to repeat the last command and `!n` to execute the nth command from history.

## Features

- **Command Execution:** Executes both built-in and external commands.
- **History Management:** Keeps track of the last 10 commands entered and allows re-execution of those commands.
- **Built-In Commands:**
  - `cd`: Changes the working directory.
  - `pwd`: Prints the current working directory.
  - `history`: Prints the history of commands.
  - `exit`: Exits the shell.
  - `help`: Provides information about built-in commands.
  - `!!`: Repeats the last command.
  - `!n`: Repeats the nth command from history.
  - `!-`: Clears the command history.
- **Signal Handling:** Handles `SIGINT` (Ctrl+C) to provide a custom help message.

## Files

- **shell.c:** The main source file containing the implementation of the shell program.

## Compilation

```sh
make clean
'''sh
make

