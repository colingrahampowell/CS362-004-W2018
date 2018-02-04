/*
 * Colin Powell
 * CS362: Assignment 3
 * test_helpers.h: unit test helper functions/macros.
 * these are universally applicable helper functions used for unit testing 
 * dominion.c code.
 */

#include <stdio.h>
#include "dominion.h"

#define TRUE 1
#define FALSE 0

void output_test_result(int pass);

int output_global_state_tests(int exp_decks[], int exp_hands[], 
                             int exp_discard[], struct gameState *st);
int output_played_card_test(int played_count, struct gameState *st);
int output_supply_test(int expected [], struct gameState *st);
void output_card_list(int plyr, struct gameState *st);
void output_supply(int k[], int num_k, struct gameState *st);

