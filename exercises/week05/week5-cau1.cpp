/*
 * ============================================================
 *  BAI 1 - MERGE SORT DE QUY
 *  Dem so phep so sanh de chung minh O(n log n)
 * ============================================================
 */

#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
#include <numeric>
#include <random>
#include <algorithm>

using namespace std;

const string RST = "\033[0m";
const string BOLD = "\033[1m";
const string CYN = "\033[96m";
const string YLW = "\033[93m";
const string GRN = "\033[92m";
const string RED = "\033[91m";
const string GRY = "\033[90m";
const string MAG = "\033[95m";

long long g_cmps = 0;   // dem so sanh toan cuc
int g_depth = 0;        // do sau de quy hien tai

// --- In mang --------------------------------------------------
void printArr(const vector<int>& a, int lo, int hi, const string& color = GRY) {
    cout << color << "[";
    for (int i = lo; i <= hi; i++) {
        cout << a[i];
        if (i < hi) cout << " ";
    }
    cout << "]" << RST;
}

// --- Merge co dem so sanh ------------------------------------
void merge(vector<int>& a, int lo, int mid, int hi) {
    vector<int> L(a.begin() + lo, a.begin() + mid + 1);
    vector<int> R(a.begin() + mid + 1, a.begin() + hi + 1);

    int i = 0, j = 0, k = lo;

    while (i < (int)L.size() && j < (int)R.size()) {
        g_cmps++;
        if (L[i] <= R[j])
            a[k++] = L[i++];
        else
            a[k++] = R[j++];
    }

    while (i < (int)L.size())
        a[k++] = L[i++];

    while (j < (int)R.size())
        a[k++] = R[j++];
}

// --- Merge Sort de quy (verbose) ------------------------------
void mergeSortVerbose(vector<int>& a, int lo, int hi, bool verbose) {
    if (lo >= hi) return;

    int mid = lo + (hi - lo) / 2;

    if (verbose) {
        string indent(g_depth * 2, ' ');

        cout << GRY << indent << "split  ";
        printArr(a, lo, hi);

        cout << "  ->  ";
        printArr(a, lo, mid, YLW);

        cout << "  ";
        printArr(a, mid + 1, hi, CYN);

        cout << "\n" << RST;
    }

    g_depth++;

    mergeSortVerbose(a, lo, mid, verbose);
    mergeSortVerbose(a, mid + 1, hi, verbose);

    g_depth--;

    merge(a, lo, mid, hi);

    if (verbose) {
        string indent(g_depth * 2, ' ');

        cout << GRN << indent << "merge  ";
        printArr(a, lo, mid);

        cout << "  +  ";
        printArr(a, mid + 1, hi);

        cout << "  ->  ";
        printArr(a, lo, hi, GRN);

        cout << "\n" << RST;
    }
}

// --- Chung minh O(n log n) -----------------------------------
void proveComplexity() {
    cout << "\n" << BOLD << CYN
        << "==================================================\n"
        << "  CHUNG MINH O(n log n) - Dem so phep so sanh\n"
        << "==================================================\n"
        << RST;

    cout << "  " << BOLD << left
        << setw(8) << "n"
        << setw(14) << "Thuc do"
        << setw(16) << "n*log2(n)"
        << setw(10) << "Ti le"
        << "\n" << RST;

    cout << "  " << string(48, '-') << "\n";

    mt19937 rng(42);

    for (int n : {8, 16, 32, 64, 128, 256, 512, 1024, 4096, 16384}) {
        vector<int> arr(n);

        iota(arr.begin(), arr.end(), 1);
        shuffle(arr.begin(), arr.end(), rng);

        g_cmps = 0;

        mergeSortVerbose(arr, 0, n - 1, false);

        long long actual = g_cmps;
        double theory = n * log2(n);
        double ratio = actual / theory;

        cout << "  "
            << YLW << setw(8) << n << RST
            << setw(14) << actual
            << setw(16) << fixed << setprecision(1) << theory
            << GRN << setw(10) << fixed << setprecision(3) << ratio << RST
            << "\n";
    }

    cout << "\n  " << MAG
        << "Nhan xet: ti le thuc_do / (n*log2(n)) hoi tu ve ~0.97\n"
        << "Chung to Merge Sort chinh xac la Theta(n log n) comparisons.\n"
        << RST;
}

int main() {
    cout << BOLD << CYN
        << "\n==========================================\n"
        << "   BAI 1 - MERGE SORT DE QUY\n"
        << "==========================================\n"
        << RST;

    // Demo nho: in tung buoc
    vector<int> demo = { 38, 27, 43, 3, 9, 82, 10 };

    cout << "\n  " << BOLD
        << "Demo mang 7 phan tu - cay de quy:\n"
        << RST;

    g_cmps = 0;
    g_depth = 0;

    mergeSortVerbose(demo, 0, (int)demo.size() - 1, true);

    cout << "\n  " << GRN << "Ket qua: ";
    printArr(demo, 0, (int)demo.size() - 1, GRN);

    cout << "  |  So sanh: " << g_cmps << "\n" << RST;

    proveComplexity();

    return 0;
}