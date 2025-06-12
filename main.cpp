#include <iostream>
#include <vector>
#include <iomanip>
#include <limits>
#include "CargoList.h"
#include "FreightList.h"
#include "Assignment.h"
#include "Scheduler.h"

using namespace std;

void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void displayMenu() {
    cout << "\n===== Transportation Management System =====\n";
    cout << "1. Display all cargo\n";
    cout << "2. Display all freight\n";
    cout << "3. Add new cargo\n";
    cout << "4. Add new freight\n";
    cout << "5. Delete cargo\n";
    cout << "6. Delete freight\n";
    cout << "7. Edit cargo\n";
    cout << "8. Edit freight\n";
    cout << "9. Generate schedule\n";
    cout << "10. Display assignments\n";
    cout << "11. Display unassigned cargo\n";
    cout << "12. Display unassigned freight\n";
    cout << "13. Save current data\n";
    cout << "14. Exit\n";
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

bool promptSave(Scheduler& scheduler, CargoList& cargoList, FreightList& freightList, const string& defaultSchedulePath) {
    char choice;
    cout << "Would you like to save before exiting? (y/n): ";
    cin >> choice;
    clearInputBuffer();

    if (tolower(choice) == 'y') {
        cout << "\nWhat would you like to save?\n";
        cout << "1. Cargo data\n";
        cout << "2. Freight data\n";
        cout << "3. Schedule/assignments\n";
        cout << "4. All of the above\n";
        cout << "Enter choice: ";

        int saveChoice;
        cin >> saveChoice;
        clearInputBuffer();

        bool success = true;
        string path;

        if (saveChoice == 1 || saveChoice == 4) {
            cout << "Save cargo to new path? (y/n): ";
            cin >> choice;
            clearInputBuffer();
            if (tolower(choice) == 'y') {
                cout << "Enter new path: ";
                getline(cin, path);
            }
            success &= cargoList.saveToFile(path);
        }

        if (saveChoice == 2 || saveChoice == 4) {
            cout << "Save freight to new path? (y/n): ";
            cin >> choice;
            clearInputBuffer();
            if (tolower(choice) == 'y') {
                cout << "Enter new path: ";
                getline(cin, path);
            }
            success &= freightList.saveToFile(path);
        }

        if (saveChoice == 3 || saveChoice == 4) {
            cout << "Save schedule to path [" << defaultSchedulePath << "]? (y/n): ";
            cin >> choice;
            clearInputBuffer();
            if (tolower(choice) == 'y') {
                success &= scheduler.saveToFile(defaultSchedulePath);
            }
            else {
                cout << "Enter new path: ";
                getline(cin, path);
                success &= scheduler.saveToFile(path);
            }
        }

        return success;
    }
    return true;
}

void addNewCargo(CargoList& cargoList) {
    string id, location, time;
    cout << "Enter Cargo ID: ";
    getline(cin, id);
    cout << "Enter Location: ";
    getline(cin, location);
    cout << "Enter Time: ";
    getline(cin, time);

    if (cargoList.addCargo(Cargo(id, location, time))) {
        cout << "Cargo added successfully!\n";
    }
    else {
        cout << "Error: Cargo with this ID already exists!\n";
    }
}

void addNewFreight(FreightList& freightList) {
    string id, location, time;
    cout << "Enter Freight ID: ";
    getline(cin, id);
    cout << "Enter Location: ";
    getline(cin, location);
    cout << "Enter Time: ";
    getline(cin, time);

    if (freightList.addFreight(Freight(id, location, time))) {
        cout << "Freight added successfully!\n";
    }
    else {
        cout << "Error: Freight with this ID already exists!\n";
    }
}

void deleteCargo(CargoList& cargoList) {
    string id;
    cout << "Enter Cargo ID to delete: ";
    getline(cin, id);

    if (cargoList.deleteCargo(id)) {
        cout << "Cargo deleted successfully!\n";
    }
    else {
        cout << "Error: Cargo with this ID not found!\n";
    }
}

void deleteFreight(FreightList& freightList) {
    string id;
    cout << "Enter Freight ID to delete: ";
    getline(cin, id);

    if (freightList.deleteFreight(id)) {
        cout << "Freight deleted successfully!\n";
    }
    else {
        cout << "Error: Freight with this ID not found!\n";
    }
}

void editCargo(CargoList& cargoList) {
    string id;
    cout << "Enter Cargo ID to edit: ";
    getline(cin, id);

    string location, time;
    cout << "Enter new Location (leave blank to keep current): ";
    getline(cin, location);
    cout << "Enter new Time (leave blank to keep current): ";
    getline(cin, time);

    if (cargoList.editCargo(id, location, time)) {
        cout << "Cargo edited successfully!\n";
    }
    else {
        cout << "Error: Cargo with this ID not found!\n";
    }
}

void editFreight(FreightList& freightList) {
    string id;
    cout << "Enter Freight ID to edit: ";
    getline(cin, id);

    string location, time;
    cout << "Enter new Location (leave blank to keep current): ";
    getline(cin, location);
    cout << "Enter new Time (leave blank to keep current): ";
    getline(cin, time);

    if (freightList.editFreight(id, location, time)) {
        cout << "Freight edited successfully!\n";
    }
    else {
        cout << "Error: Freight with this ID not found!\n";
    }
}

int main() {
    CargoList cargoList;
    FreightList freightList;
    Assignment assignment(&cargoList, &freightList);
    Scheduler scheduler(&assignment);

    // Get file paths from user
    string cargoPath, freightPath, schedulePath;
    cout << "Enter path to cargo data file: ";
    getline(cin, cargoPath);
    cout << "Enter path to freight data file: ";
    getline(cin, freightPath);
    cout << "Enter path for scheduler output file (Please include \scheduler.txt or .csv at the end): ";
    getline(cin, schedulePath);

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
        if (!(cin >> choice)) {
            clearInputBuffer();
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }
        clearInputBuffer();

        switch (choice) {
        case 1: {
            cout << "\n--- Cargo List ---\n";
            for (const auto& cargo : cargoList.getCargo()) {
                cargo.printDetails();
                cout << "\n";
            }
            break;
        }
        case 2: {
            cout << "\n--- Freight List ---\n";
            for (const auto& freight : freightList.getFreight()) {
                freight.printDetails();
                cout << "\n";
            }
            break;
        }
        case 3: addNewCargo(cargoList); break;
        case 4: addNewFreight(freightList); break;
        case 5: deleteCargo(cargoList); break;
        case 6: deleteFreight(freightList); break;
        case 7: editCargo(cargoList); break;
        case 8: editFreight(freightList); break;
        case 9: {
            cout << "Generating schedule...\n";
            scheduler.generateSchedule();
            cout << "Schedule generated with " << scheduler.getAssignments().size() << " assignments\n";
            // Auto-save the schedule after generation
            if (!schedulePath.empty()) {
                if (scheduler.saveToFile(schedulePath)) {
                    cout << "Assignments automatically saved to: " << schedulePath << "\n";
                }
                else {
                    cout << "Warning: Failed to save assignments to " << schedulePath << "\n";
                }
            }
            break;
        }
        case 10: displayAssignments(scheduler.getAssignments()); break;
        case 11: {
            cout << "\nUnassigned Cargo:\n";
            for (auto cargo : scheduler.getUnassignedCargo()) {
                cout << "ID: " << cargo->getID() << ", Location: " << cargo->getLocation() << ", Time: " << cargo->getTime() << "\n";
            }
            break;
        }
        case 12: {
            cout << "\nUnassigned Freight:\n";
            for (auto freight : scheduler.getUnassignedFreight()) {
                cout << "ID: " << freight->getID() << ", Location: " << freight->getLocation() << ", Time: " << freight->getTime() << "\n";
            }
            break;
        }
        case 13: {
            if (!promptSave(scheduler, cargoList, freightList, schedulePath)) {
                cout << "Some files failed to save!\n";
            }
            else {
                cout << "All selected files saved successfully!\n";
            }
            break;
        }
        case 14: {
            if (!promptSave(scheduler, cargoList, freightList, schedulePath)) {
                cout << "Failed to save some files. Exit anyway? (y/n): ";
                cin >> choice;
                clearInputBuffer();
                if (tolower(choice) == 'n') {
                    continue;
                }
            }
            cout << "Exiting...\n";
            running = false;
            break;
        }
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
