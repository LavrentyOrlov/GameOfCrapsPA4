/*
Programmer: Lavrenty "Larry" Orlov
Class: CptS 121; Lab Section 10L
Programming Assignment: Programming Assignment 4 - Game of Craps
Date: 9/16/2025
Description: This is a text-based version of a gambling game called Craps involving features like user input, logical decision-making,
			 checking for valid user input, and random number generation.
*/

#include "Craps.h"

int main(void)
{
	int choice = 0, valid = 0, game_over = 0;

	srand(time(NULL));

	do {
	
		do
		{
			system("cls"); // Once the user enters a value into the menu, we can clear the screen and either display the menu again or start the game!
			print_menu(); // Print menu! --> No matter what!
			choice = get_choice(); // Get choice! --> No matter what!
			valid = is_valid_input_start_of_game(choice); // Evaluate user's first choice! --> No matter what!
		} while (!valid); // input validation loop pattern! --> we need input BEFORE evaluating that input!
		// Use do-while loop to gurantee that it runs the first time (while loop may not run if iniitial condition not met)!

		// New concept! Switch statement!!
		// Symmetry in code makes it more readable and understandable!

		// More efficient than if-else statements! --> As soon as we process what's inside the parenthesis (control variable), we immediately jump to the correct case and perform only one action!
		// In contrast: if-else statements may require multiple condition checks before we reach the correct result!

		switch (choice) // integral values only - includes characters!
			// use choice as the value to act on!
		{
		case DISPLAY_RULES: print_game_rules(); // we know that DISPLAY_RULES represents 1!
			break; // Break kicks us out of the code segment (in this case, switch statement)! --> Without break: switch statement executes the next condiiton
		case PLAY:
			game_over = 0;
			play_the_game(game_over);
			break;
		case EXIT: printf("Thanks for playing! See ya next time :D\n");
			break;
		}
	} while (choice != EXIT);

	// Idea: after reading the rules, it's a good idea to go back to main menu in case the user wants to read the rules again!
}