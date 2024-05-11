#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Medicine {
private:
    string name;
    int quantity;
    float price;

public:
    Medicine(string n, int q, float p) : name(n), quantity(q), price(p) {}

    string getName() const {
        return name;
    }

    int getQuantity() const {
        return quantity;
    }

    float getPrice() const {
        return price;
    }

    void setName(string n) {
        name = n;
    }

    void setQuantity(int q) {
        quantity = q;
    }

    void setPrice(float p) {
        price = p;
    }
};

class MedicalStore {
private:
    vector<Medicine> inventory;

public:
    void addMedicine(const Medicine& med) {
        inventory.push_back(med);
        cout << "Medicine " << med.getName() << " added successfully." << endl;
    }

    void deleteMedicine(const string& name) {
        auto it = find_if(inventory.begin(), inventory.end(), [&name](const Medicine& med) {
            return med.getName() == name;
        });

        if (it != inventory.end()) {
            inventory.erase(it);
            cout << "Medicine " << name << " deleted successfully." << endl;
        } else {
            cout << "Medicine " << name << " not found." << endl;
        }
    }

    void updateMedicine(const string& name, int newQuantity, float newPrice) {
        auto it = find_if(inventory.begin(), inventory.end(), [&name](const Medicine& med) {
            return med.getName() == name;
        });

        if (it != inventory.end()) {
            it->setQuantity(newQuantity);
            it->setPrice(newPrice);
            cout << "Medicine " << name << " updated successfully." << endl;
        } else {
            cout << "Medicine " << name << " not found." << endl;
        }
    }

    void searchMedicine(const string& name) const {
        auto it = find_if(inventory.begin(), inventory.end(), [&name](const Medicine& med) {
            return med.getName() == name;
        });

        if (it != inventory.end()) {
            cout << "Medicine " << name << " found. Quantity: " << it->getQuantity() << ", Price: " << it->getPrice() << endl;
        } else {
            cout << "Medicine " << name << " not found." << endl;
        }
    }

    void displayInventory() const {
        cout << "Inventory:" << endl;
        cout << "-------------------------------------------" << endl;
        for (const Medicine& med : inventory) {
            cout << "Name: " << med.getName() << ", Quantity: " << med.getQuantity() << ", Price: " << med.getPrice() << endl;
        }
        cout << "-------------------------------------------" << endl;
    }

    void sellMedicine(const string& name, int quantity) {
    auto it = find_if(inventory.begin(), inventory.end(), [&name](const Medicine& med) {
        return med.getName() == name;
    });

    if (it != inventory.end()) {
        if (it->getQuantity() >= quantity) {
            it->setQuantity(it->getQuantity() - quantity);
            float total_price = quantity * it->getPrice();
            cout << "Sold " << quantity << " units of " << name << " for total price: " << total_price << endl;

            // Generate and save bill
            ofstream outFile("bill.txt", ios::app);
            if (outFile.is_open()) {
                outFile << "+-------------------------------------------+\n";
                outFile << "|                Bill Receipt               |\n";
                outFile << "+-------------------------------------------+\n";
                outFile << "| Medicine: " << name << "\n";
                outFile << "| Quantity: " << quantity << "\n";
                outFile << "| Price per unit: $" << it->getPrice() << "\n";
                outFile << "| Total Price: $" << total_price << "\n";
                outFile << "+-------------------------------------------+\n";
                outFile << "|             Developed by Vansh     |\n";
                outFile << "+-------------------------------------------+\n\n";
                outFile.close();
                cout << "Bill generated and saved successfully." << endl;
            } else {
                cout << "Unable to open file to save bill." << endl;
            }
        } else {
            cout << "Insufficient quantity of " << name << " in stock." << endl;
        }
    } else {
        cout << "Medicine " << name << " not found." << endl;
    }
}
};

int main() {
    MedicalStore store;

    // Adding sample medicines
    store.addMedicine(Medicine("Paracetamol", 100, 5.99));
    store.addMedicine(Medicine("Aspirin", 50, 3.49));
    store.addMedicine(Medicine("Omeprazole", 80, 7.99));

    int choice;
    string name;
    int quantity;
    float price;

    do {
        cout << "\nMenu:\n";
        cout << "1. Add Medicine\n";
        cout << "2. Delete Medicine\n";
        cout << "3. Update Medicine\n";
        cout << "4. Search Medicine\n";
        cout << "5. Display Inventory\n";
        cout << "6. Sell Medicine\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter name, quantity, and price of the medicine: ";
                cin >> name >> quantity >> price;
                store.addMedicine(Medicine(name, quantity, price));
                break;
            case 2:
                cout << "Enter name of the medicine to delete: ";
                cin >> name;
                store.deleteMedicine(name);
                break;
            case 3:
                cout << "Enter name of the medicine to update: ";
                cin >> name;
                cout << "Enter new quantity and price: ";
                cin >> quantity >> price;
                store.updateMedicine(name, quantity, price);
                break;
            case 4:
                cout << "Enter name of the medicine to search: ";
                cin >> name;
                store.searchMedicine(name);
                break;
            case 5:
                store.displayInventory();
                break;
            case 6:
                cout << "Enter name of the medicine to sell: ";
                cin >> name;
                cout << "Enter quantity to sell: ";
                cin >> quantity;
                store.sellMedicine(name, quantity);
                break;
            case 7:
                cout << "Exiting program...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    } while (choice != 7);

    return 0;
}