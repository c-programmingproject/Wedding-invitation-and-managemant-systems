/* ================================================================
   MODULE 4 : Gift Management  –  Implementation
   PKFIE Yaoundé  |  2025-2026
   ================================================================ */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>   /* strcasecmp */
#include "gift.h"
#include "ui.h"

/* ---------------------------------------------------------------
   50-item catalogue  (last = monetary donation)
   --------------------------------------------------------------- */
const CatalogueItem CATALOGUE[CATALOGUE_SIZE] = {
    /* Household & Kitchen (1-10) */
    { "Coffee Maker (Deluxe)",               45000.0f },
    { "Stand Mixer (6-Qt)",                  85000.0f },
    { "Air Fryer (5L)",                      55000.0f },
    { "Blender (Professional)",              35000.0f },
    { "Toaster Oven (Stainless)",            30000.0f },
    { "Rice Cooker (10-Cup)",                25000.0f },
    { "Pressure Cooker (8L)",                40000.0f },
    { "Knife Set (8-piece)",                 28000.0f },
    { "Non-stick Cookware Set",              60000.0f },
    { "Cast Iron Skillet",                   22000.0f },
    /* Bedroom & Linen (11-15) */
    { "Egyptian Cotton Bedsheet Set",        35000.0f },
    { "Luxury Duvet (King)",                 70000.0f },
    { "Decorative Pillow Set (4)",           18000.0f },
    { "Scented Candle Collection",           12000.0f },
    { "Wardrobe Organiser Set",              20000.0f },
    /* Dining & Entertaining (16-20) */
    { "Fine China Dinner Set (12)",         120000.0f },
    { "Crystal Wine Glasses (6)",            45000.0f },
    { "Champagne Flute Set (6)",             30000.0f },
    { "Serving Tray (Silver-plated)",        25000.0f },
    { "Cheese & Charcuterie Board",          15000.0f },
    /* Electronics (21-25) */
    { "Smart Speaker (Voice Assist)",        55000.0f },
    { "Portable Bluetooth Speaker",          35000.0f },
    { "Digital Photo Frame (10\")",          30000.0f },
    { "Robot Vacuum Cleaner",               150000.0f },
    { "Electric Kettle (Temp-Control)",      20000.0f },
    /* Decor & Art (26-30) */
    { "Wall Art (Framed Canvas)",            40000.0f },
    { "Decorative Vase (Ceramic)",           18000.0f },
    { "Indoor Plant + Ceramic Pot",          15000.0f },
    { "Mirror (Ornate Frame)",               50000.0f },
    { "Throw Blanket (Cashmere)",            28000.0f },
    /* Travel & Leisure (31-35) */
    { "Luggage Set (3-piece)",              110000.0f },
    { "Travel Toiletry Bag",                 12000.0f },
    { "Couple's Spa Voucher",                80000.0f },
    { "Weekend Getaway Gift Card",          150000.0f },
    { "Picnic Basket Set (Deluxe)",          35000.0f },
    /* Fashion & Accessories (36-40) */
    { "Monogrammed Towel Set",               20000.0f },
    { "Couple Matching Robes",               45000.0f },
    { "Silk Pillowcase Pair",                18000.0f },
    { "Jewellery Box (Wooden)",              22000.0f },
    { "Perfume Gift Set",                    55000.0f },
    /* Food & Drink (41-45) */
    { "Premium Chocolate Hamper",            30000.0f },
    { "Assorted Tea & Coffee Gift Set",      15000.0f },
    { "Local Honey & Spice Basket",          12000.0f },
    { "Wine Bottle (Premium, x2)",           40000.0f },
    { "Organic Fruit Basket",                18000.0f },
    /* Books & Stationery (46-49) */
    { "Wedding Memory Journal",              10000.0f },
    { "Couple's Recipe Book",                12000.0f },
    { "Personalised Story Book",             20000.0f },
    { "Calligraphy Set",                     15000.0f },
    /* Item 50 : Monetary donation */
    { "Monetary Donation (min 10,000 FCFA)", 10000.0f }
};

/* ---------------------------------------------------------------
   Module-level state  (file-scope only)
   --------------------------------------------------------------- */
