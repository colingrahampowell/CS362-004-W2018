#########
# Colin Powell
# CS362: Assignment 3
# Makefile
#########

# NOTE: gcov is cumulative, so method for creating output files starts
# by first removing dominion.gcda file to clear any previous code coverage
# results. This prevents other unit / random tests from "polluting" the current 
# random test and altering code coverage results.


CFLAGS = -Wall -fpic -coverage -lm
GCOV = gcov -bf

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

random_test_helpers.o: random_test_helpers.c random_test_helpers.h
	gcc -c random_test_helpers.c -g $(CFLAGS)

randomtestadventurer.out: random_test_helpers.o rngs.o dominion.o randomtestadventurer.c 
	gcc -o rtadv randomtestadventurer.c dominion.o rngs.o random_test_helpers.o -g ${CFLAGS}
	rm -f dominion.c.gcda
	printf "Result for random tests:\n"  > randomtestadventurer.out
	./rtadv >> randomtestadventurer.out
	printf "gcov function coverage results:\n\n"  >> randomtestadventurer.out
	$(GCOV)	dominion.c | grep "adventurerEffect" -A 4 >> randomtestadventurer.out
	printf "\n\nOverall test coverage results:\n\n" >> randomtestadventurer.out
	cat dominion.c.gcov >> randomtestadventurer.out

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player testDrawCard testBuyCard badTestDrawCard

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
