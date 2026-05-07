#include <stdio.h>
#include "storage.h"

void save_order(Order *order) {

    FILE *file = fopen("orders.txt", "a");

    if (file == NULL) {
        printf("Error saving order.\n");
        return;
    }

    fprintf(file, "New Order:\n");

    for (int i = 0; i < order->count; i++) {
        fprintf(file,
                "%s - $%.2f\n",
                order->items[i].name,
                order->items[i].price);
    }

    fprintf(file,
            "Total: $%.2f\n\n",
            calculate_total(order));

    fclose(file);

    printf("Order saved successfully.\n");
}
