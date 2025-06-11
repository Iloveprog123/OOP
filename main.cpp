#include <iostream>
#include <string>
#include <iomanip>
#include "CargoList.h"
#include "FreightList.h"

using namespace::std;

void displayMenu() {
    cout << "\n===== Transportation Management System =====\n";
    cout << "1. Display all cargo\n";
    cout << "2. Display all freight\n";
    cout << "3. Add new cargo\n";
    cout << "4. Add new freight\n";
    cout << "5. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    CargoList cargoList;
    FreightList freightList;

    // Get file paths from user
    string cargoPath, freightPath;

    cout << "Enter path to cargo data file: ";
    getline(cin, cargoPath);

    cout << "Enter path to freight data file: ";
    getline(cin, freightPath);

    // Load data from files
    if (!cargoList.loadFromFile(cargoPath)) {
        cerr << "Failed to load cargo data!\n";
        return 1;
    }

    if (!freightList.loadFromFile(freightPath)) {
        cerr << "Failed to load freight data!\n";
        return 1;
    }

    int choice;
    bool running = true;

    while (running) {
        displayMenu();
        cin >> choice;
        cin.ignore(); // Clear newline from buffer

        switch (choice) {
        case 1: {
            cout << "\n--- Cargo List ---\n";
            cout << left << setw(15) << "ID" << setw(15) << "Location" << setw(15) << "Time" << "\n";

            for (const auto& cargo : cargoList.getCargo()) {
                cout << left << setw(15) << cargo.getID() << setw(15) << cargo.getLocation() << setw(15) << cargo.getTime() << "\n";
            }
            break;
        }
        case 2: {
            cout << "\n--- Freight List ---\n";
            cout << left << setw(15) << "ID" << setw(15) << "Location" << setw(15) << "Time" << "\n";
            for (const auto& freight : freightList.getFreight()) {
                cout << left << setw(15) << freight.getID() << setw(15) << freight.getLocation() << setw(15) << freight.getTime() << "\n";
            }
            break;
        }
        case 3: {
            string id, location, time;
            cout << "Enter cargo ID: ";
            getline(cin, id);
            cout << "Enter location: ";
            getline(cin, location);
            cout << "Enter time: ";
            getline(cin, time);

            if (cargoList.addCargo(Cargo(id, location, time))) {
                cout << "Cargo added successfully!\n";
            }
            else {
                cout << "Error: Cargo with this ID already exists!\n";
            }
            break;
        }
        case 4: {
            string id, location, time;
            cout << "Enter freight ID: ";
            getline(cin, id);
            cout << "Enter location: ";
            getline(cin, location);
            cout << "Enter time: ";
            getline(cin, time);

            if (freightList.addFreight(Freight(id, location, time))) {
                cout << "Freight added successfully!\n";
            }
            else {
                cout << "Error: Freight with this ID already exists!\n";
            }
            break;
        }
        case 5: {
            running = false;
            // Save data back to files
            cargoList.saveToFile(cargoPath);
            freightList.saveToFile(freightPath);
            cout << "Data saved successfully. Exiting...\n";
            break;
        }
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}