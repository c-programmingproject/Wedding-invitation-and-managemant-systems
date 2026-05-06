/* ================================================================
   MODULE 5 : User Interface (Advanced Console)  –  Implementation
   PKFIE Yaoundé  |  2025-2026
   ================================================================ */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "ui.h"
#include "person.h"
#include "category.h"
#include "priority.h"
#include "gift.h"

/* ================================================================
   Low-level display helpers
   ================================================================ */

void clear_screen(void) { system(CLEAR_CMD); }

void print_line(char c, int n) {
    int i;
    for (i = 0; i < n; i++) printf("%c", c);
    printf("\n");
}

void print_centered(const char *text) {
    int len = (int)strlen(text);
    int pad = (CONSOLE_WIDTH - len) / 2;
    if (pad < 0) pad = 0;
    printf("%*s%s\n", pad, "", text);
}

void print_header(const char *title) {
    clear_screen();
    printf(CYAN);  print_line('=', CONSOLE_WIDTH);
    printf(BOLD);
    print_centered("WIGMS - Wedding Invitation & Gift Mgmt");
    print_centered("PKFIE Yaounde  |  2025-2026");
    print_line('-', CONSOLE_WIDTH);
    print_centered(title);
    print_line('=', CONSOLE_WIDTH);
    printf(RESET "\n");
}

void press_enter(void) {
    printf(YELLOW "\n  [ Press ENTER to continue ]" RESET);
    while (getchar() != '\n');
}

/* ================================================================
   Feedback helpers
   ================================================================ */

void display_error_message  (const char *msg) { printf(RED    BOLD "\n  [ERROR]   %s\n" RESET, msg); }
void display_success_message(const char *msg) { printf(GREEN  BOLD "\n  [SUCCESS] %s\n" RESET, msg); }
void display_warning_message(const char *msg) { printf(YELLOW BOLD "\n  [WARNING] %s\n" RESET, msg); }
void display_info_message   (const char *msg) { printf(CYAN        "\n  [INFO]    %s\n" RESET, msg); }

/* ================================================================
   Input helpers
   ================================================================ */

int confirm_action(const char *question) {
    char rep;
    printf(YELLOW "\n  %s (Y/N) : " RESET, question);
    scanf(" %c", &rep);
    while (getchar() != '\n');
    return (toupper((int)rep) == 'Y') ? 1 : 0;
}

int read_int(const char *prompt, int min, int max) {
    int val, ok;
    do {
        printf("  %s", prompt);
        ok = scanf("%d", &val);
        while (getchar() != '\n');
        if (!ok || val < min || val > max) {
            display_error_message("Invalid value, please try again.");
            ok = 0;
        } else {
            ok = 1;
        }
    } while (!ok);
    return val;
}

float read_float(const char *prompt, float min, float max) {
    float val;
    int   ok;
    do {
        printf("  %s", prompt);
        ok = scanf("%f", &val);
        while (getchar() != '\n');
        if (!ok || val < min || val > max) {
            display_error_message("Invalid value, please try again.");
            ok = 0;
        } else {
            ok = 1;
        }
    } while (!ok);
    return val;
}

void read_string(const char *prompt, char *buf, int max_len) {
    int len;
    do {
        printf("  %s", prompt);
        fgets(buf, max_len, stdin);
        len = (int)strlen(buf);
        if (len > 0 && buf[len - 1] == '\n') buf[--len] = '\0';
        if (len == 0) display_error_message("Required field!");
    } while (len == 0);
}

/* ================================================================
   Screen layouts
   ================================================================ */

void display_splash_screen(void) {
    clear_screen();
    printf(CYAN);        print_line('*', CONSOLE_WIDTH); printf(RESET "\n");
    printf(MAGENTA BOLD); print_centered("W  I  G  M  S");  printf(RESET "\n");
    printf(WHITE BOLD);
    print_centered("Wedding Invitation &");
    print_centered("Gift Management System");
    printf(RESET "\n\n");
    printf(YELLOW);
    print_centered("PKFIE - Institute of Excellence");
    print_centered("Dignity  -  Faith  -  Responsibility");
    printf(RESET "\n\n");
    printf(CYAN);
    print_centered("Course : Modular C Programming");
    print_centered("Year   : 2025 - 2026");
    print_centered("Prof   : Mbietieu Amos Mb.");
    printf("\n"); print_line('*', CONSOLE_WIDTH); printf(RESET "\n");
    press_enter();
}

