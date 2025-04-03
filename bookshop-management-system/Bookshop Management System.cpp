#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

using namespace std;

// Book Class
class Book {
public:
    string bookID;
    string title;
    string author;
    double price;

    // Constructor
    Book(string id, string t, string a, double p) {
        bookID = id;
        title = t;
        author = a;
        price = p;
    }

    void displayBook() {
        cout << left << setw(10) << bookID 
             << setw(30) << title 
             << setw(25) << author 
             << setw(10) << price << endl;
    }
};

// Bookshop Management Class
class Bookshop {
private:
    vector<Book> books;
    string filename = "books.txt";

public:
    Bookshop() {
        loadBooksFromFile();
    }

    // Add a Book
    void addBook() {
        string id, title, author;
        double price;
        cout << "Enter Book ID: ";
        cin >> id;
        cout << "Enter Book Title: ";
        cin.ignore();
        getline(cin, title);
        cout << "Enter Author: ";
        getline(cin, author);
        cout << "Enter Price: ";
        cin >> price;

        books.push_back(Book(id, title, author, price));
        saveBooksToFile();
        cout << "Book Added Successfully!\n";
    }

    // Display All Books
    void displayBooks() {
        cout << "\nAvailable Books:\n";
        cout << left << setw(10) << "ID" 
             << setw(30) << "Title" 
             << setw(25) << "Author" 
             << setw(10) << "Price" << endl;
        cout << string(75, '-') << endl;
        for (Book& b : books) {
            b.displayBook();
        }
    }

    // Modify a Book
    void modifyBook() {
        string id;
        cout << "Enter Book ID to Modify: ";
        cin >> id;

        for (Book& b : books) {
            if (b.bookID == id) {
                cout << "Enter New Title: ";
                cin.ignore();
                getline(cin, b.title);
                cout << "Enter New Author: ";
                getline(cin, b.author);
                cout << "Enter New Price: ";
                cin >> b.price;
                saveBooksToFile();
                cout << "Book Modified Successfully!\n";
                return;
            }
        }
        cout << "Book Not Found!\n";
    }

    // Delete a Book
    void deleteBook() {
        string id;
        cout << "Enter Book ID to Delete: ";
        cin >> id;

        for (size_t i = 0; i < books.size(); i++) {
            if (books[i].bookID == id) {
                books.erase(books.begin() + i);
                saveBooksToFile();
                cout << "Book Deleted Successfully!\n";
                return;
            }
        }
        cout << "Book Not Found!\n";
    }

    // Buy a Book
    void buyBook() {
        string id;
        cout << "Enter Book ID to Buy: ";
        cin >> id;

        for (size_t i = 0; i < books.size(); i++) {
            if (books[i].bookID == id) {
                cout << "Book Purchased: " << books[i].title << " by " << books[i].author << endl;
                books.erase(books.begin() + i); // Remove after purchase
                saveBooksToFile();
                return;
            }
        }
        cout << "Book Not Found!\n";
    }

    // Load Books from File
    void loadBooksFromFile() {
        ifstream file(filename);
        if (!file) return;
        books.clear();
        string id, title, author;
        double price;
        while (file >> id >> ws && getline(file, title) && getline(file, author) && file >> price) {
            books.push_back(Book(id, title, author, price));
        }
        file.close();
    }

    // Save Books to File
    void saveBooksToFile() {
        ofstream file(filename);
        for (Book& b : books) {
            file << b.bookID << "\n" << b.title << "\n" << b.author << "\n" << b.price << "\n";
        }
        file.close();
    }
};

// Main Function
int main() {
    Bookshop shop;
    int choice;
    do {
        cout << "\nBookshop Management System\n";
        cout << "1. Add Book\n";
        cout << "2. Display Books\n";
        cout << "3. Modify Book\n";
        cout << "4. Delete Book\n";
        cout << "5. Buy Book\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: shop.addBook(); break;
            case 2: shop.displayBooks(); break;
            case 3: shop.modifyBook(); break;
            case 4: shop.deleteBook(); break;
            case 5: shop.buyBook(); break;
            case 6: cout << "Exiting...\n"; break;
            default: cout << "Invalid Choice! Try Again.\n";
        }
    } while (choice != 6);

    return 0;
}
