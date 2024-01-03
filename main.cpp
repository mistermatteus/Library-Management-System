//
//  main.cpp
//  Project
//
//  Created by Matthew acosta on 11/24/17.
//  Copyright © 2017 Matthew Acosta. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <ctime>
#include <cstdlib>
#include "Student.h"
#include "Teacher.h"
#include "Copy.h"
#include "Librarian.h"
using namespace std;

template<typename T> void load(ifstream& data,T obj,vector<T>& list);
template<typename T> void unload(ofstream& data,vector<T>& list);
template<typename T> void sort(vector<T>& list);
void sort(vector<Book>& list,string parameter);
void sortC(vector<Copy>& list);
template<typename T> int searchUser(string uname,vector<T> list);
template<typename T> void searchBook(string search,vector<T> list,string parameter,vector<int>& result);
void searchCopy(string id,vector<Copy> list,vector<int>& result);
ifstream& operator>>(ifstream& file, Librarian& user);
ifstream& operator>>(ifstream& file, Reader& user);
ifstream& operator>>(ifstream& file, Book& book);
ifstream& operator>>(ifstream& file, Copy& copy);
ofstream& operator<<(ofstream& file, User user);
ofstream& operator<<(ofstream& file, Book book);
ofstream& operator<<(ofstream& file, Copy copy);
string newID();

