#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

class Book {
    string bno;
    string bname;
    string status;  // "Available" or "Rented"

public:
    Book() : status("Available") {}

    Book(const string& bno, const string& bname, const string& status = "Available")
        : bno(bno), bname(bname), status(status) {}

    void createBook() {
        cout << "Enter The Book no: ";
        cin >> bno;
        cout << "Enter The Name of The Book: ";
        cin.ignore();
        getline(cin, bname);  // Read the entire line for the book name
        cout << "Book Created." << endl;
    }

    void modifyBook() {
        cout << "Modify Book Name: ";
        cin.ignore();
        getline(cin, bname);  // Read the entire line for the book name
        // The status is not modified in this function
    }

    const string& getBookNo() const {
        return bno;
    }

    const string& getBookName() const {
        return bname;
    }
    const string& getStatus() const {
        return status;
    }

    void setStatus(const string& newStatus) {
        status = newStatus;
    }

    void display() {
        cout << bno << "\t" << bname <<"-" << status << endl;
    }

    string toFileFormat() const {
        // Convert book information to a string for file storage
        return bno + "\t" + bname + "\t" + status;
    }
};

class Node {
public:
    Book book;
    Node* next;

    Node(const Book& book) : book(book), next(nullptr) {}
};

class Library {
private:
    Node* head;

public:
    Library() : head(nullptr) {}

    ~Library() {
        clear();
    }

    void clear() {
        Node* current = head;
        while (current) {
            Node* next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;
    }

    void addBook(const Book& book) {
        Node* newNode = new Node(book);
        Node *current=head;

        if(current==NULL){
            head=newNode;
        }
        else{
        while(current->next!=NULL){
            current=current->next;
        }
        current->next=newNode;
        }

    }

    void loadBooksFromFile(const string& filename) {
        ifstream file(filename);
        if (!file) {
            cout << "Error opening file: " << filename << endl;
            return;
        }

        string line;
     while (getline(file, line)) {
    istringstream ss(line);
    string bno, bname, status;
    ss >> bno >> ws;
    getline(ss, bname, '\t');
    status = "Available";
    Book book(bno, bname, status);
    addBook(book);
   }


        file.close();
    }

    void saveBooksToFile(const string& filename) {
        ofstream file(filename);
        if (!file) {
            cout << "Error opening file: " << filename << endl;
            return;
        }

        Node* current = head;
        while (current) {
            file << current->book.toFileFormat() << endl;
            current = current->next;
        }

        file.close();
    }

    void createBook() {
        Book book;
        book.createBook();
        addBook(book);
    }

    void showAllBooks() {
        Node* current = head;
        while (current) {
            current->book.display();
            current = current->next;
        }
    }

 void searchBookByName(const string& bookName) const {
        Node* current = head;
        bool found = false;

        while (current) {
            if ( current->book.getBookName() == bookName) {
                current->book.display();
                found = true;
            }
            current = current->next;
        }

        if (!found) {
            cout << "No available books found with the name: " << bookName << endl;
        }
    }


    void modifyBook() {
        string bookNo;
        cout << "Enter the book number to modify: ";
        cin >> bookNo;

        Node* current = head;
        while (current) {
            if (current->book.getBookNo() == bookNo) {
                current->book.modifyBook();
                break;
            }
            current = current->next;
        }
    }

void rentBook() {
    string bookNo;
    cout << "Enter the book number to rent: ";
    cin >> bookNo;

    Node* current = head;
    while (current) {
        if (current->book.getBookNo() == bookNo) {
                            cout<<current->book.getBookName()<<" ";

            if (current->book.getStatus() == "Available") {

                current->book.setStatus("Rented");

                cout << "Book rented successfully." << endl;
            } else {
                cout << "Book is not available for rent." << endl;
            }
            return; // Return after processing the book
        }
        current = current->next;
    }

    // If the loop completes, the book was not found
    cout << "Book not found." << endl;
}


    void returnBook() {
        string bookNo;
        cout << "Enter the book number to return: ";
        cin >> bookNo;

        Node* current = head;
        while (current) {
            if (current->book.getBookNo() == bookNo && current->book.getStatus() == "Rented") {
                current->book.setStatus("Available");
                cout << "Book returned successfully." << endl;
                break;
            }
            current = current->next;
        }

        if (!current) {
            cout << "Book not found or not rented." << endl;
        }
    }

    void deleteBook() {
        string bookNo;
        cout << "Enter the book number to delete: ";
        cin >> bookNo;

        Node* current = head;
        Node* prev = nullptr;

        while (current) {
            if (current->book.getBookNo() == bookNo) {
                if (prev) {
                    prev->next = current->next;
                } else {
                    head = current->next;
                }
                delete current;
                break;
            }
            prev = current;
            current = current->next;
        }
    }
};

int main() {
    int choice;
    string Bname;
    Library library;

    // Load books from file at the beginning
    library.loadBooksFromFile("books.txt");

    do {
        cout << "\nWELCOME TO LIBRARY MANAGEMENT SYSTEM\n";
        cout << "1. Make a new entry of a book\n";
        cout << "2. Show All Books\n";
        cout << "3. Search Book by Name\n";
        cout << "4. Modify an existing Book\n";
        cout << "5. Delete Book\n";
        cout << "6. Rent Book\n";
        cout << "7. Return Book\n";
        cout << "8. Save and Exit\n";
        cout << "Enter your choice: ";

        cin >> choice;

        switch (choice) {
            case 1:
                library.createBook();
                break;
            case 2:
                library.showAllBooks();
                break;
            case 3: {
                string searchName;
                cout << "Enter the name of the book to search: ";
                cin.ignore();
                getline(cin, searchName);
                library.searchBookByName(searchName);
                }
                break;
            case 4:
                library.modifyBook();
                break;
            case 5:
                library.deleteBook();
                break;
            case 6:
                library.rentBook();
                break;
            case 7:
                library.returnBook();
                break;
            case 8:
                // Save books to file before exiting
                library.saveBooksToFile("books.txt");
                cout << "Exiting the program.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 8);

    return 0;
}


