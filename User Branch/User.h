/*  User Class          */
/*  Filename: User.h    */

#ifndef USER_H
#define USER_H

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class User {
    protected:
        string username;
        string password;
        string userType;
    public:
        User(); //Default constructor
        User(string uname, string pword); //Parameterized Constructor
    
        //Overloaded operators
        bool operator<(User user) {
            if (username < user.getUname()) {
                return true;
            }
            return false;
        }
        bool operator>(User user) {
            if (username > user.getUname()) {
                return true;
            }
            return false;
        }
    
        //Accessor Methods
        string getUname();
        string getPword();
        string getUType();
        void print();

    
        //Mutator Methods
        void changeUname(string newUser);
        void changePword(string newPword);
        void changeUType(string utype);
};

#endif