int main() {
    clock_t start = clock();
    clock_t cur;
    int ini_date,curr_date;
    srand(int(start));
    int m,n; bool flag(1); queue<string> queue,queue2;
    string uname,pword,userType,input,input2,input3,input4,str; int searchU;vector<int> searchB;vector<int> searchC;
    User cUser("DNE","0000"); /*current user*/
    Librarian lUser;Reader rUser;Teacher tUser;Student sUser;Book book;Copy copy;vector<string> reserved;//holder variables
    vector<Librarian> libList;vector<Teacher> tList;vector<Student> sList;vector<Book> bookList;vector<Copy> copyList;
    ifstream libData("librarian.dat"),readerData("reader.dat"),bookData("book.dat"),copyData("copy.dat");
    ofstream newLib,newReader,newBook,newCopy;
    
    if (libData.fail()) {
        cerr << "Error opening librarian.dat" << endl;
        exit(1);
    }
    if (readerData.fail()) {
        cerr << "Error opening reader.dat" << endl;
        exit(1);
    }
    if (bookData.fail()) {
        cerr << "Error opening book.dat" << endl;
        exit(1);
    }
    if (copyData.fail()) {
        cerr << "Error opening copy.dat" << endl;
        exit(1);
    }
    
    load(libData,lUser,libList);
    readerData >> rUser;
    while (!(readerData.eof())) {
        if (rUser.getUType() == "Teacher") {
            tUser = rUser;
            tUser.changeRes(rUser.getReserved());
            tList.push_back(tUser);
        }
        if (rUser.getUType() == "Student") {
            sUser = rUser;
            sUser.changeRes(rUser.getReserved());
            sList.push_back(sUser);
        }
        readerData >> rUser;
    }
    bookData >> ini_date; //Inititial date loaded from book.dat
    load(bookData,book,bookList);
    copyData >> copy;
    while (!(copyData.eof())) {
        searchBook(copy.getTitle(), bookList, "Title", searchB);
        book = bookList[searchB[0]];
        copy.changeAuthor(book.getAuthor());
        copy.changeISBN(book.getISBN());
        copy.changeCat(book.getCat());
        copyList.push_back(copy);
        if (copy.getRName() != "None") {
            searchU = searchUser(copy.getRName(), tList);
            if (searchU != -1) {
                tList[searchU].borrow(copy);
            }
            else {
                searchU = searchUser(copy.getRName(), sList);
                sList[searchU].borrow(copy);
            }
        }
        copyData >> copy;
    }
    
    sort(libList);
    sort(tList);
    sort(sList);
    sort(copyList);
    
    cout << "Enter username: ";
    cin >> uname;
    
    searchU = searchUser(uname, libList);
    if (searchU != -1) {
        userType = "Librarian";
        cUser = libList[searchU];
    }
    else {
        searchU = searchUser(uname, tList);
        if (searchU != -1) {
            userType = "Reader";
            cUser = tList[searchU];
            cUser.changeUType("Teacher");
        }
        searchU = searchUser(uname, sList);
        if (searchU != -1) {
            userType = "Reader";
            cUser = sList[searchU];
            cUser.changeUType("Student");
        }
        else {
            cerr << "User does not exist" << endl;
            exit(1);
        }
    }
    
    cout << "Enter password: ";
    cin >> pword;

    if (pword == cUser.getPword()) {
        cout << "\n-----------------------------------------------" << endl;
        cout <<   "-            Welcome to My Library            -" << endl;
        cout <<   "-----------------------------------------------" << endl;
        cout << "\nWelcome back, " << cUser.getUname() << endl;
        
        if (userType == "Librarian") {
            while (flag) {
                cout << "\nPlease chose:" << endl;
                cout << "\t\t1 -- Search Books" << endl;
                cout << "\t\t2 -- Add Books" << endl;
                cout << "\t\t3 -- Delete Books" << endl;
                cout << "\t\t4 -- Search Users" << endl;
                cout << "\t\t5 -- Add Users" << endl;
                cout << "\t\t6 -- Delete Users" << endl;
                cout << "\t\t7 -- My Information" << endl;
                cout << "\t\t8 -- Change Password" << endl;
                cout << "\t\t0 -- Log Out" << endl;
                cout << "-----------------------------------------------" << endl;
                
                int choice;
                cin >> choice;
                
                cout << "-----------------------------------------------" << endl;
                
                switch(choice) {
                    case 1:
                        cout << "Enter search parameter: (Title,Author,ISBN,Category)" << endl;
                        cin >> input2;
                        cout << "Enter search term: ";
                        cin >> input;
                        sort(bookList,input2);
                        searchBook(input,bookList,input2,searchB);
                        cout << "Search results for: '" << input << "'" << endl;
                        if (searchB.size() != 0) {
                            for (int i = 0; i < searchB.size(); i++) {
                                cout << endl << "Available Copies:" << endl;
                                bookList[searchB[i]].print();
                                searchBook(input,copyList,"Title",searchC);
                                for (int j= 0; j < searchC.size(); j++) {
                                    if (copyList[searchC[j]].getRName() == "None") {
                                        cout << "\t" << copyList[searchC[j]].getID() << " " << copyList[searchC[j]].getTitle() << endl;
                                    }
                                }
                            }
                        }
                        else {cout << "No results found" << endl;}
                        cout << "-----------------------------------------------" << endl;
                        searchB.clear();
                        break;
                    case 2:
                        cout << "Enter Title: ";
                        cin >> input;
                        cout << "Enter Author: ";
                        cin >> input2;
                        cout << "Enter ISBN: ";
                        cin >> input3;
                        cout << "Enter Category: ";
                        cin >> input4;
                        sort(bookList,"ISBN");
                        searchBook(input3, bookList, "ISBN", searchB);
                        book = Book(input,input2,input3,input4);
                        str = newID();
                        copyList.push_back(Copy(str,book));
                        if (searchB.size() == 0){
                            bookList.push_back(book);
                        }
                        cout << "Book added" << endl;
                        cout << "-----------------------------------------------" << endl;
                        break;
                    case 3:
                        cout << "Enter the book ID: ";
                        cin >> input;
                        searchCopy(input,copyList,searchC);
                        if (copyList[searchC[0]].getRName() == "None") {
                            copyList.erase(copyList.begin()+searchC[0]);
                            searchCopy(input,copyList,searchC);
                            if (searchB.size() == -1) {
                                copyList.erase(copyList.begin()+searchC[0]);
                            }
                            cout << "Copy deleted" << endl;
                        }
                        else {
                            cout << "Copy is lent out and can't be deleted" << endl;
                        }
                        cout << "-----------------------------------------------" << endl;
                        break;
                    case 4:
                        cout << "Enter name of user: ";
                        cin >> uname;
                        searchU = searchUser(uname, libList);
                        if (searchU != -1) {
                            cout << endl;
                            libList[searchU].print();
                            break;
                        }
                        else {
                            searchU = searchUser(uname, tList);
                            if (searchU != -1) {
                                libList[searchU].print();
                                break;
                            }
                            else {
                                searchU = searchUser(uname, sList);
                                if (searchU != -1) {
                                    cout << "\nUsername: " << sList[searchU].getUname() << endl;
                                    cout << "Password: " << sList[searchU].getPword() << endl;
                                    cout << "User Type: " << sList[searchU].getUType() << endl;
                                    cout << "Copies Borrowed: " << endl;
                                    for (int i = 0; i < sList[searchU].getBorrowed().size(); i++) {
                                        cout << "\t" << sList[searchU].getBorrowed()[i].getID() << " " << sList[searchU].getBorrowed()[i].getTitle() << " " << sList[searchU].getBorrowed()[i].getAuthor() << endl;
                                    }
                                    cout << "-----------------------------------------------" << endl;
                                    break;
                                }
                                else {
                                    cout << "User not found" << endl;
                                    cout << "-----------------------------------------------" << endl;
                                    break;
                                }
                            }
                        }
                        break;
                    case 5:
                        cout << "Enter new user type: Librarian, Student, or Teacher" << endl;
                        cin >> input;
                        if (input == "Librarian"){
                        cout << "Enter new username: ";
                                cin >> uname;
                            searchU = searchUser(uname, libList);
                            while (searchU != -1) {
                                cout << "Username is taken. Please choose another" << endl;
                                cout << "Enter new username: ";
                                cin >> uname;
                                searchU = searchUser(uname, libList);
                            }
                            cout << "Enter password: ";
                            cin >> pword;
                            libList.push_back(Librarian(uname,pword));
                            sort(libList);
                            cout << "New user created" << endl;
                        }
                        else if (input == "Student"){
                            cout << "Enter new username: ";
                            cin >> uname;
                            searchU = searchUser(uname, sList);
                            while (searchU != -1) {
                                cout << "Username is taken. Please choose another" << endl;
                                cout << "Enter new username: ";
                                cin >> uname;
                                searchU = searchUser(uname, sList);
                            }
                            cout << "Enter password: ";
                            cin >> pword;
                            sList.push_back(Student(uname,pword));
                            sort(sList);
                            cout << "New user created" << endl;
                        }
                        else if (input == "Teacher"){
                            cout << "Enter new username: ";
                            cin >> uname;
                            searchU = searchUser(uname, tList);
                            while (searchU != -1) {
                                cout << "Username is taken. Please choose another" << endl;
                                cout << "Enter new username: ";
                                cin >> uname;
                                searchU = searchUser(uname, tList);
                            }
                            cout << "Enter password: ";
                            cin >> pword;
                            tList.push_back(Teacher(uname,pword));
                            sort(tList);
                            cout << "New user created" << endl;
                        }
                        else {
                            cout << "Invalid user type" << endl;
                        }
                        cout << "-----------------------------------------------" << endl;
                        break;
                    case 6:
                        cout << "Enter name of user: ";
                        cin >> uname;
                        searchU = searchUser(uname, libList);
                        if (searchU != -1) {
                            libList.erase(libList.begin()+searchU);
                            cout << "User deleted" << endl;
                            cout << "-----------------------------------------------" << endl;
                            break;
                        }
                        else {
                            searchU = searchUser(uname, tList);
                            if (searchU != -1) {
                                if (tList[searchU].getBorrowed().size() == 0) {
                                    tList.erase(tList.begin()+searchU);
                                    cout << "User deleted" << endl;
                                    cout << "-----------------------------------------------" << endl;
                                }
                                else {
                                    cout << "User has borrowed books and can't be deleted" << endl;
                                    cout << "-----------------------------------------------" << endl;
                                }
                                break;
                            }
                            else {
                                searchU = searchUser(uname, sList);
                                if (searchU != -1) {
                                    if (sList[searchU].getBorrowed().size() == 0) {
                                        sList.erase(sList.begin()+searchU);
                                        cout << "User deleted" << endl;
                                        cout << "-----------------------------------------------" << endl;
                                    }
                                    else {
                                        cout << "User has borrowed books and can't be deleted" << endl;
                                        cout << "-----------------------------------------------" << endl;
                                    }
                                    break;
                                }
                                else {
                                    cout << "User not found" << endl;
                                    cout << "-----------------------------------------------" << endl;
                                    break;
                                }
                            }
                        }
                        break;
                    case 7:
                        cUser.print();
                        break;
                    case 8:
                        cout << "Enter new password:";
                        cin >> pword;
                        searchU = searchUser(cUser.getUname(), libList);
                        libList[searchU].changePword(pword);
                        cout << "\nPassword changed" << endl;
                        cout << "-----------------------------------------------" << endl;
                        break;
                    case 0:
                        flag = 0;
                        cout << "Logging out..." << endl;
                        break;
                    default:
                        cout << "Invalid Choice" << endl;
                        cout << "-----------------------------------------------" << endl;
                        break;
                    }
                }
            }
            if (userType == "Reader") {
                while (flag) {
                    cout << "\nPlease chose:" << endl;
                    cout << "\t\t1 -- Search Books" << endl;
                    cout << "\t\t2 -- Borrow Books" << endl;
                    cout << "\t\t3 -- Return Books" << endl;
                    cout << "\t\t4 -- Reserve Books" << endl;
                    cout << "\t\t5 -- Cancel Reservations" << endl;
                    cout << "\t\t6 -- My Information" << endl;
                    cout << "\t\t7 -- Change Password" << endl;
                    cout << "\t\t0 -- Log Out" << endl;
                    
                    int choice;
                    cin >> choice;
                    
                    cout << "-----------------------------------------------" << endl;
                    
                    switch(choice) {
                        case 1:
                            cout << "Enter search parameter: (Title,Author,ISBN,Category)" << endl;
                            cin >> input2;
                            cout << "Enter search term: ";
                            cin >> input;
                            sort(bookList,input2);
                            searchBook(input,bookList,input2,searchB);
                            cout << "Search results for: '" << input << "'" << endl;
                            if (searchB.size() != 0) {
                                for (int i = 0; i < searchB.size(); i++) {
                                    cout << endl << "Available Copies:" << endl;
                                    bookList[searchB[i]].print();
                                    searchBook(input,copyList,"Title",searchC);
                                    for (int j= 0; j < searchC.size(); j++) {
                                        if (copyList[searchC[j]].getRName() == "None") {
                                            cout << "\t" << copyList[searchC[j]].getID() << " " << copyList[searchC[j]].getTitle() << endl;
                                        }
                                    }
                                }
                            }
                            else {cout << "No results found" << endl;}
                            cout << "-----------------------------------------------" << endl;
                            searchB.clear();
                            break;
                        case 2:
                            cout << "Enter the ID of the book you wish to borrow:" << endl;
                            cin >> input;
                            searchCopy(input,copyList,searchC);
                            searchBook(copyList[searchC[0]].getTitle(),bookList,"Title",searchB);
                            cur = clock();
                            curr_date = ini_date + int(cur - start)/(5*CLOCKS_PER_SEC);
                            if (cUser.getUType() == "Teacher") {
                                searchU = searchUser(cUser.getUname(),tList);
                                if (tList[searchU].overdue(curr_date)) {
                                    cout << "Cannot borrow because of overdue books" << endl;
                                    cout << "-----------------------------------------------" << endl;
                                    break;
                                }
                            }
                            if (cUser.getUType() == "Student") {
                                searchU = searchUser(cUser.getUname(),sList);
                                if (sList[searchU].overdue(curr_date)) {
                                    cout << "Cannot borrow because of overdue books" << endl;
                                    cout << "-----------------------------------------------" << endl;
                                    break;
                                }
                            }
                            if (searchC.size() != 0) {
                                if (copyList[searchC[0]].getRName() == "None") {
                                    if ((bookList[searchB[0]].getReserved().size() == 0) || (bookList[searchB[0]].getReserved().front() == cUser.getUname())) {
                                        if (cUser.getUType() == "Teacher") {
                                            searchU = searchUser(cUser.getUname(), tList);
                                            if (tList[searchU].getBorrowed().size() <= tList[searchU].getMaxCopies()) {
                                                tList[searchU].borrow(copyList[searchC[0]]);
                                                copyList[searchC[0]].changeEDate(to_string(curr_date+30));
                                                copyList[searchC[0]].changeRDate("0");
                                            }
                                            else {
                                                cout << "Cannot borrow anymore books" << endl;
                                                cout << "-----------------------------------------------" << endl;
                                                break;
                                            }
                                        }
                                        if (cUser.getUType() == "Student") {
                                            searchU = searchUser(cUser.getUname(), sList);
                                            if (sList[searchU].getBorrowed().size() <= sList[searchU].getMaxCopies()) {
                                                sList[searchU].borrow(copyList[searchC[0]]);
                                                copyList[searchC[0]].changeEDate(to_string(curr_date+20));
                                                copyList[searchC[0]].changeRDate("0");
                                            }
                                            else {
                                                cout << "Cannot borrow anymore books" << endl;
                                                cout << "-----------------------------------------------" << endl;
                                                break;
                                            }
                                        }
                                        
                                        if (bookList[searchB[0]].getReserved().front() == cUser.getUname()) {
                                            bookList[searchB[0]].resPop();
                                        }
                                        if (cUser.getUType() == "Teacher") {
                                            reserved = tList[searchU].getReserved();
                                            for (int i = 0; i < reserved.size();i++) {
                                                if (tList[searchU].getReserved()[i] == bookList[searchB[0]].getTitle()) {
                                                    reserved.erase(reserved.begin()+i);
                                                    tList[searchU].changeRes(reserved);
                                                    break;
                                                }
                                            }
                                        }
                                        if (cUser.getUType() == "Student") {
                                            reserved = sList[searchU].getReserved();
                                            for (int i = 0; i < sList[searchU].getReserved().size();i++) {
                                                if (sList[searchU].getReserved()[i] == bookList[searchB[0]].getTitle()) {
                                                    reserved.erase(reserved.begin()+i);
                                                    sList[searchU].changeRes(reserved);
                                                    break;
                                                }
                                            }
                                        }
                                        copyList[searchC[0]].changeRName(cUser.getUname());
                                        copyList[searchC[0]].changeBDate(to_string(curr_date));
                                        cout << "Book borrowed" << endl;
                                    }
                                    else {
                                        cout << "Book is reserved and cannot be borrowed at this time" << endl;
                                    }
                                }
                            }
                            else {
                                cout << "Cannot find book" << endl;
                            }
                            cout << "-----------------------------------------------" << endl;
                            break;
                        case 3:
                            cout << "Enter the ID of the book you wish to return: " << endl;
                            cin >> input;
                            searchCopy(input,copyList,searchC);
                            if (searchC.size() != 0) {
                                if (copyList[searchC[0]].getRName() != "None") {
                                    cur = clock();
                                    curr_date = ini_date + int(cur - start)/(5*CLOCKS_PER_SEC);
                                    if (cUser.getUType() == "Teacher") {
                                        searchU = searchUser(cUser.getUname(), tList);
                                        tList[searchU].returnCopy(copyList[searchC[0]]);
                                        if (curr_date >= stoi(copyList[searchC[0]].getEDate())) {
                                            tList[searchU].changePenalties(tList[searchU].getPenalties()+1);
                                        }
                                    }
                                    if (cUser.getUType() == "Student") {
                                        searchU = searchUser(cUser.getUname(), sList);
                                        sList[searchU].returnCopy(copyList[searchC[0]]);
                                        if (curr_date >= stoi(copyList[searchC[0]].getEDate())) {
                                            sList[searchU].changePenalties(tList[searchU].getPenalties()+1);
                                        }
                                    }
                                    copyList[searchC[0]].changeRName("None");
                                    copyList[searchC[0]].changeBDate("0");
                                    copyList[searchC[0]].changeEDate("0");
                                    cout << "Book returned" << endl;
                                }
                            }
                            else {
                                cout << "Cannot find book" << endl;
                            }
                            cout << "-----------------------------------------------" << endl;
                            break;
                        case 4:
                            cout << "Enter the title of the book you wish to reserve:" << endl;
                            cin >> input;
                            searchBook(input,bookList,"Title",searchB);
                            searchBook(input,copyList,"Title",searchC);
                            cur = clock();
                            curr_date = ini_date + int(cur - start)/(5*CLOCKS_PER_SEC);
                            if (cUser.getUType() == "Teacher") {
                                searchU = searchUser(cUser.getUname(),tList);
                                if (tList[searchU].overdue(curr_date)) {
                                    cout << "Cannot reserve because of overdue books" << endl;
                                    cout << "-----------------------------------------------" << endl;
                                    break;
                                }
                                for (int i = 0; i < searchC.size(); i++) {
                                    if ((curr_date-stoi(copyList[searchC[i]].getRDate())) > 10) {
                                        bookList[searchB[i]].resPop();
                                    }
                                    if (copyList[searchC[i]].getRDate() == "0") {
                                        copyList[searchC[i]].changeRDate(to_string(curr_date));
                                        bookList[searchB[i]].resPush(tList[i].getUname());
                                        tList[searchU].resPush(bookList[searchB[0]].getTitle());
                                        cout << "Copy reserved" << endl;
                                        break;
                                    }
                                    else if (i == (searchC.size()-1)) {
                                        cout << "All copies are reserved" << endl;
                                    }
                                }
                            }
                            if (cUser.getUType() == "Student") {
                                searchU = searchUser(cUser.getUname(),sList);
                                if (sList[searchU].overdue(curr_date)) {
                                    cout << "Cannot reserve because of overdue books" << endl;
                                    cout << "-----------------------------------------------" << endl;
                                    break;
                                }
                                for (int i = 0; i < searchC.size(); i++) {
                                    if (((curr_date-stoi(copyList[searchC[i]].getRDate())) > 10) && (copyList[searchC[i]].getRDate() != "0")) {
                                        bookList[searchB[0]].resPop();
                                        copyList[searchC[i]].changeRDate("0");
                                    }
                                    if (copyList[searchC[i]].getRDate() == "0") {
                                        copyList[searchC[i]].changeRDate(to_string(curr_date));
                                        bookList[searchB[0]].resPush(sList[i].getUname());
                                        sList[searchU].resPush(bookList[searchB[0]].getTitle());
                                        cout << "Copy reserved" << endl;
                                        break;
                                    }
                                    else if (i == (searchC.size()-1)) {
                                        cout << "All copies are reserved" << endl;
                                    }
                                }
                            }
                            cout << "-----------------------------------------------" << endl;
                            break;
                        case 5:
                            cout << "Enter the title of the book for the reservation:" << endl;
                            cin >> input;
                            sortC(copyList);
                            searchBook(input,bookList,"Title",searchB);
                            searchBook(input,copyList,"Title",searchC);
                            n = 0;m = 0;
                            queue = bookList[searchB[0]].getReserved();
                            for  (int i = 0;i < bookList[searchB[0]].getReserved().size();i++) {
                                if ((queue.front()) != cUser.getUname()) {
                                    queue2.push(queue.front());
                                    queue.pop();
                                    m++;
                                }
                                else {
                                    queue.pop();
                                    n = m;
                                    m++;
                                }
                            }
                            bookList[searchB[0]].changeRes(queue2);
                            if (bookList[searchB[0]].getReserved().size() == m) {
                                cout << "No reservation to cancel" << endl;
                            }
                            else {
                                for (int i = 0; i < copyList.size(); i++) {
                                    if (copyList[searchC[i]].getRDate() != "0") {
                                        if (n == 0) {
                                            copyList[searchC[i]].changeRDate("0");
                                            if (cUser.getUType() == "Teacher") {
                                                searchU = searchUser(cUser.getUname(), tList);
                                                reserved = tList[searchU].getReserved();
                                                for (int i = 0; i < reserved.size();i++) {
                                                    if (tList[searchU].getReserved()[i] == input) {
                                                        reserved.erase(reserved.begin()+i);
                                                        tList[searchU].changeRes(reserved);
                                                        break;
                                                    }
                                                }
                                                break;
                                            }
                                            if (cUser.getUType() == "Student") {
                                                searchU = searchUser(cUser.getUname(), sList);
                                                reserved = sList[searchU].getReserved();
                                                for (int i = 0; i < sList[searchU].getReserved().size();i++) {
                                                    if (sList[searchU].getReserved()[i] == input) {
                                                        reserved.erase(reserved.begin()+i);
                                                        sList[searchU].changeRes(reserved);
                                                        break;
                                                    }
                                                }
                                                break;
                                            }
                                        }
                                        if ((copyList[searchC[i]].getTitle() == input) && (copyList[searchC[i]].getRName() == "None")) {n--;}
                                    }
                                    }
                                cout << "Reservation cancelled" << endl;
                            }
                            cout << "-----------------------------------------------" << endl;
                            break;
                        case 6:
                            searchU = searchUser(cUser.getUname(), tList);
                            if (searchU != -1) {
                                tList[searchU].print();
                            }
                            else {
                                searchU = searchUser(cUser.getUname(), sList);
                                sList[searchU].print();
                            }
                            break;
                        case 7:
                            cout << "Enter new password:";
                            cin >> pword;
                            searchU = searchUser(cUser.getUname(), libList);
                            libList[searchU].changePword(pword);
                            cout << "\nPassword changed" << endl;
                            cout << "-----------------------------------------------" << endl;
                            break;
                        case 0:
                            flag = 0;
                            cout << "Logging out..." << endl;
                            break;
                        default:
                            cout << "Invalid Choice" << endl;
                            cout << "-----------------------------------------------" << endl;
                            break;
                    }
                }
            }
        }

    else {
        cerr << "Incorrect Password" << endl;
        exit(1);
    }
    
    //Clears the the data files and rewrites data from the lists to them
    newLib.open("librarian.dat");
    newReader.open("reader.dat");
    newBook.open("book.dat");
    newCopy.open("copy.dat");
    
    cur = clock();
    curr_date = ini_date + int(cur - start)/(5*CLOCKS_PER_SEC);
    newBook << curr_date << endl;
    
    unload(newLib,libList);
    unload(newReader,tList);
    unload(newReader,sList);
    unload(newBook,bookList);
    unload(newCopy,copyList);
    
    return 0;
}

