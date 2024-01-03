/*  Teacher Class          */
/*  Filename: Teacher.h    */

#include <iostream>
#include <string>
#include "Reader.h"

class Teacher: public Reader {
public:
    Teacher(); //Default constructor
    Teacher(string uname, string pword); //Parameterized Constructor
    
    void operator=(Reader user) {
        username = user.getUname();
        password = user.getPword();
    }
};
