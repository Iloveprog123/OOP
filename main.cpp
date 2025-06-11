#include <iostream>
#include <string>
#include <iomanip>
#include "CargoList.h"
#include "FreightList.h"
using namespace std;

void displayMenu() {
    cout << "\n===== Transportation Management System =====\n";
    cout << "1. Display all cargo\n";
    cout << "2. Display all freight\n";
    cout << "3. Add new cargo\n";
    cout << "4. Add new freight\n";
    cout << "5. Delete cargo\n";
    cout << "6. Delete freight\n";
    cout << "7. Exit\n";
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
        cerr << "Warning: Could not load cargo data or file was empty.\n";
    }

    if (!freightList.loadFromFile(freightPath)) {
        cerr << "Warning: Could not load freight data or file was empty.\n";
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
            cout << left << setw(15) << "ID" << setw(15)
                << "Location" << setw(15) << "Time" << "\n";
            for (const auto& cargo : cargoList.getCargo()) {
                cout << left << setw(15) << cargo.getID()
                    << setw(15) << cargo.getLocation()
                    << setw(15) << cargo.getTime() << "\n";
            }
            break;
        }
        case 2: {
            cout << "\n--- Freight List ---\n";
            cout << left << setw(15) << "ID" << setw(15)
                << "Location" << setw(15) << "Time" << "\n";
            for (const auto& freight : freightList.getFreight()) {
                cout << left << setw(15) << freight.getID()
                    << setw(15) << freight.getLocation()
                    << setw(15) << freight.getTime() << "\n";
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
        case 5: {  // Delete cargo
            string id;
            cout << "Enter cargo ID to delete: ";
            getline(cin, id);

            if (cargoList.deleteCargo(id)) {
                cout << "Cargo deleted successfully!\n";
            }
            else {
                cout << "Error: Cargo with this ID not found!\n";
            }
            break;
        }
        case 6: {  // Delete freight
            string id;
            cout << "Enter freight ID to delete: ";
            getline(cin, id);

            if (freightList.deleteFreight(id)) {
                cout << "Freight deleted successfully!\n";
            }
            else {
                cout << "Error: Freight with this ID not found!\n";
            }
            break;
        }
        case 7: {
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