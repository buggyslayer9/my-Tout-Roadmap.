# 13.7 Disconnecting Signals

When you connect a signal, `g_signal_connect` returns a `gulong` **handler ID**. You can use this ID to disconnect the callback later.

## When to Disconnect

- When a button should only work once (disable after first click).
- When you dynamically swap behavior (connect a different handler).
- When cleaning up resources to prevent callbacks on destroyed data.

## The Pattern

```c
// Save the handler ID when connecting.
gulong handler_id = g_signal_connect(button, "clicked", G_CALLBACK(on_click), data);

// Later, disconnect it.
g_signal_handler_disconnect(button, handler_id);
```

## Blocking vs Disconnecting

Sometimes you want to temporarily mute a signal without permanently removing the handler:

```c
// Temporarily silence the handler.
g_signal_handler_block(button, handler_id);

// Re-enable it.
g_signal_handler_unblock(button, handler_id);
```

## Disconnect All by Function

If you don't have the handler ID, you can disconnect by callback function:

```c
g_signal_handlers_disconnect_by_func(button, G_CALLBACK(on_click), data);
```
