/*
Name: Danial Changez
Student ID: 1232341
Date: Oct 24, 2024
Assignment 2, Question 1
*/

#include "q1.h"

/**
 * Prompts the user for their choice of operation.
 */
void prompt()
{
    printf("1. Add a new car to the available-for-rent list,\n");
    printf("2. Add a returned car to the available-for-rent list,\n");
    printf("3. Add a returned car to the repair list,\n");
    printf("4. Transfer a car from the repair list to the available-for-rent list,\n");
    printf("5. Rent the first available car,\n");
    printf("6. Print all the lists,\n");
    printf("7. Quit.\n");
    printf("Enter your choice: ");
}

/**
 * Validates the car plate number.
 * Checks if the plate length is between 2 and 8 characters
 * and ensures it contains only alphanumeric characters.
 * @param plate The plate number to validate.
 * @return true if valid; false otherwise.
 */
bool is_valid_plate(char *plate)
{
    int length = strlen(plate);
    // Check if the length is within the allowed range
    if (length < 2 || length > 8)
    {
        printf("Plate must be between 2-8 characters long.\n");
        return false;
    }
    // Check if each character is alphanumeric
    for (int i = 0; i < length; i++)
    {
        if (!isalnum(plate[i]))
        {
            printf("Plate must contain alphanumeric characters only.\n");
            return false;
        }
    }
    return true; // Plate is valid
}

/**
 * Checks if the car plate number is unique in the linked list.
 * Cycles through the list and compares each plate with the provided one.
 * @param head Pointer to the head of the linked list of cars.
 * @param plate The plate number to check for uniqueness.
 * @return true if unique; false if a duplicate is found.
 */
bool is_unique_plate(struct car *head, char *plate)
{
    struct car *currentCar = head;

    // Cycle through the list to check for duplicates
    while (currentCar != NULL)
    {
        if (strcmp(currentCar->plate, plate) == 0)
        {
            printf("Duplicate plates found.\n");
            return false; // Duplicate plate found
        }
        currentCar = currentCar->next; // Move to the next car
    }
    return true; // Plate is unique
}

/**
 * Validates the current mileage of a car.
 * Ensures the current mileage is greater than the previous mileage.
 * @param currentMile The current mileage to validate.
 * @param previousMile The previous mileage to compare against.
 * @return true if valid; false otherwise.
 */
bool is_valid_mileage(int currentMile, int previousMile)
{
    // Check if the current mileage is less than the previous mileage
    if (currentMile < previousMile)
    {
        printf("Your current mileage must be greater than the previous mileage of the car.\n");
        return false;
    }
    return true; // Mileage is valid
}

/**
 * Validates the return date format.
 * Checks if the return date is a 6-digit number representing YYMMDD.
 * @param return_date The return date to validate.
 * @return true if valid; false otherwise.
 */
bool is_valid_return_date(int return_date)
{
    // Check if the return date is a 6-digit number
    if (return_date < 100000 || return_date > 999999)
    {
        printf("Please provide a return date in the correct format (YYMMDD).\n");
        return false;
    }
    return true; // Return date is valid
}

/**
 * Inserts a new car into the linked list.
 * @param head Pointer to the head of the list.
 * @param plate Character array containing the car's license plate.
 * @param mileage Integer representing the car's mileage.
 * @param return_date Integer representing the car's return date, you can have -1 represent no return date.
 * @return Pointer to the newly added car in the list.
 */
struct car *insert_to_list(struct car **head, char plate[], int mileage, int return_date)
{
    // Check if the plate already exists in the list
    if (is_plate_in_list(*head, plate))
    {
        printf("Car with plate %s already exists in the list.\n", plate);
        return NULL;
    }

    // Allocate memory for the new car
    struct car *newCar = (struct car *)malloc(sizeof(struct car));
    if (newCar == NULL)
    {
        printf("Memory allocation failed.\n");
        return NULL;
    }

    // Initialize the new car's fields
    strcpy(newCar->plate, plate);
    newCar->mileage = mileage;
    newCar->return_date = return_date;
    newCar->next = NULL;

