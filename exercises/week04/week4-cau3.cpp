/*
 * ============================================================
 *  BAI 3 - BEST / WORST / AVERAGE CASE
 *  Do thoi gian chay 3 thuat toan tren 3 loai mang
 * ============================================================
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iomanip>
#include <random>
#include <chrono>

using namespace std;
using namespace chrono;

const string RST = "\033[0m";
const string BOLD = "\033[1m";
const string CYN = "\033[96m";
const string YLW = "\033[93m";
const string GRN = "\033[92m";
const string RED = "\033[91m";
const string GRY = "\033[90m";

// ------------------------------------------------------------
// Bubble Sort
// ------------------------------------------------------------
void bubbleSort(vector<int>& a) {
    int n = a.size();

    for (int i = 0; i < n - 1; i++) {
        bool sw = false;

        for (int j = 0; j < n - i - 1; j++) {
            if (a[j] > a[j + 1]) {
                swap(a[j], a[j + 1]);
                sw = true;
            }
        }

        if (!sw) break;
    }
}

// ------------------------------------------------------------
// Selection Sort
// ------------------------------------------------------------
void selectionSort(vector<int>& a) {
    int n = a.size();

    for (int i = 0; i < n - 1; i++) {
        int m = i;

        for (int j = i + 1; j < n; j++) {
            if (a[j] < a[m])
                m = j;
        }

        swap(a[i], a[m]);
    }
}

// ------------------------------------------------------------
// Insertion Sort
// ------------------------------------------------------------
void insertionSort(vector<int>& a) {
    int n = a.size();

    for (int i = 1; i < n; i++) {
        int key = a[i];
        int j = i - 1;

        while (j >= 0 && a[j] > key) {
            a[j + 1] = a[j];
            j--;
        }

        a[j + 1] = key;
    }
}

// ------------------------------------------------------------
// Benchmark
// ------------------------------------------------------------
template<typename Fn>
double benchmark(Fn fn, const vector<int>& input, int runs = 5) {

    double total = 0;

    for (int r = 0; r < runs; r++) {

        vector<int> tmp = input;

        auto t1 = high_resolution_clock::now();
        fn(tmp);
        auto t2 = high_resolution_clock::now();

        total += duration<double, micro>(t2 - t1).count();
    }

    return total / runs;
}

// ------------------------------------------------------------
// In bieu do ngang bang ky tu ASCII
// ------------------------------------------------------------
void printBar(double val, double maxVal, const string& color) {

    int w = (int)(val / maxVal * 30);

    if (w < 1)
        w = 1;

    cout << color;

    for (int i = 0; i < w; i++)
        cout << "#";

    cout << RST;
}

int main() {

    const int N = 2000;
    const int RUNS = 5;

    // Tao 3 loai mang
    vector<int> sorted_arr(N);
    vector<int> reversed_arr(N);
    vector<int> random_arr(N);

    iota(sorted_arr.begin(), sorted_arr.end(), 1);

    iota(reversed_arr.begin(), reversed_arr.end(), 1);
    reverse(reversed_arr.begin(), reversed_arr.end());

    iota(random_arr.begin(), random_arr.end(), 1);

    mt19937 rng(42);
    shuffle(random_arr.begin(), random_arr.end(), rng);

    cout << BOLD << CYN
        << "\n+----------------------------------------+\n"
        << "|  BAI 3 - BEST / WORST / AVERAGE CASE  |\n"
        << "+----------------------------------------+\n"
        << RST;

    cout << "  Mang " << N
        << " phan tu, trung binh "
        << RUNS
        << " lan, don vi: microseconds\n\n";

    struct Row {
        string name;
        string color;
        double best;
        double worst;
        double avg;
    };

    vector<Row> rows = {

        {
            "Bubble Sort",
            YLW,
            benchmark(bubbleSort, sorted_arr, RUNS),
            benchmark(bubbleSort, reversed_arr, RUNS),
            benchmark(bubbleSort, random_arr, RUNS)
        },

        {
            "Selection Sort",
            GRN,
            benchmark(selectionSort, sorted_arr, RUNS),
            benchmark(selectionSort, reversed_arr, RUNS),
            benchmark(selectionSort, random_arr, RUNS)
        },

        {
            "Insertion Sort",
            CYN,
            benchmark(insertionSort, sorted_arr, RUNS),
            benchmark(insertionSort, reversed_arr, RUNS),
            benchmark(insertionSort, random_arr, RUNS)
        }
    };

    // Bang so lieu
    cout << BOLD
        << "  +------------------+-------------+-------------+-------------+\n"
        << "  | Thuat toan       | Best        | Worst       | Avg         |\n"
        << "  +------------------+-------------+-------------+-------------+\n"
        << RST;

    for (auto& r : rows) {

        cout << "  | "
            << r.color << BOLD
            << left << setw(16) << r.name
            << RST
            << " | "
            << right << fixed << setprecision(1)
            << setw(9) << r.best
            << " | "
            << setw(9) << r.worst
            << " | "
            << setw(9) << r.avg
            << " |\n";
    }

    cout << BOLD
        << "  +------------------+-------------+-------------+-------------+\n"
        << RST;

    // Bieu do
    double maxVal = 0;

    for (auto& r : rows) {
        maxVal = max({ maxVal, r.best, r.worst, r.avg });
    }

    cout << "\n  " << BOLD
        << "Bieu do (# = thoi gian):\n"
        << RST;

    auto printRowBar =
        [&](const string& label,
            double val,
            const string& col,
            const string& tag) {

                cout << "  "
                    << col
                    << left << setw(18) << label
                    << RST
                    << " "
                    << tag << " ";

                printBar(val, maxVal, col);

                cout << "  "
                    << fixed << setprecision(1)
                    << val
                    << "\n";
        };

    for (auto& r : rows) {

        cout << "\n";

        printRowBar(r.name, r.best, r.color, "Best ");
        printRowBar("", r.worst, r.color, "Worst");
        printRowBar("", r.avg, r.color, "Avg  ");
    }

    // Ket luan
    cout << "\n  "
        << BOLD << CYN
        << "KET LUAN:"
        << RST

        << "\n  - "
        << CYN
        << "Insertion Sort"
        << RST
        << ": tot nhat cho mang da/gan sap xep -> O(n) best case"

        << "\n  - "
        << GRN
        << "Selection Sort"
        << RST
        << ": on dinh giua cac case, it swap, khong phu thuoc du lieu"

        << "\n  - "
        << YLW
        << "Bubble Sort"
        << RST
        << ": worst/avg cham nhat, khong phu hop du lieu lon"

        << "\n  - Ca 3 deu O(n^2) -> voi n lon nen dung Quick Sort hoac Merge Sort\n";

    return 0;
}