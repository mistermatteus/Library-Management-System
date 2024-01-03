/*  Reader Class          */
/*  Filename: Reader.h    */

#ifndef READER_H
#define READER_H

#include <iostream>
#include <vector>
#include <string>
#include "User.h"
#include "Copy.h"

class Reader: public User {
    protected:
        int maxCopies;
        vector<Copy> borrowed;
        vector<string> reserved;
        int penalties;
    public:
        bool overdue(int dueDate);
    
        //Accessor Methods
        int getMaxCopies();
        void updateMaxCopies();
        int getPenalties();
        vector<Copy> getBorrowed();
        vector<string> getReserved();
        void print();
    
        //Mutator Methods
        void changeMaxCopies(int newMax);
        void changePenalties(int pen);
        void changeRes(vector<string> res);
        void borrow(Copy copy);
        void returnCopy(Copy copy);
        void resPush(string title);
        void resPop(int i);
};

#endif