    // Insert the new car in the correct position based on mileage and return date
    if (*head == NULL || (*head)->mileage > mileage || (return_date != -1 && (*head)->return_date > return_date))
    {
        // Insert at the beginning of the list if it's empty or the new car has the lowest mileage/return date
        newCar->next = *head;
        *head = newCar;
        return newCar;
    }
    else
    {
        // Find the correct position in the list to insert the new car
        struct car *currentCar = *head;

        // Traverse the list to find the insertion point
        while ((currentCar->next != NULL) && (currentCar->next->mileage < mileage || (return_date != -1 && currentCar->next->return_date < return_date)))
            currentCar = currentCar->next;

        // Insert the new car at the found position
        newCar->next = currentCar->next;
        currentCar->next = newCar;
    }
    return newCar; // Return the newly added car
}

/**
 * Prints all the cars in the list.
 * @param head Pointer to the head of the list.
 * This function prints out the car details, it should not print return date if it does not exist.
 */
void print_list(struct car *head)
{
    // Check if the list is empty
    if (head == NULL)
    {
        printf("The list is empty\n\n");
        return;
    }

    // Cycle through the linked list to print each car's details
    while (head != NULL)
    {
        printf("Plate: %s\n", head->plate);
        printf("Mileage: %d\n", head->mileage);

        // Check if the return date is valid (not -1)
        if (head->return_date != -1)
            printf("Return Date: %d\n\n", head->return_date);
        else
            printf("\n");

        head = head->next;
    }
    return;
}

/**
 * Checks if a car's plate is already in the list.
 * @param head Pointer to the head of the list.
 * @param plate Character array containing the car's license plate.
 * @return Boolean value indicating if the plate is found.
 */
bool is_plate_in_list(struct car *head, char plate[])
{
    // Cycle through the linked list
    while (head != NULL)
    {
        // Compare the current car's plate with the provided plate
        if (strcmp(head->plate, plate) == 0)
            return true; // Plate found
        head = head->next;
    }
    return false; // Plate not found
}

/**
 * Swaps two cars in the list.
 * @param a Pointer to the first car.
 * @param b Pointer to the second car.
 * Swaps the plate, mileage, and return date of two cars.
 */
void swap(struct car *a, struct car *b)
{
    // Temporary storage for the details of car 'a'
    char temp_plate[7];
    int temp_mileage;
    int temp_return_date;

    // Store the details of car 'a' in temporary variables
    strcpy(temp_plate, a->plate);
    temp_mileage = a->mileage;
    temp_return_date = a->return_date;

    // Swap details between car 'a' and car 'b'
    strcpy(a->plate, b->plate);
    a->mileage = b->mileage;
    a->return_date = b->return_date;

    // Assign the stored details of car 'a' to car 'b'
    strcpy(b->plate, temp_plate);
    b->mileage = temp_mileage;
    b->return_date = temp_return_date;
}

/**
 * Sorts the list of cars based on mileage or return date.
 * @param head Pointer to the head of the list.
 * @param sort_by_mileage Boolean to sort by mileage.
 * @param sort_by_return_date Boolean to sort by return date.
 */
void sort_list(struct car **head, bool sort_by_mileage, bool sort_by_return_date)
{
    if (sort_by_mileage)
        *head = merge_sort(*head, true); // Sort by mileage

    else if (sort_by_return_date)
        *head = merge_sort(*head, false); // Sort by return date
    return;
}

/**
 * Splits the linked list into two halves.
 * This function uses the slow and fast pointers to find the midpoint
 * of the list and splits it into two separate lists.
 * @param head Pointer to the head of the list to be split.
 * @return Pointer to the head of the second half of the list.
 */
struct car *split(struct car *head)
{
    if (head == NULL)
        return NULL; // Return NULL if the list is empty

    struct car *slow = head;       // Slow pointer for finding the midpoint
    struct car *fast = head->next; // Fast pointer to traverse the list

