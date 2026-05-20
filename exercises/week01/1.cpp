#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>

using namespace std;

// ======================================================
// CONFIG
// ======================================================

const int HANG = 8;
const int COT = 10;
const int GIA_VE = 80000;
const int MAX_UNDO = 5;
const int MAX_QUEUE = 100;

// ======================================================
// PHIM
// ======================================================

struct Phim {
    string maPhim;
    string tenPhim;
    string theLoai;
    int thoiLuong;
    string lichChieu;
    double doanhThu;

    Phim() {
        thoiLuong = 0;
        doanhThu = 0;
    }

    Phim(string ma, string ten, string tl, int tg, string lich) {
        maPhim = ma;
        tenPhim = ten;
        theLoai = tl;
        thoiLuong = tg;
        lichChieu = lich;
        doanhThu = 0;
    }
};

// ======================================================
// BST
// ======================================================

struct NodeBST {
    Phim phim;
    NodeBST* left;
    NodeBST* right;

    NodeBST(const Phim& p) {
        phim = p;
        left = right = nullptr;
    }
};

struct BST {

    NodeBST* root;

    BST() {
        root = nullptr;
    }

    ~BST() {
        clear(root);
    }

    void clear(NodeBST* n) {
        if (!n) return;

        clear(n->left);
        clear(n->right);

        delete n;
    }

    NodeBST* insertNode(NodeBST* n, const Phim& p) {

        if (!n)
            return new NodeBST(p);

        if (p.maPhim < n->phim.maPhim)
            n->left = insertNode(n->left, p);

        else if (p.maPhim > n->phim.maPhim)
            n->right = insertNode(n->right, p);

        return n;
    }

    void insert(const Phim& p) {
        root = insertNode(root, p);
    }

    NodeBST* searchNode(NodeBST* n, const string& ma) {

        if (!n)
            return nullptr;

        if (ma == n->phim.maPhim)
            return n;

        if (ma < n->phim.maPhim)
            return searchNode(n->left, ma);

        return searchNode(n->right, ma);
    }

    NodeBST* search(const string& ma) {
        return searchNode(root, ma);
    }

    void printInOrder(NodeBST* n) {

        if (!n)
            return;

        printInOrder(n->left);

        cout << left
            << setw(10) << n->phim.maPhim
            << setw(25) << n->phim.tenPhim
            << setw(15) << n->phim.theLoai
            << setw(8) << n->phim.thoiLuong
            << n->phim.lichChieu << "\n";

        printInOrder(n->right);
    }

    void showMovies() {

        if (!root) {
            cout << "Khong co phim!\n";
            return;
        }

        cout << left
            << setw(10) << "Ma"
            << setw(25) << "Ten phim"
            << setw(15) << "The loai"
            << setw(8) << "TG"
            << "Lich chieu\n";

        cout << string(70, '-') << "\n";

        printInOrder(root);
    }

    void revenue(NodeBST* n) {

        if (!n)
            return;

        revenue(n->left);

        cout << n->phim.tenPhim
            << " : "
            << fixed << setprecision(0)
            << n->phim.doanhThu
            << " VND\n";

        revenue(n->right);
    }

    void showRevenue() {
        revenue(root);
    }
};

// ======================================================
// STACK
// ======================================================

struct Action {

    int h;
    int c;

    char oldState;
};

struct UndoStack {

    Action data[MAX_UNDO];

    int top;

    UndoStack() {
        top = -1;
    }

    bool empty() {
        return top == -1;
    }

    bool full() {
        return top == MAX_UNDO - 1;
    }

    void push(Action a) {

        if (full()) {

            for (int i = 0; i < top; i++)
                data[i] = data[i + 1];

            data[top] = a;
        }
        else {
            data[++top] = a;
        }
    }

    Action pop() {

        if (empty())
            return { -1,-1,'O' };

        return data[top--];
    }

    void clear() {
        top = -1;
    }
};

// ======================================================
// QUEUE
// ======================================================

struct Refund {

    int h;
    int c;

    string ten;
};

struct RefundQueue {

    Refund data[MAX_QUEUE];

    int front;
    int rear;
    int size;

    RefundQueue() {
        front = rear = size = 0;
    }

    bool empty() {
        return size == 0;
    }

    bool full() {
        return size == MAX_QUEUE;
    }

    void enqueue(Refund r) {

        if (full()) {
            cout << "Queue day!\n";
            return;
        }

        data[rear] = r;

        rear = (rear + 1) % MAX_QUEUE;

        size++;
    }

    Refund dequeue() {

        if (empty())
            return { -1,-1,"" };

        Refund r = data[front];

        front = (front + 1) % MAX_QUEUE;

        size--;

        return r;
    }

    void clear() {
        front = rear = size = 0;
    }

    void print() {

        if (empty()) {
            cout << "Hang doi trong!\n";
            return;
        }

        for (int i = 0; i < size; i++) {

            Refund r = data[(front + i) % MAX_QUEUE];

            cout << i + 1
                << ". "
                << r.ten
                << " | Ghe "
                << (char)('A' + r.h)
                << r.c + 1
                << "\n";
        }
    }
};

// ======================================================
// PHONG CHIEU
// ======================================================

struct PhongChieu {

    char ghe[HANG][COT];

