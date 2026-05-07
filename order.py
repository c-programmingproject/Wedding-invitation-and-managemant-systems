class Order:
    def __init__(self):
        self.items = []

    def add_item(self, item):
        self.items.append(item)
        print(f"Added: {item['name']}")

    def remove_item(self, item_name):
        for item in self.items:
            if item["name"].lower() == item_name.lower():
                self.items.remove(item)
                print(f"Removed: {item_name}")
                return

        print("Item not found in order.")

    def calculate_total(self):
        return sum(item["price"] for item in self.items)

    def show_order(self):
        if not self.items:
            print("Order is empty.")
            return

        print("\n--- CURRENT ORDER ---")

        for item in self.items:
            print(f"{item['name']} - ${item['price']}")

        print(f"\nTotal: ${self.calculate_total():.2f}")