void display_main_menu(void) {
    print_header("MAIN MENU");
    printf("  " CYAN "[1]" RESET "  Person Management\n");
    printf("  " CYAN "[2]" RESET "  Category Management\n");
    printf("  " CYAN "[3]" RESET "  Priority Management (DPR)\n");
    printf("  " CYAN "[4]" RESET "  Gift Management\n");
    printf("  " CYAN "[5]" RESET "  About\n");
    printf("  " RED   "[0]" RESET "  Quit\n");
    printf(CYAN); print_line('-', CONSOLE_WIDTH); printf(RESET);
}

/* ================================================================
   Module menus
   ================================================================ */

/* ---------- Person menu ---------------------------------------- */
void person_menu(void) {
    int     choix, quitter = 0, n = 0, i;
    Person *guests = NULL;

    print_header("PERSON MANAGEMENT  [Module 1]");

    /* Show current next ID and offer reset */
    {
        int cur = 1;
        FILE *f = fopen(ID_FILE, "r");
        if (f) { fscanf(f, "%d", &cur); fclose(f); }
        printf(CYAN "  Next person ID will be : %d\n" RESET, cur);
    }
    if (confirm_action("Reset ID counter to 1?"))
        reset_id_counter();

    n = read_int("Number of guests to register : ", 1, 9999);
    guests = (Person *)malloc(n * sizeof(Person));
    if (!guests) {
        display_error_message("Memory allocation failed.");
        press_enter();
        return;
    }

    for (i = 0; i < n; i++) {
        print_header("PERSON MANAGEMENT  [Module 1]");
        printf(CYAN "  --- Registering Guest #%d ---\n" RESET, i + 1);
        guests[i] = create_person();
        display_success_message("Guest registered!");
    }

    /* Optional update sub-loop */
    {
        char upd;
        print_header("PERSON MANAGEMENT  [Module 1]");
        printf(YELLOW "  Do you want to update any guest? (Y/N) : " RESET);
        scanf(" %c", &upd);
        while (getchar() != '\n');

        if (upd == 'y' || upd == 'Y') {
            while (!quitter) {
                print_header("PERSON MANAGEMENT  [Module 1]");
                printf("  " CYAN "[1]" RESET "  Update a guest's info\n");
                printf("  " CYAN "[2]" RESET "  View all guests\n");
                printf("  " RED   "[3]" RESET "  Exit to main menu\n");
                printf(CYAN); print_line('-', CONSOLE_WIDTH); printf(RESET);

                choix = read_int("Your choice : ", 1, 3);
                switch (choix) {
                    case 1: {
                        int sid, found = 0;
                        print_header("UPDATE A GUEST");
                        sid = read_int("Enter ID of guest to update : ", 1, 99999);
                        for (i = 0; i < n; i++) {
                            if (guests[i].id == sid) {
                                update_person(&guests[i]);
                                display_success_message("Guest updated!");
                                found = 1;
                                break;
                            }
                        }
                        if (!found) display_warning_message("Guest ID not found.");
                        press_enter();
                        break;
                    }
                    case 2:
                        print_header("GUEST LIST");
                        for (i = 0; i < n; i++) display_person(guests[i]);
                        press_enter();
                        break;
                    case 3:
                        quitter = 1;
                        break;
                }
            }
        }
    }

    /* Persist guest names for gift verification */
    {
        FILE *gf = fopen("guests.txt", "w");
        if (gf) {
            for (i = 0; i < n; i++) fprintf(gf, "%s\n", guests[i].name);
            fclose(gf);
        }
    }
    display_success_message("Guest list saved.");
    free(guests);
    press_enter();
}

/* ---------- Helper : pick a category by position --------------- */
static Category *pick_category(Category *tete) {
    Category *cur = tete;
    int count = 0, pick, pos;

    if (!tete) return NULL;

    printf("\n  Available categories:\n");
    while (cur) {
        printf("    [%d] ID=%-4d  (%d guest%s)\n",
               ++count, cur->id, cur->nb_guests,
               cur->nb_guests == 1 ? "" : "s");
        cur = cur->next;
    }
    pick = read_int("  Select category number : ", 1, count);
    cur  = tete;
    for (pos = 1; pos < pick; pos++) cur = cur->next;
    return cur;
}

