# Assignment 29: Interrogating the Kernel

In this assignment, you will write a program that leverages the "Everything is a file" philosophy via the `/proc` Virtual File System. 

You must build a highly optimized C or Rust application that parses the kernel's RAM to build a custom Process Information Tool (a mini version of `ps`).

## Requirements

1. **Language:** You may use C or Rust (Rust is heavily recommended due to `std::fs::read_dir`).
2. **The Target:** Iterate over every single directory in `/proc`.
3. **Filtering:** You must only process directories whose names contain *only numbers*. These are the directories corresponding to active PIDs.
4. **Data Extraction:** For every numeric directory (e.g., `/proc/1234`):
   - Read the `/proc/[PID]/comm` file to get the name of the executable.
   - Read the `/proc/[PID]/stat` file to get the process state (Running, Sleeping, Zombie). Note: The state is the 3rd field in this space-separated file.
5. **Output:** Print a neatly formatted table to the terminal.

### Example Output required:
```text
PID       STATE    COMMAND
------------------------------------
1         S        systemd
2         S        kthreadd
1452      S        gnome-shell
4592      R        alacritty
4601      R        my_proc_parser
```

## Hints & Rules

*   **Do not use system commands!** You are forbidden from calling `system("ps aux")` or spawning subprocesses. You must open and parse the files directly as if you were the operating system.
*   **Permissions:** You will notice some folders inside `/proc/[PID]` throw "Permission Denied" errors. That's because Ring 3 prevents you from reading the memory of processes owned by `root`. However, `/proc/[PID]/comm` and `stat` are safely readable by any user. Make sure your code gracefully ignores "Permission Denied" errors without crashing!
*   **The VFS is fast:** Because `/proc` isn't on a real hard drive, reading thousands of files from it takes milliseconds. You do not need to use multi-threading for this assignment.

This assignment proves that you understand that the OS is not a black box—it is a structure you can reach out and touch using basic file operations.
