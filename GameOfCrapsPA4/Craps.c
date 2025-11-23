/*
Programmer: Lavrenty "Larry" Orlov
Class: CptS 121; Lab Section 10L
Programming Assignment: Programming Assignment 4 - Game of Craps
Date: 9/16/2025
Description: This is a text-based version of a gambling game called Craps involving features like user input, logical decision-making,
			 checking for valid user input, and random number generation.
*/

#include "Craps.h"

// Displays the main menu to the user
void print_menu()
{
	printf("********************************************************************************************\n");
	printf("Welcome to the game of Craps, designed by Computer Science student Lavrenty \"Larry\" Orlov!\n");
	printf("********************************************************************************************\n");
	printf("\n");
	printf("Main Menu:\n");
	printf("\n");
	printf("1. Display the game rules.\n");
	printf("2. Play game.\n");
	printf("3. Exit.\n");
}

// Prompts the user to enter an integer value from multiple options
int get_choice(void)
{
	int choice = 0;
	scanf("%d", &choice);
	return choice;
}

// Checks for user input and returns 1 if input is valid; returns 0 otherwise
int is_valid_input_start_of_game(int choice)
{
	return !(choice < DISPLAY_RULES || choice > EXIT);
}

// Checks for user input and returns 1 if input is valid; returns 0 otherwise
int is_valid_input_bank_balance(double bank_balance)
{
	return !(bank_balance <= 0.0);
}

// Checks for user input and returns 1 if input is valid; returns 0 otherwise
int is_valid_input_next_step(int choice)
{
	return !(choice < KEEP_PLAYING || choice > RETURN_TO_MAIN_MENU);
}

//Checks to
//see if the wager is within the limits of the player's available balance. If the
//wager exceeds the player's allowable balance, then 0 is returned; otherwise 1
//is returned.
int check_wager_amount(double wager_amount, double balance)
{
	return !(wager_amount <= 0.0 || wager_amount > balance);
}

// Prints out the rules of the game of "craps"
void print_game_rules(void)
{
	system("cls");
	printf("**************************************\n");
	printf("    Rules for the game of \"Craps!\"\n");
	printf("**************************************\n");
	
	printf("\n");
	
	printf("The following description has been adopted from Deitel & Deitel...\n");
	
	printf("\n");
	
	printf("One of the most popular games of chance is a dice game called \"craps,\"\n"); 
	printf("which is played in casinos and back alleys throughout the world.\n");

	printf("\n");

	printf("The rules of the game are straightforward: \n");

	printf("\n");

	printf("A player rolls two dice. Each die has six faces. These faces contain 1, 2, 3, 4, 5, and 6 spots.\n");
	printf("After the dice have come to rest, the sum of the spots on the two upward faces is calculated.\n");

	printf("\n");

	printf("- If the sum is 7 or 11 on the first throw, the player wins.\n");
	printf("- If the sum is 2, 3, or 12 on the first throw (called \"craps\"), the player loses (i.e. the \"house\" wins).\n");
	printf("- If the sum is 4, 5, 6, 8, 9, or 10 on the first throw, then the sum becomes the player's \"point.\"\n");
	printf("--> This means that the player's goal becomes to roll that sum before rolling a sum of 7!\n");

	printf("\n");

	printf("So, to win, you must continue rolling the dice until you \"make your point.\"\n");
	printf("The player loses by rolling a 7 before making the point.\n");

	printf("\n");

	printf("Ready to give this game a try? :D\n");

	printf("\n");

	system("pause");
}

