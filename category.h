#ifndef CATEGORY_H
#define CATEGORY_H

/* ================================================================
   MODULE 2 : Category Management (Linked List)  –  Header
   PKFIE Yaoundé  |  2025-2026

   NOTE : the 'char code[50]' field has been removed entirely.
          Category ID is automatically set to the first guest's
          person ID (same auto-generated counter).
   ================================================================ */

#include "person.h"

/* ---------------------------------------------------------------
   Struct : Category node (singly-linked list)
   --------------------------------------------------------------- */
typedef struct Category {
    int     id;           /* = first guest's person ID            */
    Person  guests[4];    /* up to 4 guests per category          */
    int     nb_guests;    /* actual count (0-4)                   */
    struct Category *next;
} Category;

/* ---------------------------------------------------------------
   Function prototypes
   --------------------------------------------------------------- */

/**
 * create_category
 * Interactively creates a new Category node (heap-allocated).
 * Prompts for guest count (max 4) and registers each guest.
 * Sets id = first guest's person ID.
 * Returns NULL on memory failure.
 */
Category *create_category(void);

/**
 * insert_category
 * Prepends a newly created category at the head of the list.
 */
void insert_category(Category **tete);

/**
 * delete_category
 * Finds the node whose id == id, unlinks and frees it.
 * Prints an error if not found.
 */
void delete_category(Category **tete, int id);

/**
 * update_category
 * Locates category by id, then interactively updates one of its guests.
 */
void update_category(Category *tete, int id);

/**
 * count_guest
 * Returns the total number of guests across all categories.
 */
int count_guest(Category *tete);

/**
 * sort_categories_desc
 * Bubble-sorts the linked list in descending order of nb_guests
 * by swapping node data (not relinking pointers).
 */
void sort_categories_desc(Category **tete);

/**
 * display_all_guests
 * Prints every category and its guests in formatted boxes.
 */
void display_all_guests(Category *tete);

#endif /* CATEGORY_H */
