\# Mini Discord



\## Tên ứng dụng



\*\*Mini Discord\*\* là chương trình mô phỏng một ứng dụng nhắn tin đơn giản trên Console bằng C++. Chương trình cho phép người dùng đăng ký, đăng nhập, tìm kiếm người dùng, gửi tin nhắn và lưu dữ liệu.



\---



\## Cấu trúc dữ liệu sử dụng



\### 1. Linked List

\- Dùng để lưu danh sách người dùng.

\- Lý do: dễ thêm người dùng mới và duyệt toàn bộ danh sách.



\### 2. Binary Search Tree (BST)

\- Dùng để tìm kiếm người dùng theo username.

\- Lý do: tốc độ tìm kiếm nhanh hơn so với duyệt Linked List.



\### 3. Queue

\- Dùng để lưu hàng đợi tin nhắn (Inbox).

\- Lý do: tin nhắn được xử lý theo nguyên tắc FIFO (First In First Out).



\### 4. Stack

\- Dùng để lưu lịch sử gửi tin nhắn và hỗ trợ chức năng Undo.

\- Lý do: Stack hoạt động theo nguyên tắc LIFO (Last In First Out), phù hợp để hoàn tác tin nhắn cuối cùng.



\---



\## Compile và chạy



\### Visual Studio

\- Mở Project.

\- Nhấn \*\*Ctrl + F5\*\* để chạy.



\### g++



```bash

g++ main.cpp user.cpp bst.cpp message.cpp stack.cpp file.cpp -o MiniDiscord

```



\---



\## Chức năng chính:

1. Đăng ký tài khoản (Register).

2\. Đăng nhập (Login).

3\. Hiển thị danh sách người dùng (Show Users).

4\. Tìm kiếm người dùng bằng BST (Search User).

5\. Hiển thị cây BST (Show BST).

6\. Gửi tin nhắn (Send Message).

7\. Xem hộp thư đến (Inbox).

8\. Hoàn tác tin nhắn cuối (Undo Message).

9\. Xem lịch sử tin nhắn (Message History).

10\. Lưu dữ liệu người dùng vào file (Save Data).

11\. Đọc dữ liệu người dùng từ file (Load Data).

12\. Thoát chương trình (Exit).



\## Chức năng kiểm tra:

1. Không cho phép đăng ký trùng username.

2\. Kiểm tra đúng tài khoản và mật khẩu khi đăng nhập.

3\. Chỉ gửi tin nhắn cho người dùng đã tồn tại.

4\. Không cho phép gửi tin nhắn cho chính mình.

5\. Chống trùng dữ liệu khi nạp từ file.



\---



\## Test Cases



\### Test Case 1: Đăng ký



\*\*Input\*\*



```

Username: Alice

Password: 123

```



\*\*Kết quả mong đợi\*\*



```

Đăng ký thành công.

```



\---



\### Test Case 2: Đăng nhập



\*\*Input\*\*



```

Username: Alice

Password: 123

```



\*\*Kết quả mong đợi\*\*



```

Đăng nhập thành công.

```



\---



\### Test Case 3: Tìm kiếm User



\*\*Input\*\*



```

Alice

```



\*\*Kết quả mong đợi\*\*



```

Tìm thấy User.

```



\---



\### Test Case 4: Gửi tin nhắn



\*\*Input\*\*



```

Người gửi: Alice

Người nhận: Bob

Nội dung: Hello Bob

```



\*\*Kết quả mong đợi\*\*



```

Gửi thành công.

```



Sau khi Bob đăng nhập:



```

Inbox



From : Alice

Hello Bob

```



\---



\### Test Case 5: Undo



\*\*Input\*\*



```

Undo Message

```



\*\*Kết quả mong đợi\*\*



```

Đã Undo tin nhắn cuối cùng.

```



\---



\## Cấu trúc file

┌──src/

│    ├──main.cpp

│    ├──user.h

│    ├──user.cpp

│    ├──bst.h

│    ├──bst.cpp

│    ├──message.h

│    ├──message.cpp

│    ├──stack.h

│    ├──stack.cpp

│    ├──file.h

│    └──file.cpp

├──tests/

│    └── test\_cases.cpp

│

└──README.md



\---



\- Họ và tên: Lê Văn Dinh

\- Môn học: CSDL \& GT

\- Đề tài: Mini Discord





