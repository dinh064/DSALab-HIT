#include iostream
using namespace std;


=========================================
        MINI DISCORD - TEST CASES
=========================================

TEST CASE 1 Register
-----------------------------------------
Input
Username Alice
Password 123

Expected
Dang ky thanh cong!

=========================================

TEST CASE 2 Login
-----------------------------------------
Input
Username Alice
Password 123

Expected
Dang nhap thanh cong!

=========================================

TEST CASE 3 Search User
-----------------------------------------
Input
Alice

Expected
Tim thay User!

Input
David

Expected
Khong tim thay!

=========================================

TEST CASE 4 Send Message
-----------------------------------------
Current User
Alice

Receiver
Bob

Message
Hello Bob

Expected
Gui thanh cong!

Dang nhap Bob

Inbox

Expected
From  Alice
Text  Hello Bob

=========================================

TEST CASE 5 Undo Message
-----------------------------------------
Current User
Alice

Send
Hello Bob

Undo Message

Expected
Da Undo tin nhan!

History

Expected
Lich su rong!

=========================================

TEST CASE 6 Save Data
-----------------------------------------
Input
Save Data

Expected
Da luu users.txt

=========================================

TEST CASE 7 Load Data
-----------------------------------------
Input
Load Data

Expected
Da tai du lieu!

Show Users

Expected
Danh sach User hien thi day du.

=========================================

TEST CASE 8 Gui cho chinh minh
-----------------------------------------
Current User
Alice

Receiver
Alice

Expected
Khong the gui tin nhan cho chinh minh!

=========================================

TEST CASE 9 Gui cho User khong ton tai
-----------------------------------------
Current User
Alice

Receiver
XYZ

Expected
Nguoi dung khong ton tai!

=========================================

TEST CASE 10 Load nhieu lan
-----------------------------------------
Load Data
Load Data
Load Data

Expected
Khong bi trung User.


int main()
{
    cout  =====================================n;
    cout   MINI DISCORD - TEST CASE DOCUMENTn;
    cout  =====================================nn;

    cout  Tat ca test case duoc mo ta trong comment cua file.n;
    cout  Su dung de doi chieu khi demo chuong trinh.n;

    return 0;
}