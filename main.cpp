#include"TextBuffer.h"

bool assertEqual(const string& result, const string& expected) {
    if (result == expected) {
        cout << "Right" << endl;
        return true;
    } else {
        cout << "Wrong: Expected " << expected << ", but got " << result << endl;
        return false;
    }
}

string pointToStr(Point& p) {
    stringstream ss;
    ss << p;
    return ss.str();
}

string doubleToStr(double& x) {
    stringstream ss;
    ss << fixed << setprecision(2) << x;
    return ss.str();
}

void assertEqualString(const string& actual, const string& expected) {
    if (actual == expected) {
        cout << "Right" << endl;
    } else {
        cout << "Wrong: expected \"" << expected << "\", got \"" << actual << "\"" << endl;
    }
}

void assertCursor(int actual, int expected) {
    if (actual == expected) {
        cout << "Right" << endl;
    } else {
        cout << "Wrong cursor: expected " << expected << ", got " << actual << endl;
    }
}

void testDoublyLinkedList() {
    // Test 1: insertAtHead
    {
        DoublyLinkedList<int> list;
        list.insertAtHead(3);
        list.insertAtHead(2);
        list.insertAtHead(1);
        assertEqual(list.toString(), "[1, 2, 3]");
    }

    // Test 2: insertAtTail
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        list.insertAtTail(2);
        list.insertAtTail(3);
        assertEqual(list.toString(), "[1, 2, 3]");
    }

    // Test 3: insertAt
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        list.insertAtTail(3);
        list.insertAt(1, 2);  
        assertEqual(list.toString(), "[1, 2, 3]");
    }

    // Test 4: deleteAt head
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        list.insertAtTail(2);
        list.insertAtTail(3);
        list.deleteAt(0);
        assertEqual(list.toString(), "[2, 3]");
    }

    // Test 5: deleteAt middle
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        list.insertAtTail(2);
        list.insertAtTail(3);
        list.deleteAt(1);
        assertEqual(list.toString(), "[1, 3]");
    }

    // Test 6: deleteAt tail
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        list.insertAtTail(2);
        list.insertAtTail(3);
        list.deleteAt(2);
        assertEqual(list.toString(), "[1, 2]");
    }

    // Test 7: get(index)
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(10);
        list.insertAtTail(20);
        list.insertAtTail(30);
        int x = list.get(1); // should be 20
        if (x == 20) cout << "Right" << endl;
        else cout << "Wrong: Expected 20, got " << x << endl;
    }

    // Test 8: indexOf(item)
    {cout<<"done 8";
        DoublyLinkedList<int> list;
        list.insertAtTail(5);
        list.insertAtTail(10);
        list.insertAtTail(15);
        int idx = list.indexOf(10);
        if (idx == 1) cout << "Right" << endl;
        else cout << "Wrong: Expected index 1, got " << idx << endl;
    }

    // Test 9: contains
    { cout<<"done 9";
        DoublyLinkedList<int> list;
        list.insertAtTail(2);
        list.insertAtTail(4);
        list.insertAtTail(6);
        bool has4 = list.contains(4);
        bool has7 = list.contains(7);
        if (has4 && !has7) cout << "Right" << endl;
        else cout << "Wrong: contains failed" << endl;
    }

    //Test 10: reverse()
    { 
        cout<<"test 10";
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        list.insertAtTail(2);
        list.insertAtTail(3);
        list.reverse();
        assertEqual(list.toString(), "[3, 2, 1]");
    }

    // Test 11: insert + delete + reverse kết hợp
    { 
        DoublyLinkedList<int> list;
        list.insertAtTail(10);
        list.insertAtTail(20);
        list.insertAtTail(30);
        list.insertAt(1, 15); // [10, 15, 20, 30]
        list.deleteAt(2);     // [10, 15, 30]
        list.reverse();       // [30, 15, 10]
        assertEqual(list.toString(), "[30, 15, 10]");
    }

    // Test 12: toString() empty
    {
        DoublyLinkedList<int> list;
        assertEqual(list.toString(), "[]");
    }

    // Test 13: toString() 1 phần tử
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(42);
        assertEqual(list.toString(), "[42]");
    }
}