/* ---------- Category menu -------------------------------------- */
void category_menu(void) {
    int       choix, quitter = 0;
    Category *tete = NULL, *target;

    while (!quitter) {
        print_header("CATEGORY MANAGEMENT  [Module 2]");
        printf("  " CYAN "[1]" RESET "  Insert a category\n");
        printf("  " CYAN "[2]" RESET "  Display all guests\n");
        printf("  " CYAN "[3]" RESET "  Modify a category\n");
        printf("  " CYAN "[4]" RESET "  Delete a category\n");
        printf("  " CYAN "[5]" RESET "  Count guests\n");
        printf("  " CYAN "[6]" RESET "  Sort categories\n");
        printf("  " RED   "[0]" RESET "  Back\n");
        printf(CYAN); print_line('-', CONSOLE_WIDTH); printf(RESET);

        choix = read_int("Your choice : ", 0, 6);
        switch (choix) {
            case 1:
                print_header("INSERT A CATEGORY");
                insert_category(&tete);
                display_success_message("Category inserted!");
                press_enter();
                break;
            case 2:
                print_header("GUEST LIST");
                if (!tete) display_warning_message("No category registered.");
                else       display_all_guests(tete);
                press_enter();
                break;
            case 3:
                print_header("MODIFY A CATEGORY");
                if (!tete) display_warning_message("No category available.");
                else {
                    target = pick_category(tete);
                    if (target) {
                        update_category(tete, target->id);
                        display_success_message("Category updated!");
                    }
                }
                press_enter();
                break;
            case 4:
                print_header("DELETE A CATEGORY");
                if (!tete) display_warning_message("No category available.");
                else if (confirm_action("Confirm deletion?")) {
                    target = pick_category(tete);
                    if (target) {
                        delete_category(&tete, target->id);
                        display_success_message("Category deleted!");
                    }
                } else {
                    display_info_message("Deletion cancelled.");
                }
                press_enter();
                break;
            case 5:
                print_header("GUEST COUNT");
                printf(GREEN "\n  Total guests : %d\n" RESET, count_guest(tete));
                press_enter();
                break;
            case 6:
                print_header("SORT CATEGORIES");
                sort_categories_desc(&tete);
                display_success_message("Sorted in descending order!");
                display_all_guests(tete);
                press_enter();
                break;
            case 0:
                quitter = 1;
                break;
        }
    }
}

/* ---------- Priority menu -------------------------------------- */
void priority_menu(void) {
    int       choix, quitter = 0;
    Category *tete = NULL;

    while (!quitter) {
        print_header("PRIORITY MANAGEMENT - DPR  [Module 3]");
        printf(WHITE "  Method : Divide - Process - Recombine\n\n" RESET);
        printf("  " CYAN "[1]" RESET "  Prioritize by age\n");
        printf("  " CYAN "[2]" RESET "  Prioritize by social class\n");
        printf("  " CYAN "[3]" RESET "  Merge Sort on categories\n");
        printf("  " RED   "[0]" RESET "  Back\n");
        printf(CYAN); print_line('-', CONSOLE_WIDTH); printf(RESET);

        choix = read_int("Your choice : ", 0, 3);
        switch (choix) {
            case 1:
                print_header("PRIORITY BY AGE");
                prioritize_by_age(tete);
                display_success_message("Guests sorted by age!");
                display_all_guests(tete);
                press_enter();
                break;
            case 2:
                print_header("PRIORITY BY SOCIAL CLASS");
                prioritize_by_social_class(tete);
                display_success_message("Guests sorted by social class!");
                display_all_guests(tete);
                press_enter();
                break;
            case 3:
                print_header("MERGE SORT ON CATEGORIES");
                merge_sort_categories(&tete);
                display_success_message("Merge Sort applied!");
                display_all_guests(tete);
                press_enter();
                break;
            case 0:
                quitter = 1;
                break;
        }
    }
}

