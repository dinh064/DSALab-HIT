/*
 * ============================================================
 *  BAI 2 - QUICK SORT
 *  4 chien luoc pivot: FIRST, LAST, MIDDLE, RANDOM
 *  So sanh so phep so sanh + thoi gian tren 3 loai du lieu
 * ============================================================
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <random>
#include <iomanip>
#include <chrono>
#include <string>
#include <functional>

using namespace std;
using namespace chrono;

const string RST = "\033[0m";
const string BOLD = "\033[1m";
const string CYN = "\033[96m";
const string YLW = "\033[93m";
const string GRN = "\033[92m";
const string RED = "\033[91m";
const string GRY = "\033[90m";
const string MAG = "\033[95m";

mt19937 rng(2024);

// --- Pivot strategies ----------------------------------------
enum PivotStrategy { FIRST, LAST, MIDDLE, RANDOM_P };

int choosePivot(vector<int>& a, int lo, int hi, PivotStrategy ps) {
    switch (ps) {
    case FIRST:    return lo;
    case LAST:     return hi;
    case MIDDLE:   return lo + (hi - lo) / 2;
    case RANDOM_P: return lo + rng() % (hi - lo + 1);
    }
    return hi;
}

// --- Partition (Lomuto) --------------------------------------
long long g_cmps = 0;

int partition(vector<int>& a, int lo, int hi, PivotStrategy ps) {
    int pivIdx = choosePivot(a, lo, hi, ps);

    swap(a[pivIdx], a[hi]); // dua pivot ve cuoi

    int pivot = a[hi];
    int i = lo - 1;

    for (int j = lo; j < hi; j++) {
        g_cmps++;
        if (a[j] <= pivot)
            swap(a[++i], a[j]);
    }

    swap(a[i + 1], a[hi]);
    return i + 1;
}

void quickSort(vector<int>& a, int lo, int hi, PivotStrategy ps) {
    if (lo >= hi) return;

    int p = partition(a, lo, hi, ps);

    quickSort(a, lo, p - 1, ps);
    quickSort(a, p + 1, hi, ps);
}

// --- Benchmark helper ----------------------------------------
struct Result {
    long long cmps;
    double us;
};

Result bench(const vector<int>& input, PivotStrategy ps, int runs = 3) {
    double total = 0;
    long long lastCmps = 0;

    for (int r = 0; r < runs; r++) {
        vector<int> tmp = input;

        g_cmps = 0;
        rng.seed(2024); // reset seed cho RANDOM on dinh

        auto t1 = high_resolution_clock::now();

        quickSort(tmp, 0, (int)tmp.size() - 1, ps);

        auto t2 = high_resolution_clock::now();

        total += duration<double, micro>(t2 - t1).count();
        lastCmps = g_cmps;
    }

    return { lastCmps, total / runs };
}

// --- Demo cay phan hoach -------------------------------------
void demoStep(const vector<int>& a, int lo, int hi, int pivIdx, int depth) {
    string indent(depth * 2, ' ');

    cout << GRY << indent;

    for (int i = 0; i < (int)a.size(); i++) {
        if (i < lo || i > hi)
            cout << GRY << setw(4) << a[i];
        else if (i == pivIdx)
            cout << RED << BOLD << setw(4) << a[i] << RST;
        else
            cout << YLW << setw(4) << a[i];
    }

    cout << RST << "  pivot=" << RED << BOLD << a[pivIdx] << RST << "\n";
}

int partitionVerbose(vector<int>& a, int lo, int hi, int depth) {
    int pivIdx = lo + (hi - lo) / 2;

    demoStep(a, lo, hi, pivIdx, depth);

    swap(a[pivIdx], a[hi]);

    int pivot = a[hi];
    int i = lo - 1;

    for (int j = lo; j < hi; j++)
        if (a[j] <= pivot)
            swap(a[++i], a[j]);

    swap(a[i + 1], a[hi]);

    return i + 1;
}

void quickSortVerbose(vector<int>& a, int lo, int hi, int depth = 0) {
    if (lo >= hi) return;

    int p = partitionVerbose(a, lo, hi, depth);

    quickSortVerbose(a, lo, p - 1, depth + 1);
    quickSortVerbose(a, p + 1, hi, depth + 1);
}

int main() {
    cout << BOLD << CYN
        << "\n===============================================\n"
        << "   BAI 2 - QUICK SORT (4 Pivot Strategies)\n"
        << "===============================================\n"
        << RST;

    // --- Demo nho ---
    cout << "\n  " << BOLD
        << "Demo pivot=MIDDLE, mang 10 phan tu (do=pivot, vang=vung dang xet):\n"
        << RST;

    vector<int> demo = { 8, 3, 1, 7, 0, 10, 2, 5, 9, 4 };

    cout << GRY << "  Ban dau:";
    for (int x : demo) cout << setw(4) << x;
    cout << "\n" << RST;

    quickSortVerbose(demo, 0, (int)demo.size() - 1);

    cout << GRN << "  Ket qua:";
    for (int x : demo) cout << setw(4) << x;
    cout << "\n" << RST;

    // --- Bang so sanh ---
    const int N = 1000;

    vector<int> sorted_a(N), rev_a(N), rand_a(N);

    iota(sorted_a.begin(), sorted_a.end(), 1);

    iota(rev_a.begin(), rev_a.end(), 1);
    reverse(rev_a.begin(), rev_a.end());

    iota(rand_a.begin(), rand_a.end(), 1);

    mt19937 rng2(42);
    shuffle(rand_a.begin(), rand_a.end(), rng2);

    struct PS {
        string name;
        string color;
        PivotStrategy ps;
    };

    vector<PS> strategies = {
        {"First",  RED, FIRST},
        {"Last",   YLW, LAST},
        {"Middle", GRN, MIDDLE},
        {"Random", CYN, RANDOM_P}
    };

    struct DataSet {
        string name;
        vector<int>& arr;
    };

    vector<DataSet> datasets = {
        {"Random",   rand_a},
        {"Sorted",   sorted_a},
        {"Reversed", rev_a}
    };

    for (auto& ds : datasets) {
        cout << "\n  " << BOLD << MAG
            << "Du lieu: " << ds.name
            << " (n=" << N << ")\n"
            << RST;

        cout << BOLD
            << "  -------------------------------------------------\n"
            << "  Pivot Strategy     So sanh         Thoi gian\n"
            << "  -------------------------------------------------\n"
            << RST;

        for (auto& st : strategies) {
            auto r = bench(ds.arr, st.ps);

            cout << "  "
                << st.color << BOLD << left << setw(14) << st.name << RST
                << "   "
                << right << setw(12) << r.cmps
                << "   "
                << fixed << setprecision(1)
                << setw(10) << r.us << " us\n";
        }

        cout << BOLD
            << "  -------------------------------------------------\n"
            << RST;
    }

    cout << "\n  " << BOLD << CYN << "Ket luan:\n" << RST
        << "  - " << RED << "First/Last pivot" << RST
        << ": Worst case O(n^2) khi du lieu da sap xep.\n"
        << "  - " << GRN << "Middle pivot" << RST
        << ": On dinh hon, tranh duoc worst case thuong gap.\n"
        << "  - " << CYN << "Random pivot" << RST
        << ": Ky vong O(n log n) voi moi loai du lieu.\n"
        << "  - Trong thuc te: median-of-3 hoac random la lua chon tot nhat.\n";

    return 0;
}