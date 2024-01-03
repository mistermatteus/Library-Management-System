/*  Student Class          */
/*  Filename: Student.h    */

#include <iostream>
#include <string>
#include "Reader.h"

class Student: public Reader {
public:
    Student(); //Default constructor
    Student(string uname, string pword); //Parameterized Constructor
    
    void operator=(Reader user) {
        username = user.getUname();
        password = user.getPword();
    }
};
