/*
 * Colin Powell
 * CS362: Assignment 3
 * test_helpers.h: unit test helper functions/macros
 */

// stderr printing macro
// adapted from gcc.gnu.org/onlinedocs/cpp/Variadic-Macros.html
#define TRUE 1
#define FALSE 0

#define EPRINT(format, ...)     fprintf(stderr, format, ##__VA_ARGS__)

//#define myAssert(x)     if(!(x)) { EPRINT("ASSERTION FAILED: "); }

