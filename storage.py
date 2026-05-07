import json


def save_order(order, filename="orders.json"):
    data = [item for item in order.items]

    try:
        with open(filename, "r") as file:
            existing = json.load(file)

    except:
        existing = []

    existing.append(data)

    with open(filename, "w") as file:
        json.dump(existing, file, indent=4)

    print("Order saved successfully.")