void testDoublyLinkedListWithPoint() {
    // Test 1: insertAtHead
    {
        DoublyLinkedList<Point> list;
        list.insertAtHead(Point(3, 0));
        list.insertAtHead(Point(2, 0));
        list.insertAtHead(Point(1, 0));
        assertEqual(list.toString(pointToStr), "[(1,0,0), (2,0,0), (3,0,0)]");
    }

    // Test 2: insertAtTail
    {
        DoublyLinkedList<Point> list;
        list.insertAtTail(Point(1, 2));
        list.insertAtTail(Point(3, 4));
        list.insertAtTail(Point(5, 6));
        assertEqual(list.toString(pointToStr), "[(1,2,0), (3,4,0), (5,6,0)]");
    }

    // Test 3: insertAt middle
    {
        DoublyLinkedList<Point> list;
        list.insertAtTail(Point(0, 0));
        list.insertAtTail(Point(2, 2));
        list.insertAt(1, Point(1, 1)); // chèn giữa
        assertEqual(list.toString(pointToStr), "[(0,0,0), (1,1,0), (2,2,0)]");
    }

    // Test 4: deleteAt
    {
        DoublyLinkedList<Point> list;
        list.insertAtTail(Point(0, 0));
        list.insertAtTail(Point(1, 1));
        list.insertAtTail(Point(2, 2));
        list.deleteAt(1); // xoá (1,1,0)
        assertEqual(list.toString(pointToStr), "[(0,0,0), (2,2,0)]");
    }

    // Test 5: get + ==
    {
        DoublyLinkedList<Point> list;
        Point p1(7, 8, 9);
        list.insertAtTail(p1);
        list.insertAtTail(Point(10, 11, 12));
        if (list.get(0) == p1)
            cout << "Right" << endl;
        else
            cout << "Wrong: get() failed" << endl;
    }

    // Test 6: contains
    {
        DoublyLinkedList<Point> list;
        Point p1(1, 2, 3);
        Point p2(4, 5, 6);
        list.insertAtTail(p1);
        list.insertAtTail(p2);
        Point p3(1, 2, 3);
        if (list.contains(p3))
            cout << "Right" << endl;
        else
            cout << "Wrong: contains() failed" << endl;
    }

    // Test 7: indexOf
    {cout<<"Test 7";
        DoublyLinkedList<Point> list;
        list.insertAtTail(Point(0, 0, 0));
        list.insertAtTail(Point(1, 1, 1));
        list.insertAtTail(Point(2, 2, 2));
        int idx = list.indexOf(Point(1, 1, 1));
        if (idx == 1)
            cout << "Right" << endl;
        else
            cout << "Wrong: Expected 1, got " << idx << endl;
    }

    // Test 8: reverse
    {
        DoublyLinkedList<Point> list;
        list.insertAtTail(Point(1, 0));
        list.insertAtTail(Point(2, 0));
        list.insertAtTail(Point(3, 0));
        list.reverse();
        assertEqual(list.toString(pointToStr), "[(3,0,0), (2,0,0), (1,0,0)]");
    }

    // Test 9: full combo
    {
        DoublyLinkedList<Point> list;
        list.insertAtTail(Point(1, 1));
        list.insertAtTail(Point(2, 2));
        list.insertAt(1, Point(1.5, 1.5));
        list.deleteAt(0); // xóa (1,1)
        list.reverse();   // [(2,2,0), (1.5,1.5,0)]
        assertEqual(list.toString(pointToStr), "[(2,2,0), (1.5,1.5,0)]");
    }

    // Test 10: empty
    {
        DoublyLinkedList<Point> list;
        assertEqual(list.toString(pointToStr), "[]");
    }

    // Test 11: 1 phần tử
    {
        DoublyLinkedList<Point> list;
        list.insertAtTail(Point(10, 20, 30));
        assertEqual(list.toString(pointToStr), "[(10,20,30)]");
    }
}

