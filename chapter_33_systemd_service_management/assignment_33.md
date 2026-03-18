# Assignment 33: Daemonizing Your Server

You've built a multi-threaded web server in Chapter 32. But right now, if you log out of your SSH session, the bash process dies, and your web server dies with it.

It's time to turn your code into a professional background Daemon.

## The Task

### 1. The Setup
Write a very simple C or Rust program that represents a critical backend worker.
It should run an infinitely looping `while(1)`.
Inside the loop, it should use `<unistd.h>` `sleep(2);` and print `"Worker Tick: Processing background jobs...\n"`.

Compile it to a binary named `my_worker`.

### 2. Manual Installation
In a real production environment, standard apps exist in `/opt/` or `/usr/local/bin/`.
Move your binary to `/usr/local/bin/my_worker`. (You will need `sudo mv`).

### 3. The Unit File
Create a new file called `my_worker.service` inside `/etc/systemd/system/`.
You will need `sudo nano` or `sudo vim` for this.

Write a clean `.ini` configuration:
- Describe the unit.
- Make sure the Service runs `/usr/local/bin/my_worker`.
- Add `Restart=always` and `RestartSec=1`.
- Add `WantedBy=multi-user.target`.

### 4. Taking Control
You must now execute the official daemon lifecycle:
1. Reload systemd so it sees your new file: `sudo systemctl daemon-reload`
2. Start the service: `sudo systemctl start my_worker`
3. Verify it's actually running: `sudo systemctl status my_worker`

If you did this correctly, `status` should print green text saying `Active: active (running)`.

### 5. Prove It
First, log out of your terminal entirely and log back in. The program should still be running!

Second, prove it is logging natively using the Journal:
Run `sudo journalctl -u my_worker -f`.
You should see your `"Worker Tick..."` printf statements appearing live, securely captured by the Kernel.

Third, test the Supervisor.
Open another terminal. Find the PID of your `my_worker` process using `ps aux | grep my_worker`.
Violently murder it using `sudo kill -9 <PID>`.

Wait 1 single second.
Run `sudo systemctl status my_worker` again.
You will see that `systemd` instantly resurrected the dead program to keep your "server" online.
