# 4.5 Variable Scope: The Walls of the Castle

Scope defines *where* a variable legally exists. When execution leaves a scope block `{ }`, all variables created inside it are instantly deleted from RAM.

## Local Scope (The Good)

Variables defined inside a function (or inside a loop) are **local**. They are born when the `{` opens, and they die when the `}` closes.
Local variables are invisible to the rest of the application.

```c
void calculate_taxes(void) {
    int tax_rate = 5; // Local. Only calculate_taxes() can see this.
}

int main(void) {
    // ERROR: main has no idea what 'tax_rate' is. It doesn't exist here.
    printf("%d", tax_rate); 
    return 0;
}
```

## Global Scope (The Bad)

Variables defined outside of *all* functions are **global**. They are born when the `.exe` starts, and they die when it exits. Every single function in the file can read and write to them.

```c
int global_lives = 3;  // Global state

void player_hits_spike(void) {
    global_lives--; // Any function can modify this randomly.
}

int main(void) {
    printf("Lives: %d\n", global_lives);
    return 0;
}
```

> **Why do veterans hate global variables?** Because tracking bugs becomes impossible. If `global_lives` randomly drops to 0, which of your 500 functions accidentally decremented it? You have no way of knowing. Keep state local, and pass variables between functions manually.
