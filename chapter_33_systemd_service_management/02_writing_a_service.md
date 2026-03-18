# 33.2 Writing a Service File (`.service`)

You have just written an amazing C Web Server (from Chapter 32). You compile it to `/usr/local/bin/my_webserver`.

Now you want this server to start automatically when the server boots. And you want it to automatically restart if an internet request causes it to crash.

You do this by writing a Unit File (`my_webserver.service`) and placing it in `/etc/systemd/system/`.

## A Production-Grade Service File

Unlike old bash shell scripts, `systemd` uses incredibly crisp, declarative `.ini`-style configuration files.

```ini
# /etc/systemd/system/my_webserver.service

[Unit]
Description=My Custom C Web Server
# Do not start this service until the network is officially connected!
After=network.target

[Service]
# The path to your binary
ExecStart=/usr/local/bin/my_webserver

# Security: Do NOT run this as the root user!
# If the web server gets hacked, the hacker only gets 'www-data' permissions.
User=www-data
Group=www-data

# The Supervision Rules
# Always restart the process if it goes down, no matter what its exit code is.
Restart=always
# Wait 3 seconds before trying to restart it to prevent burning out the CPU
RestartSec=3

# The 'StandardOutput' automatically routes any printf() 
# statements from your C code secretly into the systemd Journal!
StandardOutput=journal

[Install]
# This tells systemd to launch this app as part of the normal 
# multi-user desktop boot sequence.
WantedBy=multi-user.target
```

## Security Sandboxing (The True Power)
Because `systemd` launches the process, it has god-like control over the process environment. You can add directives to the `[Service]` block to radically sandbox an application.

*   `ProtectSystem=strict` (The process cannot write to *any* file on the hard drive, except specific folders you allow).
*   `PrivateNetwork=yes` (The process has no access to the internet).
*   `ProtectHome=yes` (The process literally cannot see `/home/`).

If you add `ProtectSystem=strict` to your web server, even if a highly skilled zero-day hacker breaches your web application with an exploit, they are mathematically incapable of modifying any system binaries or installing rootkits.
