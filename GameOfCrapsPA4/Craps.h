/*
Programmer: Lavrenty "Larry" Orlov
Class: CptS 121; Lab Section 10L
Programming Assignment: Programming Assignment 4 - Game of Craps
Date: 9/16/2025
Description: This is a text-based version of a gambling game called Craps involving features like user input, logical decision-making,
			 checking for valid user input, and random number generation.
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DISPLAY_RULES 1
#define PLAY 2
#define EXIT 3
#define DIE_FACES 6

#define PLAYER_WINS_FIRST_TRY 1
#define PLAYER_WINS_WITH_THEIR_POINT 1
#define PLAYER_LOSES_FIRST_TRY 0
#define PLAYER_LOSES_BEFORE_THEIR_POINT 7
#define PLAYER_GETS_THEIR_POINT -1

#define ADD_WAGER_TO_BANK_BALANCE 1
#define	SUBTRACT_WAGER_FROM_BANK_BALANCE 0

#define KEEP_BANK_BALANCE 1
#define CHANGE_BANK_BALANCE 2

#define KEEP_PLAYING 1
#define RETURN_TO_MAIN_MENU 2

// Displays the main menu to the user
void print_menu(void);

// Prompts the user to enter an integer value from multiple options
int get_choice(void);

// Checks for user input and returns 1 if input is valid; returns 0 otherwise
int is_valid_input_start_of_game(int choice);

// Checks for user input and returns 1 if input is valid; returns 0 otherwise
int is_valid_input_bank_balance(double bank_balance);

// Checks for user input and returns 1 if input is valid; returns 0 otherwise
int is_valid_input_next_step(int choice);

//Checks to
//see if the wager is within the limits of the player's available balance. If the
//wager exceeds the player's allowable balance, then 0 is returned; otherwise 1
//is returned.
int check_wager_amount(double wager, double balance);

// Prints out the rules of the game of "craps"
void print_game_rules(void);

// Function responsible for logical decision-making and overall game flow
void play_the_game(int game_over);

//-Prompts the player for an initial bank
//balance from which wagering will be added or subtracted.The player entered
//bank balance(in dollars, i.e.$100.00) is returned.
double get_bank_balance(void);

//Prompts the player for a wager on a
//particular roll.The wager is returned.
double get_wager_amount(void);

//Rolls one die.This function should randomly
//generate a value between 1 and 6, inclusively.Returns the value of the die.
//(5 pts) int calculate_sum_dice(int die1_value, int die2_value) - Sums together
//the values of the two dice and returns the result.
int roll_die(void);

//Sums together
//the values of the two dice and returns the result.Note: this result may become
//the player's point in future rolls.
int calculate_sum_dice(int die1_value, int die2_value);

//Determines the result of
//the first dice roll.If the sum is 7 or 11 on the roll, the player wins and 1 is
//returned.If the sum is 2, 3, or 12 on the first throw (called "craps"), the player
//loses(i.e.the "house" wins) and 0 is returned.If the sum is 4, 5, 6, 8, 9, or 10
//on the first throw, then the sum becomes the player's "point" and -1 is
//returned.
int is_win_loss_or_point(int sum_dice);

// Determines the result of any successive roll after the first roll.If the sum of
// the roll is the point_value, then 1 is returned. If the sum of the roll is a 7, then
// 0 is returned.Otherwise, -1 is returned.
int is_point_loss_or_neither(int sum_dice, int point_value);

//If add_or_subtract is 1, then the wager
//amount is added to the bank_balance.If add_or_subtract is 0, then the wager
//amount is subtracted from the bank_balance.Otherwise, the bank_balance
//remains the same.The bank_balance result is returned.
double adjust_bank_balance(double bank_balance, double wager_amount, int add_or_subtract);

//Prints an appropriate
//message dependent on the number of rolls taken so far by the player, the
//current balance, and whether or not the player just won his roll.The
//parameter win_loss_neither indicates the result of the previous roll.
void chatter_messages(int number_rolls, int win_loss_neither, double initial_bank_balance, double current_bank_balance);