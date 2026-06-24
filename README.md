<div align="center">

# 🖥️ MiniShell Task Manager

![Language](https://img.shields.io/badge/Language-C-blue?style=for-the-badge&logo=c)
![Concepts](https://img.shields.io/badge/Concepts-Linked%20List%20%7C%20File%20I%2FO%20%7C%20Multi--File-informational?style=for-the-badge)
![Status](https://img.shields.io/badge/Status-Complete-brightgreen?style=for-the-badge)

*A shell-style task manager written in C — add, track, and persist tasks from the command line.*

</div>

---

## 📌 Overview

MiniShell Task Manager is a terminal program that lets you manage tasks through typed shell-like commands. Tasks are stored in a linked list at runtime and automatically saved to `tasks.txt` on exit. On the next run, saved tasks are loaded back in — no data is lost between sessions.

---

## ✨ Commands

| Command | Description |
|---|---|
| `add <title> <priority>` | Add a task with optional priority (`low`, `medium`, `high`) — defaults to `medium` |
| `list` | Print all tasks with status (`[+]` done, `[ ]` pending) and priority |
| `done <id>` | Mark a task as complete by ID |
| `delete <id>` | Remove a task and re-index remaining tasks |
| `search <keyword>` | Find tasks by keyword (case-insensitive) |
| `stats` | Show total, done, pending, and breakdown by priority |
| `save` | Manually save all tasks to `tasks.txt` |
| `help` | Print all available commands |
| `exit` | Save automatically and exit |

---

## 🧠 Concepts Used

- Linked list — tasks stored as dynamically allocated `Node` structs
- Nested structs — `Task` embedded inside `Node`
- Multi-file structure — logic split across `task.c`, `fileio.c`, `commands.c`, and `task.h`
- Header guards — `#ifndef` / `#define` / `#endif` in `task.h`
- File I/O — CSV-style persistence via `fprintf` / `fscanf` to `tasks.txt`
- `strrchr` / `strstr` / `tolower` — string parsing for priority detection and case-insensitive search
- `atoi` — converting command argument strings to integers for ID lookup
- `modifyId` — re-indexes all nodes after a deletion to keep IDs consistent

---

## 🖥️ Example Session

```
MiniShell Task Manager v1.0
Loaded 3 tasks from tasks.txt!

> list
[ ] 1. Buy groceries    [medium]
[ ] 2. Fix bug report   [high]
[+] 3. Read C book      [low]

> add Write README high
Task added! ID: 4

> done 2
Task 2 marked as complete!

> stats
Total:   4
Done:    2
Pending: 2
High:    2 | Medium: 1 | Low: 1

> exit
Saved 4 tasks to tasks.txt!
```

---

## 🔧 How to Compile & Run

**Requirements:** GCC or any C99-compatible compiler

```bash
# Compile all files
gcc main.c task.c fileio.c commands.c -o minishell

# Run (Linux / macOS)
./minishell

# Run (Windows)
minishell.exe
```

---

## 📁 Structure

```
MiniShellTaskManager/
├── main.c       # Entry point — input loop and command dispatching
├── task.c       # Core linked list operations (add, list, done, delete, search, stats)
├── fileio.c     # File I/O — load, save, freeList
├── commands.c   # Command parser and help menu
├── task.h       # Struct definitions and all function declarations
├── tasks.txt    # Auto-generated persistent storage
└── README.md
```

---

## ⚠️ Limitations

- Maximum task title length: **99 characters**
- Maximum priority length: **9 characters**
- No undo functionality
- Single-user, single-file storage only

---

## 📜 License

Released under the [MIT License](../LICENSE).
