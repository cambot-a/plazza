# PLAZZA

> *"Who said anything about pizzas?"*

## Overview

Plazza is a concurrent pizzeria simulation written in C++.

The application simulates:

- A reception
- Multiple kitchens
- Multiple cooks per kitchen
- Concurrent pizza preparation

---

# Build

## Requirements

- C++17
- POSIX system
- Make
- pthread

## Compilation

```bash
make
```

Available rules:

```bash
make re
make clean
make fclean
```

---

# Usage

```bash
./plazza <multiplier> <cooks> <reload_time_ms>
```

Example:

```bash
./plazza 2 5 2000
```

| Argument | Description |
|---|---|
| `multiplier` | Pizza cooking time multiplier |
| `cooks` | Number of cooks per kitchen |
| `reload_time_ms` | Ingredient regeneration interval |

---

# Reception

The reception:

- Accepts commands
- Parses orders
- Dispatches pizzas
- Creates kitchens dynamically
- Balances workload
- Displays kitchen status

## Commands

### Order pizzas

```txt
regina XXL x2; fantasia M x1
```
# Order Grammar

```txt
S := TYPE SIZE NUMBER [; TYPE SIZE NUMBER]*
TYPE := [a..zA..Z]+
SIZE := S|M|L|XL|XXL
NUMBER := x[1..9][0..9]*
```

### Display status

```txt
status
```

---

# Kitchens

Each kitchen is a child process.

Rules:

- Maximum capacity = `2 * cooks`
- Auto closes after `5s` inactivity
- Regenerates ingredients over time
- Communicates using IPC

Each cook:

- Is a thread
- Can cook one pizza at a time
- Is managed through a thread pool

---

# IPC

Reception and kitchens communicate through IPC.

Possible implementations:

- Named pipes
- UNIX sockets
- Message queues
- Shared memory

---

# Pizzas

| Pizza | Ingredients | Time |
|---|---|---|
| Margarita | dough, tomato, gruyere | `1s * multiplier` |
| Regina | dough, tomato, gruyere, ham, mushrooms | `2s * multiplier` |
| Americana | dough, tomato, gruyere, steak | `2s * multiplier` |
| Fantasia | dough, tomato, eggplant, goat cheese, chief love | `4s * multiplier` |

---

# Ingredients

Each kitchen starts with:

```txt
5 units of each ingredient
```

Regeneration:

```txt
+1 ingredient every N milliseconds
```

---
