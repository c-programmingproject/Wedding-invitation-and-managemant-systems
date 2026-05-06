#ifndef GIFT_H
#define GIFT_H

/* ================================================================
   MODULE 4 : Gift Management  –  Header
   PKFIE Yaoundé  |  2025-2026

   Features:
   - 50 pre-defined gifts (item 50 = monetary donation ≥ 10,000 FCFA)
   - Guest name verified against guests.txt before registering
   - Binary persistence via gifts.dat
   ================================================================ */

/* ---------------------------------------------------------------
   Constants
   --------------------------------------------------------------- */
#define MAX_GIFTS      100
#define CATALOGUE_SIZE 50

/* ---------------------------------------------------------------
   Struct : Gift record
   --------------------------------------------------------------- */
typedef struct {
    int   gift_id;
    char  gift_name[100];
    float value;
    char  guest_name[100];
} Gift;

/* ---------------------------------------------------------------
   Struct : Catalogue entry (read-only table)
   --------------------------------------------------------------- */
typedef struct {
    char  name[100];
    float price;
} CatalogueItem;

/* ---------------------------------------------------------------
   The 50-item catalogue is defined in gift.c and exposed here
   as an extern so other modules can read it if needed.
   --------------------------------------------------------------- */
extern const CatalogueItem CATALOGUE[CATALOGUE_SIZE];

/* ---------------------------------------------------------------
   Function prototypes
   --------------------------------------------------------------- */

/**
 * gift_module_init
 * Must be called once before any other gift function.
 * Prompts for the couple's names (groom & bride) if not yet set.
 */
void gift_module_init(void);

/**
 * register_gift
 * Verifies the guest's name against guests.txt (3 attempts),
 * displays the catalogue, records the chosen gift.
 */
void register_gift(Gift gifts[], int *nb);

/**
 * display_gifts
 * Prints the full gift list with per-guest detail and running total.
 */
void display_gifts(Gift gifts[], int nb);

/**
 * update_gifts
 * Lets the operator replace any registered gift with a new selection.
 */
void update_gifts(Gift gifts[], int nb);

/**
 * total_gift_value
 * Returns the integer sum of all gift values in FCFA.
 */
int total_gift_value(Gift gifts[], int nb);

/**
 * save_gifts
 * Writes the Gift array to gifts.dat (binary, platform-local).
 */
void save_gifts(Gift gifts[], int nb);

/**
 * load_gifts
 * Reads the Gift array back from gifts.dat.
 */
void load_gifts(Gift gifts[], int *nb);

#endif /* GIFT_H */