void testDoublyLinkedListWithDouble() {
    // Test 1: insertAtHead
    {
        DoublyLinkedList<double> list;
        list.insertAtHead(3.3);
        list.insertAtHead(2.2);
        list.insertAtHead(1.1);
        assertEqual(list.toString(doubleToStr), "[1.10, 2.20, 3.30]");
    }

    // Test 2: insertAtTail
    {
        DoublyLinkedList<double> list;
        list.insertAtTail(1.5);
        list.insertAtTail(2.5);
        list.insertAtTail(3.5);
        assertEqual(list.toString(doubleToStr), "[1.50, 2.50, 3.50]");
    }

    // Test 3: insertAt (giữa)
    {
        DoublyLinkedList<double> list;
        list.insertAtTail(1.0);
        list.insertAtTail(3.0);
        list.insertAt(1, 2.0); // chèn giữa
        assertEqual(list.toString(doubleToStr), "[1.00, 2.00, 3.00]");
    }

    // Test 4: deleteAt (cuối)
    {
        DoublyLinkedList<double> list;
        list.insertAtTail(10.1);
        list.insertAtTail(20.2);
        list.insertAtTail(30.3);
        list.deleteAt(2); // xóa 30.3
        assertEqual(list.toString(doubleToStr), "[10.10, 20.20]");
    }

    // Test 5: deleteAt (đầu)
    {
        DoublyLinkedList<double> list;
        list.insertAtTail(5.0);
        list.insertAtTail(10.0);
        list.deleteAt(0); // xóa 5.0
        assertEqual(list.toString(doubleToStr), "[10.00]");
    }

    // Test 6: get() giá trị đúng
    {
        DoublyLinkedList<double> list;
        list.insertAtTail(1.1);
        list.insertAtTail(2.2);
        double x = list.get(1); // 2.2
        if (fabs(x - 2.2) < 1e-9) cout << "Right" << endl;
        else cout << "Wrong: Expected 2.2, got " << x << endl;
    }

    // Test 7: get() với index sai
    { cout<<"Test 7:";
        DoublyLinkedList<double> list;
        list.insertAtTail(1.0);
        try {
            list.get(5); // sai index
            cout << "Wrong: Exception not thrown!" << endl;
        } catch (const out_of_range& e) {
            if (string(e.what()) == "Index is invalid!") cout << "Right" << endl;
            else cout << "Wrong message: " << e.what() << endl;
        }
    }

    // Test 8: deleteAt với index âm
    { cout<<"test 8";
        DoublyLinkedList<double> list;
        list.insertAtTail(3.3);
        try {
            list.deleteAt(-1);
            cout << "Wrong: Exception not thrown!" << endl;
        } catch (const out_of_range& e) {
            if (string(e.what()) == "Index is invalid!") cout << "Right" << endl;
            else cout << "Wrong message: " << e.what() << endl;
        }
    }

    // Test 9: insertAt với index > size
    {
        DoublyLinkedList<double> list;
        list.insertAtTail(1.1);
        try {
            list.insertAt(5, 9.9);
            cout << "Wrong: Exception not thrown!" << endl;
        } catch (const out_of_range& e) {
            if (string(e.what()) == "Index is invalid!") cout << "Right" << endl;
            else cout << "Wrong message: " << e.what() << endl;
        }
    }

    // Test 10: insertAt tại size (cuối danh sách, hợp lệ)
    {
        DoublyLinkedList<double> list;
        list.insertAtTail(1.1);
        list.insertAt(1, 2.2); // thêm vào cuối
        assertEqual(list.toString(doubleToStr), "[1.10, 2.20]");
    }

    // Test 11: insertAt tại 0 (đầu danh sách, hợp lệ)
    { cout<<"test 11";
        DoublyLinkedList<double> list;
        list.insertAtTail(5.5);
        list.insertAt(0, 1.1);
        assertEqual(list.toString(doubleToStr), "[1.10, 5.50]");
    }

    // Test 12: reverse
    {
        DoublyLinkedList<double> list;
        list.insertAtTail(1.1);
        list.insertAtTail(2.2);
        list.insertAtTail(3.3);
        list.reverse();
        assertEqual(list.toString(doubleToStr), "[3.30, 2.20, 1.10]");
    }
}

