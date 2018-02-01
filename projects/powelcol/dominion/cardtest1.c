/*
 * Colin Powell
 * CS362: Assignment 3
 * testSmithy: Smithy unit tests
 */

#include "test_helpers.h"

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>


int smithyTest(int plyr, int draw, int test_num, struct gameState *post);

int main() {

    int i;
    int seed = 1;
    int numPlayers = 2;
    int plyr = 0;   // current player
    int draw;       // number of drawn cards expected
    int test_num;

    int k[10] = { adventurer, council_room, feast, gardens, mine, remodel, smithy,
                  village, baron, great_hall };

    // pre: pre-test game state
    // post: post-test game state 
    struct gameState pre, post;

    // init. game should give each player deck of > 3 cards
    initializeGame(numPlayers, k, seed, &pre);
    memcpy(&post, &pre, sizeof(struct gameState));
    
    EPRINT("SMITHY:\nALL TESTS: player hand size = %d\n", pre.handCount[plyr]);

    /* ---- TEST: playing smithy with deck size > 3 cards ---- */
    test_num = 1;
    draw = 3;
    
    EPRINT("\n*TEST %d: playing smithy with deck = 5 cards*\n", test_num);

    // initializeGame should produce sufficient deck sizes
    for(i = 0; i < pre.numPlayers; i++){
        assert(pre.deckCount[i] > 3);
    }
    smithyTest(plyr, draw, test_num,  &pre);

    // assert that pre and post are equivalent: this must be true
    // smithyTest cannot modify "pre" struct.
    assert(memcmp(&pre, &post, sizeof(struct gameState)) == 0);

    /* ---- TEST: playing smithy with deck size == 2 cards AND no discard pile ---- */
    test_num++;
    draw = 2;

    EPRINT("\n*TEST %d: playing smithy with deck == 2 cards, empty discard pile*\n", test_num);

    // set current player's deck to contain only two cards 
    pre.deckCount[plyr] = 2;

    memcpy(&post,&pre, sizeof(struct gameState));
    smithyTest(plyr, draw, test_num,  &pre);
    assert(memcmp(&pre, &post, sizeof(struct gameState)) == 0);

    /* ---- TEST: playing smithy with deck size == 1 card AND no discard pile ---- */
    test_num++;
    draw = 1;

    EPRINT("\n*TEST %d: playing smithy with deck == 1 card, empty discard pile*\n", test_num);

    // set current player's deck to contain only two cards 
    pre.deckCount[plyr] = 1;
    
    memcpy(&post,&pre, sizeof(struct gameState));
    smithyTest(plyr, draw, test_num,  &pre);
    assert(memcmp(&pre, &post, sizeof(struct gameState)) == 0);

    /* ---- TEST: playing smithy with deck size == 1 card AND discard pile with 5 cards ---- */
    test_num++; 
    draw = 3;

    EPRINT("\n*TEST %d: playing smithy with deck == 1 card, 5 cards in discard pile*\n", test_num);
   
    pre.deckCount[plyr] = 1;    // expect to draw from discard when deck emptied
    pre.discardCount[plyr] = 5; // set discard pile to have five cards
    // fill discard pile with copper coins
    for(i = 0; i < pre.discardCount[plyr]; i++) {
        pre.discard[plyr][i] = copper;
    } 

    smithyTest(plyr, draw, test_num, &pre);
     
    return 0; 
}

/*
 * smithyTest: smithy unit test engine. 
 * arguments: plyr, the current player. drawn, the number of cards 
 * expected to be drawn. state, a pointer to the pre-test game state.
 * checks:
 *  - current player's hand and draw count are appropriate for Smithy.
 *  - other player's hands and draw counts do not change
 *  - supply (kingdon / victory / treasure cards ) is unchanged
 * returns: TRUE (1) if tests pass, and 0 (FALSE) if tests fail.
 */

int smithyTest(int plyr, int drawn, int test_num, struct gameState *state) {

    int i = 0;          // counter
    int pass = TRUE;   // tracks test failure

    int handPos = 0;    // pos of card to play 
    int bonus = 0;      // not part of smithy; needed for cardEffect
    int disc = 1;       // number of cards expected to be discarded

    int supp_size;      // number of cards in supply

    // expected hand size after card play, including discarded smithy
    int exp_hand = state->handCount[plyr] + drawn - disc;
    
    // expected deck size after card play: if the deck would be exhausted, 
    // we'd expect discarded cards to be reshuffled into deck.
    int exp_deck = (state->deckCount[plyr] - drawn > 0) ? 
                    state->deckCount[plyr] - drawn : 
                    state->deckCount[plyr] + state->discardCount[plyr] - drawn;     
  
    struct gameState st_test;

    // copy initialized game state to st_test
    memcpy(&st_test, state, sizeof(struct gameState));

    // set size of supply
    supp_size = sizeof(st_test.supplyCount) / sizeof(st_test.supplyCount[0]);

    EPRINT("current player - checking hand/deck counts:\n");
    // handPos is a dummy value - play as if this pos. included smithy
    cardEffect(smithy, 0, 0, 0, &st_test, handPos, &bonus);

    // test that appropriate num. of cards are in plyr's hand 
    if(st_test.handCount[plyr] != (state->handCount[plyr] + drawn - disc )) {
        pass = FALSE;
    }
    EPRINT("\thand count: %d, expected: %d\n", st_test.handCount[plyr], exp_hand);
            
    // test that appropriate num. of cards have been drawn from plyr's deck
    if(st_test.deckCount[plyr] != exp_deck) {
        pass = FALSE;
    }
    EPRINT("\tdeck count: %d, expected: %d\n", st_test.deckCount[plyr], exp_deck);

    // test conditions for other players: should be no change
    EPRINT("other players - checking hand/deck counts:\n");
    for(i = 0; i < state->numPlayers; i++){
        if(i != plyr) { 
            EPRINT("\tplayer %d:\n", i);
            // ensure that hand count doesn't change
            if( st_test.handCount[i] != state->handCount[i] ) {
                pass = FALSE;
            }
            EPRINT("\thandCount: %d, expected %d\n",
                    st_test.handCount[i], state->handCount[i]);

            // ensure that deck count doesn't change
            if( st_test.deckCount[i] != state->deckCount[i] ) {
                pass = FALSE;
            }
            EPRINT("\tdeckCount: %d, expected %d\n",
                    st_test.deckCount[i], state->deckCount[i]);
        }
    } 

    // finally, no changes should occur to any kingdom/victory card piles
    EPRINT("verifying no changes to supply...reporting only failures:\n");
    for(i = 0; i < supp_size; i++ ) {
        if(st_test.supplyCount[i] != state->supplyCount[i]) {
            EPRINT("\tsupply pos %i: observed, %d, expected: %d\n", 
                    i, st_test.supplyCount[i], state->supplyCount[i]);
            pass = FALSE;
        }
    }

    // number of cards expected to be drawn or discarded
    if( pass ) { 
        EPRINT(">>> TEST %d: SUCCESS\n", test_num);
    }
    else {
        EPRINT(">>> TEST %d: FAILED\n", test_num);
    }

    return pass;    
}

