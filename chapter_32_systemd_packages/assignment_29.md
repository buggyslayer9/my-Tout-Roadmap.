# Assignment 29

## Task

Create a systemd service and build a .deb package:

### Part 1: Create a Simple Daemon

1. Create a simple daemon script that:
   - Runs continuously (infinite loop)
   - Logs timestamp to a file every 5 seconds
   - Handles SIGTERM gracefully for clean shutdown

```bash
#!/bin/bash
# my-daemon.sh

LOG_FILE="/var/log/my-daemon.log"

log_message() {
    echo "[$(date '+%Y-%m-%d %H:%M:%S')] $1" >> "$LOG_FILE"
}

trap 'log_message "Daemon stopped"; exit 0' SIGTERM

log_message "Daemon started"

while true; do
    log_message "Running..."
    sleep 5
done
```

### Part 2: Write a systemd Service File

2. Create `/etc/systemd/system/my-daemon.service`:

```ini
[Unit]
Description=My Custom Daemon
After=network.target

[Service]
Type=simple
ExecStart=/usr/local/bin/my-daemon.sh
Restart=on-failure
RestartSec=5
User=root
Group=root

[Install]
WantedBy=multi-user.target
```

3. Test the service:
   ```bash
   sudo systemctl daemon-reload
   sudo systemctl start my-daemon
   sudo systemctl status my-daemon
   journalctl -u my-daemon -f
   sudo systemctl stop my-daemon
   ```

### Part 3: Build a .deb Package

4. Create the package structure:
   ```
   my-daemon-1.0/
   ├── DEBIAN/
   │   └── control
   └── usr/
       └── local/
           └── bin/
               └── my-daemon.sh
   ```

5. Create the `DEBIAN/control` file

6. Build and install:
   ```bash
   dpkg-deb --build my-daemon-1.0
   sudo dpkg -i my-daemon-1.0.deb
   ```

7. Verify the package works:
   ```bash
   sudo systemctl enable my-daemon
   sudo systemctl start my-daemon
   ```

---

## Required Knowledge

To solve this assignment, you need to understand:

1. **systemd** - Service manager and unit files
2. **Service types** - simple, forking, oneshot
3. **Journalctl** - Reading systemd logs
4. **dpkg** - Debian package management
5. **Package structure** - DEBIAN directory and control file

---

## Sources

- [systemd documentation](https://www.freedesktop.org/wiki/Software/systemd/)
- [Debian packaging guide](https://www.debian.org/doc/manuals/maint-guide/)
- [dpkg-deb manual](https://man7.org/linux/man-pages/man1/dpkg-deb.1.html)

---

## Hints

- Make sure the script is executable: `chmod +x my-daemon.sh`
- Use `trap` to handle SIGTERM for graceful shutdown
- The control file must have a blank line at the end
- Use `dpkg-deb --build --rootdir=...` for non-root building
- Check logs with `journalctl -u my-daemon --since "1 minute ago"`

## Expected Output

After installing the .deb package:

```
$ sudo systemctl status my-daemon
● my-daemon.service - My Custom Daemon
     Loaded: loaded (/etc/systemd/system/my-daemon.service; enabled; vendor preset: enabled)
     Active: active (running) since Sat 2026-03-14 12:00:00 UTC; 5s ago
   Main PID: 1234 (my-daemon.sh)
```

And `journalctl -u my-daemon` shows timestamped log entries.
