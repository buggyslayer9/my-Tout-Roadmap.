# 8.6 Enums: Named Integer Constants

Magic numbers like `0`, `1`, `2` scattered throughout code are a maintenance nightmare. An `enum` (enumeration) lets you assign human-readable names to a set of related integer constants.

## Declaration

```c
typedef enum {
    STATE_IDLE,      // 0 (auto-assigned)
    STATE_RUNNING,   // 1
    STATE_PAUSED,    // 2
    STATE_STOPPED    // 3
} AppState;
```

By default, the first value is `0` and each subsequent value increments by 1. You can override this:

```c
typedef enum {
    LOG_DEBUG   = 0,
    LOG_INFO    = 1,
    LOG_WARNING = 2,
    LOG_ERROR   = 3,
    LOG_FATAL   = 4
} LogLevel;
```

## Usage

```c
AppState current = STATE_IDLE;

switch (current) {
    case STATE_IDLE:
        printf("Waiting for input...\n");
        break;
    case STATE_RUNNING:
        printf("Processing data...\n");
        break;
    case STATE_PAUSED:
        printf("Paused.\n");
        break;
    case STATE_STOPPED:
        printf("Terminated.\n");
        break;
}
```

## Why Enums Over `#define`

| Feature | `#define` | `enum` |
|---------|-----------|--------|
| Type safety | None (raw text substitution) | Compiler checks the type |
| Debugger visibility | Invisible (replaced before compilation) | Shows the enum name |
| Scope | Global (pollutes namespace) | Can be scoped |
| Auto-increment | Manual | Automatic |

GTK uses enums extensively for widget states, signal types, and configuration flags. You'll see types like `GtkOrientation`, `GtkAlign`, and `GtkResponseType` — all enums.
