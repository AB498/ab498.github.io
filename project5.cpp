#include <iostream>
#include <string>

using namespace std;

class Book
{
    string bookName;
    string author;
    int pages;

public:
    friend void showInfo(Book &book);
    Book(string b, string a, int p)
    {
        bookName = b;
        author = a;
        pages = p;
    }

    string getBookName()
    {
        return bookName;
    }
    // polymorphism
    string getBookName(int withPages)
    {
        return bookName + "(" + to_string(pages) + ")";
    }

    void setBookName(string b)
    {
        bookName = b;
    }
};
class ScienceBook : public Book
{
};
class PhilosophyBook : public Book
{
};
class StoryBook : public Book
{
};

// friend function
void showInfo(Book &book)
{
    cout << "Book Name: " << book.bookName << endl;
    cout << "Author: " << book.author << endl;
    cout << "Pages: " << book.pages << endl;
}
inline Book createBook(string b, string a, int p)
{
    return Book(b, a, p);
}
int main()
{
    Book b1 = createBook("Book1", "Author1", 303);
    Book b2 = createBook("Book2", "Author2", 30);
    Book b3 = createBook("Book3", "Author3", 33);

    cout << "All books: " << endl;
    cout << "1. " << b1.getBookName() << endl;
    cout << "2. " << b2.getBookName() << endl;
    cout << "3. " << b3.getBookName() << endl;

    cout << "Enter option: ";
    int input;
    cin >> input;
    cout << endl;
    if (input == 1)
    {
        showInfo(b1);
    }
    else if (input == 2)
    {
        showInfo(b2);
    }
    else if (input == 3)
    {
        showInfo(b3);
    }
    else
    {
        cout << "Invalid opiton. " << endl;
    }
}