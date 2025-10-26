# ContactDirectory_AVL
Mini Project : Contact Directory using AVL Tree(C++)

Authors:Manikandan RS,Prakash G

Language: C++

SDG Link: SDG 9--Industry,Innovation and Infrastructure

## Project Overview
This mini project implements a **Contact Directory** using an **AVL Tree** — a self-balancing binary search tree.  
Each contact record stores:
- Name  
- Phone Number  
- Email Address
  
Contacts are stored in **sorted order by name**, and the tree remains **balanced** after every insertion or deletion, ensuring efficient search, insert, and delete operations

## Features
- Add new contact  
- Search contact by name  
- Delete contact  
- Display all contacts (in alphabetical order)  
- Load contacts from CSV and save changes back to CSV
  
## Project File Structure
ContactDirectory_AVL/

main.cpp → Source code (C++)

contacts.csv → Sample dataset

README.md → Project overview

report.pdf → Optional project report

## How to Compile & Run

### Using MinGW on Windows (Command Prompt)
1. Make sure **MinGW** is installed and added to your system PATH.  
2. Open **Command Prompt** in your project folder:

    cd path\to\ContactDirectory_AVL

3. Compile the program:

   g++ main.cpp -o ContactDirectory

4. Run the program:

   ContactDirectory

 ## How It Works

1.On startup, the program loads contacts from contacts.csv.

2.Menu options allow you to add, search, delete, or display contacts.

3.When exiting, all changes are saved back to contacts.csv, so no data is lost.

## GitHub / Submission

1.Create a new repository on GitHub (e.g., ContactDirectory_AVL.)

2.Upload the project folder or the ZIP provided.

3.Add a short description and commit.
