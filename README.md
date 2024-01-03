# Library Management System
The purpose of this project was to design a library management system. The system is intended to allow users to access or modify the system depending on what kind of user they are.
## Users
All users are assigned a username and password to access the system. The password can be changed by the user. All users can search the database of books and view a book's informtation. Books searched by searched by title, author, ISBN, or category.
There are two types of users: librarians and readers. 
### Librarians
Librarians can access to system to maintain the book and user databases. Librarians are allowed to add or removes books and modify each books information. Librarians can also add or remove users from the system.
### Readers
Readers can access the system to borrow or return books. Readers can borrow books if there are available copies or reserve a book if no copies are available. Readers can also return borrowed copies. Readers are split into two subcategories: teachers and students. The only difference is that teachers have a higher limit of books they can borrow at a time.

## Databases
This system maintains two primary databases: users and books. Each database is stored as a text file that is read each time the system is accessed.
### User Database
Users are split into two databases based on the type of user.
The librarian database tracks each librarian's username and password.
The reader database tracks each reader's username and password, the user type, the amount of borrowed books, and the amount of penalties.
### Book Database
The book database tracks unique books and copies for each book.
Each book has a title, author, ISBN, and category. There is also a queue for users that have reserved the book.
Each copy has a uniqued ID and tracks the current reader, the borrow date, the return date, and the reserved date.
