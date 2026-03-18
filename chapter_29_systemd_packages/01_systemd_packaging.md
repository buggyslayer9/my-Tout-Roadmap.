# 29.1 Systemd, Init Systems & Service Management

## The Boot Process

```
BIOS/UEFI → Bootloader (GRUB) → Kernel → Init System → Services → Login
```

The **init system** is PID 1 — the first userspace process. It starts all other services.

## Init System Comparison

| Init System | Used By | Type |
|-------------|---------|------|
| **systemd** | Ubuntu, Fedora, Arch, Debian | Service manager + much more |
| **OpenRC** | Gentoo, Alpine | Shell-script based |
| **runit** | Void Linux | Minimal, supervision |
| **s6** | Some embedded | Supervision suite |

## Writing a systemd Service

```ini
# /etc/systemd/system/my-app.service
[Unit]
Description=My Custom Application
After=network.target

[Service]
Type=simple
ExecStart=/usr/local/bin/my-app
Restart=on-failure
RestartSec=5
User=myapp
Group=myapp
Environment=APP_ENV=production

[Install]
WantedBy=multi-user.target
```

### Service Commands

```bash
sudo systemctl start my-app        # Start service
sudo systemctl stop my-app         # Stop service
sudo systemctl restart my-app      # Restart
sudo systemctl enable my-app       # Start on boot
sudo systemctl disable my-app      # Don't start on boot
sudo systemctl status my-app       # Check status
journalctl -u my-app -f            # Follow logs
```

---

# 30.1 Package Management & Building Packages

## Building a .deb Package

```
my-app-1.0/
├── DEBIAN/
│   └── control          ← Package metadata
├── usr/
│   └── local/
│       └── bin/
│           └── my-app   ← Your binary
```

### `DEBIAN/control`
```
Package: my-app
Version: 1.0
Architecture: amd64
Maintainer: Ayman Salem <ayman@example.com>
Description: My custom application
Depends: libc6 (>= 2.31)
```

```bash
dpkg-deb --build my-app-1.0/
sudo dpkg -i my-app-1.0.deb
```

## Assignment 29-30

**Task**: 
1. Write a systemd service file for a simple daemon (shell script that logs timestamps)
2. Install, start, enable, and check logs with `journalctl`
3. Build a `.deb` package containing your daemon + service file
4. Install it with `dpkg` and verify it starts automatically

**Sources**:
- [systemd documentation](https://www.freedesktop.org/wiki/Software/systemd/)
- [Debian packaging tutorial](https://www.debian.org/doc/manuals/maint-guide/)
