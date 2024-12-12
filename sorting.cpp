#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#define MAX_ROWS 100
#define MAX_COLS 3
using namespace std;

// Function to open the file
bool openFile(ifstream &file, const string &filename) {
    file.open(filename);
    if (!file) {
        cerr << "Unable to open file: " << filename << endl;
        return false;
    }
    return true;
}

// Function to read data from the file
int readData(ifstream &file, string data[MAX_ROWS][MAX_COLS]) {
    string line;
    int row = 0;

    // Skip the header
    getline(file, line);

    // Read the file line by line
    while (getline(file, line) && row < MAX_ROWS) {
        stringstream ss(line);
        string value;
        int col = 0;

        // Split the line into values
        while (getline(ss, value, ',') && col < MAX_COLS) {
            data[row][col] = value;
            col++;
        }
        row++;
    }
    return row; // Return the number of rows read
}

// Function to print the data
void printData(const string data[MAX_ROWS][MAX_COLS], int rows) {
    cout << "\nData from file:" << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < MAX_COLS; j++) {
            cout << data[i][j] << " ";
        }
        cout << endl;
    }
}

// Function to sort the data using Bubble Sort
void bubbleSort(string data[MAX_ROWS][MAX_COLS], int rows, int sortColumn) {
    for (int i = 0; i < rows - 1; i++) {
        for (int j = 0; j < rows - i - 1; j++) {
            // Compare values in the specified column
            if (data[j][sortColumn] > data[j + 1][sortColumn]) {
                // Swap entire rows
                for (int k = 0; k < MAX_COLS; k++) {
                    swap(data[j][k], data[j + 1][k]);
                }
            }
        }
    }
}

// Function to add new data to the file
void addDataToFile(const string &filename) {
    ofstream file(filename, ios::app); // Open in append mode
    if (!file) {
        cerr << "Unable to open file for writing: " << filename << endl;
        return;
    }

    string name;
    int age, score;

    cout << "Enter Name: ";
    cin >> name;
    cout << "Enter Age: ";
    cin >> age;
    cout << "Enter Score: ";
    cin >> score;

    // Write the new data to the file
    file << name << "," << age << "," << score << endl;
    file.close();

    cout << "Data added successfully!" << endl;
}

int main() {
    string filename = "students.csv";
    ifstream file;
    string data[MAX_ROWS][MAX_COLS]; // Array to store data

    int choice;
    do {
        cout << "\nMenu:\n";
        cout << "1. View Data\n";
        cout << "2. Add Data\n";
        cout << "3. Sort Data\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                // View data
                if (openFile(file, filename)) {
                    int rows = readData(file, data);
                    file.close();
                    printData(data, rows);
                }
                break;
            }
            case 2: {
                // Add data
                addDataToFile(filename);
                break;
            }
            case 3: {
                // Sort data
                if (openFile(file, filename)) {
                    int rows = readData(file, data);
                    file.close();

                    int sortOption;
                    cout << "Sort by:\n";
                    cout << "1. Name\n";
                    cout << "2. Age\n";
                    cout << "3. Score\n";
                    cout << "Enter your choice: ";
                    cin >> sortOption;

                    if (sortOption >= 1 && sortOption <= 3) {
                        bubbleSort(data, rows, sortOption - 1);
                        printData(data, rows);
                    } else {
                        cout << "Invalid sorting option!" << endl;
                    }
                }
                break;
            }
            case 4:
                cout << "Exiting program." << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 4);

    return 0;
}