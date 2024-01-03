/*  Book Class          */
/*  Filename: Book.h    */

#include <iostream>
#include <string>
#include <queue>
using namespace std;

class Book {
protected:
    string ISBN;
    string Title;
    string Author;
    string Category;
    queue<string> reserved;
public:
    Book(); //Default constructor
    Book(string title, string author, string isbn, string cat); //Parameterized Constructor
    
    //Overloaded operators
    bool operator<(Book book) {
        if (Title < book.getTitle()) {
            return true;
        }
        return false;
    }
    bool operator>(Book book) {
        if (Title > book.getTitle()) {
            return true;
        }
        return false;
    }
    
    //Accessor Methods
    string getISBN();
    string getTitle();
    string getAuthor();
    string getCat();
    void print();
    queue<string> getReserved();
    
    //Mutator Methods
    void changeISBN(string isbn);
    void changeTitle(string title);
    void changeAuthor(string author);
    void changeCat(string cat);
    void changeRes(queue<string> res);
    void resPop();
    void resPush(string uname);
};