    // Traverse the list to find the midpoint
    while (fast != NULL && fast->next != NULL)
    {
        fast = fast->next->next; // Move fast pointer two steps
        slow = slow->next;       // Move slow pointer one step
    }

    struct car *temp = slow->next; // Split the list
    slow->next = NULL;             // Remove the first half
    return temp;                   // Return the head of the second half
}

/**
 * Merges two sorted linked lists into one sorted list.
 * This function merges two lists based on either mileage or return date,
 * maintaining the sorted order of the resulting list.
 * @param left Pointer to the head of the first sorted list.
 * @param right Pointer to the head of the second sorted list.
 * @param sort_by_mileage Boolean flag indicating whether to merge based on mileage.
 * @return Pointer to the head of the merged sorted list.
 */
struct car *merge(struct car *left, struct car *right, bool sort_by_mileage)
{
    // Base cases for recursion
    if (left == NULL)
        return right; // If the left list is empty, return right list
    if (right == NULL)
        return left; // If the right list is empty, return left list

    // Merge based on mileage
    if (sort_by_mileage)
    {
        if (left->mileage < right->mileage)
        {
            left->next = merge(left->next, right, sort_by_mileage); // Recursively merge
            return left;                                            // Return left node
        }
        else
        {
            right->next = merge(left, right->next, sort_by_mileage); // Recursively merge
            return right;                                            // Return right node
        }
    }
    // Merge based on return date
    else
    {
        if (left->return_date <= right->return_date)
        {
            left->next = merge(left->next, right, sort_by_mileage); // Recursively merge
            return left;                                            // Return left node
        }
        else
        {
            right->next = merge(left, right->next, sort_by_mileage); // Recursively merge
            return right;                                            // Return right node
        }
    }
}

/**
 * Performs a merge sort on the linked list of cars.
 * @param head Pointer to the head of the linked list of cars to be sorted.
 * @param sort_by_mileage A boolean flag indicating whether to sort by mileage (true) or by return date (false).
 * @return Pointer to the head of the sorted linked list.
 */
struct car *merge_sort(struct car *head, bool sort_by_mileage)
{
    // Base case: if the list is empty or contains a single car.
    if (head == NULL || head->next == NULL)
        return head;

    // Split the list into two halves and store the second half in 'right'.
    struct car *right = split(head);

    // Recursively sort both halves of the list.
    head = merge_sort(head, sort_by_mileage);
    right = merge_sort(right, sort_by_mileage);

    // Merge the two sorted halves and return the head of the merged list.
    return merge(head, right, sort_by_mileage);
}

/**
 * Removes a car from the list by its plate number.
 * @param head Pointer to the head of the list.
 * @param plate Character array containing the car's license plate.
 * @return Pointer to the removed car.
 */
struct car *remove_car_from_list(struct car **head, char plate[])
{
    // Check if the list is empty or if the head pointer is NULL.
    if (head == NULL || *head == NULL)
        return NULL;

    struct car *currentCar = *head;
    struct car *previousCar = NULL;

    // Cycle through the list to find the car with the specified plate.
    while (currentCar != NULL)
    {
        // Check if the current car's plate matches the target plate.
        if (strcmp(currentCar->plate, plate) == 0)
        {
            // If the car to be removed is the head of the list.
            if (previousCar == NULL)
                *head = currentCar->next;
            else
                previousCar->next = currentCar->next;

            return currentCar; // Return the removed car.
        }
        previousCar = currentCar;
        currentCar = currentCar->next;
    }
    return NULL;
}

/**
 * Removes the first car from the list.
 * @param head Pointer to the head of the list.
 * @return Pointer to the removed car.
 */
struct car *remove_first_from_list(struct car **head)
{
    // Check if the list is empty.
    if (*head == NULL)
        return NULL;

    // Update the head pointer to the next car in the list and remove first car.
    struct car *removedCar = *head;
    *head = (*head)->next;
    return removedCar;
}

/**
 * Calculates the profit based on the mileage difference.
 * @param initial_mileage Integer representing the car's starting mileage.
 * @param final_mileage Integer representing the car's final mileage.
 * @return Double value representing the calculated profit.
 */
