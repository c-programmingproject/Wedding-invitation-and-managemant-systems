#ifndef ORDER_H
#define ORDER_H

#include "menu.h"

#define MAX_ITEMS 100

typedef struct {
    MenuItem items[MAX_ITEMS];
    int count;
} Order;

void init_order(Order *order);
void add_item(Order *order, MenuItem item);
void remove_item(Order *order, char name[]);
float calculate_total(Order *order);
void show_order(Order *order);

#endif
