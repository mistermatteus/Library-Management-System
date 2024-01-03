/*  Student Class Implementation      */
/*  Filename: Student.cpp             */

#include <iostream>
#include <string>
#include "Student.h"

Student::Student() { //Default constructor
    username = "Student";
    password = "1234";
    userType = "Student";
    maxCopies = 5;
    penalties = 0;
}

Student::Student(string uname, string pword) { //Parameterized Constructor
    username = uname;
    password = pword;
    userType = "Student";
    maxCopies = 5;
    penalties = 0;
}