    UndoStack undoStack;

    RefundQueue refundQueue;

    double doanhThu;

    string maPhim;

    PhongChieu() {

        doanhThu = 0;

        resetRoom();
    }

    void resetRoom() {

        for (int i = 0; i < HANG; i++)
            for (int j = 0; j < COT; j++)
                ghe[i][j] = 'O';

        doanhThu = 0;

        undoStack.clear();

        refundQueue.clear();
    }

    bool validSeat(int h, int c) {

        return h >= 0 && h < HANG
            && c >= 0 && c < COT;
    }

    void printSeats() {

        cout << "\n    ";

        for (int j = 0; j < COT; j++)
            cout << setw(3) << j + 1;

        cout << "\n";

        for (int i = 0; i < HANG; i++) {

            cout << (char)('A' + i) << " |";

            for (int j = 0; j < COT; j++)
                cout << " " << ghe[i][j] << " ";

            cout << "\n";
        }
    }

    bool book(int h, int c) {

        if (!validSeat(h, c)) {
            cout << "Ghe khong hop le!\n";
            return false;
        }

        if (ghe[h][c] == 'X') {
            cout << "Ghe da dat!\n";
            return false;
        }

        ghe[h][c] = 'X';

        undoStack.push({ h,c,'O' });

        doanhThu += GIA_VE;

        cout << "Dat ve thanh cong!\n";

        return true;
    }

    bool cancel(int h, int c) {

        if (!validSeat(h, c)) {
            cout << "Ghe khong hop le!\n";
            return false;
        }

        if (ghe[h][c] == 'O') {
            cout << "Ghe chua dat!\n";
            return false;
        }

        ghe[h][c] = 'O';

        undoStack.push({ h,c,'X' });

        doanhThu -= GIA_VE;

        cout << "Da huy ghe!\n";

        return true;
    }

    int undo() {

        Action a = undoStack.pop();

        if (a.h == -1) {
            cout << "Khong co undo!\n";
            return 0;
        }

        if (a.oldState == 'O') {

            ghe[a.h][a.c] = 'O';

            doanhThu -= GIA_VE;

            cout << "Undo dat ve!\n";

            return -GIA_VE;
        }

        ghe[a.h][a.c] = 'X';

        doanhThu += GIA_VE;

        cout << "Undo huy ve!\n";

        return GIA_VE;
    }
};

// ======================================================
// UTIL
// ======================================================

bool readSeat(int& h, int& c) {

    string s;

    cin >> s;

    if (s.length() < 2)
        return false;

    s[0] = toupper(s[0]);

    h = s[0] - 'A';

    try {
        c = stoi(s.substr(1)) - 1;
    }
    catch (...) {
        return false;
    }

    return true;
}

// ======================================================
// MAIN
// ======================================================

int main() {

    BST bst;

    PhongChieu room;

    bst.insert(Phim("P001", "Avengers", "Action", 181, "14:00"));
    bst.insert(Phim("P002", "Interstellar", "Sci-Fi", 169, "16:00"));
    bst.insert(Phim("P003", "Your Name", "Anime", 106, "18:00"));

    int choice;

    do {

        cout << "\n========== RAP CHIEU PHIM ==========\n";

        cout << "1. Danh sach phim\n";
        cout << "2. Chon phim\n";
        cout << "3. Xem ghe\n";
        cout << "4. Dat ve\n";
        cout << "5. Huy ve\n";
        cout << "6. Undo\n";
        cout << "7. Doanh thu\n";
        cout << "0. Thoat\n";

        cout << "Chon: ";
        cin >> choice;

        switch (choice) {

        case 1:
            bst.showMovies();
            break;

        case 2: {

            string ma;

            cout << "Nhap ma phim: ";
            cin >> ma;

            NodeBST* n = bst.search(ma);

            if (!n) {
                cout << "Khong tim thay!\n";
                break;
            }

            room.maPhim = ma;

            room.resetRoom();

            cout << "Da chon phim: "
                << n->phim.tenPhim
                << "\n";

            break;
        }

        case 3:
            room.printSeats();
            break;

        case 4: {

            int h, c;

            cout << "Nhap ghe: ";

            if (!readSeat(h, c)) {
                cout << "Sai dinh dang!\n";
                break;
            }

            bool ok = room.book(h, c);

            if (ok) {

                NodeBST* n = bst.search(room.maPhim);

                if (n)
                    n->phim.doanhThu += GIA_VE;
            }

            break;
        }

        case 5: {

            int h, c;

            cout << "Nhap ghe: ";

            if (!readSeat(h, c)) {
                cout << "Sai dinh dang!\n";
                break;
            }

            bool ok = room.cancel(h, c);

            if (ok) {

                NodeBST* n = bst.search(room.maPhim);

                if (n)
                    n->phim.doanhThu -= GIA_VE;
            }

            break;
        }

        case 6: {

            int delta = room.undo();

            NodeBST* n = bst.search(room.maPhim);

            if (n)
                n->phim.doanhThu += delta;

            break;
        }

        case 7:
            bst.showRevenue();
            break;

        case 0:
            cout << "Tam biet!\n";
            break;

        default:
            cout << "Lua chon khong hop le!\n";
        }

    } while (choice != 0);

    return 0;
}