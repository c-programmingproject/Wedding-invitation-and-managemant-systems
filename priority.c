/* ================================================================
   MODULE 3 : Priority Management (DPR – Merge Sort)  –  Implementation
   PKFIE Yaoundé  |  2025-2026
   ================================================================ */

#include <stdio.h>
#include <string.h>
#include "priority.h"

/* ---------------------------------------------------------------
   split_list  –  Floyd's slow/fast pointer
   Divides [source] into [*front] and [*back]
   --------------------------------------------------------------- */
void split_list(Category *source, Category **front, Category **back) {
    Category *lent, *rapide;

    if (source == NULL || source->next == NULL) {
        *front = source;
        *back  = NULL;
        return;
    }

    lent   = source;
    rapide = source->next;

    /* advance rapide two steps, lent one step */
    while (rapide != NULL) {
        rapide = rapide->next;
        if (rapide != NULL) {
            lent   = lent->next;
            rapide = rapide->next;
        }
    }

    *front      = source;
    *back       = lent->next;
    lent->next  = NULL;   /* cut the list in two */
}

/* ---------------------------------------------------------------
   merge_sorted  –  merge two sorted sub-lists (desc nb_guests)
   --------------------------------------------------------------- */
Category *merge_sorted(Category *a, Category *b) {
    Category *result;

    if (a == NULL) return b;
    if (b == NULL) return a;

    if (a->nb_guests >= b->nb_guests) {
        result       = a;
        result->next = merge_sorted(a->next, b);
    } else {
        result       = b;
        result->next = merge_sorted(a, b->next);
    }

    return result;
}

/* ---------------------------------------------------------------
   merge_sort_categories  –  recursive entry point
   --------------------------------------------------------------- */
void merge_sort_categories(Category **tete) {
    Category *head = *tete;
    Category *a, *b;

    if (head == NULL || head->next == NULL) return;   /* base case */

    split_list(head, &a, &b);
    merge_sort_categories(&a);
    merge_sort_categories(&b);
    *tete = merge_sorted(a, b);
}

/* ---------------------------------------------------------------
   prioritize_by_age  –  bubble sort inside each category (asc)
   --------------------------------------------------------------- */
void prioritize_by_age(Category *tete) {
    int    i, j;
    Person temp;

    while (tete != NULL) {
        for (i = 0; i < tete->nb_guests - 1; i++) {
            for (j = 0; j < tete->nb_guests - 1 - i; j++) {
                if (tete->guests[j].age > tete->guests[j + 1].age) {
                    temp               = tete->guests[j];
                    tete->guests[j]   = tete->guests[j + 1];
                    tete->guests[j + 1] = temp;
                }
            }
        }
        tete = tete->next;
    }

    printf("  Guests sorted by age (ascending) within each category.\n");
}

/* ---------------------------------------------------------------
   prioritize_by_social_class  –  bubble sort inside each category
   --------------------------------------------------------------- */
void prioritize_by_social_class(Category *tete) {
    int    i, j;
    Person temp;

    while (tete != NULL) {
        for (i = 0; i < tete->nb_guests - 1; i++) {
            for (j = 0; j < tete->nb_guests - 1 - i; j++) {
                if (strcmp(tete->guests[j].social_class,
                           tete->guests[j + 1].social_class) > 0) {
                    temp               = tete->guests[j];
                    tete->guests[j]   = tete->guests[j + 1];
                    tete->guests[j + 1] = temp;
                }
            }
        }
        tete = tete->next;
    }

    printf("  Guests sorted by social class within each category.\n");
}
