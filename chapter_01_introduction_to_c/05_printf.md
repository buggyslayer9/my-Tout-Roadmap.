# 1.5 Formatting Output with printf

`printf` isn't just a print statement. It's a highly sophisticated string formatter that has been ported to almost every language on earth. It stands for "print formatted", and it is your primary debugging tool and command-line Swiss Army knife.

## The Specifiers

`printf` scans your string for `%` signs. When it finds one, it expects you to provide a matching variable after the string.

| Specifier | What it does | Example | Output |
| --------- | ------------ | ------- | ------ |
| `%d` / `%i` | Decimal integers | `printf("%d", 42)` | `42` |
| `%f` | Floats (dec. places) | `printf("%.2f", 3.14159)` | `3.14` |
| `%c` | A single character | `printf("%c", 'A')` | `A` |
| `%s` | A null-terminated string | `printf("%s", "Unix")` | `Unix` |
| `%p` | A raw memory pointer | `printf("%p", ptr)` | `0x7ffc1234` |
| `%x` | Hexadecimal format | `printf("0x%x", 255)` | `0xff` |

## Putting It Together

```c
#include <stdio.h>

int main(void) {
    int pid = 1;
    char process_name[] = "init";
    float uptime = 99.98f;
    
    printf("Process [%d] is %s. Uptime: %.2f%%\n", pid, process_name, uptime);
    // Process [1] is init. Uptime: 99.98%
    
    return 0;
}
```

## Width, Alignment, and Padding

When building command-line table outputs, `printf` does the alignment math for you.

```c
int main(void) {
    // %-10s means print a string, left-aligned (-), taking up exactly 10 spaces.
    // %5d means right-aligned integer, taking up 5 spaces.
    
    printf("%-10s %5d\n", "Item", 42);
    printf("%-10s %5d\n", "Keyboard", 102);
    printf("%-10s %5d\n", "Mouse", 1);
    
    return 0;
}
```
Output:
```text
Item          42
Keyboard     102
Mouse          1
```

## The Dangers of printf (Security 101)

Because C gives you a loaded gun, `printf` can be dangerous if misused. It is the source of the infamous **Format String Vulnerability**.

```c
// VERY BAD. NEVER DO THIS.
void insecure_print(char *user_input) {
    // If the user types "%x %x %x" they will start reading your RAM!
    // If they type "%n" they might be able to overwrite memory and hack your app!
    printf(user_input); 
}

// THE C VETERAN WAY
void secure_print(char *user_input) {
    // Safely treat user input strictly as a string literal.
    printf("%s", user_input); 
}
```

Always, *always* use format specifiers when printing variables. Never let a variable be the primary string of `printf`.

## Debugging with printf

Before you get comfortable with `gdb`, `printf` is going to be your debugger. Learn to use the C preprocessor macros to trace your code automatically:

```c
#include <stdio.h>

void crash_investigation() {
    // __func__ and __LINE__ are magical macros injected by the compiler!
    printf("[DEBUG] Entered function %s on line %d\n", __func__, __LINE__);
}

int main(void) {
    crash_investigation();
    return 0;
}
```
Output:
`[DEBUG] Entered function crash_investigation on line 5`

## GTK and printf

Even when you move to visual GUI apps, `printf` style formatting comes with you:

```c
// GTK string magic behind the scenes:
char *label_text = g_strdup_printf("Downloading file %d of %d...", current, total);
gtk_label_set_text(GTK_LABEL(my_label), label_text);
g_free(label_text); // Manual memory cleanup! We'll get to that.
```

Master `printf`. It's the Unix way.
