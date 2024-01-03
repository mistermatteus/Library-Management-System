/*  Teacher Class Implementation    */
/*  Filename: Teacher.cpp             */

#include <iostream>
#include <string>
#include "Librarian.h"
using namespace std;

Librarian::Librarian() {   //Default constructor
    username = "teacher";
    password = "1234";
    userType = "Librarian";
}
Librarian::Librarian(string uname, string pword) {  //Parameterized constructor
    username = uname;
    password = pword;
    userType = "Librarian";
}

