/*  Copy Class Implementation   */
/*  Filename: Copy.cpp          */

#include <iostream>
#include <string>
#include <vector>
#include "Copy.h"
using namespace std;

Copy::Copy() {  //Default constructor
    ID = "0000";
}
Copy::Copy(string iD, Book book1) { //Parameterized Constructor
    ID = iD;
    rName = "None";
    bDate = "0";
    rDate = "0";
    eDate = "0";
    Title = book1.getTitle();
    Author = book1.getAuthor();
    ISBN = book1.getISBN();
    Category = book1.getCat();
}

//Accessor Methods
string Copy::getID() {
    return ID;
}
string Copy::getRName() {
    return rName;
}
string Copy::getBDate() {
    return bDate;
}
string Copy::getRDate() {
    return rDate;
}
string Copy::getEDate() {
    return eDate;
}

//Mutator Methods
void Copy::changeID(string iD) {
    ID = iD;
}
void Copy::changeRName(string rname) {
    rName = rname;
}
void Copy::changeBDate(string bdate) {
    bDate = bdate;
}
void Copy::changeRDate(string rdate) {
    rDate = rdate;
}
void Copy::changeEDate(string edate) {
    eDate = edate;
}
