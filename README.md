# WIGMS – Wedding Invitation and Gift Management System

> **Course:** Modular C Programming | **Year:** 2025–2026
> **School:** PKFIE – Institut d'Excellence, Yaoundé
> **Professor:** Mbietieu Amos Mb.

---

## Table of Contents

1. [Project Overview](#project-overview)
2. [Architecture & File Structure](#architecture--file-structure)
3. [Module Descriptions](#module-descriptions)
4. [Header Dependency Map](#header-dependency-map)
5. [Prerequisites](#prerequisites)
6. [Build & Run on Ubuntu 24 LTS](#build--run-on-ubuntu-24-lts)
7. [Runtime Data Files](#runtime-data-files)
8. [Usage Guide](#usage-guide)
9. [Known Limitations](#known-limitations)

---

## Project Overview

WIGMS is a console-based C application split into **5 independent modules** that manage:

- Guest registration with auto-generated, file-persisted IDs
- Category management using a singly-linked list (up to 4 guests per category)
- Priority sorting via Merge Sort (Divide–Process–Recombine method)
- Gift management with a 50-item predefined catalogue and monetary donations
- Name-verified gift access cross-checked against a saved guest list

The interface uses ANSI colour codes and runs entirely in the terminal.

---

## Architecture & File Structure

WIGMS follows a simplified MVC pattern split across multiple source files:

```
wigms/
├── main.c           ← Entry point  (calls run_application)
│
├── person.h         ← Module 1 header
├── person.c         ← Module 1 implementation
│
├── category.h       ← Module 2 header
├── category.c       ← Module 2 implementation
│
├── priority.h       ← Module 3 header
├── priority.c       ← Module 3 implementation
│
├── gift.h           ← Module 4 header
├── gift.c           ← Module 4 implementation
│
├── ui.h             ← Module 5 header  (also holds ANSI macros)
├── ui.c             ← Module 5 implementation
│
├── Makefile         ← Builds each .c → .o then links
└── README.md        ← This file
│
│   (generated at runtime – not committed to version control)
├── last_id.txt      ← Persisted ID counter
├── guests.txt       ← Guest names written after each Person session
└── gifts.dat        ← Binary gift records (save / load)
```

### MVC mapping

| Layer | Role | Files |
|---|---|---|
| **Model** | Data structures & business logic | `person`, `category`, `priority`, `gift` |
| **Controller** | Menu routing & input validation | `ui.c` |
| **View** | ANSI-coloured console output | `ui.c` + ANSI macros in `ui.h` |

---

## Module Descriptions

### Module 1 – `person.h` / `person.c` — Person Management

Defines the core `Person` struct and all operations on it.

**Data:**
```c
typedef enum { LE, LA } Side;

typedef struct {
    int  id;
    char name[100];
    int  age;
    char social_class[50];
    Side side;
} Person;
```

**Key functions:**

| Function | Description |
|---|---|
| `get_and_update_next_id()` | Reads current ID from `last_id.txt`, returns it, saves `id+1` |
| `reset_id_counter()` | Overwrites `last_id.txt` with `1` |
| `create_person()` | Prompts user for all fields; auto-assigns ID |
| `display_person(p)` | Prints a formatted box with all fields |
| `update_person(&p)` | Interactively edits every field (ID preserved) |

**Design note:** `ID_FILE` (`"last_id.txt"`) is defined in `person.h` so both `person.c` and `ui.c` share the same constant without duplication.

---

### Module 2 – `category.h` / `category.c` — Category Management

Manages a singly-linked list of `Category` nodes. Each node holds up to 4 `Person` guests. The `char code[50]` field from earlier drafts has been removed; the category ID is automatically set to the first guest's person ID.

**Data:**
```c
typedef struct Category {
    int     id;           /* = first guest's person ID  */
    Person  guests[4];    /* up to 4 guests             */
    int     nb_guests;    /* actual count  (0-4)        */
    struct Category *next;
} Category;
```

**Key functions:**

| Function | Description |
|---|---|
| `create_category()` | Prompts for guest count & registers each guest; sets `id` automatically |
| `insert_category(&head)` | Prepends a new category at the list head |
| `delete_category(&head, id)` | Unlinks and frees the node with matching `id` |
| `update_category(head, id)` | Updates one guest inside the target category |
| `count_guest(head)` | Returns total guest count across all categories |
| `sort_categories_desc(&head)` | Bubble-sorts nodes descending by `nb_guests` |
| `display_all_guests(head)` | Prints every category and its guests |

---

### Module 3 – `priority.h` / `priority.c` — Priority Management (DPR)

Implements the **Divide – Process – Recombine** algorithm (Merge Sort) on the category linked list, plus intra-category bubble sorts.

**Key functions:**

| Function | Description |
|---|---|
| `merge_sort_categories(&head)` | Recursive Merge Sort on categories (descending `nb_guests`) |
| `split_list(src, &front, &back)` | Floyd's slow/fast pointer split into two halves |
| `merge_sorted(a, b)` | Merges two sorted sub-lists back into one |
| `prioritize_by_age(head)` | Bubble-sorts guests inside each category by age (ascending) |
| `prioritize_by_social_class(head)` | Bubble-sorts guests inside each category alphabetically |

---

### Module 4 – `gift.h` / `gift.c` — Gift Management

Manages a flat array of up to 100 `Gift` records backed by a 50-item read-only catalogue. Item 50 is always a monetary donation with a user-entered amount (minimum 10,000 FCFA). Guest identity is verified against `guests.txt` before any gift is recorded.

**Data:**
```c
typedef struct {
    int   gift_id;
    char  gift_name[100];
    float value;
    char  guest_name[100];
} Gift;
```

**Key functions:**

| Function | Description |
|---|---|
| `gift_module_init()` | Prompts for couple names once (idempotent) |
| `register_gift(gifts, &nb)` | Verifies name (3 attempts) → shows catalogue → records gift |
| `display_gifts(gifts, nb)` | Prints full list with running total in FCFA |
| `update_gifts(gifts, nb)` | Replaces a registered gift with a new catalogue selection |
| `total_gift_value(gifts, nb)` | Returns integer sum of all gift values |
| `save_gifts(gifts, nb)` | Binary write to `gifts.dat` |
| `load_gifts(gifts, &nb)` | Binary read from `gifts.dat` |

**Catalogue categories (50 items):**
Household & Kitchen (1–10), Bedroom & Linen (11–15), Dining & Entertaining (16–20),
Electronics (21–25), Décor & Art (26–30), Travel & Leisure (31–35),
Fashion & Accessories (36–40), Food & Drink (41–45), Books & Stationery (46–49),
Monetary Donation (50).

---

### Module 5 – `ui.h` / `ui.c` — User Interface

Contains all menus, screen layouts, and validated input helpers. Also defines the ANSI colour macros and `CONSOLE_WIDTH` used by every other module.

**ANSI macros (defined in `ui.h`):**
```c
#define RESET   "\033[0m"
#define BOLD    "\033[1m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define CYAN    "\033[36m"
#define MAGENTA "\033[35m"
#define WHITE   "\033[37m"
```

**Key functions:**

| Function | Description |
|---|---|
| `read_int(prompt, min, max)` | Loops until user enters integer in `[min, max]` |
| `read_float(prompt, min, max)` | Loops until user enters float in `[min, max]` |
| `read_string(prompt, buf, len)` | Loops until user enters a non-empty string |
| `confirm_action(question)` | Prints `(Y/N)` prompt; returns `1` for Y |
| `print_header(title)` | Clears screen and prints the standard WIGMS banner |
| `press_enter()` | Displays pause prompt and flushes stdin |
| `display_splash_screen()` | Full-screen splash on startup |
| `person_menu()` | Module 1 menu loop |
| `category_menu()` | Module 2 menu loop |
| `priority_menu()` | Module 3 menu loop |
| `gift_menu()` | Module 4 menu loop |
| `about_menu()` | Project information screen |
| `run_application()` | Main application loop (called from `main`) |

---

## Header Dependency Map

```
ui.h  ──────────────────────────────────────────────────┐
  └─ defines ANSI macros, CONSOLE_WIDTH                  │
                                                          │
person.h   (defines Person, Side, ID_FILE)               │
  └── included by: person.c, category.h, ui.c ─────────►┤
                                                          │
category.h (includes person.h)                           │
  └── included by: category.c, priority.h, ui.c ───────►┤
                                                          │
priority.h (includes category.h)                         │
  └── included by: priority.c, ui.c ───────────────────►┤
                                                          │
gift.h     (standalone – no person/category dependency)  │
  └── included by: gift.c, ui.c ───────────────────────►┤
                                                          │
main.c     (includes ui.h only) ────────────────────────►┘
```

All headers use **include guards** (`#ifndef MODULE_H / #define MODULE_H / #endif`) to prevent double inclusion.

---

## Prerequisites

Install on Ubuntu 24 LTS before building:

```bash
sudo apt update
sudo apt install -y gcc make
```

No external libraries are required. The project uses only the C standard library
(`stdio`, `stdlib`, `string`, `ctype`) plus the POSIX `strings.h` header (`strcasecmp`),
which is available by default on Ubuntu.

---

## Build & Run on Ubuntu 24 LTS

### Step 1 – Install tools

```bash
sudo apt update
sudo apt install -y gcc make
```

### Step 2 – Place all source files in one directory

```bash
mkdir ~/wigms && cd ~/wigms
# copy all .c, .h, Makefile, and README.md here
```

### Step 3 – Build

```bash
make
```

GCC compiles each `.c` file independently into a `.o` object, then links them into
the `wigms` binary. The `-Wall -Wextra -Wpedantic` flags are enabled — the project
compiles with **zero warnings**.

### Step 4 – Run

```bash
./wigms
# — or in one command —
make run
```

### Step 5 – Other Makefile targets

| Command | Description |
|---|---|
| `make` | Compile all modules and link (default) |
| `make run` | Build if needed, then launch |
| `make rebuild` | `clean` then full rebuild from scratch |
| `make clean` | Remove all `.o` files and the binary |

### Step 6 – Incremental rebuilds

Because the Makefile lists explicit header dependencies for every object file,
editing a single `.h` triggers recompilation of **only** the affected `.o` files —
not the entire project.

---

## Runtime Data Files

| File | Created by | Purpose |
|---|---|---|
| `last_id.txt` | First call to `get_and_update_next_id()` | Stores the next available person/category ID across sessions |
| `guests.txt` | End of every Person Management session | One name per line; Gift module reads this for identity verification |
| `gifts.dat` | Module 4 → Save option | Binary dump of the `Gift` array (count + records) |

**Important rules:**
- Keep all three files **in the same directory as the `wigms` binary** — the program uses relative paths.
- Keep `last_id.txt` between sessions to avoid duplicate IDs. Delete it (or use the reset option in the Person menu) only when starting completely fresh.
- `gifts.dat` is a raw binary file tied to the platform's `int` and `float` sizes — do not share it between machines with different architectures.

---

## Usage Guide

### Recommended workflow

```
1. Person Management  [1]
   └── Register all guests → names saved to guests.txt

2. Category Management  [2]
   └── Group guests into categories (up to 4 per group)
       └── Sort, count, or delete categories as needed

3. Priority Management  [3]
   └── Apply Merge Sort on categories  OR
       Sort guests within categories by age / social class

4. Gift Management  [4]
   └── Enter couple names (one-time setup)
       └── Each guest types their name → verified against guests.txt
           └── Browse 50-item catalogue → select gift
               └── Save to gifts.dat before exiting
```

### Gift registration flow

```
Gift menu → [1] Register a gift
  └─ Enter your name  (must match a name in guests.txt; 3 attempts allowed)
       └─ Browse the 50-item catalogue
            ├─ Items 1-49  → fixed price, recorded immediately
            └─ Item 50     → enter donation amount ≥ 10,000 FCFA
```

### ID counter behaviour

- The ID counter starts at `1` and **persists across sessions** via `last_id.txt`.
- Each time Person Management is entered, the current next ID is displayed.
- The operator is offered a **reset to 1** option before registering new guests.

---

## Known Limitations

- **Priority menu isolation:** The linked list inside `priority_menu()` is local to that menu session. Data entered in Category Management is not automatically shared with Priority Management within the same run. To sort data entered via categories, use the sort option inside the Category menu instead.
- **No authentication beyond name check:** Guest verification is case-insensitive string matching against `guests.txt` — no passwords or tokens.
- **Binary gift file is platform-local:** `gifts.dat` uses raw `fwrite`/`fread` on `struct Gift`. Do not transfer it between machines with different `int`/`float` sizes or endianness.
- **ANSI colours require a compatible terminal:** Works correctly on most Linux terminals (GNOME Terminal, xterm, Konsole). Raw escape codes may appear on Windows `cmd.exe` without enabling virtual terminal processing.
- **Maximum 100 gifts and 200 guest names:** These limits are compile-time constants (`MAX_GIFTS` in `gift.h`, and the `registered[200]` array inside `gift.c`). Increase them in source and recompile if needed.
#   r e s t a u r a t i o n - p r o  
 