template<typename T> void load(ifstream& data,T obj,vector<T>& list) {
    data >> obj;
    while (!(data.eof())) {
        list.push_back(obj);
        data >> obj;
    }
}

template<typename T> void unload(ofstream& data,vector<T>& list) {
    for (int i = 0; i < list.size(); i++) {
        data << list[i];
    }
}


template<typename T> void sort(vector<T>& list) {
    int n(list.size()),m; T temp;
    for (int k = 0;k <= n-2;k++) {
        m = k;
        for (int j = k+1;j <= n-1;j++) {
            if (list[j] < list[m]) {
                m = j;
            }
        }
        temp = list[m];
        list[m] = list[k];
        list[k] = temp;
    }
}

void sort(vector<Book>& list,string parameter) {
    int n(list.size()),m; Book temp;
    if (parameter == "Title") {
        for (int k = 0;k <= n-2;k++) {
            m = k;
            for (int j = k+1;j <= n-1;j++) {
                if (list[j].getTitle() < list[m].getTitle()) {
                    m = j;
                }
            }
            temp = list[m];
            list[m] = list[k];
            list[k] = temp;
        }
    }
    if (parameter == "Author") {
        for (int k = 0;k <= n-2;k++) {
            m = k;
            for (int j = k+1;j <= n-1;j++) {
                if (list[j].getAuthor() < list[m].getAuthor()) {
                    m = j;
                }
            }
            temp = list[m];
            list[m] = list[k];
            list[k] = temp;
        }
    }
    if (parameter == "ISBN") {
        for (int k = 0;k <= n-2;k++) {
            m = k;
            for (int j = k+1;j <= n-1;j++) {
                if (list[j].getISBN() < list[m].getISBN()) {
                    m = j;
                }
            }
            temp = list[m];
            list[m] = list[k];
            list[k] = temp;
        }
    }
    if (parameter == "Category") {
        for (int k = 0;k <= n-2;k++) {
            m = k;
            for (int j = k+1;j <= n-1;j++) {
                if (list[j].getCat() < list[m].getCat()) {
                    m = j;
                }
            }
            temp = list[m];
            list[m] = list[k];
            list[k] = temp;
        }
    }
}

