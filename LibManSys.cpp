#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

class Book
{
public:
    int id;
    string title;
    string author;
    string category;
    bool isAvailable;

    Book(int id, string title, string author, string category)
    {
        this->id = id;
        this->title = title;
        this->author = author;
        this->category = category;
        this->isAvailable = true;
    }

    void display() const
    {
        cout << "ID: " << id << ", Title: " << title << ", Author: " << author
             << ", Category: " << category << ", Available: " << (isAvailable ? "Yes" : "No") << endl;
    }
};

class Library
{
private:
    vector<Book> books;
    map<int, Book *> borrowedBooks; // Map to keep track of borrowed books

    void loadBooksFromFile()
    {
        ifstream file("library_data.txt");
        if (!file)
        {
            cout << "Error opening file." << endl;
            return;
        }
        int id;
        string title, author, category;
        bool isAvailable;
        while (file >> id)
        {
            file.ignore(); // Ignore newline
            getline(file, title);
            getline(file, author);
            getline(file, category);
            file >> isAvailable; // Read availability status
            file.ignore();       // Ignore newline

            books.push_back(Book(id, title, author, category));
            books.back().isAvailable = isAvailable; // Assign the read value
        }
        file.close();
    }

    void saveBooksToFile()
    {
        ofstream file("library_data.txt");
        if (!file)
        {
            cout << "Error opening file." << endl;
            return;
        }
        for (const Book &book : books)
        {
            file << book.id << endl;
            file << book.title << endl;
            file << book.author << endl;
            file << book.category << endl;
            file << book.isAvailable << endl;
        }
        file.close();
    }

public:
    Library()
    {
        loadBooksFromFile();
    }

    void addBook()
    {
        int id;
        string title, author, category;

        cout << "Enter book ID: ";
        cin >> id;
        cin.ignore(); // Ignore newline after integer input

        cout << "Enter book title: ";
        getline(cin, title);

        cout << "Enter book author: ";
        getline(cin, author);

        cout << "Enter book category: ";
        getline(cin, category);

        books.push_back(Book(id, title, author, category));
        saveBooksToFile();
        cout << "Book added successfully!" << endl;
    }

    void displayBooks()
    {
        if (books.empty())
        {
            cout << "No books available in the library." << endl;
            return;
        }
        cout << "\nBooks in Library:\n";
        for (const Book &book : books)
        {
            book.display();
        }
        cout << endl;
    }

    void searchBookByTitle()
    {
        string searchTitle;
        cout << "Enter book title to search: ";
        cin.ignore(); // Ignore the newline character
        getline(cin, searchTitle);

        bool found = false;
        for (const Book &book : books)
        {
            if (book.title.find(searchTitle) != string::npos) // string::npos (special value meaning "not found")
            {
                book.display();
                found = true;
            }
        }

        if (!found)
        {
            cout << "No books found with that title." << endl;
        }
    }

    void borrowBook()
    {
        int id;
        cout << "Enter book ID to borrow: ";
        cin >> id;

        for (Book &book : books)
        {
            if (book.id == id)
            {
                if (book.isAvailable)
                {
                    book.isAvailable = false;
                    borrowedBooks[id] = &book;
                    saveBooksToFile();
                    cout << "You have successfully borrowed: " << book.title << endl;
                }
                else
                {
                    cout << "Sorry, the book is currently unavailable." << endl;
                }
                return;
            }
        }

        cout << "No book found with that ID." << endl;
    }

    void returnBook()
    {
        int id;
        cout << "Enter book ID to return: ";
        cin >> id;
        // If id exists, it returns an iterator pointing to the key-value pair (id, Book*) in the map.
        // If id does not exist, it returns borrowedBooks.end(), meaning the key was not found.
        auto it = borrowedBooks.find(id);
        if (it != borrowedBooks.end())
        {
            it->second->isAvailable = true;
            // first = key, second = value in map
            borrowedBooks.erase(it);
            saveBooksToFile();
            cout << "You have successfully returned the book." << endl;
        }
        else
        {
            cout << "This book wasn't borrowed from this library." << endl;
        }
    }

    void deleteBook()
    {
        int id;
        cout << "Enter book ID to delete: ";
        cin >> id;
            //find if functio will store a pointer to the book (if found) in the vector
            //if no match is found it will be equal to the books.end().
        auto it = find_if(books.begin(), books.end(), [id](const Book &b)
                          { return b.id == id; });

        if (it != books.end())
        {
            books.erase(it);
            saveBooksToFile();
            cout << "Book deleted successfully!" << endl;
        }
        else
        {
            cout << "No book found with that ID." << endl;
        }
    }
};

int main()
{
    Library library;
    int choice;

    while (true)
    {
        cout << "\nLibrary Management System\n";
        cout << "1. Add Book\n";
        cout << "2. Display Books\n";
        cout << "3. Search Book by Title\n";
        cout << "4. Borrow Book\n";
        cout << "5. Return Book\n";
        cout << "6. Delete Book\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            library.addBook();
            break;
        case 2:
            library.displayBooks();
            break;
        case 3:
            library.searchBookByTitle();
            break;
        case 4:
            library.borrowBook();
            break;
        case 5:
            library.returnBook();
            break;
        case 6:
            library.deleteBook();
            break;
        case 7:
            cout << "Exiting the system...\n";
            return 0;
        default:
            cout << "Invalid choice! Please try again.\n";
        }
    }

    return 0;
}