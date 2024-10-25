/*
Name: Danial Changez
Student ID: 1232341
Date: October 24, 2024
Assignment: Assignment 2, Question 2
*/

#include "q2.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> // For isdigit

/**
 * Main function to handle command line arguments and perform stack operations
 * based on the input (digits and operators including +, -, *, /).
 * @param argc The number of command line arguments.
 * @param argv The command line arguments string.
 * @return 0 on success, 1 for insufficient arguments, -1 for errors.
 */
int main(int argc, char **argv)
{
  // Check if there are enough command line arguments
  if (argc < 2)
  {
    printf("You do not have enough arguments\n");
    return 1;
  }

  Operand *stack = NULL; // Pointer to the stack
  int digitCount = 0;    // Count of digits
  int operatorCount = 0; // Count of operators

  // Cycle through each character in the input
  for (int i = 0; i < strlen(argv[1]); i++)
  {
    char input = argv[1][i];

    if (isdigit(input))
    {
      double value = input - '0'; // Convert character to double
      push(&stack, value);        // Push the digit onto the stack
      digitCount++;               // Increment digit count
    }
    else if (input == '+' || input == '-' || input == '*' || input == '/')
    {
      operatorCount++; // Increment operator count

      // Ensure there are at least two digits available for operation
      if (digitCount < 2)
      {
        fprintf(stderr, "Insufficient values for operation: %c\n", input);
        return -1;
      }

      double v2 = pop(&stack); // Pop second value
      double v1 = pop(&stack); // Pop first value

      double result = 0;

      // Perform the operation based on the operator
      switch (input)
      {
      case '+':
        result = v1 + v2;
        break;
      case '-':
        result = v1 - v2;
        break;
      case '*':
        result = v1 * v2;
        break;
      case '/':
        if (v2 != 0)
          result = v1 / v2;
        else
        {
          fprintf(stderr, "Can't divide by 0.\n");
          return -1;
        }
        break;
      }

      push(&stack, result); // Push the result back onto the stack
      digitCount--;         // One operator replaces two digits
    }
    else
    {
      fprintf(stderr, "Invalid character: %c\n", input);
      return -1;
    }
  }

  // Ensure there is at least one result left to pop
  if (operatorCount == 0 || digitCount < 1)
  {
    fprintf(stderr, "Insufficient numbers or operators for calculation.\n");
    return -1;
  }

  // Pop the final result
  if (stack != NULL)
  {
    double final_result = pop(&stack);
    printf("The result is: %.2f\n", final_result);
  }
  else
  {
    fprintf(stderr, "No values left on the stack to pop.\n");
    return -1;
  }

  return 0;
}
