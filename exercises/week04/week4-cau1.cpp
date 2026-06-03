/*
 * ============================================================
 *  BAI 1 - BUBBLE / SELECTION / INSERTION SORT
 *  In tung buoc thay doi mang voi ANSI mau sac
 * ============================================================
 */

#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
using namespace std;

const string RST = "\033[0m";
const string BOLD = "\033[1m";
const string CYN = "\033[96m";
const string YLW = "\033[93m";
const string GRN = "\033[92m";
const string RED = "\033[91m";
const string GRY = "\033[90m";

void printHeader(const string& title) {
    cout << "\n" << BOLD << CYN
        << "+--------------------------------------+\n"
        << "| " << left << setw(36) << title << " |\n"
        << "+--------------------------------------+"
        << RST << "\n";
}

void printArray(const vector<int>& arr, int hi1 = -1, int hi2 = -1) {
    cout << "  [";
    for (int i = 0; i < (int)arr.size(); i++) {
        if (i == hi1 || i == hi2) cout << RED << BOLD;

        cout << setw(4) << arr[i];

        if (i == hi1 || i == hi2) cout << RST;

        if (i + 1 < (int)arr.size()) cout << ",";
    }
    cout << " ]\n";
}

// ------------------------------------------------------------
// Bubble Sort
// ------------------------------------------------------------
void bubbleSortVerbose(vector<int> arr) {
    printHeader("BUBBLE SORT - Tung buoc");

    int n = arr.size();
    int step = 0;

    cout << GRY << "Ban dau : " << RST;
    printArray(arr);

    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;

        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
                step++;

                cout << YLW
                    << "Buoc " << setw(2) << step
                    << " swap [" << j << "] <-> ["
                    << j + 1 << "]: "
                    << RST;

                printArray(arr, j, j + 1);
            }
        }

        if (!swapped)
            break;
    }

    cout << GRN << "Ket qua : " << RST;
    printArray(arr);
}

// ------------------------------------------------------------
// Selection Sort
// ------------------------------------------------------------
void selectionSortVerbose(vector<int> arr) {
    printHeader("SELECTION SORT - Tung buoc");

    int n = arr.size();
    int step = 0;

    cout << GRY << "Ban dau : " << RST;
    printArray(arr);

    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;

        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIdx])
                minIdx = j;
        }

        if (minIdx != i) {
            swap(arr[i], arr[minIdx]);
            step++;

            cout << YLW
                << "Buoc " << setw(2) << step
                << " swap [" << i << "] <-> ["
                << minIdx << "]: "
                << RST;

            printArray(arr, i, minIdx);
        }
    }

    cout << GRN << "Ket qua : " << RST;
    printArray(arr);
}

// ------------------------------------------------------------
// Insertion Sort
// ------------------------------------------------------------
void insertionSortVerbose(vector<int> arr) {
    printHeader("INSERTION SORT - Tung buoc");

    int n = arr.size();
    int step = 0;

    cout << GRY << "Ban dau : " << RST;
    printArray(arr);

    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;

        bool moved = false;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
            moved = true;
        }

        arr[j + 1] = key;

        if (moved) {
            step++;

            cout << YLW
                << "Buoc " << setw(2) << step
                << " chen " << key
                << " -> vi tri "
                << j + 1 << ": "
                << RST;

            printArray(arr, j + 1);
        }
    }

    cout << GRN << "Ket qua : " << RST;
    printArray(arr);
}

int main() {

    vector<int> arr = { 17, 12, 22, 8, 15, 5, 20, 3, 18 };

    cout << BOLD << CYN
        << "\n+----------------------------------------+\n"
        << "|    BAI 1 - IN TUNG BUOC SAP XEP       |\n"
        << "+----------------------------------------+\n"
        << RST;

    bubbleSortVerbose(arr);
    selectionSortVerbose(arr);
    insertionSortVerbose(arr);

    cout << "\n";
    return 0;
}