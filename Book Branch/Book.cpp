/*  Book Class Implementation   */
/*  Filename: Book.cpp          */

#include <iostream>
#include <string>
#include <vector>
#include "Book.h"
using namespace std;

Book::Book() {  //Default constructor
    
}
Book::Book(string title, string author, string isbn, string cat) { //Parameterized Constructor
    Title = title;
    Author = author;
    ISBN = isbn;
    Category = cat;
}
    
//Accessor Methods
string Book::getISBN() {
    return ISBN;
}

string Book::getTitle() {
    return Title;
}

string Book::getAuthor() {
    return Author;
}

string Book::getCat() {
    return Category;
}
void Book::print() {
    cout << "Title: " << Title << endl;
    cout << "Author: " << Author << endl;
    cout << "ISBN: " << ISBN << endl;
    cout << "Category: " << Category << endl;
    cout << "Available Copies: " << endl;
}
queue<string> Book::getReserved() {
    return reserved;
}

    
//Mutator Methods
void Book::changeISBN(string isbn) {
    ISBN = isbn;
}

void Book::changeTitle(string title) {
    Title = title;
}

void Book::changeAuthor(string author) {
    Author = author;
}

void Book::changeCat(string cat) {
    Category = cat;
}

void Book::changeRes(queue<string> res) {
    reserved.swap(res);
}

void Book::resPop() {
    reserved.pop();
}
void Book::resPush(string uname) {
    reserved.push(uname);
}
