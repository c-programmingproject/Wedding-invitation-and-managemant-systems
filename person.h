#ifndef PERSON_H
#define PERSON_H

/* ================================================================
   MODULE 1 : Person Management  –  Header
   PKFIE Yaoundé  |  2025-2026
   ================================================================ */

/* ---------------------------------------------------------------
   ID_FILE : persisted ID counter (shared with category module)
   --------------------------------------------------------------- */
#define ID_FILE "last_id.txt"

/* ---------------------------------------------------------------
   Enumeration : wedding side
   --------------------------------------------------------------- */
typedef enum { LE, LA } Side;

/* ---------------------------------------------------------------
   Struct : Person
   --------------------------------------------------------------- */
typedef struct {
    int  id;
    char name[100];
    int  age;
    char social_class[50];
    Side side;
} Person;

/* ---------------------------------------------------------------
   Function prototypes
   --------------------------------------------------------------- */

/**
 * get_and_update_next_id
 * Reads the current ID from ID_FILE, returns it, then writes id+1
 * back to the file. Creates the file with value 1 if absent.
 */
int  get_and_update_next_id(void);

/**
 * reset_id_counter
 * Overwrites ID_FILE with the value 1.
 */
void reset_id_counter(void);

/**
 * create_person
 * Prompts the user for all fields, auto-assigns an ID.
 * Returns the fully initialised Person.
 */
Person create_person(void);

/**
 * display_person
 * Prints a formatted box with all fields of p.
 */
void display_person(Person p);

/**
 * update_person
 * Interactively updates every field of *p (ID is kept).
 */
void update_person(Person *p);

#endif /* PERSON_H */
