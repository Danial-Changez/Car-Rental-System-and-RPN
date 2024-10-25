/*
Name: Danial Changez
Student ID: 1232341
Date: October 24, 2024
Assignment 2, Question 1
*/

#include "q1.h"

/*
 * Main function for the car rental program.
 * This program manages a car rental system with three linked lists:
 * - available-for-rent cars
 * - rented cars
 * - cars in repair.
 * Users can perform various operations such as adding cars, returning cars,
 * transferring cars to and from repair, renting cars, viewing lists,
 * and saving data to files.
 * The program utilizes a menu-driven interface for user interaction.
 */

int main()
{
    // Initialize three linked lists to manage car statuses.
    struct car *available_head = NULL;
    struct car *rented_head = NULL;
    struct car *repair_head = NULL;

    // Initialize variables for user input
    char plate[9];
    int mileage, return_date, choice;

    // Load initial data from files into the linked lists
    read_file_into_list("available.txt", &available_head);
    read_file_into_list("rented.txt", &rented_head);
    read_file_into_list("repair.txt", &repair_head);

    do
    {
        prompt();             // Display the menu options to the user
        scanf("%d", &choice); // Get user choice
        getchar();            // Clear the newline character from input
        printf("\n");

        switch (choice)
        {
        case 1: // Option to add a new car to the available list
        {
            printf("Enter car plate (2-8 alphanumeric characters): ");
            fgets(plate, sizeof(plate), stdin); // Read car plate from input
            plate[strcspn(plate, "\n")] = '\0'; // Remove newline character

            // Validate the plate number and ensure it is unique
            if (!is_valid_plate(plate) || !is_unique_plate(available_head, plate))
            {
                printf("Invalid plate number.\n");
                break;
            }

            printf("Enter car mileage: ");
            scanf("%d", &mileage); // Get mileage input

            // Validate mileage
            if (mileage < 0)
            {
                printf("Mileage cannot be negative.\n");
                break;
            }

            // Insert the new car into the available list and provide feedback
            if (insert_to_list(&available_head, plate, mileage, -1))
                printf("Car added to available-for-rent list.\n\n");
            else
                printf("Error adding car. Please check the input.\n\n");
            break;
        }

        case 2: // Option to return a rented car
        {
            printf("Enter car plate (2-8 alphanumeric characters): ");
            fgets(plate, sizeof(plate), stdin); // Read car plate from input
            plate[strcspn(plate, "\n")] = '\0'; // Remove newline character

            // Validate the plate number
            if (!is_valid_plate(plate))
            {
                printf("Invalid plate number.\n");
                break;
            }

            printf("Enter car mileage: ");
            scanf("%d", &mileage); // Get mileage input

            // Move the car from the rented list to the available list
            if (insert_to_list(&available_head, plate, mileage, -1) && remove_car_from_list(&rented_head, plate))
                printf("Returned car added to available-for-rent list.\n\n");
            else
                printf("Error adding car. Please check the input.\n\n");
            break;
        }

        case 3: // Option to move a car to the repair list
        {
            printf("Enter car plate (2-8 alphanumeric characters): ");
            fgets(plate, sizeof(plate), stdin); // Read car plate from input
            plate[strcspn(plate, "\n")] = '\0'; // Remove newline character

            // Validate the plate number
            if (!is_valid_plate(plate))
            {
                printf("Invalid plate number.\n");
                break;
            }

            printf("Enter car mileage: ");
            scanf("%d", &mileage); // Get mileage input

            // Move the car from the rented list to the repair list
            if (insert_to_list(&repair_head, plate, mileage, -1) && remove_car_from_list(&rented_head, plate))
                printf("Car added to repair list.\n\n");
            else
                printf("Error adding car. Please check the input.\n\n");
            break;
        }

        case 4: // Option to transfer a car from repair to available
        {
            if (repair_head == NULL) // Check if the repair list is empty
                printf("No cars in the repair list to transfer.\n");
            else
            {
                printf("Enter the plate number of the car to transfer: ");
                scanf("%s", plate); // Read car plate from input

                // Validate the plate number
                if (!is_valid_plate(plate))
                {
                    printf("Invalid plate number format.\n");
                    break;
                }

                struct car *carToTransfer = (struct car *)malloc(sizeof(struct car));
                carToTransfer = remove_car_from_list(&repair_head, plate); // Remove the car from the repair list

                if (carToTransfer)
                {
                    // Transfer the car to the available list and free the allocated memory
                    insert_to_list(&available_head, carToTransfer->plate, carToTransfer->mileage, -1);
                    free(carToTransfer);
                    printf("Car transferred to available-for-rent list.\n\n");
                }
                else
                    printf("Car with plate %s not found in the repair list.\n", plate);
            }
            break;
        }

        case 5: // Option to rent out a car
        {
            if (available_head == NULL) // Check if the available list is empty
                printf("No cars available for rent.\n");
            else
            {
                printf("Enter the expected return date (YYMMDD): ");
                scanf("%d", &return_date); // Get return date input

                // Validate the return date
                if (!is_valid_return_date(return_date))
                {
                    printf("Invalid return date format.\n");
                    break;
                }

                struct car *rentedCar = (struct car *)malloc(sizeof(struct car));
                rentedCar = remove_first_from_list(&available_head); // Remove the first available car

                if (rentedCar)
                {
                    rentedCar->return_date = return_date; // Set return date for the rented car
                    insert_to_list(&rented_head, rentedCar->plate, rentedCar->mileage, rentedCar->return_date);
                    free(rentedCar); // Free memory of the rented car
                    printf("Car rented out successfully.\n");
                }
                else
                    printf("Error renting out car.\n");
            }
            break;
        }

        case 6: // Option to print lists of cars
        {
            printf("\nAvailable for Rent List:\n");
            print_list(available_head); // Print the available cars
            printf("\nRented List:\n");
            print_list(rented_head); // Print the rented cars
            printf("\nIn Repair List:\n");
            print_list(repair_head); // Print the cars in repair
            break;
        }

        case 7: // Option to save data to files and exit
        {
            write_list_to_file("available.txt", available_head);
            write_list_to_file("rented.txt", rented_head);
            write_list_to_file("repair.txt", repair_head);
            printf("Data saved. Exiting program...\n");
            break;
        }

        default: // Handle invalid menu choices
            printf("Invalid choice. Please try again.\n");
            break;
        }
    } while (choice != 7); // Loop until the user chooses to exit

    // Free allocated memory for all linked lists
    free_list(&available_head);
    free_list(&rented_head);
    free_list(&repair_head);
    return 0;
}
