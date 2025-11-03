// shruti jadhav
// 123B1F035
// 04|08|2025


#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

// Structure to store item details
struct Item {
    string name;
    double weight;
    double value;
    bool divisible; // true = can be taken fractionally
};

// Comparison based on value/weight ratio
bool cmp(Item a, Item b) {
    double r1 = a.value / a.weight;
    double r2 = b.value / b.weight;
    return r1 > r2; // sort in descending order
}

void fractionalKnapsack(vector<Item>& items, double W) {
    // Sort items based on value/weight ratio
    sort(items.begin(), items.end(), cmp);

    double totalValue = 0.0;
    double currentWeight = 0.0;

    cout << "\nSelected Items for Transport:\n";
    cout << "-----------------------------------------------------------\n";
    cout << left << setw(15) << "Item"
         << setw(12) << "Weight(kg)"
         << setw(12) << "Value"
         << setw(12) << "Taken(kg)" << endl;
    cout << "-----------------------------------------------------------\n";

    for (auto& item : items) {
        if (currentWeight >= W) break; // capacity full

        if (currentWeight + item.weight <= W) {
            // Take full item
            totalValue += item.value;
            currentWeight += item.weight;
            cout << left << setw(15) << item.name
                 << setw(12) << item.weight
                 << setw(12) << item.value
                 << setw(12) << item.weight << endl;
        } else if (item.divisible) {
            // Take fractional part
            double remain = W - currentWeight;
            double fraction = remain / item.weight;
            totalValue += item.value * fraction;
            currentWeight += remain;
            cout << left << setw(15) << item.name
                 << setw(12) << item.weight
                 << setw(12) << item.value
                 << setw(12) << fixed << setprecision(2) << remain << endl;
        }
        // Skip indivisible items if can't take full weight
    }

    cout << "-----------------------------------------------------------\n";
    cout << "Total Weight Loaded: " << currentWeight << " kg\n";
    cout << "Maximum Utility Value: " << totalValue << "\n";
}

int main() {
    int n;
    double W;

    cout << "Enter number of relief items: ";
    cin >> n;

    vector<Item> items(n);

    cout << "Enter details for each item:\n";
    for (int i = 0; i < n; i++) {
        cout << "\nItem " << i + 1 << " name: ";
        cin >> items[i].name;
        cout << "Weight (kg): ";
        cin >> items[i].weight;
        cout << "Utility value: ";
        cin >> items[i].value;
        cout << "Divisible (1 for Yes, 0 for No): ";
        cin >> items[i].divisible;
    }

    cout << "\nEnter boat capacity (kg): ";
    cin >> W;

    fractionalKnapsack(items, W);

    return 0;
}
