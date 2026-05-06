/* ================================================================
   MODULE 1 : Person Management  –  Implementation
   PKFIE Yaoundé  |  2025-2026
   ================================================================ */

#include <stdio.h>
#include <string.h>
#include "person.h"
#include "ui.h"      /* ANSI colour macros */

/* ---------------------------------------------------------------
   ID counter  (file-persisted)
   --------------------------------------------------------------- */

int get_and_update_next_id(void) {
    int id = 1;

    FILE *f = fopen(ID_FILE, "r");
    if (f != NULL) {
        fscanf(f, "%d", &id);
        fclose(f);
    }

    FILE *out = fopen(ID_FILE, "w");
    if (out != NULL) {
        fprintf(out, "%d", id + 1);
        fclose(out);
    }

    return id;
}

void reset_id_counter(void) {
    FILE *f = fopen(ID_FILE, "w");
    if (f != NULL) {
        fprintf(f, "1");
        fclose(f);
        printf(GREEN "  [SUCCESS] ID counter reset to 1.\n" RESET);
    } else {
        printf(RED "  [ERROR] Could not reset ID counter.\n" RESET);
    }
}

/* ---------------------------------------------------------------
   CRUD
   --------------------------------------------------------------- */

Person create_person(void) {
    Person p;
    int choix;

    p.id = get_and_update_next_id();
    printf(CYAN "  [Auto-generated ID : %d]\n" RESET, p.id);

    printf("  Full name          : ");
    fgets(p.name, sizeof(p.name), stdin);
    p.name[strcspn(p.name, "\n")] = '\0';

    printf("  Age                : ");
    scanf("%d", &p.age);
    while (getchar() != '\n');

    printf("  Social class       : ");
    fgets(p.social_class, sizeof(p.social_class), stdin);
    p.social_class[strcspn(p.social_class, "\n")] = '\0';

    printf("  Side (1=LE / 2=LA) : ");
    scanf("%d", &choix);
    while (getchar() != '\n');
    p.side = (choix == 1) ? LE : LA;

    return p;
}

void display_person(Person p) {
    printf("\n  +-----------------------------------------+\n");
    printf("  | ID            : %-23d |\n", p.id);
    printf("  | Name          : %-23s |\n", p.name);
    printf("  | Age           : %-23d |\n", p.age);
    printf("  | Social class  : %-23s |\n", p.social_class);
    printf("  | Side          : %-23s |\n", (p.side == LE) ? "LE" : "LA");
    printf("  +-----------------------------------------+\n");
}

void update_person(Person *p) {
    int choix_side;

    printf("  New name [%s] : ", p->name);
    fgets(p->name, sizeof(p->name), stdin);
    p->name[strcspn(p->name, "\n")] = '\0';

    printf("  New age [%d]  : ", p->age);
    scanf("%d", &p->age);
    while (getchar() != '\n');

    printf("  New social class [%s] : ", p->social_class);
    fgets(p->social_class, sizeof(p->social_class), stdin);
    p->social_class[strcspn(p->social_class, "\n")] = '\0';

    printf("  New side (1=LE / 2=LA) [%s] : ",
           (p->side == LE) ? "LE" : "LA");
    scanf("%d", &choix_side);
    while (getchar() != '\n');
    p->side = (choix_side == 1) ? LE : LA;
}