void testTextBuffer() {
    // Test 1: insert and getContent
    {
        cout<<"Test 1: ";
        TextBuffer tb;
        tb.insert('A');
        tb.insert('b');
        tb.insert('c');
        assertEqualString(tb.getContent(), "Abc");
        assertCursor(tb.getCursorPos(), 3);
    }

    // Test 2: moveCursorLeft and insert
    {
        cout<<"Test 2: ";
        TextBuffer tb;
        tb.insert('A');
        tb.insert('B');
        tb.moveCursorLeft(); // cursor tại 1
        tb.insert('X');
        assertEqualString(tb.getContent(), "AXB");
        assertCursor(tb.getCursorPos(), 2);
    }

    // Test 3: deleteChar
    {
        cout<<"Test 3: ";
        TextBuffer tb;
        tb.insert('A');
        tb.insert('B');
        tb.insert('C'); // cursor tại 3
        tb.moveCursorLeft(); // cursor tại 2
        tb.deleteChar(); // xóa C
        assertEqualString(tb.getContent(), "AC");
        assertCursor(tb.getCursorPos(), 1);
    }

    // Test 4: moveCursorTo
    {
        cout<<"Test 4: ";
        TextBuffer tb;
        tb.insert('A'); tb.insert('B'); tb.insert('C'); // "ABC"
        tb.moveCursorTo(1);
        assertCursor(tb.getCursorPos(), 1);
    }

    // Test 5: cursor out_of_bound left
    {
        cout<<"Test 5: ";
        TextBuffer tb;
        try {
            tb.moveCursorLeft(); // cursor đang ở 0
            cout << "Wrong: exception not thrown!" << endl;
        } catch (const cursor_error& e) {
            cout << "Right" << endl;
        }
    }

    // Test 6: cursor out_of_bound right
    {
        cout<<"Test 6: ";
        TextBuffer tb;
        tb.insert('A');
        try {
            tb.moveCursorRight(); // cursor tại 1 rồi
            tb.moveCursorRight(); // lỗi
            cout << "Wrong: exception not thrown!" << endl;
        } catch (const cursor_error& e) {
            cout << "Right" << endl;
        }
    }

    // Test 7: deleteAllOccurrences
    {
        cout<<"Test 7: ";
        TextBuffer tb;
        tb.insert('A'); tb.insert('B'); tb.insert('A'); tb.insert('C'); // "ABAC"
        tb.deleteAllOccurrences('A');
        assertEqualString(tb.getContent(), "BC");
        assertCursor(tb.getCursorPos(), 0);
    }

    // Test 8: sortAscending
    {
        cout<<"Test 8: ";
        TextBuffer tb;
        tb.insert('B'); tb.insert('a'); tb.insert('b'); tb.insert('d'); tb.insert('D');
        tb.sortAscending(); 
        assertEqualString(tb.getContent(), "aBbDd");
    }

    // Test 9: findFirstOccurrence
    {
        cout<<"Test 9: ";
        TextBuffer tb;
        tb.insert('A'); tb.insert('B'); tb.insert('C');
        int pos = tb.findFirstOccurrence('B');
        if (pos == 1) cout << "Right" << endl;
        else cout << "Wrong: expected 1, got " << pos << endl;
    }

    // Test 10: undo 2 lần và insert mới
    {
        cout<<"Test 10: ";
        TextBuffer tb;
        tb.insert('A'); tb.insert('B'); tb.insert('C'); // "ABC"
        tb.undo(); // AB
        tb.undo(); // A
        tb.insert('Y'); // AY
        assertEqualString(tb.getContent(), "AY");

    }

    // Test 11: undo & redo
    {
        cout<<"Test 11: ";
        TextBuffer tb;
        tb.insert('A'); tb.insert('B'); tb.insert('C');
        tb.undo(); // AB
        tb.undo(); // A
        tb.redo(); // AB
        assertEqualString(tb.getContent(), "AB");
        assertCursor(tb.getCursorPos(), 2);
    }

    // Test 12: full action sequence history
    {
        cout<<"Test 12: ";
        TextBuffer tb;
        tb.insert('A');
        tb.insert('B');
        tb.insert('C');
        tb.moveCursorTo(2);
        tb.insert('X');
        tb.moveCursorRight();
        tb.deleteChar();

        cout << "Print history: ";
        tb.printHistory();
        
        // [(insert, 0, A), (insert, 1, B), (insert, 2, C), 
        //  (move, 3, J), (insert, 2, X), (move, 3, R), (delete, 4, C)]
        cout<<endl;
    }

    {
        cout << "Test 13: ";
        TextBuffer tb;
        tb.insert('c'); tb.insert('a'); tb.insert('b'); // cab
        tb.sortAscending(); // abc
        tb.undo(); // quay về cab
        assertEqualString(tb.getContent(), "cab");
    }

    {
        cout << "Test 14: ";
        TextBuffer tb;
        tb.insert('x'); tb.insert('y'); tb.insert('z'); // xyz
        tb.moveCursorLeft(); // xy|z
        cout<<tb.getCursorPos();
        tb.deleteChar(); // x|z
        tb.undo(); // xy|z
        tb.undo(); // xyz|
        tb.redo(); // xy|z
        tb.redo(); // x|z
        assertEqualString(tb.getContent(), "xz");
        assertCursor(tb.getCursorPos(), 1);
    }

        {
        cout << "Test 15: ";
        TextBuffer tb;
        tb.insert('d'); tb.insert('a'); tb.insert('c'); tb.insert('b'); // dacb
        tb.moveCursorLeft(); // dac|b
        tb.sortAscending(); // abcd
        tb.undo(); // quay lại dac|b
        assertEqualString(tb.getContent(), "dacb");
        assertCursor(tb.getCursorPos(), 3);
    }

    {
        cout << "Test 16: ";
        TextBuffer tb;
        tb.insert('M'); tb.insert('N');
        tb.moveCursorLeft(); // M|N
        tb.insert('O'); // MO|N
        tb.undo(); // M|N
        tb.redo(); // MO|N
        assertEqualString(tb.getContent(), "MON");
        assertCursor(tb.getCursorPos(), 2);
    }

        {
        cout << "Test 17: ";
        TextBuffer tb;
        tb.insert('3'); tb.insert('1'); tb.insert('2'); // 312
        tb.sortAscending(); // 123
        tb.moveCursorLeft(); // 12|3
        tb.deleteChar(); // 1|3
        tb.undo(); // 12|3
        tb.undo(); // 123|
        tb.undo(); // 312|
        assertEqualString(tb.getContent(), "312");
    }

        {
        cout << "Test 18: ";
        TextBuffer tb;
        tb.insert('A'); tb.insert('B'); tb.insert('C'); // ABC
        tb.deleteChar(); // AB
        tb.undo(); // ABC
        tb.insert('D'); // ABCD, redo bị xóa
        try {
            tb.redo(); // không làm gì
        } catch (...) {
            assert(false); // Không được throw
        }
        assertEqualString(tb.getContent(), "ABCD");
    }

        {
        cout << "Test 19: ";
        TextBuffer tb;
        tb.insert('b'); tb.insert('a'); tb.insert('c'); // bac
        tb.sortAscending(); // abc
        tb.undo(); // bac
        tb.redo(); // abc
        assertEqualString(tb.getContent(), "abc");
    }

        {
        cout << "Test 20: ";
        TextBuffer tb;
        tb.insert('X'); tb.insert('Y'); tb.insert('Z');
        tb.deleteChar(); // XY
        tb.moveCursorLeft(); // X|Y
 
        tb.sortAscending(); // XY
      
        // Undo 4 lần

        tb.undo(); // X|Y
        
        tb.undo(); // XY|
        
        tb.undo(); // XYZ|
        
        tb.undo(); // XY|
        
        assertEqualString(tb.getContent(), "XY");
    }

        {
        cout << "Test 21: ";
        TextBuffer tb;
        tb.insert('L'); tb.insert('M'); tb.insert('N'); // LMN
        tb.undo(); // LM
        tb.undo(); // L
        tb.undo(); // ""
        tb.redo(); // L
        tb.redo(); // LM
        tb.redo(); // LMN
        assertEqualString(tb.getContent(), "LMN");
    }

        {
        cout << "Test 22: ";
        TextBuffer tb;
        tb.insert('d'); tb.insert('c'); tb.insert('b'); tb.insert('a'); // dcba
        tb.sortAscending(); // abcd
        tb.undo(); // dcba
        tb.insert('z'); // dcbaz
        try {
            tb.redo(); // không được sort lại
        } catch (...) {
            assert(false); // không nên throw
        }
        assertEqualString(tb.getContent(), "dcbaz");
    }
}
int main(){
    testDoublyLinkedList();cout<< "done"<<endl<<endl;
    testDoublyLinkedListWithPoint();cout<< "done"<<endl<<endl;    
    testDoublyLinkedListWithDouble();cout<< "done"<<endl<<endl; 
    testTextBuffer();cout<< "done"<<endl<<endl; 
    return 0;
}