double profit_calculator(int initial_mileage, int final_mileage)
{
    if (final_mileage <= initial_mileage)
        return 0.00;

    double profit = 80.00; // Base profit for the first 200 kilometers.
    int mileDif = final_mileage - initial_mileage;

    // If the mileage difference exceeds 200 kilometers, calculate additional profit.
    if (mileDif > 200)
        profit += (mileDif - 200) * 0.15; // Add $0.15 for each kilometer beyond 200.

    return profit;
}

/**
 * Writes the list of cars to a file.
 * The file would be in the format: plate,mileage,return_date
 * @param filename Character array with the file name.
 * @param head Pointer to the head of the list.
 * Writes the details of each car in the list to a file.
 */
void write_list_to_file(char *filename, struct car *head)
{
    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        printf("File does not exist.\n");
        return;
    }

    // Check if the list is empty.
    if (head == NULL)
    {
        printf("The list is empty, nothing to write.\n");
        fclose(file);
        return;
    }

    struct car *currentCar = head;

    // Loop through each car in the list until reaching the end.
    while (currentCar != NULL)
    {
        // Write the car's details to the file.
        fprintf(file, "%s,%d,%d\n", currentCar->plate, currentCar->mileage, currentCar->return_date);
        currentCar = currentCar->next;
    }

    fclose(file);
}

/**
 * Reads car details from a file and adds them to the list.
 * The file would be in the format: plate,mileage,return_date
 * @param filename Character array with the file name.
 * @param head Pointer to the head of the list.
 */
void read_file_into_list(char *filename, struct car **head)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("File does not exist.\n");
        return;
    }
    char line[128];

    // Read each line from the file until the end is reached.
    while (fgets(line, sizeof(line), file))
    {
        // Allocate memory for a new car node.
        struct car *newCar = malloc(sizeof(struct car));
        if (newCar == NULL)
        {
            printf("newCar is NULL.\n");

            // Free all previously allocated car nodes in the list.
            struct car *temp;
            while (*head != NULL)
            {
                temp = *head;
                *head = (*head)->next;
                free(temp);
            }

            fclose(file);
            return;
        }

        // Initialize car details with default values.
        newCar->mileage = 0;
        newCar->return_date = -1;

        // Split the line at the delimiter (,) to extract car details.
        char *info = strtok(line, ",");
        if (info != NULL)
            strncpy(newCar->plate, info, sizeof(newCar->plate) - 1);
        newCar->plate[sizeof(newCar->plate) - 1] = '\0';

        // Get mileage.
        info = strtok(NULL, ",");
        if (info != NULL)
            newCar->mileage = atoi(info);

        // Get return date.
        info = strtok(NULL, ",");
        if (info != NULL)
            newCar->return_date = atoi(info);

        // Validate mileage and return date.
        if (newCar->mileage < 0 || newCar->return_date < -1)
        {
            printf("Invalid inputs in file, skipping entry: %s\n", newCar->plate);
            free(newCar);
            continue;
        }
        newCar->next = *head;
        *head = newCar;
    }
    fclose(file);
}

/**
 * Prints the date in the format of year/month/day.
 * @param date Integer representing the date in YYMMDD format.
 */
void date(int date)
{
    // Separate date into 3 variables
    int year = date / 10000;
    int month = (date / 100) % 100;
    int day = date % 100;

    // Print the formatted date
    printf("%04d/%02d/%02d\n", year, month, day);
    return;
}

/**
 * Frees all the memory allocated for the cars in the list.
 * @param head Pointer to the head of the list.
 * Frees each car node in the list.
 */
void free_list(struct car **head)
{
    struct car *currentCar = *head;
    struct car *nextCar;

    // Cycle through the list until the end is reached.
    while (currentCar != NULL)
    {
        nextCar = currentCar->next;
        free(currentCar);
        currentCar = nextCar;
    }
    *head = NULL; // Set the head to NULL to indicate that the list is empty.
}