void sortC(vector<Copy>& list) {
    int n(int(list.size())),m; Copy temp;
    for (int k = 0;k <= n-2;k++) {
        m = k;
        for (int j = k+1;j <= n-1;j++) {
            if (list[j].getRDate() < list[m].getRDate()) {
                m = j;
            }
        }
        temp = list[m];
        list[m] = list[k];
        list[k] = temp;
    }
}

ifstream& operator>>(ifstream& file,Librarian& user) {
    string uname,pword,utype;
    file >> uname >> pword;
    user.changeUname(uname);
    user.changePword(pword);
    return file;
}

ifstream& operator>>(ifstream& file,Reader& user) {
    string uname,pword,utype,title(""); vector<string> reserved;
    int max,pen; char c;
    file >> uname >> pword >> utype;
    user.changeUname(uname);
    user.changePword(pword);
    if (utype == "Teacher") {
        user.changeUType("Teacher");
    }
    if (utype == "Student") {
        user.changeUType("Student");
    }
    file >> max >> pen;
    user.changeMaxCopies(max);
    user.changePenalties(pen);
    file.get(c); file.get(c);
    while ((c != '\n') && (!(file.eof()))) {
        if ((c == ' ') && (title != "")) {
           reserved.push_back(title);
            title = "";
        }
        else {
            title += c;
        }
        file.get(c);
    }
    user.changeRes(reserved);
    return file;
}

