/*
 * Colin Powell
 * CS362: Assignment 3
 * test_helpers.h: unit test helper functions/macros
 */

#include <stdio.h>
#include "dominion.h"

#define TRUE 1
#define FALSE 0

// stderr printing macro
// adapted from gcc.gnu.org/onlinedocs/cpp/Variadic-Macros.htmlVV
#define EPRINT(format, ...)     fprintf(stderr, format, ##__VA_ARGS__)


void output_test_result(int pass);
int output_basic_state_tests(int exp_decks[], int exp_hands[], 
                             int exp_discard[], struct gameState *st);
int output_supply_test(int expected [], struct gameState *st);
void output_card_list(int plyr, struct gameState *st);

