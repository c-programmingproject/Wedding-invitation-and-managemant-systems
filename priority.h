#ifndef PRIORITY_H
#define PRIORITY_H

/* ================================================================
   MODULE 3 : Priority Management (DPR – Merge Sort)  –  Header
   PKFIE Yaoundé  |  2025-2026

   DPR = Divide – Process – Recombine
   ================================================================ */

#include "category.h"

/* ---------------------------------------------------------------
   Public function prototypes
   --------------------------------------------------------------- */

/**
 * merge_sort_categories
 * Recursively sorts the linked list of categories in descending
 * order of nb_guests using the Merge Sort algorithm (DPR method).
 */
void merge_sort_categories(Category **tete);

/**
 * prioritize_by_age
 * Bubble-sorts guests inside each category in ascending order
 * of age.
 */
void prioritize_by_age(Category *tete);

/**
 * prioritize_by_social_class
 * Bubble-sorts guests inside each category alphabetically
 * by social_class.
 */
void prioritize_by_social_class(Category *tete);

/* ---------------------------------------------------------------
   Internal helpers (declared here for transparency; used only
   inside priority.c)
   --------------------------------------------------------------- */

/**
 * split_list
 * Floyd's slow/fast pointer split: divides source into two
 * roughly equal halves (*front, *back).
 */
void split_list(Category *source, Category **front, Category **back);

/**
 * merge_sorted
 * Merges two already-sorted lists (descending nb_guests) into one.
 */
Category *merge_sorted(Category *a, Category *b);

#endif /* PRIORITY_H */
