#include "TextBuffer.h"

// ----------------- DoublyLinkedList -----------------
template <typename T>
DoublyLinkedList<T>::DoublyLinkedList() {
    // TODO
    head=nullptr; count = 0; tail=nullptr;
}

template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
    // TODO
    Node<T>* Temp = head;
			while (Temp!=nullptr) {
				Temp = head->next;
				delete head;
				head = Temp;}
    tail = nullptr;
    count = 0;
    return;
}

// TODO: implement other methods of DoublyLinkedList
//insertAtHead
template <typename T>
void DoublyLinkedList<T>::insertAtHead(T data) {
    Node<T>* temp = new Node<T>(data);

    temp->next = head;
    if (head != nullptr) head->prev = temp;
    else tail = temp;
    head = temp;
    count++;
    return;
}
//insertAtTail
template <typename T>
void DoublyLinkedList<T>:: insertAtTail(T data){
     Node<T>* temp = new Node<T>(data);
    temp->prev = tail;
    temp->next = nullptr;
    if (tail != nullptr) tail->next = temp;
    else head = temp;
    tail = temp;
    count++;
    return;
}
//insertAt
template <typename T>
void DoublyLinkedList<T>::  insertAt(int index, T data){
if((index<0)||(index>count)){throw out_of_range("Index is invalid!");}
if(index==0){insertAtHead(data);return;}
if(index==count){insertAtTail(data);return;}
int i=0;
 Node<T>* temp = head;
 Node<T>* temp0 = new Node<T>(data);

while(i<index-1){temp=temp->next;i++;}
temp0->next=temp->next;
temp0->prev=temp;
temp->next->prev=temp0;
temp->next=temp0;
count++;
return;
}
//deleteAt
template <typename T>
void DoublyLinkedList<T>:: deleteAt(int index){
if((index<0)||(index>count-1)){throw out_of_range("Index is invalid!");}
Node<T>* temp = head;
if (index==0){head=head->next;
    if(head!=nullptr){//truong hop count==1
        head->prev=nullptr;}
    else{
        tail=nullptr;
    }
    }
else{
if(index==count-1){
    temp=tail;
    tail=tail->prev;
    tail->next=nullptr;
    //khong can xet truong hop count =1 va 2 vi o tren da xet roi
}
else{
    //xet cac truong hop thong thuong
    while(index>0){temp=temp->next;index--;}
    temp->next->prev=temp->prev;
    temp->prev->next=temp->next;
}
}
delete temp;
count--;
return;
}
template <typename T>
void DoublyLinkedList<T>::set(int index,T data){
    if((index<0)||(index>count)){throw out_of_range("Index is invalid!");}
    Node<T>* temp = head;
for(int i =0; i<index;i++){temp=temp->next;}
temp->data=data;
return;
}
template <typename T>
T& DoublyLinkedList<T>:: get(int index) const{
    if((index<0)||(index>count)){throw out_of_range("Index is invalid!");}
    Node<T>* temp = head;
for(int i =0; i<index;i++){temp=temp->next;}
return temp->data;
}
//indexOf
template <typename T>
int DoublyLinkedList<T>::indexOf(T item) const{
Node<T>* temp=head;
int i;
for(i=0 ; i<count;i++){if(temp->data==item){return i;}temp=temp->next;}
return -1;
}
//contain
template <typename T>
bool DoublyLinkedList<T>:: contains(T item) const{
Node<T>* temp=head;    
int i;
for(i=0 ; i<count;i++){if(temp->data==item){break;}temp=temp->next;}
if(i==count){return 0;}
return 1;
}
//size
template <typename T>
int DoublyLinkedList<T>::size() const {
    return count;
}
//reverse
template <typename T>
void DoublyLinkedList<T>::reverse() {
    Node<T>* curr = head;
    Node<T>* temp = nullptr;
    if((curr==nullptr)||curr->next==nullptr)return;
    while (curr!=nullptr) {
        temp=curr->prev;
        curr->prev=curr->next;
        curr->next=temp;
        curr=curr->prev;
    }
    if(temp!=nullptr){
        tail=head;
        head=temp->prev;
    }
    return;
}
//to string
template <typename T>
string DoublyLinkedList<T>:: toString(string (*convert2str)(T&)) const{
    string result="";result="[";
    Node<T>* temp = head;
    for(int i=0;i<count;i++){
        if(convert2str==nullptr){
            ostringstream text;
            text<<temp->data;
            result += text.str();
            if(temp->next!=nullptr){result+=", ";}
        }
        else {
            result += convert2str(temp->data);
            if(i+1!=count)result+=", ";
        }
        temp=temp->next;
    }
result+="]";
return result;
}
// ----------------- TextBuffer -----------------
TextBuffer::TextBuffer() {
    cursorPos=0;
    history=new HistoryManager();
    sorttime=0;
    sortcount=0;
    sortload=new string[sortcount];
}

