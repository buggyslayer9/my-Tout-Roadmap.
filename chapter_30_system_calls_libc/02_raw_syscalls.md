# 30.2 Raw System Calls (Bypassing `libc`)

What if we want to bypass the friendly `libc` wrappers? What if we are writing our own language compiler, or we want to execute a hyper-optimized application that removes the overhead of `glibc` entirely?

On Linux, you can directly ask the OS to execute a numbered syscall using the `syscall()` function provided by `<unistd.h>`.

## Example: Writing without `printf` or `write`

Every syscall in Linux has a permanent ID number.
For example, on x86_64 architecture:
- `SYS_read` is `0`
- `SYS_write` is `1`
- `SYS_open` is `2`
- `SYS_close` is `3`
- `SYS_exit` is `60`

Let's bypass the `libc` `write()` wrapper and talk to the kernel directly:

### In C:
```c
#include <unistd.h>
#include <sys/syscall.h>

int main() {
    char msg[] = "Hello Raw Kernel!\n";
    
    // syscall(Syscall_Number, Arg1, Arg2, Arg3)
    // Here, we invoke Syscall 1 (write), 
    // passing File Descriptor 1 (stdout), the string pointer, and the length.
    long result = syscall(SYS_write, 1, msg, 18);
    
    // We can also exit directly, bypassing libc's cleanup
    syscall(SYS_exit, 0); 
    
    return 0; // This line is never reached
}
```

### In Rust:
Safe Rust doesn't let you do this directly because raw syscalls are highly unsafe (you could pass garbage pointers directly into Ring 0). 
To make a raw Linux syscall in Rust, we must use `unsafe` and the `libc` crate (which provides the raw wrapper):

```toml
# Cargo.toml
[dependencies]
libc = "0.2"
```

```rust
fn main() {
    let msg = "Hello from Rust via Raw Syscall!\n";
    
    unsafe {
        libc::syscall(
            libc::SYS_write, 
            1, // File descriptor (STDOUT)
            msg.as_ptr(), // The raw pointer to the string
            msg.len() // The length
        );
        
        libc::syscall(libc::SYS_exit, 0);
    }
}
```

## Why do this?
For 99% of applications, you should use standard libraries. But for malware analysis, high-frequency trading where microseconds matter, or reverse-engineering legacy binaries, understanding how to read and write raw syscalls is the dividing line between junior coders and senior systems engineers.
