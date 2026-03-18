# 20.1 Project Overview: The Task Manager

You have survived 19 chapters of intense C and GTK4 training. You've learned pointers, dynamic memory, GObject memory management, layout boxes, signal callbacks, and CSS styling.

Now, you have to put it all together.

For the Phase 2 Capstone, you will build a complete, professional-grade desktop application: **A Personal Task Manager**.

## Functional Requirements

1. **Dashboard (The List)**
   - Display all active tasks in a sleek, scrollable `GtkListBox`.
   - Each row must have a checkbox (`GtkCheckButton`) to mark it complete.
   - Rows must show the Task Title, Due Date, and a colored Priority Badge (Red/Yellow/Green).

2. **Task Creation Form**
   - A modal `GtkWindow` or a dedicated view for adding new tasks.
   - Text inputs for Title and Description.
   - A `GtkDropDown` to select Priority (High, Medium, Low).
   - Date selection.

3. **Filtering & Search**
   - Three main tabs (`GtkNotebook` or `GtkStack`): "All Tasks", "Pending", and "Completed".
   - A `GtkSearchEntry` in the `GtkHeaderBar` that automatically filters the list in real-time as the user types.

4. **Data Persistence**
   - The application must save tasks to the hard drive on exit, and load them on startup.
   - You will use raw binary File I/O for this.

5. **Aesthetics**
   - Use a custom `-styles.css` file to make the app look like a modern GNOME application. Card-style rows, clean spacing, and clear typography.

> **Instructor Challenge:** Don't just paste code. Plan this out on paper first. How does the data flow from the Add Task dialog into the `GList` of tasks, and then into the `GtkListBox`?