TextBuffer::~TextBuffer() {
    delete history;
}

// TODO: implement other methods of TextBuffer
void TextBuffer::insert(char c){
    buffer.insertAt(cursorPos,c);
    history->addAction("insert",cursorPos,c);
    cursorPos++;
    return;
}

void TextBuffer::deleteChar(){
    if(cursorPos==0)return;
    char temp=buffer.get(cursorPos-1);
    buffer.deleteAt(cursorPos-1);
    history->addAction("delete",cursorPos,temp);
    cursorPos--;
    return;
}
void TextBuffer::moveLeft(){
    cursorPos--;
    return;
}
void TextBuffer::moveRight(){
    cursorPos++;
    return;
}
void TextBuffer::moveCursorLeft(){
    if (cursorPos <= 0) throw cursor_error();
    history->addAction("move",cursorPos,'L');
    moveLeft();
    return;
}
void TextBuffer::moveCursorRight(){
    if (cursorPos >= buffer.size()) throw cursor_error();
    history->addAction("move",cursorPos,'R');
    moveRight();
    return;
}
void TextBuffer::moveCursorTo(int index){
    if((index<0)||(index>buffer.size())){throw out_of_range("Index is invalid!");}
    if(index==cursorPos)return;
    while(index<cursorPos){moveLeft();}
    while(index>cursorPos){moveRight();}
    history->addAction("move",index,'J');
    return;
}
string TextBuffer::getContent() const{
    string result;
    for(int i=0;i<buffer.size();i++){
        result+=buffer.get(i);
    }
    return result;  
}
void TextBuffer::printHistory()const{
    history->printHistory();
}
int TextBuffer::getCursorPos() const{
    return cursorPos;
}

int TextBuffer::findFirstOccurrence(char c) const{
    for(int i=0 ;i<buffer.size();i++){
        if(c==buffer.get(i)){history->reset();return i;}
    }
    history->reset();
    return -1;
}

int* TextBuffer::findAllOccurrences(char c, int &count) const{
    //dang su dung 2 vung cap phat cung 1 luc, co the toi uu hon vung max cap phat 
    //nhung se ton nhieu thoi gian cho vong lap thu 2
    int *a=new int [buffer.size()];
    count=0;
    for(int i=0 ;i<buffer.size();i++){
        if(c==buffer.get(i)){a[count]=i;count++;}
    }
    int *b=new int [count];
    for(int i=0;i<count;i++){
        b[i]=a[i];
    }
    delete[] a;
    history->reset();
    return b;
}
bool TextBuffer::compare(char a, char b){
    if(tolower(a)>tolower(b)){return 1;}//a>b
    if(tolower(a)<tolower(b)){return 0;}//a<b
    if(isupper(a)<isupper(b)){return 1;}//neu a la
        else{return 0;};
    }
