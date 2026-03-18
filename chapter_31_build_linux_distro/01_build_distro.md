# 31.1 Building Your Own Linux Distribution

## Three Approaches

| Method | Difficulty | Best For |
|--------|-----------|----------|
| **Linux From Scratch (LFS)** | ★★★★★ | Deep learning, full control |
| **Buildroot** | ★★★☆☆ | Embedded/minimal systems |
| **Custom ISO (live-build/archiso)** | ★★☆☆☆ | Desktop distro based on existing base |

## Linux From Scratch (LFS) Overview

LFS builds **everything from source** — compiler, kernel, shell, init, libraries:

```
1. Prepare host system
2. Build temporary toolchain (cross-compiler)
3. Build core system (glibc, bash, coreutils, gcc)
4. Configure system (fstab, network, init)
5. Build Linux kernel
6. Install bootloader (GRUB)
7. Boot your system!
```

**Essential Reference**: [linuxfromscratch.org](https://www.linuxfromscratch.org/)

## Buildroot — Embedded Linux

```bash
git clone https://github.com/buildroot/buildroot.git
cd buildroot
make menuconfig    # Configure target arch, packages, filesystem
make               # Build everything
# Output: output/images/rootfs.ext2, bzImage
```

### Key Buildroot Configuration

```
Target Architecture: x86_64
Toolchain: Buildroot toolchain (glibc)
System configuration:
  - Root filesystem: ext4
  - Init system: systemd
  - /dev management: eudev
Kernel: Linux 6.x (custom config)
Packages: busybox, openssh, gtk4, ...
Filesystem: ext4 root, squashfs for live
Bootloader: GRUB2
```

---

# 32.1 Creating a Live ISO

## Using `live-build` (Debian-based)

```bash
# Install tools
sudo apt install live-build

# Create project
mkdir my-distro && cd my-distro
lb config \
  --distribution bookworm \
  --architectures amd64 \
  --archive-areas "main contrib non-free non-free-firmware" \
  --bootappend-live "boot=live components keyboard-layouts=us" \
  --debian-installer none

# Add custom packages
echo "firefox-esr" >> config/package-lists/my-packages.list.chroot
echo "neovim" >> config/package-lists/my-packages.list.chroot
echo "build-essential" >> config/package-lists/my-packages.list.chroot

# Add custom files (wallpaper, configs)
mkdir -p config/includes.chroot/etc/skel
cp my-wallpaper.png config/includes.chroot/etc/skel/

# Build ISO
sudo lb build

# Test in QEMU
qemu-system-x86_64 -cdrom live-image-amd64.hybrid.iso -m 2G
```

## Assignment 31-32 — Capstone: Build Your Mini Distro

**Task**: Build a minimal bootable Linux system:

### Option A (LFS — Advanced)
1. Follow LFS chapters 1-8 to build a minimal system
2. Boot it in a VM (QEMU or VirtualBox)

### Option B (Buildroot — Intermediate)  
1. Configure Buildroot for x86_64 with busybox + networking
2. Boot the resulting image in QEMU
3. Add a custom startup script

### Option C (live-build — Beginner)
1. Create a Debian-based live ISO with custom packages
2. Include a custom wallpaper and shell configuration
3. Boot it in QEMU and verify everything works

**Sources**:
- [Linux From Scratch Book](https://www.linuxfromscratch.org/lfs/view/stable/)
- [Buildroot Manual](https://buildroot.org/downloads/manual/manual.html)
- [Debian live-build docs](https://live-team.pages.debian.net/live-manual/)
- [ArchWiki — archiso](https://wiki.archlinux.org/title/Archiso)

---

## 📚 Resources for This Chapter

### Essential Guides
- [**Linux From Scratch**](https://www.linuxfromscratch.org/lfs/view/stable/) — Build a full system from source ⭐
- [**Beyond Linux From Scratch**](https://www.linuxfromscratch.org/blfs/view/stable/) — Add desktop, networking, X11/Wayland
- [**Buildroot Manual**](https://buildroot.org/downloads/manual/manual.html) — Official embedded Linux guide
- [**Yocto Project**](https://docs.yoctoproject.org/) — Industrial-grade embedded Linux

### Desktop Customization
- [**ArchWiki: archiso**](https://wiki.archlinux.org/title/Archiso) — Build Arch-based ISOs
- [**Debian live-build**](https://live-team.pages.debian.net/live-manual/) — Debian/Ubuntu-based ISOs
- [**Calamares Installer**](https://calamares.io/) — Universal Linux installer framework

### Testing Tools
- `qemu-system-x86_64` — Fast VM for testing ISOs
- VirtualBox, GNOME Boxes — GUI alternatives

