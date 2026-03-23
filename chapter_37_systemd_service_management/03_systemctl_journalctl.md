# 33.3 Managing the System (`systemctl` and `journalctl`)

Once you drop a `.service` file into `/etc/systemd/system/`, `systemd` will not read it automatically.

You use the primary configuration command, `systemctl`, to interact with PID 1.

## Controlling the Daemon
You must reload the systemd manager configuration every time you edit or create a `.service` file:
```bash
$ sudo systemctl daemon-reload
```

Then you can control your app:
```bash
# Launch the application running in the background right now
$ sudo systemctl start my_webserver

# Stop the application
$ sudo systemctl stop my_webserver

# Enable auto-start when the system boots up
$ sudo systemctl enable my_webserver

# If it crashed, tell me why it crashed and what its current status is
$ sudo systemctl status my_webserver
```

## Reading Logs with `journalctl`

In old Linux, if your app crashed, you had to `cat /var/log/syslog` and manually `grep` through gigabytes of text looking for your specific program's output, mixed together with networking logs and hardware failures. 

`systemd` solved this by inventing the **Journal** (`systemd-journald`).

Because `systemd` spawns every process on the computer, it automatically hijacks File Descriptor 1 (`stdout`, `printf()`) and File Descriptor 2 (`stderr`, `fprintf(stderr)`) for *every single program*.

It stores these outputs in a highly compressed, indexed binary database rather than a flat text file.

You read this database using `journalctl`.

```bash
# Show me only the logs exactly matching my C web server, and nothing else
$ sudo journalctl -u my_webserver

# Show me the logs for my web server hitting errors TODAY
$ sudo journalctl -u my_webserver --since today

# "Tail" the logs live. (Update instantly when a new printf happens)
$ sudo journalctl -u my_webserver -f
```

## Why this changes everything for developers
In C or Rust backend development, you **do not need to write files** for logging!
You do not need to say `FILE *log = fopen("/var/log/my_app.log");`.

You can literally just use `printf("User logged in\n");`.
Because `systemd` captures standard output and standard error silently, your print statements automatically become part of the central, rotating, infinitely-queryable system journal.
