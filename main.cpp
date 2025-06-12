#include <iostream>
#include <vector>
#include <iomanip>
#include "CargoList.h"
#include "FreightList.h"
#include "Assignment.h"
#include "Scheduler.h"

using namespace std;

void displayMenu() {
    cout << "\n===== Transportation Management System =====\n";
    cout << "1. Display all cargo\n";
    cout << "2. Display all freight\n";
    cout << "3. Add new cargo\n";
    cout << "4. Add new freight\n";
    cout << "5. Generate schedule\n";
    cout << "6. Display assignments\n";
    cout << "7. Display unassigned cargo\n";
    cout << "8. Display unassigned freight\n";
    cout << "9. Exit\n";
    cout << "Enter your choice: ";
}

void displayAssignments(const vector<pair<Cargo*, Freight*>>& assignments) {
    if (assignments.empty()) {
        cout << "No assignments found.\n";
        return;
    }
    cout << "\nAssignments:\n";
    cout << left << setw(15) << "Cargo ID" << setw(15) << "Freight ID"
        << setw(15) << "Location" << setw(15) << "Time" << "\n";
    for (const auto& pair : assignments) {
        cout << left << setw(15) << pair.first->getID()
            << setw(15) << pair.second->getID()
            << setw(15) << pair.first->getLocation()
            << setw(15) << pair.first->getTime() << "\n";
    }
}

int main() {
    CargoList cargoList;
    FreightList freightList;
    Assignment assignment(&cargoList, &freightList);
    Scheduler scheduler(&assignment);

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

    // Update assignment with loaded data
    //assignment = Assignment(cargoList, freightList);

    int choice;
    bool running = true;

    while (running) {
        displayMenu();
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1: {
            cout << "\n--- Cargo List ---\n";
            for (const auto& cargo : cargoList.getCargo()) {
                cout << "ID: " << cargo.getID() << " Location: "
                    << cargo.getLocation() << " Time: " << cargo.getTime() << "\n";
            }
            break;
        }
        case 2: {
            cout << "\n--- Freight List ---\n";
            for (const auto& freight : freightList.getFreight()) {
                cout << "ID: " << freight.getID() << " Location: "
                    << freight.getLocation() << " Time: " << freight.getTime() << "\n";
            }
            break;
        }
        case 5: {
            cout << "Generating schedule...\n";
            scheduler.generateSchedule();
            cout << "Schedule generated with " << scheduler.getAssignments().size() << " assignments\n";
            break;
        }
        case 6: {
            displayAssignments(scheduler.getAssignments());
            break;
        }
        case 7: {
            cout << "\nUnassigned Cargo:\n";
            for (auto cargo : scheduler.getUnassignedCargo()) {
                cout << "ID: " << cargo->getID() << "\n";
            }
            break;
        }
        case 8: {
            cout << "\nUnassigned Freight:\n";
            for (auto freight : scheduler.getUnassignedFreight()) {
                cout << "ID: " << freight->getID() << "\n";
            }
            break;
        }
        case 9: {
            running = false;
            cout << "Exiting...\n";
            break;
        }
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
