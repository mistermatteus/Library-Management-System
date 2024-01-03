/*  Reader Class Implementation   */
/*  Filename: Reader.cpp          */

#include <iostream>
#include <string>
#include "Reader.h"

bool Reader::overdue(int dueDate) {
    for (int i = 0; i < borrowed.size(); i++) {
        if (stoi(borrowed[i].getEDate()) > dueDate) return true;
    }
    return false;
}

//Acessor Methods
int Reader::getMaxCopies() {
    return maxCopies;
}
vector<Copy> Reader::getBorrowed() {
    return borrowed;
}
vector<string> Reader::getReserved() {
    return reserved;
}
int Reader::getPenalties() {
    return penalties;
}
void Reader::print() {
    cout << "Username: " << username << endl;
    cout << "Password: " << password << endl;
    cout << "Maximum Copies Allowed: " << maxCopies << endl;
    cout << "Penalties: " << penalties << endl;
    cout << "Copies Borrowed: " << endl;
    for (int i = 0; i < borrowed.size(); i++) {
        cout << "\t" << borrowed[i].getID() << " " << borrowed[i].getTitle() << endl;
    }
    cout << "Books Reserved: " << endl;
    for (int i = 0; i < reserved.size(); i++) {
        cout << "\t" << reserved[i] << endl;
    }
    cout << "-----------------------------------------------" << endl;
}

//Mutator Methods
void Reader::changeMaxCopies(int newMax) {
    maxCopies = newMax;
}
void Reader::changePenalties(int pen) {
    penalties = pen;
}
void Reader::changeRes(vector<string> res) {
    reserved = res;
}
void Reader::borrow(Copy copy) {
    borrowed.push_back(copy);
}

void Reader::updateMaxCopies() {
    if ((penalties%5) == 0) {
        maxCopies--;
    }
}
void Reader::returnCopy(Copy copy) {
    for (int i = 0; i < borrowed.size(); i++) {
        if (copy.getID() == borrowed[i].getID()) {
            borrowed.erase(borrowed.begin()+i);
            return;
        }
    }
}
void Reader::resPush(string title) {
    reserved.push_back(title);
}
void Reader::resPop(int i) {
    reserved.erase(reserved.begin()+i);

}

