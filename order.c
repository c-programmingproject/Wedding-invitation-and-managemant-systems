#include <stdio.h>
#include <string.h>
#include "order.h"

void init_order(Order *order) {
    order->count = 0;
}

void add_item(Order *order, MenuItem item) {
    if (order->count < MAX_ITEMS) {
        order->items[order->count++] = item;
        printf("Added: %s\n", item.name);
    }
}

void remove_item(Order *order, char name[]) {
    for (int i = 0; i < order->count; i++) {

        if (strcmp(order->items[i].name, name) == 0) {

            for (int j = i; j < order->count - 1; j++) {
                order->items[j] = order->items[j + 1];
            }

            order->count--;
            printf("Removed: %s\n", name);
            return;
        }
    }

    printf("Item not found.\n");
}

float calculate_total(Order *order) {
    float total = 0;

    for (int i = 0; i < order->count; i++) {
        total += order->items[i].price;
    }

    return total;
}

void show_order(Order *order) {

    if (order->count == 0) {
        printf("Order is empty.\n");
        return;
    }

    printf("\n--- CURRENT ORDER ---\n");

    for (int i = 0; i < order->count; i++) {
        printf("%s - $%.2f\n",
               order->items[i].name,
               order->items[i].price);
    }

    printf("\nTotal: $%.2f\n",
           calculate_total(order));
}
