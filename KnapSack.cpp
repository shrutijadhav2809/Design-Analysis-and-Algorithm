#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Item {
    string name;
    double weight;
    double value;
    bool divisible;
    int priority;

    Item(string n, double w, double v, bool d, int p)
        : name(n), weight(w), value(v), divisible(d), priority(p) {}

    double valuePerWeight() const {
        return value / weight; }
};

// Sort by priority first, then value per weight
bool compare(const Item& a, const Item& b) {
    if (a.priority == b.priority)
        return a.valuePerWeight() > b.valuePerWeight();
    return a.priority < b.priority;
}

double fractionalKnapsack(vector<Item>& items, double capacity, double& totalWeightCarried) {
    sort(items.begin(), items.end(), compare);

    cout << "\nSorted Items (by Priority, then Value/Weight):\n";
    cout << left << setw(20) << "Item"
         << setw(10) << "Weight"
         << setw(10) << "Value"
         << setw(12) << "Priority"
         << setw(15) << "Value/Weight"
         << setw(15) << "Type" << "\n";

    for (const auto& item : items) {
        cout << left << setw(20) << item.name
             << setw(10) << item.weight
             << setw(10) << item.value
             << setw(12) << item.priority
             << setw(15) << fixed << setprecision(2) << item.valuePerWeight()
             << setw(15) << (item.divisible ? "Divisible" : "Indivisible")
             << "\n";
    }

    double totalValue = 0.0;
    totalWeightCarried = 0.0;

    cout << "\nItems selected for transport:\n";

    for (const auto& item : items) {
        if (capacity <= 0) break;

        if (item.divisible) {
            double takenWeight = min(item.weight, capacity);
            double takenValue = item.valuePerWeight() * takenWeight;
            totalValue += takenValue;
            capacity -= takenWeight;
            totalWeightCarried += takenWeight;

            cout << " - " << item.name << ": " << takenWeight << " kg, Utility = " << takenValue
                 << ", Priority = " << item.priority << ", Type = Divisible\n";
        } else {
            if (item.weight <= capacity) {
                totalValue += item.value;
                capacity -= item.weight;
                totalWeightCarried += item.weight;

                cout << " - " << item.name << ": " << item.weight << " kg, Utility = " << item.value
                     << ", Priority = " << item.priority << ", Type = Indivisible\n";  }
        }
    }
    return totalValue;
}

int main() {
    vector<Item> items = {
        Item("Medical Kits",     10, 100, false, 1),
        Item("Food Packets",     20, 60,  true,  3),
        Item("Drinking Water",   30, 90,  true,  2),
        Item("Blankets",         15, 45, false, 3),
        Item("Infant Formula",    5, 50, false, 1)
    };

    double capacity;
    cout << "Enter maximum weight capacity of the boat (in kg): ";
    cin >> capacity;

    double totalWeightCarried;
    double maxValue = fractionalKnapsack(items, capacity, totalWeightCarried);

    cout << "\n===== Final Report =====\n";
    cout << "Total weight carried: " << fixed << setprecision(2) << totalWeightCarried << " kg\n";
    cout << "Total utility value carried: " << fixed << setprecision(2) << maxValue << " units\n";

    return 0;
}

Output
Enter maximum weight capacity of the boat (in kg): 40

Sorted Items (by Priority, then Value/Weight):
Item                Weight    Value     Priority   Value/Weight   Type           
Infant Formula      5         50        1           10.00          Indivisible   
Medical Kits        10        100       1           10.00          Indivisible   
Drinking Water      30        90        2           3.00           Divisible     
Blankets            15        45        3           3.00           Indivisible   
Food Packets        20        60        3           3.00           Divisible     

Items selected for transport:
 - Infant Formula: 5 kg, Utility = 50, Priority = 1, Type = Indivisible
 - Medical Kits: 10 kg, Utility = 100, Priority = 1, Type = Indivisible
 - Drinking Water: 25 kg, Utility = 75, Priority = 2, Type = Divisible

===== Final Report =====
Total weight carried: 40.00 kg
Total utility value carried: 225.00 units