static char couple_groom[100] = "";
static char couple_bride[100] = "";
static int  gift_id_counter   = 1;

/* ---------------------------------------------------------------
   Internal helpers
   --------------------------------------------------------------- */

/* Display the full 50-item catalogue */
static void display_catalogue(void) {
    int i;
    printf("\n" CYAN
           "  =====================================================\n"
           "  Gift Catalogue for %s & %s\n"
           "  =====================================================\n" RESET,
           couple_groom, couple_bride);
    printf("  %-3s  %-40s  %s\n", "#", "Gift", "Price (FCFA)");
    printf("  -----------------------------------------------------\n");
    for (i = 0; i < CATALOGUE_SIZE; i++) {
        if (i == CATALOGUE_SIZE - 1) printf(YELLOW);
        printf("  %-3d  %-40s  %.0f\n",
               i + 1, CATALOGUE[i].name, CATALOGUE[i].price);
        if (i == CATALOGUE_SIZE - 1) printf(RESET);
    }
    printf("  -----------------------------------------------------\n\n");
}

/* Verify guest name against guests.txt  (3 attempts) */
static int verify_username(char *out_name) {
    char input[100];
    char registered[200][100];
    int  nb_reg = 0, attempts = 0, i;

    FILE *f = fopen("guests.txt", "r");
    if (f != NULL) {
        while (nb_reg < 200 && fgets(registered[nb_reg], 100, f)) {
            registered[nb_reg][strcspn(registered[nb_reg], "\n")] = '\0';
            if (registered[nb_reg][0] != '\0') nb_reg++;
        }
        fclose(f);
    }

    while (attempts < 3) {
        printf(CYAN "  Enter your name to access Gift Registration : " RESET);
        fgets(input, 100, stdin);
        input[strcspn(input, "\n")] = '\0';

        /* If no guest list exists yet, accept any non-empty name */
        if (nb_reg == 0 && input[0] != '\0') {
            strncpy(out_name, input, 99);
            out_name[99] = '\0';
            return 1;
        }

        for (i = 0; i < nb_reg; i++) {
            if (strcasecmp(input, registered[i]) == 0) {
                strncpy(out_name, registered[i], 99);
                out_name[99] = '\0';
                return 1;
            }
        }

        attempts++;
        printf(RED "  [ACCESS DENIED] Name not found in guest list. "
               "Attempts left: %d\n" RESET, 3 - attempts);
    }
    return 0;
}

/* ---------------------------------------------------------------
   Public interface
   --------------------------------------------------------------- */

void gift_module_init(void) {
    if (couple_groom[0] != '\0') return;   /* already initialised */

    printf("\n  --- Couple Setup ---\n");
    printf("  Groom's name : ");
    fgets(couple_groom, sizeof(couple_groom), stdin);
    couple_groom[strcspn(couple_groom, "\n")] = '\0';

    printf("  Bride's name : ");
    fgets(couple_bride, sizeof(couple_bride), stdin);
    couple_bride[strcspn(couple_bride, "\n")] = '\0';
}

void register_gift(Gift gifts[], int *nb) {
    Gift  *g;
    int    pick;
    float  donation_amount;
    char   verified_name[100];

    if (*nb >= MAX_GIFTS) {
        printf("  [ERROR] Maximum capacity reached (%d gifts).\n", MAX_GIFTS);
        return;
    }

    /* Step 1 : verify guest identity */
    if (!verify_username(verified_name)) {
        printf(RED "  [ERROR] Access denied. Too many failed attempts.\n" RESET);
        return;
    }
    printf(GREEN "  Welcome, %s!\n" RESET, verified_name);

    /* Step 2 : show catalogue and collect selection */
    display_catalogue();
    pick = read_int("  Choose a gift by number (1-50) : ", 1, CATALOGUE_SIZE);

    g          = &gifts[*nb];
    g->gift_id = gift_id_counter++;

    if (pick == CATALOGUE_SIZE) {
        /* Monetary donation */
        printf(YELLOW "  Minimum donation is 10,000 FCFA.\n" RESET);
        do {
            printf("  Enter donation amount (FCFA) : ");
            scanf("%f", &donation_amount);
            while (getchar() != '\n');
            if (donation_amount < 10000.0f)
                printf(RED "  Amount must be at least 10,000 FCFA.\n" RESET);
        } while (donation_amount < 10000.0f);

        strncpy(g->gift_name, "Monetary Donation", 99);
        g->gift_name[99] = '\0';
        g->value = donation_amount;
        printf(GREEN "  Donation of %.0f FCFA recorded. Thank you!\n" RESET,
               donation_amount);
    } else {
        strncpy(g->gift_name, CATALOGUE[pick - 1].name, 99);
        g->gift_name[99] = '\0';
        g->value = CATALOGUE[pick - 1].price;
        printf(GREEN "  Selected : %s  -  %.0f FCFA\n" RESET,
               g->gift_name, g->value);
    }

    strncpy(g->guest_name, verified_name, 99);
    g->guest_name[99] = '\0';
    (*nb)++;
}

