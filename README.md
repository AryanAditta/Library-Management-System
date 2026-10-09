# Library Management System

**Console-based C++ library-management project using a linked-list data structure and simple file persistence.**

The program models a small library workflow around book creation, search, modification, deletion, renting and returns. It uses a custom singly linked list to manage book records in memory and saves the collection to a text file when the program exits.

## Features

- Add new books.
- Display all stored books.
- Search for a book by name.
- Modify an existing book record.
- Delete a book.
- Rent a book and track availability status.
- Return a rented book.
- Load and save records using `books.txt`.

## Implementation

- **Language:** C++
- **Data structure:** singly linked list
- **Persistence:** text-file I/O using `fstream`
- **Interface:** menu-driven console application

## Repository Contents

- [`Library Management System.CPP`](Library%20Management%20System.CPP) — complete C++ source code.
- [`Library Management System.docx`](Library%20Management%20System.docx) — project documentation.
- [`CSE Project Presentation Final.pptm`](CSE%20Project%20Presentation%20Final.pptm) — project presentation.

## Running the Project

1. Compile `Library Management System.CPP` with a standard C++ compiler.
2. Run the executable from a writable working directory.
3. The program will read from `books.txt` if the file exists and save the current records to `books.txt` on exit.

Example with `g++`:

```bash
g++ "Library Management System.CPP" -o library_system
./library_system
```

## Technical Focus

`C++` · `Linked Lists` · `File I/O` · `Object-Oriented Programming` · `Data Structures`

This is an undergraduate programming project and is retained as part of my broader engineering portfolio.

[GitHub Profile](https://github.com/AryanAditta)
