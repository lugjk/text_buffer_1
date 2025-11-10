#ifndef __TEXT_BUFFER_H__
#define __TEXT_BUFFER_H__

#include "main.h"
template <typename T>
class Node {
 	public:	
		T data; 
	 	Node* next;
        Node* prev;

     Node(T val) : data(val), prev(nullptr), next(nullptr) {}
};
template <typename T>
class DoublyLinkedList {
    // TODO: may provide some attributes
    int count;
	Node<T>* head;
    Node<T>* tail;
public:
    DoublyLinkedList();
    ~DoublyLinkedList();

    void insertAtHead(T data);
    void insertAtTail(T data);
    void insertAt(int index, T data);
    void deleteAt(int index);
    void set(int index,T data);
    T& get(int index) const;
    int indexOf(T item) const;
    bool contains(T item) const;
    int size() const;
    void reverse();
    string toString(string (*convert2str)(T&) = 0) const;
};

class TextBuffer {
    public:
    struct Act{
            string actioname;
            int pos;
            char letter;
            Act(const string &actionName, int cursorPos, char c):actioname(actionName),pos(cursorPos),letter(c){}};
    class HistoryManager {
        // TODO: may provide some attributes
        private:
            int current;
            DoublyLinkedList<Act> history;
        public:

        HistoryManager();
        ~HistoryManager();
        void addAction(const string &actionName, int cursorPos, char c);
        void printHistory() const;
        int size() const;
        void reset();
        friend class TextBuffer;
    };
private:
    DoublyLinkedList<char> buffer; 
    int cursorPos;
    HistoryManager* history;
    int sorttime;
    int sortcount;
    string *sortload;
    // TODO: may provide some attributes

public:
    TextBuffer();
    ~TextBuffer();
    void insert(char c);                                // add insert
    void deleteChar();                                  // add delete
    void moveCursorLeft();                              //add L
    void moveCursorRight();                             //add R
    void moveCursorTo(int index);                       //add J
    string getContent() const;                          //
    int getCursorPos() const;                           //
    int findFirstOccurrence(char c) const;              //
    int* findAllOccurrences(char c, int &count) const;  //
    void sortAscending();                               // add sort
    void deleteAllOccurrences(char c);                  // 
    void undo();
    void redo();
    void stringtochar(int num);
    void printHistory()const;
protected:
    void moveLeft();
    void moveRight();
    bool compare(char a,char b);
    void merge(char* arr,int left,int mid, int right);
    void mergesort(char* arr,int left, int right);
    
};

#endif // __TEXT_BUFFER_H__