// Function responsible for logical decision-making and overall game flow
void play_the_game(int game_over)
{
	int choice = 0, valid = 0, die1 = 0, die2 = 0, sum = 0, understanding_result = 0, point_value = 0, valid_input = 0, 
		add_or_subtract = 0;
	double bank_balance = 0.0, wager_amount = 0.0;

	do
	{
		system("cls");
		bank_balance = get_bank_balance();
		valid_input = is_valid_input_bank_balance(bank_balance);
	} while (!valid_input);

	do
	{
		do
		{
			system("cls");
			wager_amount = get_wager_amount();
			valid_input = check_wager_amount(wager_amount, bank_balance);
		} while (!valid_input);

		system("cls");
		printf("Awesome, let's go! Ready when you are :D\n");
		system("pause");
		
		system("cls");
		die1 = roll_die();
		die2 = roll_die();
		printf("- First die is: %d\n- Second die is: %d\n", die1, die2);
		
		sum = calculate_sum_dice(die1, die2);
		printf("--> Sum is: %d\n", sum);

		understanding_result = is_win_loss_or_point(sum);

		switch (understanding_result)
		{
		case PLAYER_WINS_FIRST_TRY: printf("Yay, you win on the first roll!\n");
			add_or_subtract = 1;
			break;
		case PLAYER_LOSES_FIRST_TRY: printf("Aw man, you lost on the first roll!\n");
			add_or_subtract = 0;
			break;
		case PLAYER_GETS_THEIR_POINT: printf("Nice, your point is %d!\n", sum);
			point_value = sum;
			do
			{
				system("pause");

				printf("\n");
				die1 = roll_die();
				die2 = roll_die();
				printf("First die is: %d\n Second die is: %d\n", die1, die2);

				sum = calculate_sum_dice(die1, die2);
				printf("Sum is: %d\n", sum);

				understanding_result = is_point_loss_or_neither(sum, point_value);

			} while (understanding_result == PLAYER_GETS_THEIR_POINT);
			if (understanding_result == PLAYER_WINS_WITH_THEIR_POINT)
			{
				printf("Hooray, you win by getting your point of %d!\n", point_value);
				add_or_subtract = 1;
			}
			else
			{
				printf("Aw man, you lost... a 7 came as you tried getting your point!\n");
				add_or_subtract = 0;
			}
		}

		printf("\n");
		printf("We've reached the end of the round! Your bank balance went from $%.2lf to ", bank_balance);
		bank_balance = adjust_bank_balance(bank_balance, wager_amount, add_or_subtract);
		printf("$%.2lf!\n", bank_balance);

		system("pause");

		printf("\n");
		if (bank_balance <= 0)
		{
			printf("Uh-oh! You're bank balance is $0 or less! Returning to the main menu...\n");
			system("pause");
			game_over = 1;
		}
		else 
		{
			printf("Would you like to keep playing?\n");
			printf("1. Yes\n");
			printf("2. No\n");
			
			do
			{
				choice = get_choice();
				valid = is_valid_input_next_step(choice);
			} while (!valid);

			switch (choice)
			{
			case KEEP_PLAYING:
				printf("Yay, playing another round! :D\n");
				system("pause");
				printf("Would you like to use the same bank balance for the next round?\n");
				printf("1. Yes\n");
				printf("2. No\n");
				do
				{
					choice = get_choice();
					valid = is_valid_input_next_step(choice);
				} while (!valid);

				switch (choice)
				{
				case KEEP_BANK_BALANCE:
					printf("Playing with same bank balance!\n");
					system("pause");
					break;
				case CHANGE_BANK_BALANCE:
					printf("You'll be able to change your bank balance!\n");
					system("pause");
					do
					{
						system("cls");
						bank_balance = get_bank_balance();
						valid_input = is_valid_input_bank_balance(bank_balance);
					} while (!valid_input);
					break;
				}
				break;
			case RETURN_TO_MAIN_MENU:
				printf("Got it, returning to the main menu! :)\n");
				system("pause");
				game_over = 1;
				break;
			}
		}

	} while (!game_over);
}

//Rolls one die.This function should randomly
//generate a value between 1 and 6, inclusively.Returns the value of the die.
//(5 pts) int calculate_sum_dice(int die1_value, int die2_value) - Sums together
//the values of the two dice and returns the result.
int roll_die(void)
{
	return rand() % DIE_FACES + 1;
}

//Sums together
//the values of the two dice and returns the result.Note: this result may become
//the player's point in future rolls.
int calculate_sum_dice(int die1_value, int die2_value)
{
	return die1_value + die2_value;
}

//Determines the result of
//the first dice roll.If the sum is 7 or 11 on the roll, the player wins and 1 is
//returned.If the sum is 2, 3, or 12 on the first throw (called "craps"), the player
//loses(i.e.the "house" wins) and 0 is returned.If the sum is 4, 5, 6, 8, 9, or 10
//on the first throw, then the sum becomes the player's "point" and -1 is
//returned.
int is_win_loss_or_point(int sum_dice)
{
	if (sum_dice == 7 || sum_dice == 11)
	{
		return 1;
	}
	else if (sum_dice == 2 || sum_dice == 3 || sum_dice == 12)
	{
		return 0;
	}
	else
	{
		return -1;
	}
}

// Determines the result of any successive roll after the first roll.If the sum of
// the roll is the point_value, then 1 is returned. If the sum of the roll is a 7, then
// 0 is returned.Otherwise, -1 is returned.
int is_point_loss_or_neither(int sum_dice, int point_value)
{
	if (sum_dice == point_value)
	{
		return 1;
	} 
	else if (sum_dice == 7)
	{
		return 0;
	}
	else
	{
		return -1;
	}
}

//-Prompts the player for an initial bank
//balance from which wagering will be added or subtracted.The player entered
//bank balance(in dollars, i.e.$100.00) is returned.
double get_bank_balance(void)
{
	double bank_balance = 0.0;
	printf("What's your starting bank balance? $");
	scanf("%lf", &bank_balance);
	return bank_balance;
}

//Prompts the player for a wager on a
//particular roll.The wager is returned.
double get_wager_amount(void)
{
	double wager = 0.0;
	printf("Almost ready to start! How much are you wagering? $");
	scanf("%lf", &wager);
	return wager;
}

//If add_or_subtract is 1, then the wager
//amount is added to the bank_balance.If add_or_subtract is 0, then the wager
//amount is subtracted from the bank_balance.Otherwise, the bank_balance
//remains the same.The bank_balance result is returned.
double adjust_bank_balance(double bank_balance, double wager_amount, int add_or_subtract)
{
	switch (add_or_subtract)
	{
	case ADD_WAGER_TO_BANK_BALANCE: return bank_balance + wager_amount;
	case SUBTRACT_WAGER_FROM_BANK_BALANCE: return bank_balance - wager_amount;
	}
}