void display_gifts(Gift gifts[], int nb) {
    int   i;
    float total = 0;

    if (nb == 0) { printf("  No gifts registered.\n"); return; }

    printf("\n" CYAN
           "  ===========================================================\n"
           "  Gift List for %s & %s\n"
           "  ===========================================================\n" RESET,
           couple_groom, couple_bride);
    printf("  %-3s  %-22s  %-28s  %s\n", "#", "Guest", "Gift", "Price (FCFA)");
    printf("  -----------------------------------------------------------\n");

    for (i = 0; i < nb; i++) {
        printf("  %-3d  %-22s  %-28s  %.0f\n",
               i + 1, gifts[i].guest_name,
               gifts[i].gift_name, gifts[i].value);
        total += gifts[i].value;
    }

    printf("  -----------------------------------------------------------\n");
    printf(GREEN "  Total value : %.0f FCFA\n" RESET, total);
}

void update_gifts(Gift gifts[], int nb) {
    int   pick, i;
    float donation_amount;

    printf("\n  Registered gifts:\n");
    for (i = 0; i < nb; i++)
        printf("    [%d] %-22s  %s  (%.0f FCFA)\n",
               i + 1, gifts[i].guest_name,
               gifts[i].gift_name, gifts[i].value);

    pick = read_int("  Select gift number to modify : ", 1, nb);
    i    = pick - 1;

    display_catalogue();
    int new_pick = read_int("  Choose new gift by number (1-50) : ", 1, CATALOGUE_SIZE);

    if (new_pick == CATALOGUE_SIZE) {
        printf(YELLOW "  Minimum donation is 10,000 FCFA.\n" RESET);
        do {
            printf("  Enter donation amount (FCFA) : ");
            scanf("%f", &donation_amount);
            while (getchar() != '\n');
            if (donation_amount < 10000.0f)
                printf(RED "  Amount must be at least 10,000 FCFA.\n" RESET);
        } while (donation_amount < 10000.0f);
        strncpy(gifts[i].gift_name, "Monetary Donation", 99);
        gifts[i].gift_name[99] = '\0';
        gifts[i].value = donation_amount;
    } else {
        strncpy(gifts[i].gift_name, CATALOGUE[new_pick - 1].name, 99);
        gifts[i].gift_name[99] = '\0';
        gifts[i].value = CATALOGUE[new_pick - 1].price;
    }

    printf(GREEN "  Gift updated successfully.\n" RESET);
}

int total_gift_value(Gift gifts[], int nb) {
    float total = 0;
    int   i;
    for (i = 0; i < nb; i++) total += gifts[i].value;
    return (int)total;
}

void save_gifts(Gift gifts[], int nb) {
    FILE *f = fopen("gifts.dat", "wb");
    if (!f) { printf("  [ERROR] Cannot open gifts.dat.\n"); return; }
    fwrite(&nb,    sizeof(int),  1,  f);
    fwrite(gifts,  sizeof(Gift), nb, f);
    fclose(f);
}

void load_gifts(Gift gifts[], int *nb) {
    FILE *f = fopen("gifts.dat", "rb");
    if (!f) { printf("  [ERROR] File gifts.dat not found.\n"); return; }
    fread(nb,    sizeof(int),  1,   f);
    fread(gifts, sizeof(Gift), *nb, f);
    fclose(f);
}
