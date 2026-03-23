# 37.1 Phase 4 Capstone: The "SysGuard" Daemon

You have reached the end of Phase 4: Systems and Operating Systems.
You now understand:
1. The Kernel VFS (`/proc`)
2. `libc` and raw system calls.
3. IPC (`fork()`, pipes).
4. Network Sockets (TCP `bind`, `listen`, `accept`).
5. Process Supervision (`systemd`).

It is time to combine 100% of these concepts into a single, massive C (or Rust) project.

## The Specification: SysGuard

You must build a Remote System Monitoring Daemon.
Imagine you manage a fleet of 50 Linux servers. You need a way to connect to them remotely and ask: "What is your CPU temperature, and how much RAM do you have available?"

### Requirements

1. **The Core Engine**
   - The program must be written in C (or Rust using `<libc>`).
   - It must open a TCP Server Socket on port `9999`.
   - It must loop infinitely, `accept()`-ing incoming connections.
   - When a connection arrives, it must immediately `fork()` a child to handle the request so the parent can return to listening. (Handle `SIGCHLD` to prevent zombies).

2. **The Protocol**
   - The Child process must `read()` a command string sent by the client over TCP.
   - Support two commands:
     - `"MEM"`: The server must parse `/proc/meminfo`, extract total RAM and Free RAM in Megabytes, format it as a string, and `write()` it back down the socket.
     - `"CPU"`: The server must search `/proc/stat` or `/sys/class/thermal/thermal_zone0/temp`, extract the data, format it, and send it back.
   - After responding, the Child process must `close()` the socket and `exit(0)`.

3. **System Integration**
   - Use `syslog` or `printf` correctly so `journalctl` can capture when the daemon starts, when a client connects, and when it disconnects.
   - You must write a `sysguard.service` file.
   - You must deploy your binary to `/usr/local/bin/sysguard`.
   - You must start the service using `sudo systemctl start sysguard` and verify it survives a `kill -9` attack using systemd's `Restart=always` supervisor.

## How to Test
Once the daemon is running in the background, open a completely separate terminal tab.
Act like the client using the legendary `nc` (Netcat) utility:

```bash
# Connect to your own daemon on port 9999 and send the text "MEM"
$ echo "MEM" | nc 127.0.0.1 9999

# Expected output from the socket back to your terminal:
Total RAM: 16384 MB - Free RAM: 8192 MB
```

This Capstone proves you are capable of writing backend software that fundamentally interfaces with the hardware via the Linux Kernel, whilst integrating professionally into the modern Systemd initialization architecture.
