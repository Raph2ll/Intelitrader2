#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <stdexcept>

using namespace std;

struct Offer {
    double value;
    int quantity;
};

vector<Offer> offers;

bool isValidIndex(int index) {
    return index >= 0 && index < offers.size();
}

void insert(int position, double value, int quantity) {
    int index = position - 1; // Convert to 0-based index

    // Verifica se o vetor offers é grande o suficiente para conter a posição index. 
    while (offers.size() <= index) {
        offers.push_back({0, 0});
    }

    if (offers[index].value != 0 || offers[index].quantity != 0) {
        cout << "Repeated action. It will not be inserted again." << endl;
        return;
    }

    offers[index] = {value, quantity};
}

void modify(int position, double newValue, int newQuantity) {
    int index = position - 1; // Convert to 0-based index

    if (!isValidIndex(index)) {
        cout << "Offer with position " << position << " not found." << endl;
        return;
    }
    
    offers[index].value = newValue;
    offers[index].quantity = newQuantity;
}

void erase(int position) {
    int index = position - 1; // Convert to 0-based index

    if (!isValidIndex(index)) {
        cout << "Offer with position " << position << " not found." << endl;
        return;
    }

    // Insert a placeholder {0, 0} instead of erasing the element
    offers[index] = {0, 0};
}

void printOffers() {
    for (size_t i = 0; i < offers.size(); ++i) {
        cout << (i + 1) << "," << offers[i].value << "," << offers[i].quantity << endl; // Convert back to 1-based position
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <number of notifications> <offers...>" << endl;
        return 1;
    }

    int numNotifications;
    try {
        numNotifications = stoi(argv[1]);
    } catch (const invalid_argument& e) {
        cerr << "Invalid number of notifications." << endl;
        return 1;
    }

    for (int i = 2; i < argc; ++i) {
        stringstream ss(argv[i]);
        string token;
        vector<string> parameters;

        while (getline(ss, token, ',')) {
            parameters.push_back(token);
        }
        
        if (parameters.size() != 4) {
            cerr << "Invalid notification format: " << argv[i] << endl;
            continue;
        }

        int position = stoi(parameters[0]);
        int action = stoi(parameters[1]);
        double value = stod(parameters[2]);
        int quantity = stoi(parameters[3]);

        switch (action) {
            case 0:
                insert(position, value, quantity);
                break;
            case 1:
                modify(position, value, quantity);
                break;
            case 2:
                erase(position);
                break;
            default:
                cerr << "Invalid action: " << action << endl;
                break;
        }
    }

    printOffers();

    return 0;
}