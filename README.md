<b> Overview</b>
<br>
 This C++ program implements a Library Management System, allowing users to manage books,
 including adding, removing, searching, and displaying book details. It uses file handling for data
 persistence and provides a command-line interface for user interaction
 <br>
 <br>
<b> 2. Book Class</b>
<br>
 The `Book` class represents a book entity with attributes:- id: Unique identifier for each book.- title: Name of the book.- author: Name of the author.- category: Genre or type of the book.- isAvailable: Boolean flag to indicate availability.
 A constructor initializes these attributes
 <br>
 <br>
<b>3. Library Class </b>
<br>
 Manages book records using a data structure like `vector<Book>` or `map<int, Book>`.
 Possible functionalities:- addBook(): Adds a new book to the system.- removeBook(): Deletes a book using its ID.- searchBook(): Finds books by title or author.- displayBooks(): Shows available books
 <br>
 <br>
 <b>4. File Handling</b><br>
 The system uses file operations to store book details persistently. It reads and writes book records
 from/to a file, ensuring data is retained even after the program exits.
 <br>
 <br>
<b> 5. User Interaction<?b>
<br>
 The system provides a command-line interface (CLI) for users. It likely supports the following
 operations:- Adding new books.- Viewing book details.- Searching for a book.- Borrowing and returning books
