/*  Teacher Class Implementation      */
/*  Filename: Teacher.cpp             */

#include <iostream>
#include <string>
#include "Teacher.h"

Teacher::Teacher() { //Default constructor
    username = "teacher";
    password = "1234";
    userType = "Teacher";
    maxCopies = 10;
    penalties = 0;
}

Teacher::Teacher(string uname, string pword) { //Parameterized Constructor
    username = uname;
    password = pword;
    userType = "Teacher";
    maxCopies = 10;
    penalties = 0;
}
