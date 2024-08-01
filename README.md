# Self-Deletion
This project demonstrates how to create a self-deleting executable on Windows using C++. The program utilizes Windows API functions to manage file operations, including renaming the file with an alternate data stream and subsequently deleting it.

## Description
The self-deletion process involves several key steps:

1.Memory Allocation: Allocates memory for the FILE_RENAME_INFO structure.
2.Path Retrieval: Obtains the current executable's file path.
3.File Opening: Opens the file with the appropriate access rights for deletion.
4.Renaming: Changes the file name to include an alternate data stream.
5.Deletion: Deletes the file.

### Features
1.Self-Renaming: The executable renames itself to include an alternate data stream.
2.Self-Deletion: The renamed executable deletes itself from the filesystem.
3.Error Handling: The program includes error handling for various steps to ensure robustness.

### Requirements
Windows Operating System
C++ Compiler
Windows SDK (for access to Windows API functions)

### Usage
Compile the program using a C++ compiler.
Run the compiled executable.
The program will rename itself and then delete itself.

### Important Notes
The program should be run with appropriate permissions to ensure it can delete the file.
Error messages will be displayed in case of any issues during the process.

## Disclaimer
This code is for educational purposes only. Use it responsibly and ensure you understand the implications of running self-deleting executables on your system.
