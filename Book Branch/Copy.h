/*  Copy Class          */
/*  Filename: Copy.h    */

#ifndef COPY_H
#define COPY_H

#include <iostream>
#include <string>
#include <vector>
#include "Book.h"
using namespace std;

class Copy: public Book {
protected:
    string ID;
    string rName;
    string bDate;
    string rDate;
    string eDate;
public:
    Copy(); //Default constructor
    Copy(string iD, Book book1); //Parameterized Constructor
    
    //Accessor Methods
    string getID();
    string getRName();
    string getBDate();
    string getRDate();
    string getEDate();
    
    //Mutator Methods
    void changeID(string iD);
    void changeRName(string rname);
    void changeBDate(string bdate);
    void changeRDate(string rdate);
    void changeEDate(string edate);    
};

#endif
