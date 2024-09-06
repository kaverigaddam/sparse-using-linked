#include <iostream>
#include <iomanip>

// Node structure for the linked list as shown in the image
struct Node {
    int row, col, value;
    Node* next;
    Node(int r, int c, int v) : row(r), col(c), value(v), next(nullptr) {}
};

class SparseMatrix {
private:
    Node* start;
    int numRows, numCols;

public:
    SparseMatrix(int rows, int cols) : start(nullptr), numRows(rows), numCols(cols) {}

    // Add a new element to the sparse matrix
    void addElement(int row, int col, int value) {
        if (value == 0) return; // Don't add zero elements

        Node* newNode = new Node(row, col, value);
        if (!start || row < start->row || (row == start->row && col < start->col)) {
            newNode->next = start;
            start = newNode;
        } else {
            Node* current = start;
            while (current->next && (current->next->row < row || 
                   (current->next->row == row && current->next->col < col))) {
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
        }
    }

    // Display the sparse matrix in linked list format as shown in the image
    void display() const {
        std::cout << "Sparse Matrix Representation (Linked List):\n";
        Node* current = start;
        while (current) {
            std::cout << "[" << current->row << " " << current->col << " " << current->value << "]";
            if (current->next) {
                std::cout << " -> ";
            } else {
                std::cout << " -> NULL";
            }
            current = current->next;
        }
        std::cout << std::endl;
    }

    // Display the original matrix
    void displayOriginal() const {
        int** matrix = new int*[numRows];
        for (int i = 0; i < numRows; ++i) {
            matrix[i] = new int[numCols]();
        }

        Node* current = start;
        while (current) {
            matrix[current->row][current->col] = current->value;
            current = current->next;
        }

        std::cout << "Original Matrix:\n";
        for (int i = 0; i < numRows; ++i) {
            for (int j = 0; j < numCols; ++j) {
                std::cout << std::setw(2) << matrix[i][j] << " ";
            }
            std::cout << "\n";
        }

        // Clean up
        for (int i = 0; i < numRows; ++i) {
            delete[] matrix[i];
        }
        delete[] matrix;
    }

    // Destructor to free allocated memory
    ~SparseMatrix() {
        Node* current = start;
        while (current) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }
};

int main() {
    // Creating a sparse matrix with dimensions from the image
    SparseMatrix sparseMatrix(4, 5);

    // Adding elements as shown in the image
    sparseMatrix.addElement(0, 2, 3);
    sparseMatrix.addElement(0, 4, 4);
    sparseMatrix.addElement(1, 2, 5);
    sparseMatrix.addElement(1, 3, 7);
    sparseMatrix.addElement(3, 1, 2);
    sparseMatrix.addElement(3, 2, 6);

    // Display the original matrix
    sparseMatrix.displayOriginal();

    std::cout << "\n";

    // Displaying the  final sparse matrix representation
    sparseMatrix.display();

    return 0;
}
