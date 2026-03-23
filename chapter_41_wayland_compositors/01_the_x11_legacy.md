# 35.1 The Death of X11

We have spent our time in C, GTK, and Rust building code that creates pixel-perfect interactive Windows. 

But how do those windows actually get drawn to the physical LCD monitor?
The answer is the **Display Server**.

For over 30 years, the global standard Display Server across all UNIX machines was **The X Window System** (specifically **X11** and the `X.org` server).

X11 is dead. It is no longer under active development. Why did it have to die?

## The Architecture of X11
X11 was created in the 1980s. Its primary design goal was not smooth 60fps animations, but **network transparency**. You could run a math application on a supercomputer in another building, and render its window on a dumb terminal on your desk over a slow network.

### The Problem with Tearing
Under X11, the X Server draws directly to the screen. 
However, there is a third program involved called the **Compositor** (which adds drop shadows, transparency, and animations to windows).

Because the Compositor is totally separate from the X Server, the timing is terrible. If an application updates its pixels, the X Server grabs them. Before the Compositor has a chance to apply drop shadows, the X Server might push half of the frame to the physical screen, causing massive visual lag, stutter, and **Screen Tearing**.

### The Problem with Security
In X11, the X Server has no concept of security boundaries.
If you install a random "Calculator" App that uses X11, that app can secretly monitor every single keystroke you type into your "Bank Login" app. The calculator can also capture screenshots of your entire desktop without asking for permission.
This is because all apps dump their data blindly into the central X Server, which happily shares it with everyone.

This architecture is fundamentally unfixable. The core engineers of `X.org` abandoned it to start over.
