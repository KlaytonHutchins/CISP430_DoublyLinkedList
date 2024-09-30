#include <iostream>
#include <fstream>

using namespace std;

//Change file names here if applicable
string inFileName = "input.txt";
string outFileName = "output.txt";

//Node class with previous and next nodes.
//Member variables are private, must use getter and setter functions.
class Node {
public:
        //Construct new node with a name
        Node(string initName) {
                name = initName;
                next = nullptr;
                prev = nullptr;
        }
        //Getters and Setters
        void setName(string n) {
                name = n;
        }
        string getName() {
                return name;
        }
        void setNext(Node* n) {
                next = n;
        }
        Node* getNext() {
                return next;
        }
        void setPrev(Node* p) {
                prev = p;
        }
        Node* getPrev() {     
                return prev;
        }
private:
        string name;
        Node* next;
        Node* prev;
};

//Doubly Linked List class with private head and tail.
//Contains:
//Constructor, Destructor, Getters and Setters.
//Self Sorting Insert function, Delete function, and Traversal functions.
class DoublyLL {
public:
        //Construct new empty Doubly Linked List
        DoublyLL() {
                head = nullptr;
                tail = nullptr;
        }
        //Destructor
        ~DoublyLL() {
                Node* curr = head;
                while (curr) {
                        Node* tempNext = curr->getNext();
                        delete curr;
                        curr = tempNext;
                }
        }
        //Insert function
        void insert(string nameToInsert) {
                Node* newNode = new Node(nameToInsert);
                if (!head) {  //empty list
                        head = newNode;
                        tail = newNode;
                } else if (nameToInsert < head->getName()) {  //insert at head
                        newNode->setNext(head);
                        head->setPrev(newNode);
                        head = newNode;
                } else if (nameToInsert > tail->getName()) {  //insert at tail
                        newNode->setPrev(tail);
                        tail->setNext(newNode);
                        tail = newNode;
                } else {  //insert somewhere in the middle of the list
                        Node* curr = head;
                        while(curr) {  //loop through list to find insertion point
                                if (nameToInsert < curr->getName()) {  //insert before curr
                                        newNode->setNext(curr);
                                        newNode->setPrev(curr->getPrev());
                                        curr->getPrev()->setNext(newNode);
                                        curr->setPrev(newNode);
                                        break;
                                }
                                curr = curr->getNext();
                        }
                }
        }
        //Delete function
        void deleteNode(string nameToDelete) {
                Node* curr = head;
                while (curr) {
                        Node* nextNode = curr->getNext();
                        if (curr->getName() == nameToDelete) {
                                if (curr->getPrev()) {  //if curr != head
                                        curr->getPrev()->setNext(curr->getNext());
                                } else {  //curr == head, reassign head to the second node
                                        head = curr->getNext();
                                }
                                if (curr->getNext()) {  //if curr != tail
                                        curr->getNext()->setPrev(curr->getPrev());
                                } else {  //deleting tail, reassign tail to its previous node
                                        tail = curr->getPrev();
                                }
                                delete curr;
                                break;  //comment out if expecting duplicates and want to delete all instances
                        }
                        curr = nextNode;
                }
        }
        //Traverse function, uses ofstream to pass data back to main
        ofstream& traverseAscending(ofstream& outFile) {
                Node* curr = head;
                while (curr) {
                        outFile << curr->getName() << endl;
                        curr = curr->getNext();
                }
                return outFile;
        }
        //Traverse function, uses ofstream to pass data back to main
        ofstream& traverseDescending(ofstream& outFile) {
                Node* curr = tail;
                while (curr) {
                        outFile << curr->getName() << endl;
                        curr = curr->getPrev();
                }
                return outFile;
        }
        //Getters and Setters   
        void setHead(Node* h) {
                head = h;
        }
        Node* getHead() {
                return head;
        }
        void setTail(Node* t) {
                tail = t;
        }
        Node* getTail() {
                return tail;
        }
private:
        Node* head;
        Node* tail;
};

//Helper function to convert text to all lower case
string toLower(string str) {
        for (size_t i = 0; i < str.length(); i++) {
                str[i] = tolower(str[i]);
        }
        return str;
}

int main() {
        ifstream inFile;
        inFile.open(inFileName);
        string newName;
        DoublyLL* nameList = new DoublyLL;
        while (inFile >> newName) {
                newName = toLower(newName);
                if (newName == "delete") {
                        //Delete encountered, need to take in a new name before deletion
                        inFile >> newName;
                        newName = toLower(newName);
                        nameList->deleteNode(newName);
                } else { 
                        nameList->insert(newName);
                }
        }
        inFile.close();
        ofstream outFile;
        outFile.open(outFileName);
        nameList->traverseAscending(outFile);
        outFile << "=============" << endl;
        nameList->traverseDescending(outFile);
        outFile.close();
        delete nameList;
        return 0;
}
