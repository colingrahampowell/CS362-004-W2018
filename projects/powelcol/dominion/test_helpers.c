/*
 * Colin Powell
 * CS362: Assignment 3
 * test_helpers.c: helper functions for unit tests
 * used to build unit test reports
 */


#include "test_helpers.h"


/*
 * output_test_result: outputs the result of a specific 
 * test; pass is an int representing the overall state
 * of the test - 0 if the test failed, and 1 if the 
 * test passed.
 */

void output_test_result(int pass) {
    
    if( pass ) { 
        printf(">>> TEST RESULT: SUCCESS\n");
    }
    else {
        printf(">>> TEST RESULT: FAILED\n");
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
    printf("verifying supply state matches expectations...\n");

    for(i = 0; i < supp_size; i++ ) {
        if(st->supplyCount[i] != expected[i]) {
            printf("--supply pos %i: observed, %d, expected: %d\n", 
                    i, st->supplyCount[i], expected[i]);
            good_supply = FALSE;
        }
    }

    if(good_supply){
        printf("--no unexpected changes to supply - OK\n");
    }

    return good_supply;

}

/*
 * output_basic_state_tests: 
 * -test each player's hand count and deck count against expected, 
 * -output results to stderr
 */

int output_global_state_tests(int exp_decks[], int exp_hands[], 
                              int exp_discard[], struct gameState *st) {

    int i = 0;
    int pass = TRUE;
    
    // test conditions for other players: should be no change
    printf("all players - checking hand/deck counts:\n");
    for(i = 0; i < st->numPlayers; i++){

        printf("-player %d:\n", i);
        // ensure that hand count matches expectations 
        if( st->handCount[i] != exp_hands[i] ) {
            pass = FALSE;
        }
        printf("--hand count: %d, expected %d\n",
                st->handCount[i], exp_hands[i]);

        // ensure that deck count matches expectations 
        if( st->deckCount[i] != exp_decks[i] ) {
            pass = FALSE;
        }
        printf("--deck count: %d, expected %d\n",
                st->deckCount[i], exp_decks[i]);

        if( st->discardCount[i] != exp_discard[i] ) {
            pass = FALSE;
        }
        // ensure that discard count matches expectations 
        printf("--discard count: %d, expected %d\n",
                st->discardCount[i], exp_discard[i]);

    } 

    return pass;
}

/*
 * output_played_card_test() 
 */

//int output_played_card_test(int exp_played[], int exp_count, struct gameState *st) {
int output_played_card_test(int exp_count, struct gameState *st) {

//    int i;
    int pass = TRUE;

    printf("checking played card count:\n");
    if( exp_count != st->playedCardCount ) {
        pass = FALSE;
        printf("--mismatch: played cards: %d, expected %d\n", st->playedCardCount, exp_count);
    }
    else  {
        printf("--played count matches - OK\n");
    }
/*
    printf("checking played cards:\n");
    for(i = 0; i < st->playedCardCount; i++) {
        if( st->playedCards[i] != exp_played[i] ) {
            printf("-ERROR: position %d: played card id: %d, expected %d\n", 
                    i, st->playedCards[i], exp_played[i]);
            pass = FALSE;
        }
    }

    if(pass) {
        printf("--no unexpected changes to played cards - OK\n");
    }
*/
    return pass;
}

/*
 * output_card_list()
 */

void output_card_list(int plyr, struct gameState *st) {

    int i = 0;

    printf("player %d\n", plyr);
    
    // output hand, deck, discard contents (as integers)

    printf("--hand: ");
    for(i = 0; i < st->handCount[plyr]; i++) {
        printf("(%d)", st->hand[plyr][i]);
    }

    printf("\n--deck: ");
    for(i = 0; i < st->deckCount[plyr]; i++) {
        printf("(%d)", st->deck[plyr][i]);
    }
    printf("\n--discard: ");
    for(i = 0; i < st->discardCount[plyr]; i++) {
        printf("(%d)", st->discard[plyr][i]);
    }

    printf("\n"); // output newline for convenience
}


/*
 * output_supply: outputs cards / counts for the given game state
 */

void output_supply(int k[], int num_k, struct gameState *st) {

    int i = 0;

    // print treasure cards
    printf("cards in game:\t");
    for(i = 0; i < adventurer; i++) {
        printf("(%2d)", i);
    }

    // print kingdom cards in game
    for(i = 0; i < num_k; i++) {
        printf("(%2d)", k[i]);
    }
    
    // print treasure card amounts
    printf("\ncard amounts:\t");
    for(i = 0; i < adventurer; i++) {
        printf("(%2d)", st->supplyCount[i]);
    }

    // print kingdom card amounts
    for(i = 0; i < num_k; i++) {
        printf("(%2d)", st->supplyCount[ k[i] ]);
    }
    
    printf("\n");
    
}


