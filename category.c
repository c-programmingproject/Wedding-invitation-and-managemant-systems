/* ================================================================
   MODULE 2 : Category Management (Linked List)  –  Implementation
   PKFIE Yaoundé  |  2025-2026
   ================================================================ */

#include <stdio.h>
#include <stdlib.h>
#include "category.h"
#include "ui.h"

/* ---------------------------------------------------------------
   create_category
   --------------------------------------------------------------- */
Category *create_category(void) {
    int i;
    Category *c = (Category *)malloc(sizeof(Category));
    if (c == NULL) {
        printf("  [ERROR] Insufficient memory.\n");
        return NULL;
    }

    c->nb_guests = 0;
    c->next      = NULL;

    printf("  Number of guests (max 4) : ");
    scanf("%d", &c->nb_guests);
    while (getchar() != '\n');

    if (c->nb_guests > 4) c->nb_guests = 4;
    if (c->nb_guests < 0) c->nb_guests = 0;

    for (i = 0; i < c->nb_guests; i++) {
        printf("\n  --- Guest %d ---\n", i + 1);
        c->guests[i] = create_person();
    }

    /* Category ID = first guest's person ID */
    c->id = (c->nb_guests > 0) ? c->guests[0].id : 0;
    printf(CYAN "  [Category ID auto-set to : %d]\n" RESET, c->id);
    return c;
}

/* ---------------------------------------------------------------
   insert_category  (prepend)
   --------------------------------------------------------------- */
void insert_category(Category **tete) {
    Category *nouvelle = create_category();
    if (nouvelle == NULL) return;
    nouvelle->next = *tete;
    *tete = nouvelle;
}

/* ---------------------------------------------------------------
   delete_category
   --------------------------------------------------------------- */
void delete_category(Category **tete, int id) {
    Category *courant  = *tete;
    Category *precedent = NULL;

    while (courant != NULL && courant->id != id) {
        precedent = courant;
        courant   = courant->next;
    }

    if (courant == NULL) {
        printf("  [ERROR] Category ID=%d not found.\n", id);
        return;
    }

    if (precedent == NULL) *tete          = courant->next;
    else                    precedent->next = courant->next;

    free(courant);
}

/* ---------------------------------------------------------------
   update_category  (update one guest inside the category)
   --------------------------------------------------------------- */
void update_category(Category *tete, int id) {
    Category *courant = tete;
    int i;

    while (courant != NULL && courant->id != id)
        courant = courant->next;

    if (courant == NULL) {
        printf("  [ERROR] Category ID=%d not found.\n", id);
        return;
    }

    printf("  Which guest do you want to update? (1-%d) : ",
           courant->nb_guests);
    scanf("%d", &i);
    while (getchar() != '\n');
    i--;   /* convert to 0-based index */

    if (i >= 0 && i < courant->nb_guests)
        update_person(&courant->guests[i]);
    else
        printf("  [ERROR] Invalid guest number.\n");
}

/* ---------------------------------------------------------------
   count_guest
   --------------------------------------------------------------- */
int count_guest(Category *tete) {
    int total = 0;
    while (tete != NULL) {
        total += tete->nb_guests;
        tete = tete->next;
    }
    return total;
}

/* ---------------------------------------------------------------
   sort_categories_desc  (bubble sort on node data)
   --------------------------------------------------------------- */
void sort_categories_desc(Category **tete) {
    int      permutation, i;
    Category *courant;
    int       temp_id, temp_nb;
    Person    temp_guests[4];

    if (*tete == NULL) return;

    do {
        permutation = 0;
        courant = *tete;
        while (courant->next != NULL) {
            if (courant->nb_guests < courant->next->nb_guests) {
                /* swap data between adjacent nodes */
                temp_id = courant->id;
                temp_nb = courant->nb_guests;
                for (i = 0; i < 4; i++) temp_guests[i] = courant->guests[i];

                courant->id       = courant->next->id;
                courant->nb_guests = courant->next->nb_guests;
                for (i = 0; i < 4; i++) courant->guests[i] = courant->next->guests[i];

                courant->next->id        = temp_id;
                courant->next->nb_guests = temp_nb;
                for (i = 0; i < 4; i++) courant->next->guests[i] = temp_guests[i];

                permutation = 1;
            }
            courant = courant->next;
        }
    } while (permutation);
}

/* ---------------------------------------------------------------
   display_all_guests
   --------------------------------------------------------------- */
void display_all_guests(Category *tete) {
    int i, num = 1;

    if (tete == NULL) {
        printf("  No categories.\n");
        return;
    }

    while (tete != NULL) {
        printf("\n  ====================================\n");
        printf("  Category #%-2d  (ID=%-4d)  Guests=%d\n",
               num++, tete->id, tete->nb_guests);
        printf("  ------------------------------------\n");
        for (i = 0; i < tete->nb_guests; i++)
            display_person(tete->guests[i]);
        tete = tete->next;
    }
}
