/*  Teacher Class          */
/*  Filename: Teacher.h    */

#include <iostream>
#include <string>
#include "User.h"
using namespace std;

class Librarian: public User {
    public:
        Librarian();    //Default constructor
        Librarian(string uname, string pword);  //Parameterized constructor
};
