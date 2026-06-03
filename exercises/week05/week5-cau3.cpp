/*
 * ============================================================
 *  BAI 3 - HEAP SORT TU DAU (khong dung priority_queue)
 *  In tung buoc xay dung heap va extract
 * ============================================================
 */

#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <string>
#include <cmath>

using namespace std;

const string RST = "\033[0m";
const string BOLD = "\033[1m";
const string CYN = "\033[96m";
const string YLW = "\033[93m";
const string GRN = "\033[92m";
const string RED = "\033[91m";
const string GRY = "\033[90m";
const string MAG = "\033[95m";

// --- Ve cay nhi phan ra console -------------------------------
void printTree(const vector<int>& a, int size, int hi1 = -1, int hi2 = -1) {
    int h = 0;
    while ((1 << h) - 1 < size) h++;

    int idx = 0;

    for (int level = 0; level < h && idx < size; level++) {
        int nodesInLevel = 1 << level;
        int spacing = (1 << (h - level)) - 1;
        int halfSp = spacing / 2;

        cout << string(halfSp * 2, ' ');

        for (int i = 0; i < nodesInLevel && idx < size; i++, idx++) {
            if (idx == hi1)
                cout << RED << BOLD;
            else if (idx == hi2)
                cout << YLW << BOLD;
            else
                cout << CYN;

            cout << setw(3) << a[idx] << RST;

            if (i + 1 < nodesInLevel && idx + 1 < size)
                cout << string(spacing * 2 - 1, ' ');
        }

        cout << "\n";
    }
}

// --- Sift-down (heapify down) --------------------------------
long long g_cmps = 0;
long long g_swaps = 0;

void siftDown(vector<int>& a, int i, int n, bool verbose = false) {
    while (true) {
        int largest = i;
        int l = 2 * i + 1;
        int r = 2 * i + 2;

        if (l < n) {
            g_cmps++;
            if (a[l] > a[largest])
                largest = l;
        }

        if (r < n) {
            g_cmps++;
            if (a[r] > a[largest])
                largest = r;
        }

        if (largest == i)
            break;

        if (verbose) {
            cout << YLW
                << "  siftDown: swap [" << i << "]="
                << a[i] << " <-> ["
                << largest << "]="
                << a[largest]
                << "\n"
                << RST;
        }

        swap(a[i], a[largest]);
        g_swaps++;

        i = largest;
    }
}

// --- Build Max-Heap ------------------------------------------
void buildHeap(vector<int>& a, bool verbose) {
    int n = (int)a.size();

    cout << "\n  " << BOLD << MAG
        << "[ Phase 1: Build Max-Heap ]\n"
        << RST;

    if (verbose) {
        cout << GRY << "  Mang ban dau:\n  ";

        for (int x : a)
            cout << setw(4) << x;

        cout << "\n" << RST;
    }

    for (int i = n / 2 - 1; i >= 0; i--) {
        if (verbose) {
            cout << "\n  "
                << CYN
                << "Heapify node [" << i << "]="
                << a[i]
                << ":\n"
                << RST;
        }

        siftDown(a, i, n, verbose);

        if (verbose) {
            cout << "  Cay sau buoc nay:\n";
            printTree(a, n, i, -1);
        }
    }

    if (verbose) {
        cout << "\n  "
            << GRN
            << BOLD
            << "Max-Heap da xay xong:\n"
            << RST;

        printTree(a, n);

        cout << GRN << "  Mang: ";

        for (int x : a)
            cout << setw(4) << x;

        cout << "\n" << RST;
    }
}

// --- Heap Sort -----------------------------------------------
void heapSort(vector<int>& a, bool verbose) {
    int n = (int)a.size();

    g_cmps = 0;
    g_swaps = 0;

    buildHeap(a, verbose);

    cout << "\n  "
        << BOLD
        << MAG
        << "[ Phase 2: Extract Max x "
        << n
        << " ]\n"
        << RST;

    for (int i = n - 1; i > 0; i--) {
        if (verbose) {
            cout << "\n  "
                << YLW
                << "Extract max="
                << a[0]
                << " -> vi tri ["
                << i
                << "]\n"
                << RST;
        }

        swap(a[0], a[i]);
        g_swaps++;

        siftDown(a, 0, i, verbose);

        if (verbose) {
            cout << "  Heap con lai:  " << CYN;

            for (int k = 0; k < i; k++)
                cout << setw(4) << a[k];

            cout << RST
                << GRN
                << "  |sorted|";

            for (int k = i; k < n; k++)
                cout << setw(4) << a[k];

            cout << "\n" << RST;
        }
    }
}

// --- Demo nho -------------------------------------------------
void runDemo() {
    cout << BOLD << CYN
        << "\n==========================================\n"
        << "   BAI 3 - HEAP SORT (Verbose Demo)\n"
        << "==========================================\n"
        << RST;

    vector<int> arr = { 4, 10, 3, 5, 1, 8, 7, 2, 9, 6 };

    cout << "\n  Mang demo: ";

    for (int x : arr)
        cout << setw(4) << x;

    cout << "\n";

    heapSort(arr, true);

    cout << "\n  "
        << GRN
        << BOLD
        << "Ket qua: ";

    for (int x : arr)
        cout << setw(4) << x;

    cout << "\n" << RST;

    cout << "  "
        << GRY
        << "So sanh: "
        << g_cmps
        << "  |  Hoan vi: "
        << g_swaps
        << "\n"
        << RST;
}

// --- Chung minh O(n log n) -----------------------------------
void proveComplexity() {
    cout << "\n"
        << BOLD
        << CYN
        << "==================================================\n"
        << "  Dem ops theo n - Chung minh O(n log n)\n"
        << "==================================================\n"
        << RST;

    cout << "  "
        << BOLD
        << left
        << setw(8) << "n"
        << setw(14) << "So sanh"
        << setw(14) << "Hoan vi"
        << setw(16) << "n*log2(n)"
        << setw(10) << "cmp/nlogn"
        << "\n"
        << RST;

    cout << "  " << string(62, '-') << "\n";

    for (int n : {16, 64, 256, 1024, 4096, 16384}) {
        vector<int> arr(n);

        for (int i = 0; i < n; i++)
            arr[i] = n - i;

        g_cmps = 0;
        g_swaps = 0;

        heapSort(arr, false);

        double theory = n * log2(n);

        cout << "  "
            << YLW << setw(8) << n << RST
            << setw(14) << g_cmps
            << setw(14) << g_swaps
            << setw(16) << fixed << setprecision(1) << theory
            << GRN << setw(10) << fixed << setprecision(3)
            << (double)g_cmps / theory
            << RST
            << "\n";
    }

    cout << "\n  "
        << MAG
        << "Ti le cmp/(n*log2(n)) on dinh -> Heap Sort la Theta(n log n)\n"
        << "Best case = Average case = Worst case.\n"
        << RST;
}

int main() {
    runDemo();
    proveComplexity();
    return 0;
}