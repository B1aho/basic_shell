# Basic Shell
- A simple Unix-like shell implementation in C, providing essential functionality such as command execution, process handling, and built-in commands. 
- This project showcases fundamental knowledge of system programming in C, including process creation and execution using fork() and exec(), input parsing, and directory navigation.

## Features
- Execute system commands (e.g., ls, pwd, echo)
- Built-in commands: cd, help, exit
- Can detect the system's package manager and check the availability of a package
- Process creation and execution
- Argument parsing, including support for quoted strings
- Basic prompt customization with working directory display

## Installation & Build
- To build the shell, use the provided Makefile. 
- Run the following command inside the project directory:
`make`
- Once compiled, you can start the shell by running:
`./shell`

## Example:
[gif.gif]

## Future Improvements
- Implement piping (|) and redirection (>, <)
- Add support for background processes (&)
