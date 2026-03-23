# Assignment 31

## Task

Build a minimal bootable Linux system using one of the three approaches:

---

### Option A: Buildroot (Recommended for Beginners)

1. Clone and configure Buildroot:
   ```bash
   git clone https://github.com/buildroot/buildroot.git
   cd buildroot
   make menuconfig
   ```

2. Configure the following:
   - Target architecture: x86_64
   - Build options: Enable compiler optimizations
   - System configuration:
     - Root filesystem: ext4
     - Init system: BusyBox
     - /dev management: eudev
   - Kernel: Linux 6.x (use default config)
   - Target packages: 
     - BusyBox
     - Network: wget, curl
     - Shell: bash (optional)
   - Filesystem images: ext4

3. Build:
   ```bash
   make -j$(nproc)
   ```

4. Test in QEMU:
   ```bash
   qemu-system-x86_64 \
     -kernel output/images/bzImage \
     -drive file=output/images/rootfs.ext4 \
     -append "root=/dev/sda" \
     -m 512M
   ```

---

### Option B: Live ISO (Intermediate)

1. Install live-build:
   ```bash
   sudo apt install live-build
   ```

2. Create a minimal Debian-based distro:
   ```bash
   mkdir my-distro && cd my-distro
   lb config --distribution bookworm --architectures amd64
   ```

3. Add custom packages:
   ```bash
   echo "vim" > config/package-lists/my-packages.list.chroot
   echo "curl" >> config/package-lists/my-packages.list.chroot
   ```

4. Add a custom welcome message:
   ```bash
   mkdir -p config/includes.chroot/etc/update-motd.d/
   echo '#!/bin/sh
   echo "Welcome to My Custom Linux!"' > config/includes.chroot/etc/update-motd.d/01-welcome
   chmod +x config/includes.chroot/etc/update-motd.d/01-welcome
   ```

5. Build and test:
   ```bash
   sudo lb build
   qemu-system-x86_64 -cdrom live-image-amd64.hybrid.iso -m 2G
   ```

---

## Required Knowledge

To solve this assignment, you need to understand:

1. **Build system** - GNU Make, configuration interfaces
2. **Cross-compilation** - Building for different architectures
3. **Filesystems** - ext4, squashfs
4. **QEMU** - Virtual machine testing
5. **ISO9660** - Live CD/DVD format

---

## Sources

- [Linux From Scratch](https://www.linuxfromscratch.org/lfs/view/stable/)
- [Buildroot Manual](https://buildroot.org/downloads/manual/manual.html)
- [Debian live-build docs](https://live-team.pages.debian.net/live-manual/)
- [QEMU documentation](https://www.qemu.org/documentation/)

---

## Hints

- Start with Buildroot for fastest results (30-60 minutes)
- Use `make help` to see all targets
- Increase QEMU RAM if system runs slowly: `-m 2G`
- Use `-nographic` with QEMU for console-only testing
- Take a snapshot of your VM so you can revert changes

## Expected Outcome

After completing this assignment, you should have:

1. A bootable Linux system (either Buildroot image or Live ISO)
2. Ability to log in (root with no password for Buildroot)
3. Basic commands working: `ls`, `cat`, `echo`, `date`
4. Network connectivity (if configured)
5. Screenshot of the system running in QEMU