ifstream& operator>>(ifstream& file,Book& book) {
    string title,author,isbn,cat,uname("");char c;
    queue<string> reserved;
    file >> title >> author >> isbn >> cat;
    file.get(c); file.get(c);
    while ((c != '\n') && (!(file.eof()))) {
        if ((c == ' ') && (uname != "")) {
            reserved.push(uname);
            uname = "";
        }
        else {
            uname += c;
        }
        file.get(c);
    }
    book.changeRes(reserved);
    book.changeTitle(title);
    book.changeAuthor(author);
    book.changeISBN(isbn);
    book.changeCat(cat);
    return file;
}

ifstream& operator>>(ifstream& file,Copy& copy) {
    string id,rname,bdate,rdate,edate,title;
    file >> id >> rname >> bdate >> rdate >> edate >> title;
    copy.changeID(id);
    copy.changeRName(rname);
    copy.changeBDate(bdate);
    copy.changeRDate(rdate);
    copy.changeEDate(edate);
    copy.changeTitle(title);
    return file;
}

ofstream& operator<<(ofstream& file,Librarian user) {
    file << user.getUname() << " " << user.getPword() << endl;
    return file;
}

ofstream& operator<<(ofstream& file,Reader user) {
    vector<string> reserved = user.getReserved();
    file << user.getUname() << " " << user.getPword() << " " << user.getUType() << " " << endl;
    file << user.getMaxCopies() << " " << user.getPenalties() << endl;
    if (!(reserved.empty())) {
        for (int i = 0; i < reserved.size(); i++) {
            file << reserved.front() << " ";
            reserved.erase(reserved.begin());
        }
    }
    else {
        file << " ";
    }
    file << endl;
    return file;
}

