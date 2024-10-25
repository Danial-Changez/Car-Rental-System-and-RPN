/*
Name: Danial Changez
Student ID: 1232341
Date: October 24, 2024
Assignment 2, Question 1
*/

// Libraries Used Add more here if needed
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h> //For isalnum

// Our Linked List Node
struct car
{
  char plate[9];
  int mileage;
  int return_date; // Return date will be -1 for a car with no return date
  struct car *next;
};

// Function Definitions
void prompt();
struct car *insert_to_list(struct car **head, char plate[], int mileage, int return_date);
void print_list(struct car *head);
bool is_plate_in_list(struct car *head, char plate[]);
void swap(struct car *a, struct car *b);
void sort_list(struct car **head, bool sort_by_mileage, bool sort_by_return_date);
struct car *remove_car_from_list(struct car **head, char plate[]);
struct car *remove_first_from_list(struct car **head);
double profit_calculator(int intial_mileage, int final_mileage);
void write_list_to_file(char *filename, struct car *head);
void read_file_into_list(char *filename, struct car **head);
void date(int date);
void free_list(struct car **head);
struct car *split(struct car *head);
struct car *merge(struct car *left, struct car *right, bool sort_by_mileage);
struct car *merge_sort(struct car *head, bool sort_by_mileage);
bool is_valid_plate(char *plate);
bool is_unique_plate(struct car *head, char *plate);
bool is_valid_mileage(int currentMile, int previousMile);
bool is_valid_return_date(int return_date);