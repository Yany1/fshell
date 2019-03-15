# traSH
This is a continuation of the Unix-like shell I did in my OS class. I want to add more functionality that makes it more usable.

## Goal

A complete overhaul of my previous sshell, along with additional features from a real shell (e.g. bash or tcsh)

## Features

* Execute programs or commands with arguments
* Change current working directory
* Redirect program input / output
* Pipelining
* Background execution

### Additional Features
* Log and reuse previous commands
* Auto complete

## Building

## File Organization
* `./include/` for all self defined header files
* `./src/` for all source files
* `./test/` for all testing files
* Final executable names fshell is at the outer most folder

## Conventions

### Coding Style
Follows Kernel style, specifically:
* 4 spaces indentation
* Curly brackets start on the next line.
* All operators padded with space, including if and while, except
for function calls
* All virtual disk files generated should be named `*.fs`
* In line comment using single-line comments. Documentations using multi-line comments

### Naming Convention
* small_letter_snake_case for type alias, variables and functions
* SCREAMING_SNAKE_CASE for macros
* All type alias postfixed with `_t`
* For functions associated with struct, function name always 
starts with the associated struct name, with the first parameter
being the struct pointer.

## Program Specification

### Command_line and Command

#### Command_line
A Command_line is an entire line of command entered by the user. It is a string that terminates wirh "\n\0"
* A command line cannot exceed 512 characters

#### Parsing Command_line

#### Command
A command is a string that issues a single shell command (built-in or otherwise). A command_line can consist of multiple commands pipelined together
* There can be at most 16 arguments per single command. An argument can be as long as 64 characters

### Pipeline

## Testing
Unit testing c script and a total testing shell script
