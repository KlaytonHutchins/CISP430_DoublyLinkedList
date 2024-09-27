#include <iostream>
#include <fstream>

using namespace std;

//Change file names here if applicable
string inFileName = "input.txt";
string outFileName = "output.txt"

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

class DoublyLL {
public:
private:
};

//Helper function to convert text to all lower case
string toLower(string str) {
}

int main() {
}
