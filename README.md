# Task Manager Program

This is a C++ program that simulates a basic task manager, allowing users to view and sort processes based on various criteria such as name, PID, and memory usage. It fetches the list of processes from the system using the `tasklist` command (on Windows) and displays them in a user-friendly manner with support for sorting.

## Features

- Fetches the list of processes running on the system using the `tasklist` command.
- Displays the processes with the following details:
  - Image Name (Process Name)
  - PID (Process ID)
  - Session Name
  - Session Number
  - Memory Usage (Formatted with commas for thousands separation)
- Allows sorting of processes based on the following criteria:
  - Unsorted (Displays processes without sorting)
  - Sort by Name
  - Sort by PID
  - Sort by Memory Usage
- A simple user interface to interact with the program and select sorting criteria.

## Requirements

- **Operating System**: This program is designed for Windows since it uses the `tasklist` command.
- **C++ Compiler**: The program requires a C++ compiler supporting C++11 or higher.

