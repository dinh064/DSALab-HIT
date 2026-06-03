/*
 * ============================================================
 *  BAI 2 - DEM SO PHEP SO SANH VA HOAN VI
 *  Cung 1 mang 100 phan tu, in bang so sanh
 * ============================================================
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iomanip>
#include <random>
using namespace std;

const string RST = "\033[0m";
const string BOLD = "\033[1m";
const string CYN = "\033[96m";
const string YLW = "\033[93m";
const string GRN = "\033[92m";
const string RED = "\033[91m";
const string GRY = "\033[90m";

struct Stats {
    long long cmps = 0;
    long long swaps = 0;
};

Stats bubbleSortCount(vector<int> arr) {
    Stats s;
    int n = arr.size();

    for (int i = 0; i < n - 1; i++) {
        bool sw = false;

        for (int j = 0; j < n - i - 1; j++) {
            s.cmps++;

            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                s.swaps++;
                sw = true;
            }
        }

        if (!sw) break;
    }

    return s;
}

Stats selectionSortCount(vector<int> arr) {
    Stats s;
    int n = arr.size();

    for (int i = 0; i < n - 1; i++) {
        int m = i;

        for (int j = i + 1; j < n; j++) {
            s.cmps++;

            if (arr[j] < arr[m])
                m = j;
        }

        if (m != i) {
            swap(arr[i], arr[m]);
            s.swaps++;
        }
    }

    return s;
}

Stats insertionSortCount(vector<int> arr) {
    Stats s;
    int n = arr.size();

    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0) {
            s.cmps++;

            if (arr[j] > key) {
                arr[j + 1] = arr[j];
                j--;
                s.swaps++;
            }
            else {
                break;
            }
        }

        arr[j + 1] = key;
    }

    return s;
}

int main() {

    // Tao mang 100 phan tu ngau nhien
    mt19937 rng(2024);

    vector<int> arr(100);
    iota(arr.begin(), arr.end(), 1);
    shuffle(arr.begin(), arr.end(), rng);

    auto bs = bubbleSortCount(arr);
    auto ss = selectionSortCount(arr);
    auto is = insertionSortCount(arr);

    cout << BOLD << CYN
        << "\n+----------------------------------------+\n"
        << "|   BAI 2 - DEM SO SANH & HOAN VI       |\n"
        << "+----------------------------------------+\n"
        << RST;

    cout << "  Mang " << arr.size()
        << " phan tu (1..100, tron ngau nhien, seed=2024)\n\n";

    cout << BOLD
        << "  +------------------+--------------+--------------+\n"
        << "  | Thuat toan       | So sanh      | Hoan vi      |\n"
        << "  +------------------+--------------+--------------+\n"
        << RST;

    auto row = [&](const string& name,
        const Stats& s,
        const string& color) {

            cout << "  | "
                << color << BOLD
                << left << setw(16) << name
                << RST
                << " | "
                << right << setw(12) << s.cmps
                << " | "
                << right << setw(12) << s.swaps
                << " |\n";
        };

    row("Bubble Sort", bs, YLW);
    row("Selection Sort", ss, GRN);
    row("Insertion Sort", is, CYN);

    cout << BOLD
        << "  +------------------+--------------+--------------+\n"
        << RST;

    cout << "\n  " << BOLD << CYN << "Nhan xet:" << RST
        << "\n  - " << GRN << "Selection Sort" << RST
        << ": luon dung n(n-1)/2 so sanh, it hoan vi nhat (<= n-1)"
        << "\n  - " << CYN << "Insertion Sort" << RST
        << ": thuong it so sanh hon Bubble trong average case"
        << "\n  - " << YLW << "Bubble Sort" << RST
        << ": nhieu hoan vi nhat, kem hieu qua nhat\n";

    return 0;
}