void TextBuffer::merge(char* arr,int left,int mid, int right){
    int n1=mid-left+1;
    int n2=right-mid;
    char *arr1=new char[n1];
    char *arr2=new char[n2];
    for(int i=0;i< n1;i++){arr1[i]=arr[left+i];}
    for(int i=0;i< n2;i++){arr2[i]=arr[mid+1+i];}
    int i=0,j=0,k=left;
    while((i<n1) && (j<n2)){
    if(compare(arr1[i],arr2[j])){arr[k++]=arr2[j++];}
    else{arr[k++]=arr1[i++];}
    }
    while (i<n1){arr[k++]=arr1[i++];}
    while (j<n2){arr[k++]=arr2[j++];}
    delete[]arr1;
    delete[]arr2;
}
void TextBuffer::mergesort(char* arr,int left, int right){
    if(left>=right)return;
    int mid=(left+right)/2;
    mergesort(arr,left,mid);
    mergesort(arr,mid+1,right);
    merge(arr,left,mid,right);
}
void TextBuffer::sortAscending(){
    int n=buffer.size();
    if(n==0)return;
    //neu chua sort lan nao
    if(sortcount==0){
    sortcount=1;
    string line="";
        for(int i=0;i<buffer.size();i++){
        line+=buffer.get(i);
    }sortload=new string[1];
    sortload[0]=line;
    }
    //
    
    //bat dau sort
    char *arr=new char[n];
    for(int i=0;i<n;i++){
        arr[i]=buffer.get(i);
    }
    //merge sort
    mergesort(arr,0,n-1);
    //
    for(int i=0;i<n;i++){
        buffer.get(i)=arr[i];
    }
    //sort xong, luu dang da sort vao sort sortload
    
    sorttime++;
    sortcount=sorttime+1;
    
    string *temp=new string[sortcount];
    for(int i=0;i<sortcount-1;i++){
        temp[i]=sortload[i];
    }
    string line="";
    for(int i=0;i<buffer.size();i++){
        line+=buffer.get(i);
    }
    temp[sortcount-1]=line;
    delete[] sortload;
    sortload=temp;
    history->addAction("sort",cursorPos,'\0');
    delete[] arr;  
}
void TextBuffer::deleteAllOccurrences(char c){
    for(int i=0 ;i<buffer.size();i++){
        if(c==buffer.get(i)){buffer.deleteAt(i); }
    }
    cursorPos=0;
    return ;
}
void TextBuffer::undo(){
    
    if((history->current<=0)|| history->size()==0){return;}
    
    
    Act temp=history->history.get(history->current-1);
    history->current--;
    if(temp.actioname=="insert"){
    buffer.deleteAt(temp.pos);
    cursorPos=temp.pos;
    }
    if(temp.actioname=="delete"){
    buffer.insertAt(temp.pos-1,temp.letter);
    cursorPos=temp.pos;}
    if(temp.actioname=="sort"){
        if(sorttime>0){
        sorttime--;
        stringtochar(sorttime);}//undo sort
    }
    //con lai cac truong hop move
    if(temp.letter=='L'){cursorPos++;}
    if(temp.letter=='R'){cursorPos--;}
    if(temp.letter=='J'){cursorPos=temp.pos;}
}
void TextBuffer::redo(){
    if((history->current>=history->size())|| history->size()==0){return;}
    history->current++;
    Act temp=history->history.get(history->current-1);
    if(temp.actioname=="insert"){   
    buffer.insertAt(temp.pos,temp.letter);
    cursorPos=temp.pos+1;
    }
    if(temp.actioname=="delete"){
    buffer.deleteAt(temp.pos-1);
    cursorPos=temp.pos-1;
    }
    if(temp.actioname=="sort"){
        if(sortcount>sorttime){
        sorttime++;
        stringtochar(sorttime);}//redo sort 
    }
    //con lai cac truong hop move
    if(temp.letter=='L'){cursorPos--;}
    if(temp.letter=='R'){cursorPos++;}
    if(temp.letter=='J'){cursorPos=temp.pos;}
}
void TextBuffer::stringtochar(int num){
    
    string line=sortload[num];
    for(int i=0;i<line.size();i++){
        buffer.set(i,line[i]);
    }
    sorttime=num;
}

// ----------------- HistoryManager -----------------
TextBuffer::HistoryManager::HistoryManager() {
    // TODO
    current=0;
}

TextBuffer::HistoryManager::~HistoryManager() {
    // TODO
}
void TextBuffer::HistoryManager::addAction(const string &actionName, int cursorPos, char c){
while(current<history.size()){history.deleteAt(history.size()-1);}
    history.insertAtTail(Act(actionName,cursorPos,c));
    current++;
}
void TextBuffer::HistoryManager::printHistory() const{
    cout<<"[";
    Act temp("",0,'\0');
    for(int i=0;i<history.size();i++){
        temp=history.get(i);
        cout<<"("<<temp.actioname<<","<<temp.pos<<","<<temp.letter<<")";
        if(i!=history.size()-1){cout<<",";}
    }
    cout<<"]";
}
int TextBuffer::HistoryManager::size() const{return history.size();}
void TextBuffer::HistoryManager::reset() {
    for(int i=0;i<history.size();i++){
        history.deleteAt(history.size()-1);
    }
    return;
}
//TODO: implement other methods of HistoryManager

//   template instantiation for char, string, int, double, float, and Point
template class DoublyLinkedList<char>;
template class DoublyLinkedList<string>;
template class DoublyLinkedList<int>;
template class DoublyLinkedList<double>;
template class DoublyLinkedList<float>;
template class DoublyLinkedList<Point>;