ofstream& operator<<(ofstream& file,Book book) {
    queue<string> reserved = book.getReserved();
    file << book.getTitle() << " " << book.getAuthor() <<  " " << book.getISBN() << " " << book.getCat() << endl;
    if (!(reserved.empty())) {
        for (int i = 0; i < reserved.size(); i++) {
            file << reserved.front() << " ";
            reserved.pop();
        }
    }
    else {
        file << " ";
    }
    file << endl;
    return file;
}

ofstream& operator<<(ofstream& file,Copy copy) {
    file << copy.getID() << " " << copy.getRName() << " " << copy.getBDate() << " " << copy.getRDate() << " " << copy.getEDate() <<  " " << copy.getTitle() << endl;
    return file;
}

template<typename T> int searchUser(string uname,vector<T> list) {
    int top(0),bottom,mid(0);
    
    bottom = list.size()-1;
    while (top <= bottom) {
        mid = (top+bottom)/2;
        if (uname == list[mid].getUname()) {
            return mid;
        }
        else if(list[mid].getUname() > uname) {
            bottom = mid-1;
        }
        else {
            top = mid+1;
        }
    }
    return -1;
}

template<typename T> void searchBook(string search,vector<T> list,string parameter,vector<int>& result) {
    result.clear();
    for (int i = 0; parameter[i];i++) {
        parameter[i] = toupper(parameter[i]);
    }
    for (int i = 0; i < list.size(); i++) {
        if(parameter == "TITLE") {
            if (search == list[i].getTitle()) {
                result.push_back(i);
            }
        }
        else if(parameter == "AUTHOR") {
            if (search == list[i].getAuthor()) {
                result.push_back(i);
            }
        }
        else if(parameter == "ISBN") {
            if (search == list[i].getISBN()) {
                result.push_back(i);
            }
        }
        else if(parameter == "CATEGORY") {
            if (search == list[i].getCat()) {
                result.push_back(i);
            }
        }
    }
}

void searchCopy(string id,vector<Copy> list,vector<int>& result) {
    result.clear();
    for (int i = 0; i < list.size(); i++) {
        if (id == list[i].getID()) {
            result.push_back(i);
        }
    }
}

string newID() {
    string id;
    id = to_string(rand()%10000); //Converts a random number between 0 and 9999 to a string
    return id;
}
