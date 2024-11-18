# Car Rental System and Reverse Polish Notation (RPN) Calculator

This project was developed as **Assignment 2** for the **CIS*2520 Data Structures** course at the University of Guelph. It encompasses two main components:

1. **Car Rental System:** A simulation of a car rental company utilizing data structures such as singly linked lists, stacks, and merge sort algorithms.
2. **RPN Calculator:** An implementation of a Reverse Polish Notation calculator using stack data structures.


## Table of Contents
1. [Data Structures and Algorithms](#data-structures-and-algorithms)
2. [Car Rental System](#car-rental-system)
   - [Features](#features)
3. [RPN Calculator](#rpn-calculator)
   - [Features](#features-1)
4. [Installation and Usage](#installation-and-usage)
5. [Resources](#resources)

## Data Structures and Algorithms

- **Singly Linked Lists:** Manage the dynamic lists of cars.
- **Stacks:** Implement the RPN calculator and manage certain operations within the car rental system.
- **Merge Sort:** Sort the car lists based on specific criteria.


## Car Rental System

The Car Rental System is designed to manage a fleet of cars categorized into three lists efficiently:

- **Available for Rent**
- **Rented**
- **In Repair**

### Features

- **Add New Cars:** Introduce new vehicles into the system.
- **Rent Cars:** Move cars from the available list to the rented list.
- **Return Cars:** Transition cars from rented to available or repair lists based on their condition.
- **Transfer to Repair:** Shift cars from available or rented lists to the repair list.
- **Transfer from Repair:** Move cars from the repair list back to the available list.
- **Display Lists:** View the current status of all three car lists.
- **Save and Load Data:** Persist and retrieve car lists to and from text files.


## RPN Calculator

The Reverse Polish Notation (RPN) Calculator evaluates mathematical expressions written in postfix notation. This component demonstrates the application of stack data structures.

### Features

- **Evaluate Expressions:** Compute results for valid RPN expressions.
- **Error Handling:** Identify and report errors in invalid expressions.


## Installation and Usage

1. **Clone the Repository:**
   ```bash
   git clone https://github.com/Danial-Changez/Car-Rental-System-and-RPN.git
   ```
   
2. **Compile the Programs:**
  ```bash
  make
  ```

3. **Run the Car Rental System:**
  ```bash
  ./a2q1
  ```

4. **Run the RPN Calculator:**
  - Sample test case provided
  ```bash
  ./a2q2 512+4*+3-
  ```
Note: Ensure you have a C compiler and make utility installed on your system.

## Resources

The following resources supported the development of this project:

- **Course Materials:** Slides and notes on singly linked lists, stacks, and merge sort algorithms.
- **Online References:**
  - [Merge Sort for Linked List](https://www.geeksforgeeks.org/merge-sort-for-linked-list/)
  - [C String Functions](https://www.w3schools.com/c/c_ref_string.php)
  - [C File Handling](https://www.w3schools.com/c/c_files.php)
  - [C Error Handling](https://www.w3schools.in/c-programming/error-handling)
  - [C `isalnum()` Function](https://www.tutorialspoint.com/isalnum-function-in-c-language)
