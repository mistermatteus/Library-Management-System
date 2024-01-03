/*  User Class Implementation   */
/*  Filename: User.cpp          */

#include <iostream>
#include <string>
#include "User.h"

//Constructors
User::User() {
    username = "user";
    password = "1234";
}
User::User(string uname, string pword) {
    username = uname;
    password = pword;
}

//Acessor Methods
string User::getUname() {
    return username;
}
string User::getPword() {
    return password;
}
string User::getUType() {
    return userType;
}
void User::print() {
    cout << "Username: " << username << endl;
    cout << "Password: " << password << endl;
    cout << "-----------------------------------------------" << endl;
}



//Mutator Methods
void User::changeUname(string newUser) {
    username = newUser;
}
void User::changePword(string newPword) {
    password = newPword;
}
void User::changeUType(string utype) {
    userType = utype;
}
