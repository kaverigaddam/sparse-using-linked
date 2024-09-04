#include <iostream>

struct Node {
    int row, col, value;
    Node *next, *prev;
    Node(int r, int c, int v) : row(r), col(c), value(v), next(nullptr), prev(nullptr) {}
};

class SparseMatrix {
private:
    Node *head, *tail;
    int numRows, numCols;

public:
    SparseMatrix(int r, int c) : head(nullptr), tail(nullptr), numRows(r), numCols(c) {}

    void insert(int r, int c, int v) {
        if (v == 0) return;
        Node* newNode = new Node(r, c, v);
        if (!head) {
            head = tail = newNode;
        } else if (r < head->row || (r == head->row && c < head->col)) {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        } else {
            Node* current = head;
            while (current->next && (current->next->row < r || 
                   (current->next->row == r && current->next->col < c))) {
                current = current->next;
            }
            newNode->next = current->next;
            newNode->prev = current;
            if (current->next) {
                current->next->prev = newNode;
            } else {
                tail = newNode;
            }
            current->next = newNode;
        }
    }

    void display() {
        Node* current = head;
        for (int i = 0; i < numRows; i++) {
            for (int j = 0; j < numCols; j++) {
                if (current && current->row == i && current->col == j) {
                    std::cout << current->value << " ";
                    current = current->next;
                } else {
                    std::cout << "0 ";
                }
            }
            std::cout << std::endl;
        }
    }

    ~SparseMatrix() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

int main() {
    SparseMatrix sm(4, 5);
    sm.insert(0, 2, 3);
    sm.insert(0, 4, 4);
    sm.insert(1, 2, 5);
    sm.insert(1, 3, 7);
    sm.insert(3, 1, 2);
    sm.insert(3, 2, 6);
    sm.display();
    return 0;
}