/* ---------- Gift menu ------------------------------------------ */
void gift_menu(void) {
    int  choix, quitter = 0, nb = 0;
    Gift gifts[MAX_GIFTS];

    print_header("GIFT MANAGEMENT  [Module 4]");
    gift_module_init();   /* set couple names once */

    while (!quitter) {
        print_header("GIFT MANAGEMENT  [Module 4]");
        printf("  " CYAN "[1]" RESET "  Register a gift\n");
        printf("  " CYAN "[2]" RESET "  Display gifts\n");
        printf("  " CYAN "[3]" RESET "  Modify a gift\n");
        printf("  " CYAN "[4]" RESET "  Total gift value\n");
        printf("  " CYAN "[5]" RESET "  Save (file)\n");
        printf("  " CYAN "[6]" RESET "  Load (file)\n");
        printf("  " RED   "[0]" RESET "  Back\n");
        printf(CYAN); print_line('-', CONSOLE_WIDTH); printf(RESET);

        choix = read_int("Your choice : ", 0, 6);
        switch (choix) {
            case 1:
                print_header("REGISTER A GIFT");
                register_gift(gifts, &nb);
                if (nb > 0) display_success_message("Gift registered!");
                press_enter();
                break;
            case 2:
                print_header("GIFT LIST");
                display_gifts(gifts, nb);
                press_enter();
                break;
            case 3:
                print_header("MODIFY A GIFT");
                if (nb == 0) display_warning_message("No gift registered.");
                else { update_gifts(gifts, nb); display_success_message("Gift updated!"); }
                press_enter();
                break;
            case 4:
                print_header("TOTAL VALUE");
                printf(GREEN "\n  Total value : %d FCFA\n" RESET,
                       total_gift_value(gifts, nb));
                press_enter();
                break;
            case 5:
                print_header("SAVE");
                if (confirm_action("Save to gifts.dat?")) {
                    save_gifts(gifts, nb);
                    display_success_message("Save completed!");
                } else {
                    display_info_message("Save cancelled.");
                }
                press_enter();
                break;
            case 6:
                print_header("LOAD");
                if (confirm_action("Load from gifts.dat?")) {
                    load_gifts(gifts, &nb);
                    display_success_message("Load completed!");
                } else {
                    display_info_message("Load cancelled.");
                }
                press_enter();
                break;
            case 0:
                quitter = 1;
                break;
        }
    }
}

/* ---------- About menu ----------------------------------------- */
void about_menu(void) {
    print_header("ABOUT THE PROJECT");
    printf(WHITE BOLD "  Project  : " RESET "WIGMS\n");
    printf(WHITE BOLD "  Course   : " RESET "Modular C Programming\n");
    printf(WHITE BOLD "  Year     : " RESET "2025 - 2026\n");
    printf(WHITE BOLD "  Prof     : " RESET "Mbietieu Amos Mb.\n");
    printf(WHITE BOLD "  School   : " RESET "PKFIE - Yaounde\n\n");
    print_line('-', CONSOLE_WIDTH);
    printf(CYAN "\n  Implemented modules :\n\n" RESET);
    printf("  " GREEN "Module 1" RESET " : Person Management  (person.h / person.c)\n");
    printf("  " GREEN "Module 2" RESET " : Categories         (category.h / category.c)\n");
    printf("  " GREEN "Module 3" RESET " : Priorities DPR     (priority.h / priority.c)\n");
    printf("  " GREEN "Module 4" RESET " : Gifts              (gift.h / gift.c)\n");
    printf("  " GREEN "Module 5" RESET " : Console Interface  (ui.h / ui.c)\n\n");
    print_line('-', CONSOLE_WIDTH);
    printf(YELLOW "\n  MVC Architecture :\n" RESET);
    printf("    Model      -> Modules 1 to 4\n");
    printf("    Controller -> Module 5 (ui.c)\n");
    printf("    View       -> ANSI Console\n\n");
    press_enter();
}

/* ================================================================
   Application loop
   ================================================================ */

void run_application(void) {
    int choix, quitter = 0;

    display_splash_screen();

    while (!quitter) {
        display_main_menu();
        choix = read_int("Your choice : ", 0, 5);
        switch (choix) {
            case 1: person_menu();   break;
            case 2: category_menu(); break;
            case 3: priority_menu(); break;
            case 4: gift_menu();     break;
            case 5: about_menu();    break;
            case 0:
                if (confirm_action("Do you really want to quit?"))
                    quitter = 1;
                break;
        }
    }

    clear_screen();
    printf(CYAN);         print_line('=', CONSOLE_WIDTH);
    printf(MAGENTA BOLD); print_centered("Thank you for using WIGMS!");
    printf(RESET CYAN);   print_centered("PKFIE Yaounde  |  2025-2026");
    print_line('=', CONSOLE_WIDTH);
    printf(RESET "\n");
}
