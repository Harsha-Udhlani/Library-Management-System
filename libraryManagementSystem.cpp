#include <bits/stdc++.h>
using namespace std;
struct Book
{
    int ISBn;
    string title;
    string author;
    bool isBorrowed = false;
};

struct User
{
    string userName;
    string password;
    bool operator<(const User &other) const
    {
        return userName < other.userName;
    }
};

set<User> userSet;
vector<Book> bookData;
vector<User> usersData;
map<string, string> validate;

bool compareBooks(const Book &b1, const Book &b2)
{
    return b1.ISBn < b2.ISBn;
}

void registerUSer()
{
    string usname, pass;
    cout << "Enter userName and Password" << endl;

    cin.ignore(); // Clear input buffer before using getline
    getline(cin, usname);
    getline(cin, pass);
    if (pass.length() == 0 || pass == " " || usname.length() == 0 || usname == " ")
    {
        cout << "Enter correct details!!" << endl;
        cout << "Enter userName" << endl;
        getline(cin, usname);
        cout << "Enter password" << endl;
        getline(cin, pass);
    }
    User us = {usname, pass};
    if (userSet.find(us) == userSet.end())
    {
        usersData.push_back(us);
        userSet.insert(us);
        validate[usname] = pass;
        cout << "Registration successful!" << endl;
    }
    else
    {
        cout << "User already registered!!" << endl;
    }
    return;
}

bool login()
{
    string usname, pass;
    cout << "Enter userName and Password" << endl;

    cin.ignore(); // Clear input buffer before using getline
    getline(cin, usname);
    getline(cin, pass);
    if (pass.length() == 0 || pass == " " || usname.length() == 0 || usname == " ")
    {
        cout << "Enter correct details!!" << endl;
        cout << "Enter userName" << endl;
        getline(cin, usname);
        cout << "Enter password" << endl;
        getline(cin, pass);
    }
    if (validate.find(usname) == validate.end())
    {
        cout << "User not registered!!" << endl;
        return false;
    }
    else if (validate.find(usname) != validate.end())
    {
        if (validate[usname] == pass)
        {
            cout << "Access Granted!!";
            return true;
        }
        else
        {
            cout << "Invalid Credentials!!" << endl;
            return false;
        }
    }
    return false;
}

void addBooks()
{
    int n;
    string t, a;
    cout << "Enter the ISBN of the book:\n";

    cin >> n;
    cin.ignore();
    cout << "Enter the Title of the book:\n";
    getline(cin, t);
    cout << "Enter the Author of the book:\n";
    getline(cin, a);

    Book b = {n, t, a, false};
    bookData.push_back(b);
    sort(bookData.begin(), bookData.end(), compareBooks);
}

void searchBooks(int num)
{
    if (bookData.empty())
    {
        cout << "No books available.\n";
        return;
    }
    int s = 0;
    int e = bookData.size() - 1;
    while (s <= e)
    {
        int mid = (s + (e - s) / 2);
        if (bookData[mid].ISBn == num)
        {
            cout << "Book Found: " << bookData[mid].title << " by " << bookData[mid].author;
            cout << (bookData[mid].isBorrowed ? " (Borrowed)\n" : " (Available)\n");
            return;
        }
        else if (bookData[mid].ISBn > num)
        {
            e = mid - 1;
        }
        else
        {
            s = mid + 1;
        }
    }
    cout << "Book not found.\n";
}

void displayBooks()
{
    if (bookData.empty())
    {
        cout << "No books found" << endl;
        return;
    }
    for (Book &b : bookData)
    {
        cout << b.ISBn << " | " << b.title << " by " << b.author;
        cout << (b.isBorrowed ? " (Borrowed)\n" : " (Available)\n");
    }
}

void borrow(int num)
{
    for (int i = 0; i < bookData.size(); i++)
    {
        if (bookData[i].ISBn == num)
        {
            if (!bookData[i].isBorrowed)
            {
                bookData[i].isBorrowed = true;
                cout << "You have successfully borrowed: " << bookData[i].title << endl;
            }
            else
            {
                cout << "Sorry! The book is currently borrowed." << endl;
            }
            return; // Exit after processing the book
        }
    }
    cout << "Book not found.\n";
}

void returnBook(int num)
{
    for (int i = 0; i < bookData.size(); i++)
    {
        if (bookData[i].ISBn == num)
        {
            if (!bookData[i].isBorrowed)
            {
                cout << "This book was not borrowed." << endl;
            }
            else
            {
                bookData[i].isBorrowed = false;
                cout << "You have successfully returned: " << bookData[i].title << endl;
            }
            return; // Exit after processing the book
        }
    }
    cout << "Book not found.\n";
}

int main()
{
    int choice;
    bool grant = false;
    while (grant == false)
    {
        cout << "\n1. Register User\n2. Login\n";
        cout << "Enter Choice: " << endl;
        cin >> choice;

        if (choice == 1)
        {
            registerUSer();
            cout << "Now Login!!" << endl;
        }
        if (choice == 2)
        {
            grant = login();
        }
        else
        {
            cout << "Invalid choice! Please enter 1 or 2.\n";
        }
    }
    if (grant)
    {
        while (true)
        {

            cout << "\n3. Add Book\n4. Search Book\n5. Display Books\n";
            cout << "6. Borrow Book\n7. Return Book\n8. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;

            if (choice == 8)
            {
                cout << "Exiting the system. Goodbye!\n";
                break;
            }

            int n;
            switch (choice)
            {
            case 3:
                addBooks();
                break;
            case 4:
                cout << "Enter ISBN of the book to search: ";
                cin >> n;
                searchBooks(n);
                break;
            case 5:
                displayBooks();
                break;
            case 6:
                cout << "Enter ISBN of the book to borrow: ";
                cin >> n;
                borrow(n);
                break;
            case 7:
                cout << "Enter ISBN of the book to return: ";
                cin >> n;
                returnBook(n);
                break;
            default:
                cout << "Invalid choice! Please enter a valid option.\n";
            }
        }
    }
    else
    {
        cout << "Access Denied!!" << endl;
        cout << "\n1. Register User\n2. Login\n";
        cin >> choice;
        grant = false;
    }
}
