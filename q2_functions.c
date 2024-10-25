/*
Name: Danial Changez
Student ID: 1232341
Date: October 24, 2024
Assignment 2, Question 2
*/

#include "q2.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * Pushes a new value onto the stack.
 * @param stack Pointer to the pointer of the stack's head.
 * @param value The value to be added to the stack.
 */
void push(Operand **stack, double value)
{
    Operand *newNode = (Operand *)malloc(sizeof(Operand)); // Allocate memory for a new stack node
    if (newNode == NULL)
    {
        fprintf(stderr, "Cannot add a NULL value to the stack\n");
        return;
    }

    newNode->value = value; // Set the value for the new node
    newNode->next = *stack; // Link the new node to the previous top
    *stack = newNode;       // Update the stack pointer to the new node
}

/**
 * Pops the top value from the stack and returns it.
 * @param stack Pointer to the pointer of the stack's head.
 * @return The value that was at the top of the stack.
 */
double pop(Operand **stack)
{
    if (*stack == NULL) // Check if the stack is empty
    {
        fprintf(stderr, "Stack is empty, underflow error\n");
        exit(-1);
    }

    Operand *temp = *stack;     // Store the current top node
    double value = temp->value; // Retrieve the value to return
    *stack = temp->next;        // Move the stack pointer to the next node
    free(temp);                 // Free the memory of the popped node

    return value; // Return the popped value
}

/**
 * Prints all values in the stack.
 * @param stack Pointer to the stack's head.
 */
void print(Operand *stack)
{
    if (stack == NULL) // Check if the stack is empty
    {
        printf("Stack is empty.\n");
        return;
    }

    printf("Stack contents:\n");
    Operand *current = stack; 
    while (current != NULL)   // Traverse the stack from the start
    {
        printf("%f\n", current->value); 
        current = current->next;        
    }
}
