# Assignment 35: The Wayland Audit

Because writing a raw Wayland client in C is an exercise in 500 lines of extreme boilerplate pain, this assignment shifts to an architectural audit. 

As a Systems Engineer, you must know how to trace the boundaries of the graphics stack on a live system.

## The Requirements

### 1. Identify your Display Server
Are you running X11 or Wayland right now?
Open your terminal and check the global environment variables:
```bash
echo $XDG_SESSION_TYPE
```
If it says `x11`, you are on legacy graphics. If it says `wayland`, you are on a modern compositor.

### 2. Find the Wayland Socket
If you are on Wayland, the Compositor creates an IPC socket file. Find it.
Run this command to search your user's temporary runtime folder:
```bash
ls -la /run/user/$(id -u)/ | grep wayland
```
Do you see `wayland-0`? What are its file permissions? Notice that the file type (the first character in the permissions block) is an `s` (for **Socket**), not a standard `-` (file) or `d` (directory)!

### 3. Trace a Wayland Connection Live
Remember `strace` from Chapter 30? We can use it to definitively prove that GTK applications secretly bypass X11 and talk directly to the `wayland-0` socket.

Run the simple GTK `gedit` text editor, but attach `strace` to it and filter specifically for the `connect()` system call:

```bash
strace -e connect gedit
```
*(If you don't have gedit, try `gnome-calculator` or any GTK/Qt app).*

Look closely at the incredibly verbose output. Mixed into all the connection attempts, you should find a line that looks exactly like this:
```c
connect(3, {sa_family=AF_UNIX, sun_path="/run/user/1000/wayland-0"}, 27) = 0
```
This is mathematical proof! The massive millions of lines of C code inside the GTK framework boiled down to a single POSIX `connect()` call to the local UNIX Domain Socket, officially beginning the Wayland Handshake.

### 4. Extra Credit: Prove XWayland
Some apps, like old Steam games or Discord, refuse to support Wayland.
Run Discord or Steam through `strace -e connect`.
You will **not** find `wayland-0`. Instead, you will find it trying to connect to a different socket: `/tmp/.X11-unix/X0`. 

That `/tmp/` socket belongs to **XWayland**, the invisible translator bridge bridging the 1980s protocol to your modern compositor!
