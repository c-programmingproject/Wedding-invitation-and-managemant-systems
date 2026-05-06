# =============================================================
#  WIGMS – Wedding Invitation and Gift Management System
#  Makefile  –  Modular version
#  PKFIE Yaoundé  |  2025-2026
# =============================================================

# ---------- Compiler & flags ----------
CC      = gcc
CFLAGS  = -Wall -Wextra -Wpedantic -std=c11 -g

# ---------- Target binary ----------
TARGET  = wigms

# ---------- Source & object files ----------
SRCS    = main.c person.c category.c priority.c gift.c ui.c
OBJS    = $(SRCS:.c=.o)

# ---------- Header dependencies ----------
#   Each .o depends on its own .c plus every header it includes.
DEPS_MAIN     = main.c     ui.h
DEPS_PERSON   = person.c   person.h   ui.h
DEPS_CATEGORY = category.c category.h person.h ui.h
DEPS_PRIORITY = priority.c priority.h category.h person.h
DEPS_GIFT     = gift.c     gift.h     ui.h
DEPS_UI       = ui.c       ui.h       person.h category.h priority.h gift.h

# =============================================================
#  Default target
# =============================================================
.PHONY: all
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)
	@echo ""
	@echo "  Build successful  -->  ./$(TARGET)"
	@echo ""

# =============================================================
#  Compile rules  (explicit so header changes trigger recompile)
# =============================================================
main.o: $(DEPS_MAIN)
	$(CC) $(CFLAGS) -c main.c -o main.o

person.o: $(DEPS_PERSON)
	$(CC) $(CFLAGS) -c person.c -o person.o

category.o: $(DEPS_CATEGORY)
	$(CC) $(CFLAGS) -c category.c -o category.o

priority.o: $(DEPS_PRIORITY)
	$(CC) $(CFLAGS) -c priority.c -o priority.o

gift.o: $(DEPS_GIFT)
	$(CC) $(CFLAGS) -c gift.c -o gift.o

ui.o: $(DEPS_UI)
	$(CC) $(CFLAGS) -c ui.c -o ui.o

# =============================================================
#  Convenience targets
# =============================================================
.PHONY: run
run: $(TARGET)
	./$(TARGET)

.PHONY: rebuild
rebuild: clean all

.PHONY: clean
clean:
	rm -f $(OBJS) $(TARGET)
	@echo "  Cleaned: object files and binary removed."
