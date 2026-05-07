#ifndef ORDER_H
#define ORDER_H

/* ================================================================
   MODULE 6 : Order Management  –  Header
   PKFIE Yaoundé  |  2025-2026

   Features:
   - Shopping cart-style order management
   - Add/remove items from current order
   - Calculate order total
   - Display and persist order data
   ================================================================ */

/* ---------------------------------------------------------------
   Constants
   --------------------------------------------------------------- */
#define MAX_ITEMS      50
#define MAX_ORDERS     100

/* ---------------------------------------------------------------
   Struct : Order item
   --------------------------------------------------------------- */
typedef struct {
    char  name[100];
    float price;
    int   quantity;
} OrderItem;

/* ---------------------------------------------------------------
   Struct : Complete order record
   --------------------------------------------------------------- */
typedef struct {
    int         order_id;
    OrderItem   items[MAX_ITEMS];
    int         item_count;
    float       total;
    char        customer_name[100];
} Order;

/* ---------------------------------------------------------------
   Function prototypes
   --------------------------------------------------------------- */

/**
 * order_module_init
 * Initialize order management module.
 */
void order_module_init(void);

/**
 * create_new_order
 * Create a new empty order and return it.
 */
Order create_new_order(void);

/**
 * add_item_to_order
 * Add an item to the current order.
 * Returns 1 on success, 0 if order is full.
 */
int add_item_to_order(Order *order, const char *item_name, float price, int quantity);

/**
 * remove_item_from_order
 * Remove an item by name from the order (case-insensitive).
 * Returns 1 if item found and removed, 0 otherwise.
 */
int remove_item_from_order(Order *order, const char *item_name);

/**
 * calculate_order_total
 * Recalculates and returns the total value of the order.
 */
float calculate_order_total(Order *order);

/**
 * display_order
 * Prints the current order with items and total.
 */
void display_order(Order *order);

/**
 * save_order
 * Persists the order to orders.dat (binary format).
 */
void save_order(Order *order);

/**
 * load_orders
 * Loads all orders from orders.dat into the orders array.
 * Sets nb to the number of orders loaded.
 */
void load_orders(Order orders[], int *nb);

/**
 * display_all_orders
 * Prints all saved orders with details.
 */
void display_all_orders(Order orders[], int nb);

#endif /* ORDER_H */
