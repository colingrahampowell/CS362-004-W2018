/*
 * Colin Powell
 * CS362: Assignment 3
 * test_helpers.c: helper functions for unit tests
 * used to build unit test reports
 */


#include "test_helpers.h"

// custom assert function used for testing

/*
int myAssert(cond) {

    if(!cond) EPRINT("ASSERTION FAILED: ");

    return cond;    // return result of conditional test

}
*/

/*
 * output_test_result: outputs the result of a specific 
 * test; pass is an int representing the overall state
 * of the test - 0 if the test failed, and 1 if the 
 * test passed.
 */

void output_test_result(int pass) {
    
    if( pass ) { 
        EPRINT(">>> TEST RESULT: SUCCESS\n");
    }
    else {
        EPRINT(">>> TEST RESULT: FAILED\n");
    }

}

/*
 * output_supply_test: test supply against expected, output to stderr
 */

int output_supply_test(int expected [], struct gameState *st) {

    int i = 0;
    int good_supply = TRUE;
    int supp_size = sizeof(st->supplyCount) / sizeof(st->supplyCount[0]);

    // no unexpected should occur to any kingdom/victory card piles
    EPRINT("verifying supply state matches expectations...\n");

    for(i = 0; i < supp_size; i++ ) {
        if(st->supplyCount[i] != expected[i]) {
            EPRINT("--supply pos %i: observed, %d, expected: %d\n", 
                    i, st->supplyCount[i], expected[i]);
            good_supply = FALSE;
        }
    }

    if(good_supply){
        EPRINT("-no unexpected changes to supply - OK\n");
    }

    return good_supply;

}

/*
 * output_basic_state_tests: 
 * -test each player's hand count and deck count against expected, 
 * -output results to stderr
 */

int output_basic_state_tests(int exp_decks[], int exp_hands[], 
                             int exp_discard[], struct gameState *st) {

    int i = 0;
    int pass = TRUE;
    
    // test conditions for other players: should be no change
    EPRINT("all players - checking hand/deck counts:\n");
    for(i = 0; i < st->numPlayers; i++){

        EPRINT("-player %d:\n", i);
        // ensure that hand count matches expectations 
        if( st->handCount[i] != exp_hands[i] ) {
            pass = FALSE;
        }
        EPRINT("--hand count: %d, expected %d\n",
                st->handCount[i], exp_hands[i]);

        // ensure that deck count matches expectations 
        if( st->deckCount[i] != exp_decks[i] ) {
            pass = FALSE;
        }
        EPRINT("--deck count: %d, expected %d\n",
                st->deckCount[i], exp_decks[i]);

        if( st->discardCount[i] != exp_discard[i] ) {
            pass = FALSE;
        }
        // ensure that discard count matches expectations 
        EPRINT("--discard count: %d, expected %d\n",
                st->discardCount[i], exp_discard[i]);
    } 

    return pass;
}

/*
 * output_card_list()
 */

void output_card_list(int plyr, struct gameState *st) {

    int i = 0;
    
    // output hand and deck contents (as integers)
    EPRINT("player %d deck: ", plyr);
    for(i = 0; i < st->deckCount[plyr]; i++) {
        EPRINT("(%d)", st->deck[plyr][i]);
    }

    EPRINT("\nplayer %d hand: ", plyr);
    for(i = 0; i < st->handCount[plyr]; i++) {
        EPRINT("(%d)", st->hand[plyr][i]);
    }

    EPRINT("\n"); // output newline for convenience
}

